#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "TaskQueue.h"
#include "Storage.h"
#include "Date.h"

class Human
{
    public:
        Human(const Date* date, int seed = -1);
        std::string firstName;
        std::string lastName;
        Date busy = Date(1,1,1,1,1,1);//Need to init to something
        int fastForward = 1;
        float health = 100;
        float money = 10000;
        float hunger = 0;
        std::string tick();
    protected:
        int eat();
    private:
        TaskQueue<std::string> todoQueue = TaskQueue<std::string>(50);
        Storage inventory = Storage(0.000546);
        const Date* simDate;
};

class HumanComparatorBussy {
public:
    bool operator()(const Human* a, const Human* b)
    {
        return !(a->busy <= b->busy);
    }
};

#endif // HUMAN_H
