#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

#include <string>
#include <vector>
#include <map>

namespace GameData {

struct PropertyData {
    std::string name;
    std::string type;  // "boolean", "integer", "string"
    std::string value;

    PropertyData() = default;
    PropertyData(const std::string& name, const std::string& type, const std::string& value)
        : name(name), type(type), value(value) {}
};

struct ItemData {
    std::string id;
    std::vector<std::string> names;
    std::vector<std::string> descriptions;
    std::vector<PropertyData> properties;
    std::string pathFileText;

    ItemData() = default;
};

struct ConnectionData {
    std::string sceneIdOrigin;
    std::string cardinalOrigin;
    std::string sceneIdDestination;
    std::string cardinalDestination;

    ConnectionData() = default;
    ConnectionData(const std::string& sceneOrigin, const std::string& cardOrigin,
                   const std::string& sceneDest, const std::string& cardDest)
        : sceneIdOrigin(sceneOrigin), cardinalOrigin(cardOrigin),
          sceneIdDestination(sceneDest), cardinalDestination(cardDest) {}
};

struct SceneData {
    std::string id;
    std::string title;
    std::string description;
    std::string observation;
    std::string imagePath;
    std::vector<std::string> itemIds;  // References to items present in this scene
    std::map<std::string, std::string> exits;  // cardinal direction -> destination scene id

    SceneData() = default;
};

struct GameWorldData {
    std::string version;
    std::map<std::string, SceneData> scenes;
    std::map<std::string, ItemData> items;
    std::vector<ConnectionData> connections;

    GameWorldData() = default;
};

} // namespace GameData

#endif
