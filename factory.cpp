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

pScene FactoryGame::buildGameById(string gameId){


     //CONSTRUIMOS LA PRIMERA ESCENA: TODO:Cargar desde fichero
     // TODO: Build automatically all these objects running over its ids.
     pScene esc1 = this->buildScenarioById("game.scenes.scene.sce001");
     pScene esc2 = this->buildScenarioById("game.scenes.scene.sce002");
     pScene esc3 = this->buildScenarioById("game.scenes.scene.sce003");
     pScene esc4 = this->buildScenarioById("game.scenes.scene.sce004");
     pScene esc5 = this->buildScenarioById("game.scenes.scene.sce005");
     pScene esc6 = this->buildScenarioById("game.scenes.scene.sce006");
	  
     //CONSTRUIR OBJETOS
     // TODO: Build automatically all these objects running over its ids.	  
     pItem o_baston    = this->buildItemById("game.items.item.item01");
     pItem o_ladrillo  = this->buildItemById("game.items.item.item02");
     pItem o_cerradura = this->buildItemById("game.items.item.item03");
     pItem o_palanca   = this->buildItemById("game.items.item.item04");
     pItem o_figurita  = this->buildItemById("game.items.item.item05");
     pItem o_hueco     = this->buildItemById("game.items.item.item06");

     // Events on objects
     IEvent *eventOpenConnection1 = new EventOpenConnection(esc5,
							    s_oeste,
							    postMessageActivationToEventOpenConnection1);

     o_hueco->insert_event(eventOpenConnection1);

//Continuar con el bucle principal del juego
//	  continuar_loop=true;
//   configurar reloj
//	  tiempo=0; //segundos	  
//   variables del jugador
//	  contador_mal_comportamiento=0;
  	 	  	  	 

     //insertar escenario en mundo
/*    mundo[nombre1]=esc1;
      mundo[nombre2]=esc2;
      mundo[nombre3]=esc3;
      mundo[nombre4]=esc4;*/
	 
     // Enlaces entre escenas
     //Id: 1->[2(o),3(e)] ,2->[1(e),4(i)), 3->[1(o)], 4->[2(e)]
     connect(esc1,west,esc2,east);
     connect(esc1,east,esc3,west);
     connect(esc2,west,esc4,east);

	 
     esc1->set_salida(esc2,oeste,true);	 
     esc2->set_salida(esc1,este,true);
		  
     esc1->set_salida(esc3,este,true);
     esc3->set_salida(esc1,oeste,true);
	 
     esc2->set_salida(esc4,oeste,true);
     esc4->set_salida(esc2,este,true);

     esc4->set_salida(esc5,oeste,true);
     esc5->set_salida(esc4,este,true);

     esc5->set_salida(esc6,oeste,false);
     esc6->set_salida(esc5,este,true);

     //RELACIONAR OBJETOS
     // Ladrillo con llave
     string descrip_tirar_ladrillo="Tiras con fuerza del ladrillo de la pared, y parece que comienza a ceder. Una vez sacado el ladrillo, tras el, aparece una cerradura escondida.";
     o_ladrillo->set_tirable(o_cerradura,descrip_tirar_ladrillo);

     //o_hueco->subscribed(
	 
     //INSERTAR OBJETOS EN ESCENARIOS
     esc1->set_objeto(o_ladrillo);
     esc1->set_objeto(o_cerradura);
     esc2->set_objeto(o_baston);
     esc3->set_objeto(o_figurita);
     esc4->set_objeto(o_palanca);
     esc5->set_objeto(o_hueco);
     //CONSTRUIR INVENTARIO
     //inventario.insertar_objeto(objeto);

     
          // Setear la escena de comienzo del juego
     return esc1;
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

     pNode child = 0;
     while((child = parent->IterateChildren(child)))
     {
	  pElem temp = child->ToElement();
	  string value_attribute = temp->Attribute("id");
	  if(id.compare(value_attribute)==0 )
	  {
	       return temp;
	  }
     }	  
     return NULL;
}



/* This method accepts and item id, looking
   into the xml file of the game to get all its
   informations and build an item with those 
*/
pItem FactoryGame::buildItemById(string itemId){

     // getting element item
     pElem elem_Items=this->getGameElement(string("items"));
     assert(elem_Items!=NULL);
	  
     pElem elem_Item=this->searchForElementId(elem_Items,itemId);
     assert(elem_Item!=NULL);
	  
     // handler over xml
     TiXmlHandle itemHandle(elem_Item);
	  
     pElem elem_names=itemHandle.FirstChild("names").ToElement();
     assert(elem_names!=NULL);
     vector<string> names=getTextListFromNode(elem_names);
	  			 
     pElem elem_descriptions=itemHandle.FirstChild("descriptions").ToElement();
     assert(elem_descriptions!=NULL);
     vector<string> descrip=getTextListFromNode(elem_descriptions);	  

     pElem elem_properties=itemHandle.FirstChild("properties").ToElement();
     assert(elem_properties!=NULL);
	  
     // Getting the properties
     vector<string> prop=getTextListFromNode(elem_properties);	  
     vector<string> propN=getNameListFromNode(elem_properties);
     vector<pair<string,string> > props;	  
     vector<string>::iterator it1;
     vector<string>::iterator it2;
     for(it1 = propN.begin(),it2 = prop.begin();
	 it1 < propN.end() && it2 < prop.end();
	 it1++,it2++)
     {			 					
	  pair<string,string> pa(*it1,*it2);
	  props.push_back(pa);			 
     }

     // Getting path file to image
     // pElem elem_image = itemHandle.FirstChild("images").ToElement();

     TiXmlHandle itemHandle2(elem_Item);	  	  
     pElem elem_image=itemHandle.FirstChild("image").ToElement();	  
     assert(elem_image != NULL);
     string pathFileText = elem_image->GetText();
					
     // vector<string> v_pathFileText = getTextListFromNode(elem_image);	  
     // string pathFileText=v_pathFileText[0];
	  
     const Entidad& ent =  Entidad(itemId,names[0],descrip[0]);	  	  
     pItem item=new Item(ent,names,descrip,props,pathFileText);
	
     return item;
}


pScene FactoryGame::buildScenarioById(string scenId){

     string mainNode("scenes");
     string attrib("title");
     string childrenNode("descriptions");
     string childrenNode2("image");

     // getting element item
     pElem elem_Scenes = this->getGameElement(mainNode.c_str());	  	  
     pElem elem_Scene  = this->searchForElementId(elem_Scenes,scenId.c_str());

     if(elem_Scenes==NULL){
	  cout<<"Handle returned a Null at elem_Scenes"<<endl;
	  exit(0);
     }
	  
     if(elem_Scene==NULL){
	  cout<<"Handle returned a Null at elem_Scen"<<endl;
	  exit(0);
     }

     const string& scen_title = elem_Scene->Attribute(attrib.c_str());

     //cout<<"title scenary:"<<scen_title<<endl;
	  
     // handler
     TiXmlHandle itemHandle(elem_Scene);	  	  
     pElem scen_descrips=itemHandle.FirstChild(childrenNode.c_str()).ToElement();
	  
     if(scen_descrips==NULL){
	  // TODO: Add an asscertion
	  cout<<"Handle returned a Null value"<<endl;
	  exit(0);
     }
	  
     vector<string> descripts = getTextListFromNode(scen_descrips);

     pElem scen_image = itemHandle.FirstChild(childrenNode2.c_str()).ToElement();	  
     string pathText  = scen_image->GetText();

     const Entidad& ent = Entidad(scenId,scen_title,descripts[0]);
	  
     pScene scene = new Escenario(ent,descripts[1],pathText);
			 
     return scene;
}
