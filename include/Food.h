#ifndef FOOD_H
#define FOOD_H

#include "Item.h"


class Food : public Item
{
    public:
        Food();
        virtual ~Food();
        int hunger;
    protected:
    private:
};

#endif // FOOD_H
