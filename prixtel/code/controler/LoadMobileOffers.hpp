//
//  MobileOffersImplementation.hpp
//  prixtel
//
//  Created by Micheli Knechtel on 06/02/2021.
//

#ifndef MobileOffers_hpp
#define MobileOffers_hpp

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "Parameter.hpp"
using namespace std;
class LoadMobileOffers{
private:
    vector<string> parseLineToFields(int &key, string &line);
    void fileProcessing(ifstream &file);
    string fileLocation;
    string delimiter;
    void fileOpen(ifstream &file);
  public:
    LoadMobileOffers();
    void load();
    map<int, vector<string>> mobileOffers;
};
#endif /* MobileOffers_hpp */
