#include "SimReporter.h"

#include <fstream>

SimReporter::SimReporter(){
    //ctor
}

SimReporter::~SimReporter(){
    //dtor
}

void SimReporter::generateReport(){
    std::ofstream myfile;
    myfile.open ("simReport.txt");
    myfile << "Simulation start date: " << simStartDate << "\n";
    myfile << "Simulation end date: " << simEndDate << "\n";
    //Human statistics
    int averageLifeSpan = 0;
    int oldest = 0;
    std::map<char*, humanReportItem>::iterator it = humans.begin();
    while (it != humans.end()){
		averageLifeSpan += it->second.age();
        if(oldest < it->second.age()){
            oldest = it->second.age();
        }
		it++;
	}
	averageLifeSpan /= humans.size();
	myfile << "Humans statistics\n";
	myfile << "Average human lifespan: " << averageLifeSpan << " years\n";
	myfile << "Oldest human: " << oldest << " years\n";
    myfile.close();
}

void SimReporter::setSimStartDate(Date simStartDate){
    SimReporter::simStartDate = simStartDate;
}

void SimReporter::setSimEndDate(Date simEndDate){
    SimReporter::simEndDate = simEndDate;
}

void SimReporter::setHumanBornDate(char* id, Date bornDate){
    SimReporter::humans[id].bornDate = bornDate;
}

void SimReporter::setHumanDieDate(char* id, Date dieDate){
    SimReporter::humans[id].dieDate = dieDate;
}
