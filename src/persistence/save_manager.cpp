#include "save_manager.h"
#include "../core/escenario.h"
#include "../core/inventario.h"
#include "../core/objeto.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <ctime>

namespace SaveSystem {

const std::string SaveManager::SAVE_DIRECTORY = "./saves/";
const std::string SaveManager::AUTOSAVE_FILENAME = "autosave.json";

SaveManager::SaveManager() : lastError_("") {
    ensureSaveDirectoryExists();
}

bool SaveManager::ensureSaveDirectoryExists() {
    struct stat st;
    if (stat(SAVE_DIRECTORY.c_str(), &st) != 0) {
        // Directory doesn't exist, create it
        #ifdef _WIN32
        int result = mkdir(SAVE_DIRECTORY.c_str());
        #else
        int result = mkdir(SAVE_DIRECTORY.c_str(), 0755);
        #endif
        if (result != 0) {
            lastError_ = "Failed to create save directory";
            return false;
        }
    }
    return true;
}

std::string SaveManager::getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);
    std::stringstream ss;
    ss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string SaveManager::getSlotFilePath(int slotNumber) {
    return SAVE_DIRECTORY + "slot_" + std::to_string(slotNumber) + ".json";
}

std::string SaveManager::getAutoSaveFilePath() {
    return SAVE_DIRECTORY + AUTOSAVE_FILENAME;
}

bool SaveManager::writeJsonToFile(const std::string& filePath, const json& data) {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        lastError_ = "Could not open file for writing: " + filePath;
        return false;
    }
    file << std::setw(2) << data << std::endl;
    file.close();
    return true;
}

bool SaveManager::readJsonFromFile(const std::string& filePath, json& outData) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        lastError_ = "Could not open file for reading: " + filePath;
        return false;
    }
    try {
        file >> outData;
    } catch (const json::parse_error& e) {
        lastError_ = "JSON parse error: " + std::string(e.what());
        return false;
    }
    file.close();
    return true;
}

json SaveManager::serializeItemProperties(Objeto* item) {
    json props;
    if (item == nullptr) return props;
    
    // Serialize common boolean properties
    std::vector<std::string> boolProps = {
        "used", "fix", "visibility", "tirable", "alcanzable",
        "desatascador", "reacher", "stucked", "plug", "key", "socket", "lock"
    };
    
    for (const auto& propName : boolProps) {
        props[propName] = item->get_value<bool>(propName.c_str());
    }
    
    // Serialize integer properties
    props["code"] = item->get_value<int>("code");
    
    return props;
}

json SaveManager::serializeInventory(Inventario& inventory) {
    json invJson = json::array();
    // Note: We need to iterate through inventory items
    // Since Inventario doesn't expose iteration, we'll save item names
    // This is a simplified approach - in production, you'd want to expose iteration
    return invJson;
}

json SaveManager::serializeSceneState(Escenario* scene) {
    json sceneJson;
    if (scene == nullptr) return sceneJson;
    
    sceneJson["id"] = scene->id();
    
    // Serialize exit states
    json exits;
    std::map<std::string, pScene> salidas = scene->get_salidas();
    for (const auto& pair : salidas) {
        exits[pair.first] = scene->get_estado_salida(pair.first);
    }
    sceneJson["exitStates"] = exits;
    
    // Serialize items in scene
    json items = json::array();
    std::map<std::string, pItem> objetos = scene->get_objetos();
    for (const auto& pair : objetos) {
        if (pair.second != nullptr) {
            json itemJson;
            itemJson["id"] = pair.second->id();
            itemJson["name"] = pair.second->Name();
            itemJson["properties"] = serializeItemProperties(pair.second);
            items.push_back(itemJson);
        }
    }
    sceneJson["items"] = items;
    
    return sceneJson;
}

json SaveManager::serializeGameState(Escenario* currentScene,
                                     Inventario& inventory,
                                     const std::map<std::string, Escenario*>& world,
                                     int playTime) {
    json state;
    
    // Save metadata
    state["version"] = "1.0";
    state["timestamp"] = getCurrentTimestamp();
    state["playTime"] = playTime;
    
    // Save current scene
    state["currentSceneId"] = currentScene ? currentScene->id() : "";
    
    // Save all scene states
    json scenes;
    for (const auto& pair : world) {
        if (pair.second != nullptr) {
            scenes[pair.first] = serializeSceneState(pair.second);
        }
    }
    state["scenes"] = scenes;
    
    // Save inventory
    state["inventory"] = serializeInventory(inventory);
    
    return state;
}

GameState SaveManager::deserializeGameState(const json& data) {
    GameState state;
    
    if (data.contains("currentSceneId")) {
        state.currentSceneId = data["currentSceneId"].get<std::string>();
    }
    
    if (data.contains("playTime")) {
        state.playTime = data["playTime"].get<int>();
    }
    
    if (data.contains("inventory") && data["inventory"].is_array()) {
        for (const auto& itemId : data["inventory"]) {
            state.inventoryItemIds.push_back(itemId.get<std::string>());
        }
    }
    
    if (data.contains("scenes") && data["scenes"].is_object()) {
        for (auto& [sceneId, sceneData] : data["scenes"].items()) {
            // Load exit states
            if (sceneData.contains("exitStates")) {
                for (auto& [exitDir, isOpen] : sceneData["exitStates"].items()) {
                    state.sceneExitStates[sceneId][exitDir] = isOpen.get<bool>();
                }
            }
            
            // Load items in scene
            if (sceneData.contains("items") && sceneData["items"].is_array()) {
                for (const auto& itemData : sceneData["items"]) {
                    std::string itemId = itemData["id"].get<std::string>();
                    state.sceneItems[sceneId].push_back(itemId);
                    
                    // Load item properties
                    if (itemData.contains("properties")) {
                        for (auto& [propName, propValue] : itemData["properties"].items()) {
                            if (propValue.is_boolean()) {
                                state.itemProperties[itemId][propName] = propValue.get<bool>();
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (data.contains("achievements") && data["achievements"].is_array()) {
        for (const auto& ach : data["achievements"]) {
            state.unlockedAchievements.push_back(ach.get<std::string>());
        }
    }
    
    return state;
}

bool SaveManager::saveGame(int slotNumber, const std::string& saveName,
                           Escenario* currentScene,
                           Inventario& inventory,
                           const std::map<std::string, Escenario*>& world,
                           int playTime) {
    if (slotNumber < 1 || slotNumber > MAX_SAVE_SLOTS) {
        lastError_ = "Invalid slot number";
        return false;
    }
    
    if (!ensureSaveDirectoryExists()) {
        return false;
    }
    
    json state = serializeGameState(currentScene, inventory, world, playTime);
    state["saveName"] = saveName;
    state["slotNumber"] = slotNumber;
    
    return writeJsonToFile(getSlotFilePath(slotNumber), state);
}

bool SaveManager::autoSave(Escenario* currentScene,
                           Inventario& inventory,
                           const std::map<std::string, Escenario*>& world,
                           int playTime) {
    if (!ensureSaveDirectoryExists()) {
        return false;
    }
    
    json state = serializeGameState(currentScene, inventory, world, playTime);
    state["saveName"] = "Auto Save";
    state["isAutoSave"] = true;
    
    return writeJsonToFile(getAutoSaveFilePath(), state);
}

bool SaveManager::loadGame(int slotNumber, GameState& outState) {
    if (slotNumber < 1 || slotNumber > MAX_SAVE_SLOTS) {
        lastError_ = "Invalid slot number";
        return false;
    }
    
    json data;
    if (!readJsonFromFile(getSlotFilePath(slotNumber), data)) {
        return false;
    }
    
    outState = deserializeGameState(data);
    return true;
}

bool SaveManager::loadAutoSave(GameState& outState) {
    json data;
    if (!readJsonFromFile(getAutoSaveFilePath(), data)) {
        return false;
    }
    
    outState = deserializeGameState(data);
    return true;
}

std::vector<SaveSlotInfo> SaveManager::getSaveSlots() {
    std::vector<SaveSlotInfo> slots;
    
    for (int i = 1; i <= MAX_SAVE_SLOTS; i++) {
        slots.push_back(getSlotInfo(i));
    }
    
    return slots;
}

SaveSlotInfo SaveManager::getSlotInfo(int slotNumber) {
    SaveSlotInfo info;
    info.slotNumber = slotNumber;
    info.isEmpty = true;
    
    json data;
    if (readJsonFromFile(getSlotFilePath(slotNumber), data)) {
        info.isEmpty = false;
        
        if (data.contains("saveName")) {
            info.saveName = data["saveName"].get<std::string>();
        }
        if (data.contains("timestamp")) {
            info.timestamp = data["timestamp"].get<std::string>();
        }
        if (data.contains("currentSceneId")) {
            info.currentSceneId = data["currentSceneId"].get<std::string>();
        }
        if (data.contains("playTime")) {
            info.playTime = data["playTime"].get<int>();
        }
    }
    
    return info;
}

bool SaveManager::deleteSlot(int slotNumber) {
    if (slotNumber < 1 || slotNumber > MAX_SAVE_SLOTS) {
        lastError_ = "Invalid slot number";
        return false;
    }
    
    std::string filePath = getSlotFilePath(slotNumber);
    if (std::remove(filePath.c_str()) != 0) {
        lastError_ = "Failed to delete save file";
        return false;
    }
    
    return true;
}

bool SaveManager::isSlotEmpty(int slotNumber) {
    return getSlotInfo(slotNumber).isEmpty;
}

} // namespace SaveSystem
