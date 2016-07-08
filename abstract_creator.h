#ifndef _abstract_creator_
#define _abstract_creator_

#include <vector>
#include <string>
#include <tinyxml.h>

#include "entidad.h"

typedef TiXmlNode* pNode;
typedef TiXmlElement* pElem;
typedef TiXmlHandle* pHand;

enum InfoClass{Name,Text};

class AbstractGameCreator{
	public:
	  virtual Entidad* createById(const std::string itemId) = 0;
	protected:
	  vector<string> getInfoList(const pNode &parent,const InfoClass &info);

	  pElem searchForGame(const string &gameName);
	  pElem searchForId(const pElem &parent,const std::string &id);

	  TiXmlDocument xmlDoc;
};

#endif
