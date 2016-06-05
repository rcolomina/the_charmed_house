#ifndef _FACTORY_
#define _FACTORY_

#include <vector>

#include <tinyxml.h>
#include "game.h"

typedef TiXmlNode* pNode;
typedef TiXmlElement* pElem;
typedef TiXmlHandle* pHand;

typedef Game* pGame;
typedef Objeto* pItem;
typedef Objeto Item;

typedef Escenario* pScene;

class FactoryGame{
	public:
	  FactoryGame(string xmlGameSpecifications);

	  pGame buildGameById(string gameId);
	  pScene buildScenarioById(string scenarioId);
	  pItem buildItemById(string itemId);

	private:
	  
	  vector<string> getNameListFromNode(pNode node);
	  vector<string> getTextListFromNode(pNode node);

	  pElem getGameElement(string name);
	  pElem searchForElementId(pElem parent,string id);
	  
	  string xmlGameSpecifications;
	  TiXmlDocument xmlDoc;
};


#endif
