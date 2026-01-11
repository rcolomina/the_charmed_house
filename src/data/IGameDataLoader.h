#ifndef _IGAME_DATA_LOADER_H_
#define _IGAME_DATA_LOADER_H_

#include <string>
#include "GameData.h"

/**
 * Interface for loading game data from different sources (JSON, XML, Database, etc.)
 * This follows the Strategy Pattern to decouple data format from game logic.
 */
class IGameDataLoader {
public:
    virtual ~IGameDataLoader() = default;

    /**
     * Load the complete game world data including scenes, items, and connections
     * @param filePath Path to the game data file
     * @return GameWorldData structure containing all game data
     * @throws std::runtime_error if loading fails
     */
    virtual GameData::GameWorldData loadGameWorld(const std::string& filePath) = 0;

    /**
     * Load a specific scene by its ID
     * @param filePath Path to the game data file
     * @param sceneId Scene identifier
     * @return SceneData for the requested scene
     * @throws std::runtime_error if scene not found
     */
    virtual GameData::SceneData loadScene(const std::string& filePath, const std::string& sceneId) = 0;

    /**
     * Load a specific item by its ID
     * @param filePath Path to the game data file
     * @param itemId Item identifier
     * @return ItemData for the requested item
     * @throws std::runtime_error if item not found
     */
    virtual GameData::ItemData loadItem(const std::string& filePath, const std::string& itemId) = 0;
};

#endif
