#include <iostream>
#include "../../src/data/JSONGameDataLoader.h"
#include "../../src/patterns/factory/factory.h"

int main() {
    std::cout << "=== JSON Game Data Loader Test ===" << std::endl << std::endl;

    try {
        // Create a JSON data loader
        JSONGameDataLoader jsonLoader;

        // Test loading the game world (Spanish)
        std::cout << "Loading gameData_es.json..." << std::endl;
        GameData::GameWorldData gameWorld = jsonLoader.loadGameWorld("gameData_es.json");

        std::cout << "Successfully loaded game data!" << std::endl;
        std::cout << "Version: " << gameWorld.version << std::endl;
        std::cout << "Scenes loaded: " << gameWorld.scenes.size() << std::endl;
        std::cout << "Items loaded: " << gameWorld.items.size() << std::endl;
        std::cout << "Connections loaded: " << gameWorld.connections.size() << std::endl << std::endl;

        // Print some scene information
        std::cout << "--- Scenes ---" << std::endl;
        for (auto it = gameWorld.scenes.begin(); it != gameWorld.scenes.end(); ++it) {
            const std::string& sceneKey = it->first;
            const GameData::SceneData& scene = it->second;
            std::cout << "  " << sceneKey << ": " << scene.title << std::endl;
            std::cout << "    Items in scene: " << scene.itemIds.size() << std::endl;
            std::cout << "    Exits: " << scene.exits.size() << std::endl;
        }
        std::cout << std::endl;

        // Print some item information
        std::cout << "--- Items ---" << std::endl;
        for (auto it = gameWorld.items.begin(); it != gameWorld.items.end(); ++it) {
            const std::string& itemKey = it->first;
            const GameData::ItemData& item = it->second;
            std::cout << "  " << itemKey << ": ";
            if (!item.names.empty()) {
                std::cout << item.names[0];
            }
            std::cout << " (properties: " << item.properties.size() << ")" << std::endl;
        }
        std::cout << std::endl;

        // Test using FactoryGame with JSON loader
        std::cout << "--- Testing FactoryGame with JSON ---" << std::endl;
        FactoryGame factory(&jsonLoader, "gameData_es.json");

        std::cout << "Testing buildItemById..." << std::endl;
        pItem testItem = factory.buildItemById("item01");
        if (testItem) {
            std::cout << "  Successfully built item01: " << testItem->Name() << std::endl;
        }

        std::cout << "Testing buildScenarioById..." << std::endl;
        pScene testScene = factory.buildScenarioById("sce001");
        if (testScene) {
            std::cout << "  Successfully built sce001: " << testScene->Name() << std::endl;
        }

        std::cout << std::endl << "=== All tests passed! ===" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
