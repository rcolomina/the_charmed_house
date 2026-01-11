#include "factory.h"
#include <iostream>

// Legacy constructor for XML loading
FactoryGame::FactoryGame(std::string xmlGameSpecifications)
    : xmlGameSpecifications(xmlGameSpecifications),
      useDataLoader(false),
      dataLoader(nullptr) {

    bool loadOkay = xmlDoc.LoadFile(xmlGameSpecifications.c_str());

    if (!loadOkay)
    {
        printf("Could not load test xml file. Error='%s'. Exiting.\n", xmlDoc.ErrorDesc());
        exit(1);
    }
}

// New constructor using data loader strategy
FactoryGame::FactoryGame(IGameDataLoader* loader, const std::string& dataFilePath)
    : dataLoader(loader),
      dataFilePath(dataFilePath),
      useDataLoader(true),
      xmlGameSpecifications("") {

    if (dataLoader == nullptr) {
        std::cerr << "Error: DataLoader is nullptr" << std::endl;
        exit(1);
    }

    try {
        gameWorldData = dataLoader->loadGameWorld(dataFilePath);
        std::cout << "Successfully loaded game data from: " << dataFilePath << std::endl;
        std::cout << "Loaded " << gameWorldData.scenes.size() << " scenes and "
                  << gameWorldData.items.size() << " items" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to load game data: " << e.what() << std::endl;
        exit(1);
    }
}

pScene FactoryGame::buildGameById(string gameId){

    // *** building process ***
    // RUN SCENE IDS
    // FOR EACH SCENEID
    //    BUILD SECEN
    // FOR EACH OBJECTID
    //    BUILD OBJECT
    // ADD OBJECTS TO SECENES
    // ADD LINKS AMONG SCENES
    
    
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

    // TODO: Depending on data origin setup work on JSON, XML or SQL table
    
    // Looking for the Element Items
    pNode node=nullptr;
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
     return nullptr;
}



/* This method accepts and item id, looking
   into the xml file of the game to get all its
   informations and build an item with those
*/
pItem FactoryGame::buildItemById(std::string itemId){

    // Use new data loader if available
    if (useDataLoader) {
        // Try to find with full ID first
        auto it = gameWorldData.items.find(itemId);

        // If not found, try extracting short ID (last part after last '.')
        if (it == gameWorldData.items.end()) {
            size_t lastDot = itemId.find_last_of('.');
            if (lastDot != std::string::npos) {
                std::string shortId = itemId.substr(lastDot + 1);
                it = gameWorldData.items.find(shortId);
            }
        }

        if (it != gameWorldData.items.end()) {
            return buildItemFromData(it->second);
        } else {
            std::cerr << "Item not found: " << itemId << std::endl;
            exit(1);
        }
    }

    // Legacy XML code
    // getting element item
    pElem elem_Items=this->getGameElement(std::string("items"));
    assert(elem_Items!=nullptr);

    pElem elem_Item=this->searchForElementId(elem_Items,itemId);
    assert(elem_Item!=nullptr);

    // handler over xml
    TiXmlHandle itemHandle(elem_Item);

    pElem elem_names=itemHandle.FirstChild("names").ToElement();
    assert(elem_names!=nullptr);
    std::vector<std::string> names=getTextListFromNode(elem_names);

    pElem elem_descriptions=itemHandle.FirstChild("descriptions").ToElement();
    assert(elem_descriptions!=nullptr);
    std::vector<std::string> descrip=getTextListFromNode(elem_descriptions);

    pElem elem_properties=itemHandle.FirstChild("properties").ToElement();
    assert(elem_properties!=nullptr);

    // Getting the properties
    std::vector<std::string> prop=getTextListFromNode(elem_properties);
    std::vector<std::string> propN=getNameListFromNode(elem_properties);
    std::vector<std::pair<std::string,std::string> > props;
    std::vector<std::string>::iterator it1;
    std::vector<std::string>::iterator it2;
    for(it1 = propN.begin(),it2 = prop.begin();
        it1 < propN.end() && it2 < prop.end();
        it1++,it2++)
    {
        std::pair<std::string,std::string> pa(*it1,*it2);
        props.push_back(pa);
    }

    // Getting path file to image
    // pElem elem_image = itemHandle.FirstChild("images").ToElement();

    TiXmlHandle itemHandle2(elem_Item);
    pElem elem_image=itemHandle.FirstChild("image").ToElement();
    assert(elem_image != nullptr);
    std::string pathFileText = elem_image->GetText();

    // vector<string> v_pathFileText = getTextListFromNode(elem_image);
    // string pathFileText=v_pathFileText[0];

    const Entidad& ent =  Entidad(itemId,names[0],descrip[0]);
    pItem item=new Item(ent,names,descrip,props,pathFileText);

    return item;
}

pItem FactoryGame::buildItemFromData(const GameData::ItemData& itemData){
    // Convert PropertyData to pair<string,string> format expected by Item
    std::vector<std::pair<std::string,std::string>> props;
    for (const auto& prop : itemData.properties) {
        props.push_back(std::make_pair(prop.name, prop.value));
    }

    // Create the item using the GameData DTO
    const Entidad& ent = Entidad(itemData.id,
                                  itemData.names.empty() ? "" : itemData.names[0],
                                  itemData.descriptions.empty() ? "" : itemData.descriptions[0]);

    pItem item = new Item(ent,
                          itemData.names,
                          itemData.descriptions,
                          props,
                          itemData.pathFileText);

    return item;
}


pScene FactoryGame::buildScenarioById(std::string scenId){

    // Use new data loader if available
    if (useDataLoader) {
        // Try to find with full ID first
        auto it = gameWorldData.scenes.find(scenId);

        // If not found, try extracting short ID (last part after last '.')
        if (it == gameWorldData.scenes.end()) {
            size_t lastDot = scenId.find_last_of('.');
            if (lastDot != std::string::npos) {
                std::string shortId = scenId.substr(lastDot + 1);
                it = gameWorldData.scenes.find(shortId);
            }
        }

        if (it != gameWorldData.scenes.end()) {
            return buildScenarioFromData(it->second);
        } else {
            std::cerr << "Scene not found: " << scenId << std::endl;
            exit(1);
        }
    }

    // Legacy XML code
    std::string mainNode("scenes");
    std::string attrib("title");
    std::string childrenNode("descriptions");
    std::string childrenNode2("image");

    // getting element item
    pElem elem_Scenes = this->getGameElement(mainNode.c_str());
    pElem elem_Scene  = this->searchForElementId(elem_Scenes,scenId.c_str());

    if(elem_Scenes==nullptr){
        cout<<"Handle returned a Null at elem_Scenes"<<endl;
        exit(0);
    }

    if(elem_Scene==nullptr){
        cout<<"Handle returned a Null at elem_Scen"<<endl;
        exit(0);
    }

    const std::string& scen_title = elem_Scene->Attribute(attrib.c_str());

    //cout<<"title scenary:"<<scen_title<<endl;

    // handler
    TiXmlHandle itemHandle(elem_Scene);
    pElem scen_descrips=itemHandle.FirstChild(childrenNode.c_str()).ToElement();

    if(scen_descrips==nullptr){
        // TODO: Add an asscertion
        cout<<"Handle returned a Null value"<<endl;
        exit(0);
    }

    std::vector<std::string> descripts = getTextListFromNode(scen_descrips);

    pElem scen_image = itemHandle.FirstChild(childrenNode2.c_str()).ToElement();
    std::string pathText  = scen_image->GetText();

    const Entidad& ent = Entidad(scenId,scen_title,descripts[0]);

    pScene scene = new Escenario(ent,descripts[1],pathText);

    return scene;
}

pScene FactoryGame::buildScenarioFromData(const GameData::SceneData& sceneData){
    // Create the scene using the GameData DTO
    const Entidad& ent = Entidad(sceneData.id, sceneData.title, sceneData.description);

    // Use observation as the second description parameter
    pScene scene = new Escenario(ent, sceneData.observation, sceneData.imagePath);

    return scene;
}
