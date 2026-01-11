#ifndef _JSON_GAME_DATA_LOADER_H_
#define _JSON_GAME_DATA_LOADER_H_

#include "IGameDataLoader.h"
#include <json.hpp>
#include <fstream>
#include <stdexcept>

using json = nlohmann::json;

/**
 * Concrete implementation of IGameDataLoader that reads from JSON files
 * Uses nlohmann/json library for parsing
 */
class JSONGameDataLoader : public IGameDataLoader {
public:
    JSONGameDataLoader() = default;
    virtual ~JSONGameDataLoader() = default;

    GameData::GameWorldData loadGameWorld(const std::string& filePath) override;
    GameData::SceneData loadScene(const std::string& filePath, const std::string& sceneId) override;
    GameData::ItemData loadItem(const std::string& filePath, const std::string& itemId) override;

private:
    // Helper method to load and parse JSON file
    json loadJsonFile(const std::string& filePath);

    // Helper methods to parse JSON objects into DTOs
    GameData::SceneData parseScene(const json& sceneJson, const std::string& sceneKey);
    GameData::ItemData parseItem(const json& itemJson, const std::string& itemKey);
    GameData::PropertyData parseProperty(const json& propJson);
    GameData::ConnectionData parseConnection(const json& connJson);
};

#endif
