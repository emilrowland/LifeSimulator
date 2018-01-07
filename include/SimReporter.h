#ifndef SIMREPORTER_H
#define SIMREPORTER_H

#include <map>

#include "Date.h"


class SimReporter{
    public:
        SimReporter();
        virtual ~SimReporter();
        void generateReport();
        void setSimStartDate(Date simStartDate);
        void setSimEndDate(Date simEndDate);
        void setHumanBornDate(char* id, Date bornDate);
        void setHumanDieDate(char* id, Date dieDate);
    protected:
    private:
        Date simStartDate;
        Date simEndDate;

        struct humanReportItem {
            Date bornDate;
            Date dieDate;
            int age(){
                //TODO FIX
                return dieDate.year - bornDate.year;
            }
        };
        std::map<char*, humanReportItem> humans;
};

#endif // SIMREPORTER_H
