#ifndef _FACTORY_
#define _FACTORY_

#include <vector>
#include <memory>
#include <tinyxml.h>

//#include "../../core/escenario.h"
//#include "../../core/objeto.h"
#include "../../core/game.h"
#include "../../data/IGameDataLoader.h"
#include "../../data/GameData.h"

typedef TiXmlNode* pNode;
typedef TiXmlElement* pElem;
typedef TiXmlHandle* pHand;

//typedef Objeto* pItem;
//typedef Objeto Item;
//typedef Escenario* pScene;


class FactoryGame{
public:
    // Legacy constructor for XML loading
    FactoryGame(std::string xmlGameSpecifications);

    // New constructor using data loader strategy
    FactoryGame(IGameDataLoader* loader, const std::string& dataFilePath);

    pScene buildGameById(std::string gameId);
    pScene buildScenarioById(std::string scenarioId);
    pItem buildItemById(std::string itemId);


private:
    // Legacy XML methods
    std::vector<std::string> getNameListFromNode(pNode node);
    std::vector<std::string> getTextListFromNode(pNode node);

    pElem getGameElement(std::string name);
    pElem searchForElementId(pElem parent,std::string id);

    // New data-driven methods
    pScene buildScenarioFromData(const GameData::SceneData& sceneData);
    pItem buildItemFromData(const GameData::ItemData& itemData);

    // Data storage
    bool useDataLoader;  // Flag to determine which system to use
    IGameDataLoader* dataLoader;
    std::string dataFilePath;
    GameData::GameWorldData gameWorldData;

    // Legacy XML data
    std::string xmlGameSpecifications;
    TiXmlDocument xmlDoc;
};


#endif
