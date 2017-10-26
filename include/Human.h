#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "TaskQueue.h"
#include "Storage.h"

class Human
{
    public:
        Human();
        virtual ~Human();
        std::string firstName;
        std::string lastName;
        float health = 100;
        float money = 10000;
        float hunger = 0;
        std::string tick();
    protected:
        int eat();
    private:
        TaskQueue<std::string> todoQueue = TaskQueue<std::string>(50);
        Storage inventory = Storage(0.000546);
};

#endif // HUMAN_H
