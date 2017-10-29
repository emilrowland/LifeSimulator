#include <iostream>
#include "Human.h"
#include "Date.h"

using namespace std;

int main(){
    Date date = Date(2017,6,1,12,0,0); //2017-06-01 12:00:00
    DeltaTime runTime = DeltaTime(1,0,0,0,0,0);
    Date stopDate = date;
    stopDate.add(runTime);
    cout << "Creating Human" << endl;
    Human human1 = Human();
    cout << human1.firstName << " " << human1.lastName << endl;
    while(date < stopDate){
        if(date.day == 1 && date.hour == 12 && date.minute == 0 && date.second == 0){
            cout << human1.firstName << " " << human1.lastName << endl;
            cout << "Date: " << date << endl;
            cout << "Health: " << human1.health << endl;
            cout << "Hunger: " << human1.hunger << endl;
            cout << "Money: " << human1.money << endl;
        }
        std::string what = human1.tick();
        if(!what.empty() && what == "Died"){
            cout << "Date: " << date.toString() << endl;
            cout << human1.firstName << " " << human1.lastName << " " << what << endl;
            break;
        }
        date.tick(1); //Add one second
    }
    cout << "Simulation ended at: " << date.toString() << endl;
    return 0;
}
