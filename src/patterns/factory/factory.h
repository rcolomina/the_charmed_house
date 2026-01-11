#ifndef _FACTORY_
#define _FACTORY_

#include <vector>
#include <tinyxml.h>

//#include "../../core/escenario.h"
//#include "../../core/objeto.h"
#include "../../core/game.h"

typedef TiXmlNode* pNode;
typedef TiXmlElement* pElem;
typedef TiXmlHandle* pHand;

//typedef Objeto* pItem;
//typedef Objeto Item;
//typedef Escenario* pScene;


class FactoryGame{
public:
    FactoryGame(string xmlGameSpecifications);
	  
    pScene buildGameById(string gameId);
    pScene buildScenarioById(string scenarioId);
    pItem buildItemById(string itemId);

	  
private:
	  
    vector<string> getNameListFromNode(pNode node);
    vector<string> getTextListFromNode(pNode node);

    pElem getGameElement(string name);
    pElem searchForElementId(pElem parent,string id);

    // specs given by XML file
    string xmlGameSpecifications;
    TiXmlDocument xmlDoc;

    // specs given by sql table
    
    
    // specs given by a JSON file
};


#endif
