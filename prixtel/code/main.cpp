//
//  main.cpp
//  prixtel
//
//  Created by Micheli Knechtel on 06/02/2021.
//

//#include <iostream>
//using namespace std;
//#include "FileManager.hpp"
//#include "DataManager.hpp"
//
//
//
//int main(int argc, const char * argv[]) {
//
//    FileManager::getFileManager()->loadFile(DataManager::getDataManager()->mobileOffers);
//
//    cout << "Hello, World!\n";
//
//    return 0;
//}

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>

#include <string>
using namespace std;

//class LoadFileImplementation {
//  public:
//    LoadFileImplementation(string fileLocation, string delimiter)
//    {
//        fileLocation = fileLocation;
//        delimiter = delimiter;
//    }
//    virtual void load()
//    {
//        cout << "LoadFileImplementation is "   << fileLocation << delimiter << endl;
//    }
//  protected:
//    string fileLocation, delimiter;
//};

//class MobileOffersImplementation: public LoadFileImplementation {
//  public:
//    MobileOffersImplementation(string fileLocation, string delimiter, map<int, vector<string>> &mobileOffers): LoadFileImplementation(fileLocation, delimiter)
//    {
//        cout <<"MobileOffers "<<endl;
//        mobileOffers = mobileOffers;
//    }
//
//    void load() {
//        cout << "MobileOffers is "   << fileLocation << delimiter << endl;
//    }
//  protected:
//    map<int, vector<string>> mobileOffers;
//};



//class LoadFile {
//  public:
//    LoadFile(){}
//    LoadFile(string fileLocation, string delimiter) {
//        imp_ = new LoadFileImplementation( fileLocation, delimiter);
//    }
//    virtual void load() {
//        imp_->load();
//    }
//  protected:
//    LoadFileImplementation *imp_;
//};

//class MobileOffer: public LoadFile {
//  public:
//    MobileOffer(string fileLocation, string delimiter, map<int, vector<string>> &mobileOffers) {
//        imp_ = new MobileOffersImplementation( fileLocation,  delimiter, mobileOffers);
//    }
//};

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "LoadConsumation.hpp"
#include "LoadMobileOffers.hpp"
#include "Parameter.hpp"
#include "PrintSummary.hpp"
using namespace std;

int main(int argc, char **argv)
{
    //Parameter::getParameter()->loadingFromCommandLine(argc, argv);
    
    Parameter::getParameter()->scenarioTwo();
    
    LoadMobileOffers* mobileOffer =  new LoadMobileOffers();
    LoadConsumation* comsumation =  new LoadConsumation();
    
    mobileOffer->load();
    comsumation->load();
    
    PrintSummary* p = new PrintSummary();
    p->printContent(comsumation, mobileOffer);
}
