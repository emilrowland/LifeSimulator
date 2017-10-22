//#include <iostream>
#include "Food.h"

#include "Human.h"

Human::Human(){
    Human::firstName = "Emil";
    Human::lastName = "Rowland";
}

Human::~Human(){
}

std::string Human::tick(){
    //One tick is one second
    std::string what;
    if(!Human::todoQueue.empty()){
        std::string todo = Human::todoQueue.top();
        if(todo == "Eat"){
            Human::todoQueue.pop();
            Human::eat();
            what = "Eat";
        }
    }
    if(Human::hunger > 6){
        //Want to eat
        Human::todoQueue.push("Eat", 5);
    }
    Human::hunger += 0.0002;
    if(Human::hunger > 100){ //Dead to hungry
        Human::hunger = 100;
        Human::health = 0;
    }
    if(Human::health <= 0){
        return "Died";
    }
    return what;
}

void Human::eat(){
    if(Human::money >= 20){
        Human::money -= 20;
        Food* food = new Food();
        Human::hunger -= food->hunger;
        delete food;
        if(Human::hunger < 0){
            Human::hunger = 0;
        }
    }
}
