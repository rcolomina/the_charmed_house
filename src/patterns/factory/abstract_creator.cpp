#include "abstract_creator.h"

std::vector<std::string> AbstractGameCreator::getInfoList(const pNode &parent,const InfoClass &info)
{

     std::vector<std::string> output;
     pNode child = 0;
     while((child = parent->IterateChildren(child)))
     {
	  std::string value_text;
	  if(info==Name)
	       value_text = child->Value();
	  else if(info==Text){
	       pElem temp = child->ToElement();
	       value_text = temp->GetText();
	  }								 
	  output.push_back(value_text);
     }
     return output;	  
}

pElem AbstractGameCreator::searchForGame(const std::string &name){
     // Looking for the Element Items
     pNode node=nullptr;
     node = xmlDoc.FirstChild("games");
     assert(node);	  
     TiXmlHandle docHandle(node);
     pElem elem = docHandle.FirstChild("game").FirstChild(name.c_str()).ToElement();
     return elem;
}

// Return the child element with a specific id 
pElem AbstractGameCreator::searchForId(const pElem &parent,const std::string &id){

     pNode child = 0;
     while((child = parent->IterateChildren(child)))
     {
	  pElem temp = child->ToElement();
	  std::string value_attribute = temp->Attribute("id");
	  if(id.compare(value_attribute)==0 )
	  {
	       return temp;
	  }
     }	  
     return nullptr;
}
