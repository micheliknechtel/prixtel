//
//  LoadConsumation.cpp
//  prixtel
//
//  Created by Micheli Knechtel on 06/02/2021.
//

#include "LoadConsumation.hpp"

LoadConsumation::LoadConsumation()
{
    this->fileLocation = Parameter::getParameter()->fileLocation_1;
    this->delimiter = Parameter::getParameter()->delimiter;
}

void LoadConsumation::totalByAddingOne(map<string, int> &hashMap, dataStructure &d)
{
    map<string, int>::iterator itMap = hashMap.find(d.c.anum);
    if(itMap == hashMap.end())
        hashMap.insert(pair<string, int>(d.c.anum,1));
    else
        itMap->second = itMap->second +1;
}

void LoadConsumation::totalByAccumulation(map<string, int> &hashMap, dataStructure &d)
{
    map<string, int>::iterator itMap = hashMap.find(d.c.anum);
    if(itMap == hashMap.end())
        hashMap.insert(pair<string, int>(d.c.anum,0));
    else
        itMap->second = itMap->second + d.c.amount;
    
}


void LoadConsumation::updatingSecondMapStructure(const dataStructure &d)
{
    map<string, fileFields>::iterator itVoiceConsumation;
    itVoiceConsumation = d.itMap->second.find(d.key);
    if(itVoiceConsumation == d.itMap->second.end())
    {
        const fileFields value = {d.c.anum, d.c.date, d.c.carrier, d.c.amount, d.c.offer_id};
        d.itMap->second.insert(pair<string, fileFields>(d.key,value));
    }
    else
    {
        itVoiceConsumation->second.amount += d.c.amount;
        itVoiceConsumation->second.anum = d.c.anum;
        itVoiceConsumation->second.offer_id = d.c.offer_id;
        itVoiceConsumation->second.date = d.c.date;
    }
}

void LoadConsumation::buildingSecondMapStructure(dataStructure &d)
{
    map<string, fileFields> voiceConsumation;
    const fileFields value = {d.c.anum, d.c.date, d.c.carrier, d.c.amount,d.c.offer_id, d.c.total};
    voiceConsumation.insert(pair<string, fileFields>(d.key, value));
    d.hashMap.insert(pair<string, map<string, fileFields>>(d.c.anum,  voiceConsumation));
}

void LoadConsumation::loadStructures(dataStructure d)
{
    if (d.c.anum.compare(d.filter) == 0 || d.filter.compare(ALL)== 0)
    {
        totalByAddingOne(globalTotal,d);
        d.itMap = d.hashMap.find(d.c.anum);
        if(d.itMap == d.hashMap.end())
            buildingSecondMapStructure(d);
        else
            updatingSecondMapStructure(d);
    }
}

fileFields LoadConsumation::parseLineToFields(string &line)
{
    string token;
    size_t position = 0;
    vector<string> value;
    char space= ' ';
    
    
    while ((position = line.find(delimiter)) != string::npos)
    {
        token = line.substr(0, position);
        value.push_back(token);
        line.erase(0, position + delimiter.length());
    }
    
    value.push_back(line);
    
    fileFields c = {value.at(0), split(value.at(1),space), value.at(3),  stoi(value.at(2)), stoi(value.at(7))};
    return c;
}


void LoadConsumation::fileProcessing(ifstream &file)
{
    string line, key, tel;
    getline(file, line);
    
    map<string, map<string, fileFields>>::iterator itMapSMS;
    
    while (getline(file, line))
    {
        fileFields c = parseLineToFields(line);
        key  = c.anum + " " + c.date + " " + to_string(c.offer_id);
        
        
        if (c.carrier.compare(VOICE) == 0)
        {
            map<string, map<string, fileFields>>::iterator itMapVoice;
            dataStructure d = {c, itMapVoice, key, mapVoice,filter};
            loadStructures(d);
            totalByAccumulation(totalVoice,d);
        }
        
        if (c.carrier.compare(DATA) == 0)
        {
            map<string, map<string, fileFields>>::iterator itMapData;
            dataStructure d = {c, itMapData, key, mapData,filter};
            loadStructures(d);
            totalByAccumulation(totalData,d);
        }

        if (c.carrier.compare(SMS) == 0 || c.carrier.compare(MMS) == 0)
        {
            dataStructure d = {c, itMapSMS, key, mapSMS,filter};
            loadStructures(d);
            if (c.carrier.compare(SMS) == 0)
                totalByAddingOne(totalSMS,d);
            
        }
    }
    
//    cout<<total.at(filter)<<endl;
//    cout<<totalData.at(filter)<<endl;
//    cout<<totalVoice.at(filter)<<endl;
//    cout<<totalSMS.at(filter)<<endl;
//    
//    
//    int total = totalVoice.at(filter);
//    int seconds, hours, minutes;
//    minutes = total / 60;
//    seconds = total % 60;
//    hours = minutes / 60;
//    minutes = minutes % 60;
//    cout << hours << "h" << minutes<< "m" << seconds << "s"<<endl;


}

string LoadConsumation::split(const string& content, char delimiter)
{
    string token;
    vector<string> tokens;
    istringstream tokenStream(content);
    
    while(getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    
    return tokens.at(0);
}

void LoadConsumation::fileOpen(ifstream &file)
{
    file.open(fileLocation.c_str());
    if (file.fail())
    {
        cerr << "Error opening a file" << endl;
        file.close();
        exit(1);
    }
}

void LoadConsumation::load()
{
    ifstream file;
    fileOpen(file);
    fileProcessing(file);
    file.close();
}


