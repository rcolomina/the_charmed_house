#include "factory.h"
#include "game.h"
#include <string>


using namespace std;

int main(){

    cout<<"Starting with Factory class test"<<endl;
    cout<<"--------------------------------"<<endl;


    string xmlSpecs("gamesInfo.xml");
    FactoryGame fac(xmlSpecs);

    //
    string prefix="game.items.item";
    string postfix=".item03";	 
    string buildItem ="Building Item item03";
    cout<<buildItem<<endl;
    pItem item=fac.buildItemById(prefix.append(postfix));

    cout<<"Visible:"<<item->get_value<bool>("visibility")<<endl;
    cout<<"Fijo:"<<item->get_value<bool>("fix")<<endl;

    //
    buildItem ="Building Item item05";
    prefix="game.items.item";
    postfix=".item05";
    cout<<buildItem<<endl;
    item=fac.buildItemById(prefix.append(postfix));
    cout<<"key:"<<item->get_value<bool>("key")<<endl;	  
    cout<<"code:"<<item->get_value<int>("code")<<endl;

	  
    buildItem ="Building Item item06";
    prefix="game.items.item";
    postfix=".item06";
    cout<<buildItem<<endl;
    item=fac.buildItemById(prefix.append(postfix));
    cout<<"lock:"<<item->get_value<bool>("lock")<<endl;	  
    cout<<"code:"<<item->get_value<int>("code")<<endl;
	  
    cout<<"--------------------------------"<<endl;

    string idScen("game.scenes.scene.sce002");
    cout<<"Building Scenario "<<idScen<<" "<<endl;
	  
    pScene scene=fac.buildScenarioById(idScen);

    cout<<"Scenario Id:"<<scene->sId()<<endl;
    cout<<"Scenario Name:"<<scene->Name()<<endl;
    cout<<"Scenario Description:"<<scene->examine()<<endl;
    cout<<"Scenario Observation:"<<scene->get_observacion()<<endl;
    cout<<"Scenario Path File:"<<scene->get_path_image()<<endl;


    cout<<"Building Game by Id"<<endl;
    scene = fac.buildGameById("idgame");

    cout<<"Scenario Id:"<<scene->sId()<<endl;
    cout<<"Scenario Name:"<<scene->Name()<<endl;
    cout<<"Scenario Description:"<<scene->examine()<<endl;
    cout<<"Scenario Observation:"<<scene->get_observacion()<<endl;
    cout<<"Scenario Path File:"<<scene->get_path_image()<<endl;


    
}
 
