#include <iostream>
#include <queue>
#include "Human.h"
#include "Date.h"

#define NUMHUMANS 2


int main(){
    Date* date = new Date(2017,6,1,12,0,0); //2017-06-01 12:00:00
    DeltaTime runTime = DeltaTime(1,0,0,0,0,0);
    Date stopDate = *date;
    stopDate.add(runTime);
    const Date* readDate = date;
    std::cout << "Creating Humans" << std::endl;
    std::priority_queue<Human*, std::vector<Human*>, HumanComparatorBussy> humanQueue;
    for(int i = 0; i < NUMHUMANS; i++){
        Human* human = new Human(readDate, i*3);
        humanQueue.push(human);
        std::cout << human->firstName << " " << human->lastName << std::endl;
    }
    while(*date < stopDate && !humanQueue.empty()){
        while(humanQueue.top()->busy <= *date && !humanQueue.empty()){
            Human* human = humanQueue.top();
            humanQueue.pop();
            /*if(date->day == 1 && date->hour == 12 && date->minute == 0 && date->second == 0){
                std::cout << human->firstName << " " << human->lastName << std::endl;
                std::cout << "Date: " << *date << std::endl;
                std::cout << "Health: " << human->health << std::endl;
                std::cout << "Hunger: " << human->hunger << std::endl;
                std::cout << "Money: " << human->money << std::endl;
            }*/
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
    std::cout << "Simulation ended at: " << *date << std::endl;
    delete date;
    return 0;
}
