#include "Food.h"
#include "RandomGenerator.h"

#include "Human.h"

Human::Human(const Date* date, char* id, SimReporter* simReporter, int seed){
    Human::id = id;
    Human::simReporter = simReporter;
    if(seed == -1){
        seed = date->second + date->day;
    }
    RandomGenerator random = RandomGenerator(seed);
    Human::simDate = date;
    simReporter->setHumanBornDate(id, *date);
    Human::firstName = random.randomName(2,10);
    Human::lastName = random.randomName(2,10);
    Human::busy = *date;
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
                fastForward = 15*60;
            }
        }
    }
    if(Human::hunger > 25){
        Human::todoQueue.push("Eat", 1);
    }else if(Human::hunger > 6){
        Human::todoQueue.push("Eat", 5);
    }
    Human::hunger += 0.0002 * fastForward;
    if(Human::hunger > 100){ //Dead because of hunger
        Human::hunger = 100;
        Human::health = 0;
    }
    if(Human::health <= 0){
        Human::simReporter->setHumanDieDate(Human::id, *Human::simDate);
        return "Died";
    }
    if(Human::busy <= *Human::simDate){
        Human::busy.tick(1);
        fastForward = 1;
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
