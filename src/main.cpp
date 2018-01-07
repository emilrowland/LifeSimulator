#include <iostream>
#include <queue>
#include <vector>

#include "Human.h"
#include "Date.h"
#include "SimConfigurations.h"
#include "SimReporter.h"
#include "RandomGenerator.h"

char* generateValidHumanId(std::vector<char*> humanIds, RandomGenerator* randomGenerator){
    while(true){
        bool uniqueId = true;
        char* id = randomGenerator->randomId(50);
        for(int i = 0;  i < humanIds.size(); i++){
            if(humanIds[i] == id){
                uniqueId = false;
            }
        }
        if(uniqueId){
            return id;
        }
    }
}


int main(){
    //Read configurations
    SimConfigurations simConfigs("default_sim_profile.json");
    //Reporter
    SimReporter* simReporter = new SimReporter();
    //Setup
    RandomGenerator* randomGenerator = new RandomGenerator();
    Date* date = simConfigs.getStartDate();
    std::cout << "Start date: " << *date << std::endl;
    simReporter->setSimStartDate(*date);
    DeltaTime runTime = simConfigs.getSimDuration();
    Date stopDate = *date;
    stopDate.add(runTime);
    const Date* readDate = date;
    std::vector<char*> humanIds;
    std::cout << "Creating Humans" << std::endl;
    std::priority_queue<Human*, std::vector<Human*>, HumanComparatorBussy> humanQueue;
    for(int i = 0; i < simConfigs.getHumanStartNum(); i++){
        char* id = generateValidHumanId(humanIds, randomGenerator);
        humanIds.push_back(id);
        Human* human = new Human(readDate, id, simReporter, i*3);
        humanQueue.push(human);
        std::cout << human->firstName << " " << human->lastName << std::endl;
    }
    //Run simulation
    while(*date < stopDate && !humanQueue.empty()){
        while(humanQueue.top()->busy <= *date && !humanQueue.empty()){
            Human* human = humanQueue.top();
            humanQueue.pop();

            std::string what = human->tick();
            if(!what.empty() && what == "Died"){
                std::cout << human->firstName << " " << human->lastName << " " << what << " At: " << *date << std::endl;
                delete human; //Delete human
            }else{
                humanQueue.push(human);
            }
        }
        date->tick(1); //Add one second
    }
    //Ending simulation
    std::cout << "Simulation ended at: " << *date << std::endl;
    simReporter->setSimEndDate(*date);
    std::cout << "Generating report" << std::endl;
    simReporter->generateReport();
    delete date;
    return 0;
}
