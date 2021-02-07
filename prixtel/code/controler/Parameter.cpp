//
//  Parameter.cpp
//  prixtel
//
//  Created by Micheli Knechtel on 06/02/2021.
//

#include "Parameter.hpp"


Parameter* Parameter::parameter = NULL;

Parameter* Parameter::getParameter()
{
    if(!parameter)
    {
        parameter = new Parameter;
    }
    return parameter;
}

void Parameter::scenarioOne()
{
    // test scenario one) recap -tel "062XX00273"
    int argc = 3;
    char so0[] = "recap";
    char so1[] = "-tel";
    char so2[] = "062XX00273";
    char* scenarioOne[] = {so0,so1,so2, NULL};
    loadingFromCommandLine(argc, scenarioOne);
    
}

void Parameter::scenarioTwo()
{
    // test scenario two) recap
     int argc = 1;
     char st0[] = "recap";
     char* scenarioTwo[] = {st0, NULL};

    loadingFromCommandLine(argc, scenarioTwo);
    
}

void Parameter::loadingFromCommandLine(int argc, char **argv)
{
    for (int i = 0; i<argc; i++)
    {
        string strAux = argv[i];
        loadInput(strAux, argv, i);
    }
    checkInput();
    
}

void Parameter::loadInput(string strAux, char **argv, int i)
{
    if ( i== 0 && strAux.compare("recap")==0 )
        recap = true;
   
    if ( i == 1 && strAux.compare("-tel")==0 )
        telNumber = argv[++i];
    else if (i == 1)
        telNumber = "";
}


void Parameter::checkInput()
{
    if (!recap)
    {
        cout << "Error: recap not specified "<<endl;
        exit(1);
    }
    else
    {
        if (telNumber.empty())
        {
            cout << "Error: prefixe <<-tel>> or <<number>> not specified (i.e. recap -tel 062XX00273)"<<endl;
            exit(1);
        }

    }
}

void Parameter::predefinedParameters()
{
    
}
