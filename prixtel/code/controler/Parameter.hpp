//
//  Parameter.hpp
//  prixtel
//
//  Created by Micheli Knechtel on 06/02/2021.
//

#ifndef DataManager_hpp
#define DataManager_hpp

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#define ALL "all"

class Parameter
{
    static Parameter *parameter;
    bool recap = false;
    void loadInput(string strAux, char **argv, int i);
    void checkInput();
public:
    void scenarioOne();
    void scenarioTwo();
    string telNumber = ALL;
    static Parameter* getParameter();
    void loadingFromCommandLine(int argc, char **argv);
    void predefinedParameters();
    string fileLocation_1 = "/Users/micheliknechtel/Documents/xCode/prixtel/prixtel/resources/extrait_data_sept.csv";
    string fileLocation_2 ="/Users/micheliknechtel/Documents/xCode/prixtel/prixtel/resources/Gsm_offers.csv";
    string delimiter = ",";
};

#endif /* DataManager_hpp */
