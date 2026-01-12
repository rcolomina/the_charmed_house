# Architecture Analysis: The Charmed House Game

## Executive Summary

This document provides a comprehensive analysis of the architecture of "The Charmed House" - a text-based adventure game written in C++. The analysis identifies architectural strengths, code smells, and proposes specific improvements focused on data loading architecture.

## Overall Architecture Overview

The application follows a **text-based adventure game architecture** with the following key components:

### Core Components

1. **Domain Objects**: `Entidad` (base), `Escenario` (scenes), `Objeto` (items), `Jugador` (player), `Inventario` (inventory)
2. **Data Loading Layer**: Strategy pattern with `IGameDataLoader` interface, `JSONGameDataLoader` implementation
3. **Factory Pattern**: `FactoryGame` creates game objects from data
4. **Command Pattern**: `Invocador` and `ICommand` implementations for game actions
5. **Event System**: `IEvent` interface with `EventsQueue` for game logic
6. **Game Loop**: `Manager` coordinates everything, recently refactored with `GameLoop` class

### Architectural Patterns Used

- **Strategy Pattern**: Data loading abstraction
- **Factory Pattern**: Object creation
- **Command Pattern**: User action handling
- **Observer Pattern**: Event system
- **Layered Architecture**: Data → Domain → Presentation separation

## Architecture Strengths

✅ **Clean Data Abstraction**: Strategy pattern allows different data formats
✅ **Modular Object Creation**: Factory pattern centralizes instantiation
✅ **Extensible Commands**: Command pattern makes adding new actions easy
✅ **Decoupled Game Logic**: Event system separates concerns
✅ **Recent Refactoring**: Manager class split into focused components

## Code Smells and Issues

### 1. Data Loading Architecture Issues

#### Hardcoded Scene/Item IDs
**Location**: `FactoryGame::buildGameById()`

**Problem**:
```cpp
// Hardcoded scene creation
pScene esc1 = this->buildScenarioById("game.scenes.scene.sce001");
pScene esc2 = this->buildScenarioById("game.scenes.scene.sce002");
// ... continues for 6 scenes
```

**Impact**: Changes require code modifications, not data changes.

#### Inconsistent ID Resolution
**Location**: `FactoryGame::buildItemById()`, `FactoryGame::buildScenarioById()`

**Problem**:
```cpp
// Try full ID first, then extract short ID
auto it = gameWorldData.items.find(itemId);
if (it == gameWorldData.items.end()) {
    size_t lastDot = itemId.find_last_of('.');
    if (lastDot != std::string::npos) {
        std::string shortId = itemId.substr(lastDot + 1);
        it = gameWorldData.items.find(shortId);
    }
}
```

**Impact**: Complex lookup logic, potential for bugs, inconsistent ID handling.

#### Manual Scene Connections
**Location**: `FactoryGame::buildGameById()`

**Problem**:
```cpp
// Hardcoded connections instead of using JSON data
connect(esc1, west, esc2, east);
connect(esc1, east, esc3, west);
// JSON has "connections" array but it's ignored
```

**Impact**: Scene topology changes require code changes, not data updates.

### 2. Domain Model Issues

#### Primitive Obsession
**Location**: Property handling throughout the system

**Problem**:
```cpp
// Properties stored as string pairs
std::vector<std::pair<std::string,std::string>> props;
// Manual parsing required
if (propJson["value"].is_boolean()) {
    prop.value = propJson["value"].get<bool>() ? "true" : "false";
}
```

**Impact**: Type safety issues, parsing errors, complex validation.

#### Weak Object Relationships
**Location**: Scene-item relationships

**Problem**:
```cpp
struct SceneData {
    std::vector<std::string> itemIds;  // Just strings, not objects
    // No direct references to actual Item objects
};
```

**Impact**: Runtime lookups, no compile-time relationship validation.

### 3. Architecture Smells

#### God Object: FactoryGame
**Location**: `src/patterns/factory/factory.cpp`

**Problems**:
- Handles both XML and JSON loading logic
- Contains hardcoded game world construction
- Mixes data loading with game logic
- Over 200 lines in single method

**Impact**: Difficult to test, maintain, and extend.

#### Incomplete Strategy Implementation
**Location**: Data loading strategy

**Problem**:
- Only JSON loader implemented
- XML loader referenced but missing
- Factory has dual constructors for different formats

**Impact**: Inconsistent data loading approaches.

## Data Loading Architecture Improvements

### 1. Implement Data-Driven Scene Connections

**Current State**:
```json
{
  "connections": [
    {
      "sceneIdOrigin": "sce001",
      "cardinalOrigin": "north",
      "sceneIdDestination": "sce002",
      "cardinalDestination": "south"
    }
  ]
}
```

**But Code Does**:
```cpp
// Ignores JSON connections, uses hardcoded ones
connect(esc1, west, esc2, east);
```

**Proposed Solution**:
```cpp
// In FactoryGame::buildGameById()
for (const auto& conn : gameWorldData.connections) {
    auto sceneA = sceneRepository.getScene(conn.sceneIdOrigin);
    auto sceneB = sceneRepository.getScene(conn.sceneIdDestination);
    connect(sceneA, stringToCardinal(conn.cardinalOrigin),
            sceneB, stringToCardinal(conn.cardinalDestination));
}
```

### 2. Create Strongly-Typed Property System

**Current Implementation**:
```cpp
struct PropertyData {
    std::string name;
    std::string type;  // "boolean", "integer", "string"
    std::string value; // Everything as string
};
```

**Improved Implementation**:
```cpp
enum class PropertyType { Boolean, Integer, String, Float };

struct Property {
    std::string name;
    PropertyType type;
    std::variant<bool, int, float, std::string> value;

    // Template getter with type safety
    template<typename T>
    T getValue() const {
        return std::get<T>(value);
    }
};
```

### 3. Implement Repository Pattern

**Current**: Direct object creation and storage
```cpp
pScene FactoryGame::buildScenarioById(std::string scenId) {
    // Creates and returns object directly
}
```

**Improved**: Centralized object management
```cpp
class GameObjectRepository {
public:
    std::shared_ptr<Escenario> getScene(const std::string& id) {
        auto it = scenes_.find(id);
        if (it == scenes_.end()) {
            auto scene = loadSceneFromData(id);
            scenes_[id] = scene;
            return scene;
        }
        return it->second;
    }

private:
    std::map<std::string, std::shared_ptr<Escenario>> scenes_;
    std::map<std::string, std::shared_ptr<Objeto>> items_;
};
```

### 4. Add Data Validation Layer

```cpp
class GameDataValidator {
public:
    struct ValidationResult {
        bool isValid;
        std::vector<std::string> errors;
    };

    ValidationResult validate(const GameData::GameWorldData& data) {
        ValidationResult result{true, {}};

        // Check scene references exist
        for (const auto& scene : data.scenes) {
            for (const auto& itemId : scene.second.itemIds) {
                if (data.items.find(itemId) == data.items.end()) {
                    result.errors.push_back("Scene " + scene.first +
                                          " references non-existent item " + itemId);
                    result.isValid = false;
                }
            }
        }

        // Check connection validity
        for (const auto& conn : data.connections) {
            if (data.scenes.find(conn.sceneIdOrigin) == data.scenes.end()) {
                result.errors.push_back("Connection references invalid origin scene: " +
                                      conn.sceneIdOrigin);
                result.isValid = false;
            }
            // Additional validation...
        }

        return result;
    }
};
```

### 5. Implement Builder Pattern for Complex Objects

**Current**: Complex constructors
```cpp
Objeto::Objeto(const Entidad &ent,
               vector<string> names,
               vector<string> descriptions,
               vector<pair<string,string> > nameValues,
               string pathFileText,
               vector<string> oidChildren,
               string typeObject);
```

**Improved**: Fluent builder interface
```cpp
class ObjetoBuilder {
public:
    ObjetoBuilder& withEntity(const Entidad& ent) {
        entity_ = ent;
        return *this;
    }

    ObjetoBuilder& withNames(const std::vector<std::string>& names) {
        names_ = names;
        return *this;
    }

    ObjetoBuilder& withProperties(const std::vector<Property>& props) {
        properties_ = props;
        return *this;
    }

    std::unique_ptr<Objeto> build() {
        return std::make_unique<Objeto>(entity_, names_,
                                      descriptions_, properties_,
                                      pathFileText_);
    }

private:
    Entidad entity_;
    std::vector<std::string> names_;
    std::vector<std::string> descriptions_;
    std::vector<Property> properties_;
    std::string pathFileText_;
};
```

### 6. Add Configuration Management

**Current**: Hardcoded paths and settings
```cpp
std::string gameDataFile = "gameData_" + language + ".json";
```

**Improved**: External configuration
```json
{
  "game": {
    "title": "The Charmed House",
    "version": "1.0"
  },
  "data": {
    "files": {
      "en": "gameData_en.json",
      "es": "gameData_es.json"
    },
    "imagePath": "./txt"
  },
  "defaults": {
    "language": "es",
    "maxMisbehaviors": 3
  }
}
```

### 7. Implement Data Migration System

```cpp
class DataMigrator {
public:
    GameData::GameWorldData migrate(const GameData::GameWorldData& data,
                                   int targetVersion) {
        GameData::GameWorldData migrated = data;

        if (data.version == "1.0" && targetVersion == 2) {
            // Add new required fields
            for (auto& [id, scene] : migrated.scenes) {
                if (scene.observation.empty()) {
                    scene.observation = "No observations.";
                }
            }
        }

        migrated.version = std::to_string(targetVersion);
        return migrated;
    }
};
```

## Implementation Roadmap

### Phase 1: Data Layer Improvements (High Priority)
1. Replace hardcoded scene connections with data-driven approach
2. Implement strongly-typed property system
3. Add Repository pattern for object management

### Phase 2: Domain Model Enhancement (Medium Priority)
1. Create proper domain relationships (scenes contain items)
2. Add domain-level validation
3. Implement Builder pattern for complex object construction

### Phase 3: Configuration & Extensibility (Low Priority)
1. Add external configuration management
2. Implement data migration system
3. Create plugin architecture for additional data loaders

## Benefits of Proposed Changes

- **Maintainability**: Data changes won't require code changes
- **Testability**: Domain logic separated from data concerns
- **Extensibility**: Easy to add new data formats, object types
- **Reliability**: Type safety and validation reduce runtime errors
- **Performance**: Repository pattern enables object reuse and caching

## Conclusion

The current architecture has solid foundations with good use of design patterns, but suffers from data loading being tightly coupled with domain logic. The proposed improvements will create a more maintainable, testable, and extensible system while preserving the existing functionality.

The refactoring should be done incrementally, starting with the high-priority data layer improvements, to minimize risk and allow for thorough testing at each step.
