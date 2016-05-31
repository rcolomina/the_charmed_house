#include "factory.h"

FactoryGame::FactoryGame(string xmlGameSpecifications)
	  :xmlGameSpecifications(xmlGameSpecifications){

      bool loadOkay = xmlDoc.LoadFile(xmlGameSpecifications.c_str());

		if (!loadOkay)
		{
			  printf("Could not load test xml file. Error='%s'. Exiting.\n", xmlDoc.ErrorDesc());
			  exit(1);
		}

}


vector<string> FactoryGame::getIdListFromElement(pNode node,string nameAttribute){
	  vector<string> output;


	  
	  return output;
}

vector<string> FactoryGame::getTextListFromElement(pNode parent){

	  vector<string> output;
	  pNode child = 0;
	  while(child = parent->IterateChildren(child))
	  {
			 pElem temp = child->ToElement();
			 string value_text = temp->GetText();
			 output.push_back(value_text);
	  }
	  return output;	  
}


pElem FactoryGame::getGameElement(string name){
	  // Looking for the Element Items
	  pNode node=NULL;
	  node = xmlDoc.FirstChild("games");
	  assert(node);	  
	  TiXmlHandle docHandle(node);
	  pElem elem = docHandle.FirstChild("game").FirstChild(name.c_str()).ToElement();
	  return elem;
}

// Return the child element with a specific id 
pElem FactoryGame::searchForElementId(pElem parent,string id){

	  pNode child = 0;
	  while(child = parent->IterateChildren(child))
	  {
			 pElem temp = child->ToElement();
			 string value_attribute = temp->Attribute("id");
			 if( id.compare(value_attribute)==0 )
			 {
					return temp;
			 }
	  }
	  return NULL;
}




Objeto* FactoryGame::buildItemById(string itemId){
	  
	  Objeto* item=new Objeto();

	  pElem elem_Items=this->getGameElement(string("items"));	  
	  pElem elem_Item=this->searchForElementId(elem_Items,itemId);

	  // CREATING THE ITEM
	  TiXmlHandle itemHandle(elem_Item);

	  pElem elem_names=itemHandle.FirstChild("names").ToElement();
	  vector<string> names=getTextListFromElement(elem_names);
	  vector<string>::iterator it;
	  for(it=names.begin();it!=names.end();++it){
			 cout<<*it<<endl;
	  }
			 

	  pElem elem_descriptions=itemHandle.FirstChild("descriptions").ToElement();
	  vector<string> descrip=getTextListFromElement(elem_descriptions);
	  for(it=descrip.begin();it!=descrip.end();++it){
			 cout<<*it<<endl;
	  }

	  pElem elem_properties=itemHandle.FirstChild("properties").ToElement();
	  vector<string> prop=getTextListFromElement(elem_properties);
	  for(it=prop.begin();it!=prop.end();++it){
			 cout<<*it<<endl;
	  }

	  
	  return item;
}


