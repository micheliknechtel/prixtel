//
//  LoadConsumation.hpp
//  prixtel
//
//  Created by Micheli Knechtel on 06/02/2021.
//

#ifndef FileManager_hpp
#define FileManager_hpp

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>


#include "Parameter.hpp"


#define VOICE "voix"
#define DATA "data"
#define SMS "sms"
#define MMS "mms"

using namespace std;
struct fileFields {string anum; string date; string carrier; int amount = 0; int offer_id = 0; int total = 1;};
struct dataStructure { fileFields &c; map<string, map<string, fileFields>>::iterator &itMap; const string &key; map<string, map<string, fileFields>> &hashMap; string filter;};

class LoadConsumation
{
private:
    void totalByAddingOne(map<string, int> &hashMap, dataStructure &d);
    void totalByAccumulation( map<string, int> &hashMap, dataStructure &d);
    void updatingSecondMapStructure(const dataStructure &d);
    void buildingSecondMapStructure(dataStructure &d);
    void loadStructures(dataStructure d);
    fileFields parseLineToFields(string &line);
    void extracted();
    void fileProcessing(ifstream &file);
    string fileLocation;
    string delimiter;
    string split(const string& content, char delimite);
    void fileOpen(std::ifstream &file);
public:
    void load();
    LoadConsumation();
    string filter = Parameter::getParameter()->telNumber;
    
    map<string, map<string, fileFields>> mapVoice;
    map<string, map<string, fileFields>> mapData;
    map<string, map<string, fileFields>> mapSMS;
    
    map<string, int> globalTotal;
    map<string, int> totalSMS;
    map<string, int> totalData;
    map<string, int> totalVoice;
};

#endif /* FileManager_hpp */
