#include "Storage.h"

Storage::Storage(float maxVolume){
    Storage::maxVolume = maxVolume;
    Storage::volume = 0;
    Storage::mass = 0;
}

Storage::~Storage()
{
    //dtor
}

bool Storage::addItem(Item* item){
    if( (Storage::volume + item->volume) >= Storage::maxVolume){
        Storage::inventory.push_back(item);
        Storage::mass += item->mass;
        Storage::volume += item->volume;
        return true;
    }
    return false;
}

std::vector<Item*> Storage::getItems(){
    return Storage::inventory;
}

Item* Storage::popItem(unsigned int pos){
    Item* item = Storage::inventory.at(pos);
    Storage::inventory.erase(Storage::inventory.begin()+pos);
    Storage::volume -= item->volume;
    Storage::mass -= item->mass;
    return item;
}
