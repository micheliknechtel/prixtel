//
//  MobileOffersImplementation.cpp
//  prixtel
//
//  Created by Micheli Knechtel on 06/02/2021.
//

#include "LoadMobileOffers.hpp"
#include "Parameter.hpp"
#include <string>


LoadMobileOffers::LoadMobileOffers()
{
    this->fileLocation = Parameter::getParameter()->fileLocation_2;
    this->delimiter = Parameter::getParameter()->delimiter;
}

vector<string> LoadMobileOffers::parseLineToFields(int &key, string &line) {
    vector<string> value;
    string token;
    size_t position = 0;
    int index = 0;
    
    while ((position = line.find(delimiter)) != string::npos)
    {
        token = line.substr(0, position);
        if (index==0)
            key = stoi(token);
        else
            value.push_back(token);
        index++;
        line.erase(0, position + delimiter.length());
      
    }
    value.push_back(line);
    
    return value;
}

void LoadMobileOffers::fileProcessing(ifstream &file)
{
    string line;
    getline(file, line);
    while (getline(file, line))
    {
        int key;
       
        vector<std::string> value = parseLineToFields(key, line);
       
        mobileOffers.insert(pair<int, vector<string>>(key,value));
    }
}


void LoadMobileOffers::fileOpen(ifstream &file)
{
    file.open(fileLocation.c_str());
    if (file.fail())
    {
        cerr << "Error opening a file" << endl;
        file.close();
        exit(1);
    }
}

void LoadMobileOffers::load()
{
    ifstream file;
    fileOpen(file);
    fileProcessing(file);
    file.close();
}
