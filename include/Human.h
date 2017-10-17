#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <queue>
#include "Storage.h"

struct todo {
    int priority;
    std::string what;
    bool operator<(const todo& other)const
    { return priority > other.priority; }
};

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
        std::priority_queue<todo*> todoQueue;
        Storage inventory = Storage(0.000546);
};

#endif // HUMAN_H
