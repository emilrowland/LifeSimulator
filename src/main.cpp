#include <iostream>
#include <queue>
#include "Human.h"
#include "Date.h"
#include "SimConfigurations.h"


int main(){
    //Read configurations
    SimConfigurations simConfigs("default_sim_profile.json");
    //Setup
    Date* date = simConfigs.getStartDate();
    std::cout << "Start date: " << *date << std::endl;
    DeltaTime runTime = simConfigs.getSimDuration();
    Date stopDate = *date;
    stopDate.add(runTime);
    const Date* readDate = date;
    std::cout << "Creating Humans" << std::endl;
    std::priority_queue<Human*, std::vector<Human*>, HumanComparatorBussy> humanQueue;
    for(int i = 0; i < simConfigs.getHumanStartNum(); i++){
        Human* human = new Human(readDate, i*3);
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
    delete date;
    return 0;
}
