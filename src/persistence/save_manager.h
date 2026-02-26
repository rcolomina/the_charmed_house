#ifndef _SAVE_MANAGER_H_
#define _SAVE_MANAGER_H_

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <json.hpp>

using json = nlohmann::json;

// Forward declarations
class Escenario;
class Inventario;
class Objeto;

namespace SaveSystem {

/**
 * Structure to hold save game metadata
 */
struct SaveSlotInfo {
    int slotNumber;
    std::string saveName;
    std::string timestamp;
    std::string currentSceneId;
    int playTime;  // in seconds
    bool isEmpty;
    
    SaveSlotInfo() : slotNumber(0), playTime(0), isEmpty(true) {}
};

/**
 * Structure to hold complete game state for serialization
 */
struct GameState {
    std::string currentSceneId;
    std::vector<std::string> inventoryItemIds;
    std::map<std::string, std::map<std::string, bool>> itemProperties;  // itemId -> propertyName -> value
    std::map<std::string, std::map<std::string, bool>> sceneExitStates; // sceneId -> exitDirection -> open
    std::map<std::string, std::vector<std::string>> sceneItems;         // sceneId -> list of itemIds
    int playTime;
    std::vector<std::string> unlockedAchievements;
    std::map<std::string, int> puzzleProgress;  // puzzleId -> progress state
};

/**
 * SaveManager handles game state persistence
 * Supports multiple save slots and auto-save functionality
 */
class SaveManager {
public:
    static const int MAX_SAVE_SLOTS = 5;
    static const std::string SAVE_DIRECTORY;
    static const std::string AUTOSAVE_FILENAME;
    
    SaveManager();
    ~SaveManager() = default;
    
    // Save operations
    bool saveGame(int slotNumber, const std::string& saveName,
                  Escenario* currentScene,
                  Inventario& inventory,
                  const std::map<std::string, Escenario*>& world,
                  int playTime);
    
    bool autoSave(Escenario* currentScene,
                  Inventario& inventory,
                  const std::map<std::string, Escenario*>& world,
                  int playTime);
    
    // Load operations
    bool loadGame(int slotNumber, GameState& outState);
    bool loadAutoSave(GameState& outState);
    
    // Slot management
    std::vector<SaveSlotInfo> getSaveSlots();
    SaveSlotInfo getSlotInfo(int slotNumber);
    bool deleteSlot(int slotNumber);
    bool isSlotEmpty(int slotNumber);
    
    // Utility
    std::string getLastError() const { return lastError_; }
    bool ensureSaveDirectoryExists();
    
private:
    std::string lastError_;
    
    // Serialization helpers
    json serializeGameState(Escenario* currentScene,
                           Inventario& inventory,
                           const std::map<std::string, Escenario*>& world,
                           int playTime);
    
    GameState deserializeGameState(const json& data);
    
    json serializeInventory(Inventario& inventory);
    json serializeSceneState(Escenario* scene);
    json serializeItemProperties(Objeto* item);
    
    std::string getSlotFilePath(int slotNumber);
    std::string getAutoSaveFilePath();
    std::string getCurrentTimestamp();
    
    bool writeJsonToFile(const std::string& filePath, const json& data);
    bool readJsonFromFile(const std::string& filePath, json& outData);
};

} // namespace SaveSystem

#endif
