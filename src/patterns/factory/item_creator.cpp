#include "abstract_creator.h"
#include "item_creator.h"

ItemGameCreator::ItemGameCreator(const string xmlGameSpecs)
{
    bool loadOkay = xmlDoc.LoadFile(xmlGameSpecs.c_str());
    if (!loadOkay)
    {
        printf("Could not load test xml file. Error='%s'. Exiting.\n", xmlDoc.ErrorDesc());
        exit(1);
    }
}

Entidad* ItemGameCreator::createById(std::string itemId){

    // getting element item
    pElem elem_Items=this->searchForGame(string("items"));
    assert(elem_Items!=nullptr);
	  
    pElem elem_Item=this->searchForId(elem_Items,itemId);
    assert(elem_Item!=nullptr);
	  
    // handler
    TiXmlHandle itemHandle(elem_Item);
	  
    pElem elem_names=itemHandle.FirstChild("names").ToElement();
    assert(elem_names!=nullptr);
    vector<std::string> names=getInfoList(elem_names,Name);
	  			 
    pElem elem_descriptions=itemHandle.FirstChild("descriptions").ToElement();
    assert(elem_descriptions!=nullptr);
    vector<string> descrip=getInfoList(elem_descriptions,Text);	  

    pElem elem_properties=itemHandle.FirstChild("properties").ToElement();
    assert(elem_properties!=nullptr);
	  
    vector<string> prop=getInfoList(elem_properties,Text);	  
    vector<string> propN=getInfoList(elem_properties,Name);

    vector<pair<string,string> > props;
	  
    vector<string>::iterator it1;
    vector<string>::iterator it2;
    for(it1 = propN.begin(),it2 = prop.begin();
        it1 < propN.end() && it2 < prop.end();
        it1++,it2++)
    {
/*			 cout<<"it1:"<<*it1<<" it2:"<<*it2<<endl;		 
			 bool boolvalue=false;
			 if(*it2==string("true"))
                         boolvalue=true;
*/					
//			 pair<string,bool> pa(*it1,boolvalue);
//			 props.push_back(pa);
        pair<string,string> pa(*it1,*it2);
        props.push_back(pa);			 
    }

    const Entidad& ent=Entidad(itemId,names[0],descrip[0]);

    string pathFileText; //TODO: connect with XML
    pItem item=new Item(ent,names,descrip,props,pathFileText);
	
    return item;
}

