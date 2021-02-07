//
//  PrintSummary.cpp
//  prixtel
//
//  Created by Micheli Knechtel on 07/02/2021.
//

#include "PrintSummary.hpp"


void PrintSummary::dataTable(map<string, map<string, fileFields>> &hashMap, string anum)
{
    map<string, map<string, fileFields>>::iterator itMap;
    
    for (itMap = hashMap.begin();itMap!= hashMap.end(); itMap++)
    {
        map<string, fileFields>::iterator it;
        for (it = itMap->second.begin();it!= itMap->second.end(); it++)
        {
            if (itMap->first.compare(anum) == 0)
            {
                double amount = ((float)it->second.amount/1000.00);
                cout<<" | "<<it->second.date <<" | "<<std::setprecision(5)<<amount<<" Mo"<<endl;
            }
        }
    }
}

void PrintSummary::footer(const std::string &anum, LoadConsumation *c)
{
    cout<<"----------------------------------------------"<<endl;
    cout<<"Consommation Voix Moyenne : ?"<<endl;
    
    float amount = 0;
    
    map<string, int>::iterator itMap = c->totalSMS.find(anum);
    if (itMap != c->totalSMS.end())
        amount = (float)c->totalSMS.at(anum);
    
    float numberOfDays = 0;;
    float everageSMS = amount/numberOfDays;
    
    cout<<"Consommation SMS/MMS Moyenne :"<<everageSMS<<"mn"<<endl;
    cout<<"Consommation Data Moyenne : "<< "?"<< "Go"<<endl;
}

void PrintSummary::bodyData(const std::string &anum, LoadConsumation *c, int offer_id, LoadMobileOffers* o)
{
    header(offer_id, anum, c, o);
    cout<<"+---------------------------+"<<endl;
    dataTable(c->mapData, anum);
    cout<<"+---------------------------+"<<endl;
    footer(anum, c);
}


void PrintSummary::bodySMSXORVoice(const string anum, LoadConsumation *c, LoadMobileOffers* o)
{
    map<string, map<string, fileFields>>::iterator itMapVoice = c->mapVoice.find(anum);
    if (itMapVoice != c->mapVoice.end())
    {
        map<string, fileFields>::iterator it = itMapVoice->second.begin();
        int offer_id = it->second.offer_id;
        header(offer_id, anum, c, o);
    }
    else
    {
        map<string, map<string, fileFields>>::iterator itMapSMS = c->mapSMS.find(anum);
        if (itMapSMS != c->mapSMS.end())
        {
            map<string, fileFields>::iterator it = itMapSMS->second.begin();
            int offer_id = it->second.offer_id;
            header(offer_id, anum, c, o);
        }
    }
}

void PrintSummary::printContent(LoadConsumation *c, LoadMobileOffers* o)
{
    string anum;
    
    cout<<o->mobileOffers.at(162).at(2);
    map<string, int>::iterator itTotal;
    for (itTotal = c->globalTotal.begin(); itTotal!= c->globalTotal.end(); itTotal++)
    {
        anum = itTotal->first;
        map<string, map<string, fileFields>>::iterator itMapData = c->mapData.find(anum);
        if (itMapData != c->mapData.end())
        {
            map<string, fileFields>::iterator it = itMapData->second.begin();
            int offer_id = it->second.offer_id;
            bodyData(anum, c, offer_id, o);
        }
        else
            bodySMSXORVoice(anum, c, o);
    }
}

void PrintSummary::timeConversion(struct time &t, LoadConsumation *c)
{
    map<string, int>::iterator itTotalVoice = c->totalVoice.find(t.anum);
    if(itTotalVoice != c->totalVoice.end())
    {
        t.total =  c->totalVoice.at(t.anum);
        t.minutes = t.total/60;
        t.seconds = t.total%60;
        t.hours = t.minutes/60;
        t.minutes = t.minutes%60;
    }
}

void PrintSummary::header(int offer_id, string anum, LoadConsumation *c, LoadMobileOffers* o)
{
    float amountData = 0;
    int index = o->mobileOffers.at(offer_id).size()-1;
    
    map<string, int>::iterator itMap = c->totalData.find(anum);
    if (itMap != c->totalData.end())
        amountData = (float)(c->totalData.at(anum))/1000000.0;
    
    float amountFixData = stof(o->mobileOffers.at(offer_id).at(index)) / 1000000.0;
    int smsSummary = (c->totalSMS.size() == 0 ?c->totalSMS.at(anum):0);
    
    string consumation = to_string(c->globalTotal.at(anum));
    string labelOffer =  o->mobileOffers.at(offer_id).at(0);
    
    struct time t = {anum, 0, 0, 0, 0};
    timeConversion(t, c);
    
    cout<<"> recap -tel "<<anum<<endl<<endl;
    cout<<"Ligne : \t " << anum << ", " <<consumation <<" consommations."<<endl;
    cout<<"Offre : \t " << labelOffer<<"("+to_string(offer_id)+")"<<endl;
    cout<<"Voix : \t " << t.hours << "h" << t.minutes<< "m" << t.seconds << "s"<<endl;
    cout<<"SMS/MMS : \t "<< smsSummary<<endl;
    cout<<"Data : \t " << setprecision(4)<<amountData<<" Go / "<< amountFixData<<"Go"<<endl<<endl;
}


