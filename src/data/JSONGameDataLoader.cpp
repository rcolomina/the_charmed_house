#include "JSONGameDataLoader.h"
#include <iostream>

json JSONGameDataLoader::loadJsonFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }

    json j;
    try {
        file >> j;
    } catch (const json::parse_error& e) {
        throw std::runtime_error("JSON parse error in file " + filePath + ": " + e.what());
    }

    return j;
}

GameData::GameWorldData JSONGameDataLoader::loadGameWorld(const std::string& filePath) {
    json j = loadJsonFile(filePath);

    GameData::GameWorldData gameWorld;

    // Load version
    if (j.contains("version")) {
        gameWorld.version = j["version"].get<std::string>();
    }

    // Load all scenes
    if (j.contains("scenes") && j["scenes"].is_object()) {
        for (auto& [sceneKey, sceneJson] : j["scenes"].items()) {
            GameData::SceneData scene = parseScene(sceneJson, sceneKey);
            gameWorld.scenes[sceneKey] = scene;
        }
    }

    // Load all items
    if (j.contains("items") && j["items"].is_object()) {
        for (auto& [itemKey, itemJson] : j["items"].items()) {
            GameData::ItemData item = parseItem(itemJson, itemKey);
            gameWorld.items[itemKey] = item;
        }
    }

    // Load connections
    if (j.contains("connections") && j["connections"].is_array()) {
        for (auto& connJson : j["connections"]) {
            GameData::ConnectionData connection = parseConnection(connJson);
            gameWorld.connections.push_back(connection);
        }
    }

    return gameWorld;
}

GameData::SceneData JSONGameDataLoader::loadScene(const std::string& filePath, const std::string& sceneId) {
    json j = loadJsonFile(filePath);

    if (!j.contains("scenes") || !j["scenes"].contains(sceneId)) {
        throw std::runtime_error("Scene not found: " + sceneId);
    }

    return parseScene(j["scenes"][sceneId], sceneId);
}

GameData::ItemData JSONGameDataLoader::loadItem(const std::string& filePath, const std::string& itemId) {
    json j = loadJsonFile(filePath);

    if (!j.contains("items") || !j["items"].contains(itemId)) {
        throw std::runtime_error("Item not found: " + itemId);
    }

    return parseItem(j["items"][itemId], itemId);
}

GameData::SceneData JSONGameDataLoader::parseScene(const json& sceneJson, const std::string& sceneKey) {
    GameData::SceneData scene;

    // Set the key as the ID if no explicit ID field
    if (sceneJson.contains("id")) {
        scene.id = sceneJson["id"].get<std::string>();
    } else {
        scene.id = sceneKey;
    }

    // Parse title
    if (sceneJson.contains("title")) {
        scene.title = sceneJson["title"].get<std::string>();
    }

    // Parse descriptions array
    if (sceneJson.contains("descriptions") && sceneJson["descriptions"].is_array()) {
        for (auto& desc : sceneJson["descriptions"]) {
            scene.description += desc.get<std::string>();
            if (&desc != &sceneJson["descriptions"].back()) {
                scene.description += "\n";  // Add newline between descriptions
            }
        }
    }

    // Parse observation
    if (sceneJson.contains("observation")) {
        scene.observation = sceneJson["observation"].get<std::string>();
    }

    // Parse image path
    if (sceneJson.contains("imagePath")) {
        scene.imagePath = sceneJson["imagePath"].get<std::string>();
    }

    // Parse items in this scene
    if (sceneJson.contains("items") && sceneJson["items"].is_array()) {
        for (auto& itemId : sceneJson["items"]) {
            scene.itemIds.push_back(itemId.get<std::string>());
        }
    }

    // Parse exits
    if (sceneJson.contains("exits") && sceneJson["exits"].is_object()) {
        for (auto& [direction, destSceneId] : sceneJson["exits"].items()) {
            scene.exits[direction] = destSceneId.get<std::string>();
        }
    }

    return scene;
}

GameData::ItemData JSONGameDataLoader::parseItem(const json& itemJson, const std::string& itemKey) {
    GameData::ItemData item;

    // Set the key as the ID if no explicit ID field
    if (itemJson.contains("id")) {
        item.id = itemJson["id"].get<std::string>();
    } else {
        item.id = itemKey;
    }

    // Parse names array
    if (itemJson.contains("names") && itemJson["names"].is_array()) {
        for (auto& name : itemJson["names"]) {
            item.names.push_back(name.get<std::string>());
        }
    }

    // Parse descriptions array
    if (itemJson.contains("descriptions") && itemJson["descriptions"].is_array()) {
        for (auto& desc : itemJson["descriptions"]) {
            item.descriptions.push_back(desc.get<std::string>());
        }
    }

    // Parse properties array
    if (itemJson.contains("properties") && itemJson["properties"].is_array()) {
        for (auto& propJson : itemJson["properties"]) {
            GameData::PropertyData prop = parseProperty(propJson);
            item.properties.push_back(prop);
        }
    }

    // Parse pathFileText
    if (itemJson.contains("pathFileText")) {
        item.pathFileText = itemJson["pathFileText"].get<std::string>();
    }

    return item;
}

GameData::PropertyData JSONGameDataLoader::parseProperty(const json& propJson) {
    GameData::PropertyData prop;

    if (propJson.contains("name")) {
        prop.name = propJson["name"].get<std::string>();
    }

    if (propJson.contains("type")) {
        prop.type = propJson["type"].get<std::string>();
    }

    if (propJson.contains("value")) {
        // Store value as string regardless of type
        if (propJson["value"].is_string()) {
            prop.value = propJson["value"].get<std::string>();
        } else if (propJson["value"].is_boolean()) {
            prop.value = propJson["value"].get<bool>() ? "true" : "false";
        } else if (propJson["value"].is_number_integer()) {
            prop.value = std::to_string(propJson["value"].get<int>());
        } else {
            prop.value = propJson["value"].dump();  // Fallback to JSON string representation
        }
    }

    return prop;
}

GameData::ConnectionData JSONGameDataLoader::parseConnection(const json& connJson) {
    GameData::ConnectionData conn;

    if (connJson.contains("sceneIdOrigin")) {
        conn.sceneIdOrigin = connJson["sceneIdOrigin"].get<std::string>();
    }

    if (connJson.contains("cardinalOrigin")) {
        conn.cardinalOrigin = connJson["cardinalOrigin"].get<std::string>();
    }

    if (connJson.contains("sceneIdDestination")) {
        conn.sceneIdDestination = connJson["sceneIdDestination"].get<std::string>();
    }

    if (connJson.contains("cardinalDestination")) {
        conn.cardinalDestination = connJson["cardinalDestination"].get<std::string>();
    }

    return conn;
}
