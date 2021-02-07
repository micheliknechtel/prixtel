//
//  PrintSummary.hpp
//  prixtel
//
//  Created by Micheli Knechtel on 07/02/2021.
//

#ifndef PrintSummary_hpp
#define PrintSummary_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "LoadMobileOffers.hpp"
#include "LoadConsumation.hpp"

struct time{const string anum; int hours; int minutes; int seconds; int total;};

class PrintSummary
{
public:
    void dataTable(map<string, map<string, fileFields>> &hashMap, string anum);
    void summary();
    void header(int offer_id, string anum, LoadConsumation *c, LoadMobileOffers* o);
    void footer(const string &anum, LoadConsumation *c);
    void bodyData(const string &anum, LoadConsumation *c, int offer_id, LoadMobileOffers* o);
    void bodySMSXORVoice(const string anum, LoadConsumation *c, LoadMobileOffers* o);
    void printContent(LoadConsumation *c, LoadMobileOffers* o);
    void timeConversion(struct time &t, LoadConsumation *c);
};
#endif /* PrintSummary_hpp */
