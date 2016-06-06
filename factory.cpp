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


vector<string> FactoryGame::getNameListFromNode(pNode parent){

	  vector<string> output;
	  pNode child = 0;
	  while((child = parent->IterateChildren(child)))
	  {
			 string value_text = child->Value();
			 output.push_back(value_text);
	  }
	  return output;	  
}

vector<string> FactoryGame::getTextListFromNode(pNode parent){

	  vector<string> output;
	  pNode child = 0;
	  while((child = parent->IterateChildren(child)))
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

/*	  pNode child = parent->IterateChildren(child);
	  while(child != NULL )
	  {
			 pElem temp = child->ToElement();
			 string value_attribute = temp->Attribute("id");
			 if( id.compare(value_attribute)==0 )
			 {
					return temp;
			 }
			 child = parent->IterateChildren(child);
	  }
*/
	  pNode child = 0;
//	  bool contin
	  while((child = parent->IterateChildren(child)))
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




pItem FactoryGame::buildItemById(string itemId){

	  pElem elem_Items=this->getGameElement(string("items"));	  	  
	  pElem elem_Item=this->searchForElementId(elem_Items,itemId);


	  // CREATING THE ITEM
	  TiXmlHandle itemHandle(elem_Item);

	  pElem elem_names=itemHandle.FirstChild("names").ToElement();
	  vector<string> names=getTextListFromNode(elem_names);
	  vector<string>::iterator it;
	  for(it=names.begin();it!=names.end();++it){
			 //	 cout<<*it<<endl;
	  }
			 
	  pElem elem_descriptions=itemHandle.FirstChild("descriptions").ToElement();
	  vector<string> descrip=getTextListFromNode(elem_descriptions);
	  for(it=descrip.begin();it!=descrip.end();++it){
			 //	 cout<<*it<<endl;
	  }

	  pElem elem_properties=itemHandle.FirstChild("properties").ToElement();
	  vector<string> prop=getTextListFromNode(elem_properties);
	  for(it=prop.begin();it!=prop.end();++it){
			 //	 cout<<*it<<endl;
	  }

	  vector<string> propN=getNameListFromNode(elem_properties);
	  for(it=propN.begin();it!=propN.end();++it){
			 // cout<<*it<<endl;
	  }

	  vector<string>::iterator it1;
	  vector<string>::iterator it2;
	  for(it1 = prop.begin(),it2 = propN.begin();
			it1 < prop.end() && it2 < propN.end();
			it1++,it2++)
	  {
			 

	  }

	  cout<<"names:"<<names[0]<<endl;
	  cout<<"descrip:"<<descrip[0]<<endl;

	  
	  const Entidad& ent =  Entidad(1,names[0],descrip[0]);
	  	  
	  pItem item=new Item(ent,
								 names,
								 descrip,
								 prop,
								 propN);
	
	  cout<<"Id:"<<item->Name();  
	  return item;
}


