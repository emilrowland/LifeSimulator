#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "Item.h"


class Storage
{
    public:
        Storage(float maxVolume);
        virtual ~Storage();
        float volume;//m^3
        float maxVolume;//m^3
        float mass;//kg
        bool addItem(Item* item);
        std::vector<Item*> getItems();
        Item* popItem(unsigned int pos);
    protected:
    private:
        std::vector<Item*> inventory;
};

#endif // STORAGE_H
