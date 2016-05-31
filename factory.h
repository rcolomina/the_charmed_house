#ifndef _FACTORY_
#define _FACTORY_

#include <vector>

#include <tinyxml.h>
#include "game.h"

typedef TiXmlNode* pNode;
typedef TiXmlElement* pElem;
typedef TiXmlHandle* pHand;

class FactoryGame{
	public:
	  FactoryGame(string xmlGameSpecifications);

	  Game* buildGameById(string gameId);
	  Escenario* buildScenarioById(string scenarioId);
	  Objeto* buildItemById(string itemId);

	private:
	  
	  vector<string> getIdListFromElement(pNode node,string nameAttribute);
	  vector<string> getTextListFromElement(pNode node);

	  pElem getGameElement(string name);
	  pElem searchForElementId(pElem parent,string id);
	  
	  string xmlGameSpecifications;
	  TiXmlDocument xmlDoc;
};


#endif
