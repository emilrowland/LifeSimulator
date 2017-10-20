#include <iostream>
#include "Human.h"
#include "Date.h"

#include "TaskQueue.h"

using namespace std;


void test(){
    TaskQueue<int> tasks = TaskQueue<int>(10);
    for(int i = 5; i > 0; i--){
        tasks.push(i,i);
    }
    for(int i = 0; i < 5; i++){
        tasks.push(i,i);
    }
    tasks.print();
    std::cout << tasks.pop() << std::endl;
    tasks.print();
}

int main(){
    Date date = Date(2017,6,1,12,0,0); //2017-06-01 12:00:00
    cout << "Creating Human" << endl;
    Human human1 = Human();
    cout << human1.firstName << " " << human1.lastName << endl;
    while(true){
        if(date.day == 1 && date.hour == 12 && date.minute == 0 && date.second == 0){
            cout << human1.firstName << " " << human1.lastName << endl;
            cout << "Date: " << date.toString() << endl;
            cout << "Health: " << human1.health << endl;
            cout << "Hunger: " << human1.hunger << endl;
            cout << "Money: " << human1.money << endl;
        }
        if(date.year == 2018){
            break;
        }
        std::string what = human1.tick();
        if(!what.empty() && what != "Eat"){
            cout << "Date: " << date.toString() << endl;
            cout << human1.firstName << " " << human1.lastName << " " << what << endl;
            if(what == "Died"){
                break;
            }
        }
        date.tick(1);
    }
    //test();
    return 0;
}
