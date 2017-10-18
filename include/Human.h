#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "PriorityQueueOrder.h"
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
        void eat();
    private:
        PriorityQueueOrder<std::string> todoQueue;
        Storage inventory = Storage(0.000546);
};

#endif // HUMAN_H
