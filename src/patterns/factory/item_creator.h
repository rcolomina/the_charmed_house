#ifndef _item_creator_
#define _item_creator_

#include <vector>
#include <tinyxml.h>

#include "abstract_creator.h"
#include "../../core/objeto.h"

class ItemGameCreator : public AbstractGameCreator{
public:
    ItemGameCreator(const string xmlItemSpecs);	  
    Entidad* createById(string itemId);	  	  
};

#endif
