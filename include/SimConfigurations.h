#ifndef SIMCONFIGURATIONS_H
#define SIMCONFIGURATIONS_H

#include <string>
#include "Date.h"



class SimConfigurations
{
    public:
        SimConfigurations(std::string confFilePath);
        Date* getStartDate();
        DeltaTime getSimDuration();
        int getHumanStartNum();
    protected:
    private:
        Date* startDate;
        DeltaTime simDuration;
        int humanStartNum;

};

#endif // SIMCONFIGURATIONS_H
