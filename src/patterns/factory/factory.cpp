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
    // 1. Build all scenes from data
    // 2. Build connections from data
    // 3. Build items and place in scenes
    // 4. Set up events and special object relationships

    // Use data-driven approach if data loader is available
    if (useDataLoader) {
        return buildGameFromData();
    }

    // Legacy XML-based game building (fallback)
    pScene esc1 = this->buildScenarioById("game.scenes.scene.sce001");
    pScene esc2 = this->buildScenarioById("game.scenes.scene.sce002");
    pScene esc3 = this->buildScenarioById("game.scenes.scene.sce003");
    pScene esc4 = this->buildScenarioById("game.scenes.scene.sce004");
    pScene esc5 = this->buildScenarioById("game.scenes.scene.sce005");
    pScene esc6 = this->buildScenarioById("game.scenes.scene.sce006");

    pItem o_baston    = this->buildItemById("game.items.item.item01");
    pItem o_ladrillo  = this->buildItemById("game.items.item.item02");
    pItem o_cerradura = this->buildItemById("game.items.item.item03");
    pItem o_palanca   = this->buildItemById("game.items.item.item04");
    pItem o_figurita  = this->buildItemById("game.items.item.item05");
    pItem o_hueco     = this->buildItemById("game.items.item.item06");

    IEvent *eventOpenConnection1 = new EventOpenConnection(esc5,
                                                           s_oeste,
                                                           postMessageActivationToEventOpenConnection1);
    o_hueco->insert_event(eventOpenConnection1);

    connect(esc1,west,esc2,east);
    connect(esc1,east,esc3,west);
    connect(esc2,west,esc4,east);
    connect(esc4,west,esc5,east);
    connect(esc5,west,esc6,east);

    esc1->set_estado_salida(oeste,true);
    esc1->set_estado_salida(este,true);
    esc2->set_estado_salida(este,true);
    esc2->set_estado_salida(oeste,true);
    esc3->set_estado_salida(oeste,true);
    esc4->set_estado_salida(este,true);
    esc4->set_estado_salida(oeste,true);
    esc5->set_estado_salida(este,true);
    esc5->set_estado_salida(oeste,false);
    esc6->set_estado_salida(este,true);

    string descrip_tirar_ladrillo="Tiras con fuerza del ladrillo de la pared, y parece que comienza a ceder. Una vez sacado el ladrillo, tras el, aparece una cerradura escondida.";
    o_ladrillo->set_tirable(o_cerradura,descrip_tirar_ladrillo);

    esc1->set_objeto(o_ladrillo);
    esc1->set_objeto(o_cerradura);
    esc2->set_objeto(o_baston);
    esc3->set_objeto(o_figurita);
    esc4->set_objeto(o_palanca);
    esc5->set_objeto(o_hueco);

    return esc1;
}

pScene FactoryGame::buildGameFromData() {
    std::cout << "Building game from JSON data..." << std::endl;

    // Step 1: Build all scenes and store in map
    std::map<std::string, pScene> sceneMap;
    for (auto it = gameWorldData.scenes.begin(); it != gameWorldData.scenes.end(); ++it) {
        const std::string& sceneId = it->first;
        const GameData::SceneData& sceneData = it->second;
        pScene scene = buildScenarioFromData(sceneData);
        sceneMap[sceneId] = scene;
        std::cout << "Built scene: " << sceneId << " (" << sceneData.title << ")" << std::endl;
    }

    // Step 2: Build connections from data (uses exits defined in each scene)
    buildConnectionsFromData(sceneMap);

    // Step 3: Build items and place them in scenes based on JSON data
    std::map<std::string, pItem> itemMap;
    for (auto it = gameWorldData.items.begin(); it != gameWorldData.items.end(); ++it) {
        const std::string& itemId = it->first;
        const GameData::ItemData& itemData = it->second;
        pItem item = buildItemFromData(itemData);
        itemMap[itemId] = item;
        std::cout << "Built item: " << itemId << std::endl;
    }

    // Place items in scenes as defined in JSON
    for (auto it = gameWorldData.scenes.begin(); it != gameWorldData.scenes.end(); ++it) {
        const std::string& sceneId = it->first;
        const GameData::SceneData& sceneData = it->second;
        pScene scene = sceneMap[sceneId];
        for (size_t i = 0; i < sceneData.itemIds.size(); ++i) {
            const std::string& itemId = sceneData.itemIds[i];
            auto itemIt = itemMap.find(itemId);
            if (itemIt != itemMap.end()) {
                scene->set_objeto(itemIt->second);
                std::cout << "Placed item " << itemId << " in scene " << sceneId << std::endl;
            } else {
                std::cerr << "Warning: Item not found: " << itemId << std::endl;
            }
        }
    }

    // Step 4: Set up special object relationships and events
    // TODO: These could also be data-driven in the future
    setupSpecialObjectRelationships(sceneMap, itemMap);

    // Return the starting scene (sce001)
    auto startScene = sceneMap.find("sce001");
    if (startScene != sceneMap.end()) {
        return startScene->second;
    }

    // Fallback: return first scene if sce001 not found
    if (!sceneMap.empty()) {
        return sceneMap.begin()->second;
    }

    std::cerr << "Error: No scenes found in game data!" << std::endl;
    exit(1);
}

void FactoryGame::setupSpecialObjectRelationships(
    std::map<std::string, pScene>& sceneMap,
    std::map<std::string, pItem>& itemMap) {

    // Special relationship: ladrillo reveals cerradura when pulled
    auto ladrilloIt = itemMap.find("item02");
    auto cerraduraIt = itemMap.find("item03");
    if (ladrilloIt != itemMap.end() && cerraduraIt != itemMap.end()) {
        string descrip_tirar_ladrillo = "Tiras con fuerza del ladrillo de la pared, y parece que comienza a ceder. Una vez sacado el ladrillo, tras el, aparece una cerradura escondida.";
        ladrilloIt->second->set_tirable(cerraduraIt->second, descrip_tirar_ladrillo);

        // Also add cerradura to sce001 (hidden initially)
        auto sce001It = sceneMap.find("sce001");
        if (sce001It != sceneMap.end()) {
            sce001It->second->set_objeto(cerraduraIt->second);
        }
    }

    // Event: hueco opens west connection from sce005
    auto huecoIt = itemMap.find("item06");
    auto sce005It = sceneMap.find("sce005");
    if (huecoIt != itemMap.end() && sce005It != sceneMap.end()) {
        IEvent *eventOpenConnection1 = new EventOpenConnection(
            sce005It->second,
            s_oeste,
            postMessageActivationToEventOpenConnection1);
        huecoIt->second->insert_event(eventOpenConnection1);

        // Set west exit as initially locked
        sce005It->second->set_estado_salida(oeste, false);
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

void FactoryGame::buildConnectionsFromData(std::map<std::string, pScene>& sceneMap) {
    // Build connections from JSON data (exits field in each scene)
    for (auto itScene = gameWorldData.scenes.begin(); itScene != gameWorldData.scenes.end(); ++itScene) {
        const std::string& sceneId = itScene->first;
        const GameData::SceneData& sceneData = itScene->second;

        auto itOrigin = sceneMap.find(sceneId);
        if (itOrigin == sceneMap.end()) {
            continue;  // Scene not in our map, skip
        }
        pScene originScene = itOrigin->second;

        // Process exits for this scene
        for (auto itExit = sceneData.exits.begin(); itExit != sceneData.exits.end(); ++itExit) {
            const std::string& direction = itExit->first;
            const std::string& destSceneId = itExit->second;

            auto itDest = sceneMap.find(destSceneId);
            if (itDest == sceneMap.end()) {
                std::cerr << "Warning: Connection destination not found: " << destSceneId << std::endl;
                continue;
            }
            pScene destScene = itDest->second;

            // Use string-based set_salida for escenarioSalidas map
            originScene->set_salida(destScene, direction, true);

            std::cout << "Connected: " << sceneId << " [" << direction << "] -> " << destSceneId << std::endl;
        }
    }

    // Also process global connections array if present (bidirectional connections)
    for (size_t i = 0; i < gameWorldData.connections.size(); ++i) {
        const auto& conn = gameWorldData.connections[i];
        auto itOrigin = sceneMap.find(conn.sceneIdOrigin);
        auto itDest = sceneMap.find(conn.sceneIdDestination);

        if (itOrigin == sceneMap.end() || itDest == sceneMap.end()) {
            std::cerr << "Warning: Connection scenes not found: " << conn.sceneIdOrigin
                      << " -> " << conn.sceneIdDestination << std::endl;
            continue;
        }

        pScene originScene = itOrigin->second;
        pScene destScene = itDest->second;

        parametros::cardinal cardOrigin = originScene->stringToCardinal(conn.cardinalOrigin);
        parametros::cardinal cardDest = destScene->stringToCardinal(conn.cardinalDestination);

        // Use bidirectional connect for cardinal-based map
        connect(originScene, cardOrigin, destScene, cardDest);

        std::cout << "Connected (bidirectional): " << conn.sceneIdOrigin << " <-> " << conn.sceneIdDestination << std::endl;
    }
}
