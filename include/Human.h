#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "TaskQueue.h"
#include "Storage.h"
#include "Date.h"

class Human
{
    public:
        Human(const Date* date);
        virtual ~Human();
        std::string firstName;
        std::string lastName;
        Date busy = Date(1,1,1,1,1,1);//Need to init to something
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

#endif // HUMAN_H
