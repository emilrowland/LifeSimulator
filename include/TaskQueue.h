#ifndef TASKQUEUE_H_INCLUDED
#define TASKQUEUE_H_INCLUDED

/*  Min priority queue with dependencies and preserve order
/   The data structure uses an heap for the priority queue.
/   To preserve order each object in the heap have an priority
/   and sequence number. If multiple items has the same priority
/   then there sequence number will sort them.
/   For dependencies each object in the heap is the beginning of an
/   linked list/stack. If an item need to have an dependencies, then
/   the dependencies is pushed to the stack. If the dependencies has
/   an higher priority than the top item in the stack then the
/   dependencies will change it priority to match the top of the stack
/   before pushed.
/   When removing an item on the heap the next item on the stack will
/   take its place. If the stack is empty the last item on the heap
/   will replace the current slot. After removing sorting is done.
*/

#include <iostream>
#include <vector>

template <class T>
class TaskQueue{
    private:
        unsigned short int maxSize;
        unsigned short int currentSeq = 0;
        unsigned short int endPos = 0;
        struct item {
            unsigned short int priority;
            T obj;
            unsigned short int seq;
            item* next = nullptr;
            bool operator>(const item& other)const{
                if(priority == other.priority){
                    return seq > other.seq;
                }
                return priority > other.priority;
            }
        };
        item** heapArray;
    public:
        TaskQueue(unsigned short int predSize=100){
            TaskQueue::maxSize = predSize;
            TaskQueue::heapArray = new item*[predSize];
        }
        void print(){
            for(unsigned short int i = 0; i < TaskQueue::endPos; i++){
                std::cout << "Priority: " << TaskQueue::heapArray[i]->priority << " Seq: " << TaskQueue::heapArray[i]->seq << " Object: " << TaskQueue::heapArray[i]->obj << std::endl;
            }
        }
    private:
        void bubbleUp(unsigned short int index){//Sort upwards
            if(index == 0){
                return;
            }
            unsigned short int parentIndex = (index-1)/2; //Floor 2.8 => 2
            if(*TaskQueue::heapArray[parentIndex] > *TaskQueue::heapArray[index]){
                item* temp = heapArray[parentIndex];
                TaskQueue::heapArray[parentIndex] = TaskQueue::heapArray[index];
                TaskQueue::heapArray[index] = temp;
                TaskQueue::bubbleUp(parentIndex);
            }
        }
        void bubbleDown(unsigned short int index){
            unsigned short int leftChildIndex = 2*index + 1;
            unsigned short int rightChildIndex = 2*index + 2;
            if(leftChildIndex >= TaskQueue::endPos){
                return; //index is a leaf
            }
            unsigned short int minIndex = index;
            if(*TaskQueue::heapArray[index] > *TaskQueue::heapArray[leftChildIndex]){
                minIndex = leftChildIndex;
            }
            if((rightChildIndex < TaskQueue::endPos) && (*TaskQueue::heapArray[minIndex] > *TaskQueue::heapArray[rightChildIndex])){
                minIndex = rightChildIndex;
            }
            if(minIndex != index){
                //Swap
                item* temp = TaskQueue::heapArray[index];
                TaskQueue::heapArray[index] = TaskQueue::heapArray[minIndex];
                TaskQueue::heapArray[minIndex] = temp;
                TaskQueue::bubbleDown(minIndex);
            }
        }
    public:
        T pop(){
            item* res = TaskQueue::heapArray[0];
            item* next = res->next;
            T ret = res->obj;
            delete res;
            if(next){
                TaskQueue::heapArray[0] = next;

            }else if(endPos <= 1){
                TaskQueue::currentSeq = 0;
                TaskQueue::endPos = 0;
                return ret;
            }else{
                TaskQueue::heapArray[0] = TaskQueue::heapArray[TaskQueue::endPos-1];
                TaskQueue::endPos--;
            }
            TaskQueue::bubbleDown(0);
            return ret;
        }
        T top(){return TaskQueue::heapArray[0]->obj;}
        bool empty(){
            if(TaskQueue::endPos == 0){
                TaskQueue::currentSeq = 0;
                return true;
            }
            return false;
        }
        virtual ~TaskQueue(){
            while(!TaskQueue::empty()){
                TaskQueue::pop();
            }
            delete TaskQueue::heapArray;
        }
        bool deleteFirstMatch(T obj){
            for(int i = 0; i < TaskQueue::endPos; i++){
                item* currentItem = TaskQueue::heapArray[i];
                if(obj == currentItem->obj){
                    //Found
                    if(i == endPos-1){
                        TaskQueue::endPos--;
                    }else{
                        TaskQueue::heapArray[i] = TaskQueue::heapArray[TaskQueue::endPos-1];
                        TaskQueue::endPos--;
                    }
                    delete currentItem;
                    TaskQueue::bubbleDown(i);
                    return true;
                }
                item* prevItem = currentItem;
                while(prevItem->next){
                    currentItem = prevItem->next;
                    if(obj == currentItem->obj){
                        //Found
                        prevItem->next = currentItem->next;
                        delete currentItem;
                        return true;
                    }
                    prevItem = currentItem;
                }
            }
            return false;
        }
        bool changePriorityOfFirstMatch(T obj, unsigned short int newPriority){
            for(unsigned short int i = 0; i < TaskQueue::endPos; i++){
                item* currentItem = TaskQueue::heapArray[i];
                if(obj == currentItem->obj){
                    //Found
                    unsigned short int oldPriority = currentItem->priority;
                    currentItem->priority = newPriority;
                    if(oldPriority < newPriority){
                        TaskQueue::bubbleDown(i);
                    }else if(oldPriority > newPriority){
                        TaskQueue::bubbleUp(i);
                    }
                    return true;
                }
                std::vector<item*> prevItems;
                item* prevItem = currentItem;
                while(prevItem->next){
                    prevItems.push_back(prevItem);
                    currentItem = prevItem->next;
                    if(obj == currentItem->obj){
                        //Found
                        unsigned short int oldPriority = currentItem->priority;
                        currentItem->priority = newPriority;
                        if(oldPriority > newPriority){
                            //Change priority on all the items before.
                            for(unsigned int i = 0; i < prevItems.size(); i++){
                                prevItems.at(i)->priority = newPriority;
                            }
                        }
                        return true;
                    }
                    prevItem = currentItem;
                }
            }
            return false;
        }
        void push(T obj, unsigned short int priority){
            if(!TaskQueue::changePriorityOfFirstMatch(obj, priority)){
                item* i = new item();
                i->obj = obj;
                i->priority = priority;
                i->seq = TaskQueue::currentSeq++;
                TaskQueue::heapArray[TaskQueue::endPos++] = i;
                TaskQueue::bubbleUp(TaskQueue::endPos-1);
            }
        }
        bool addDependencie(T obj, T dependencie, short int dependenciePriority = -1){
            for(int i = 0; i < TaskQueue::endPos; i++){
                item* currentItem = TaskQueue::heapArray[i];
                if(obj == currentItem->obj){
                    //Found
                    item* depItem = new item();
                    depItem->obj = dependencie;
                    if(dependenciePriority < currentItem->priority && dependenciePriority >= 0){
                        depItem->priority = dependenciePriority;
                    }else{
                        depItem->priority = currentItem->priority;
                    }
                    depItem->seq = currentItem->seq;
                    depItem->next = currentItem;
                    TaskQueue::heapArray[i] = depItem;
                    return true;
                }
            }
            return false;
        }
        void addDependencieTop(T dependencie, short int dependenciePriority = -1){
            if(TaskQueue::endPos != 0){
                item* currentItem = TaskQueue::heapArray[0];
                item* depItem = new item();
                depItem->obj = dependencie;
                if(dependenciePriority < currentItem->priority && dependenciePriority >= 0){
                    depItem->priority = dependenciePriority;
                }else{
                    depItem->priority = currentItem->priority;
                }
                depItem->seq = currentItem->seq;
                depItem->next = currentItem;
                TaskQueue::heapArray[0] = depItem;
            }
        }
};

/*
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
    std::cout << "Deleted first 3" << std::endl;
    tasks.deleteFirstMatch(3);
    tasks.print();
    std::cout << "Deleted first 5" << std::endl;
    tasks.deleteFirstMatch(5);
    tasks.print();
    std::cout << "Deleted first 1" << std::endl;
    tasks.deleteFirstMatch(1);
    tasks.print();
    std::cout << "Change priority on 1 to 99" << std::endl;
    tasks.changePriorityOfFirstMatch(1, 99);
    tasks.print();
    std::cout << "Change priority on 3 to 0" << std::endl;
    tasks.changePriorityOfFirstMatch(3, 0);
    tasks.print();
    while(!tasks.empty()){
        std::cout << tasks.pop() << std::endl;
    }
}
*/

#endif // TASKQUEUE_H_INCLUDED
