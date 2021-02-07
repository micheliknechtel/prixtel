//
//  Consumation.hpp
//  prixtel
//
//  Created by Micheli Knechtel on 06/02/2021.
//

#ifndef Consumation_hpp
#define Consumation_hpp
#include <iostream>
#include <stdio.h>
using namespace std;
class fileFields{
public:
    fileFields(string anum, string date, string carrier, int amount, int offer_id)
    {
        this->anum = anum;
        this->date = date;
        this->carrier = carrier;
        this->amount = offer_id;
    };
    
    string anum, date, carrier;
    int amount, offer_id;
};
#endif /* Consumation_hpp */
