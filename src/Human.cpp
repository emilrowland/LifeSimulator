//#include <iostream>
#include "Food.h"

#include "Human.h"

Human::Human(const Date* date){
    Human::simDate = date;
    Human::firstName = "Emil";
    Human::lastName = "Rowland";
    Human::busy = *date;
}

Human::~Human(){
}

std::string Human::tick(){
    //One tick is one second
    std::string what;
    if(!Human::todoQueue.empty()){
        std::string todo = Human::todoQueue.top();
        if(todo == "Eat"){
            int status = Human::eat();
            if(status == 2){
                what = "No money can't eat";
            }else{
                what = "Eat";
                Human::todoQueue.pop();
                Human::busy.add(DeltaTime(0,0,0,0,15,0)); //Eat for 15min
            }
        }
        //Nothing to do
        Human::busy.tick(1);
    }
    if(Human::hunger > 25){
        Human::todoQueue.push("Eat", 1);
    }else if(Human::hunger > 6){
        Human::todoQueue.push("Eat", 5);
    }
    Human::hunger += 0.0002;
    if(Human::hunger > 100){ //Dead because of hunger
        Human::hunger = 100;
        Human::health = 0;
    }
    if(Human::health <= 0){
        return "Died";
    }
    return what;
}

int Human::eat(){
    /*
    / Return codes:
    /   1 - Everything is fine
    /   2 - Can't afford food
    */
    if(Human::money >= 20){
        Human::money -= 20;
        Food* food = new Food();
        Human::hunger -= food->hunger;
        delete food;
        if(Human::hunger < 0){
            Human::hunger = 0;
        }
        return 1;
    }
    return 2;
}
