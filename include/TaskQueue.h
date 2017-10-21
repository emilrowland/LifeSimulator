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

template <class T>
class TaskQueue{
    private:
        int maxSize;
        int currentSeq = 0;
        int endPos = 0;
        struct item {
            int priority;
            T obj;
            int seq;
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
        TaskQueue(int predSize=100){
            TaskQueue::maxSize = predSize;
            TaskQueue::heapArray = new item*[predSize];
        }
        void print(){
            for(int i = 0; i < TaskQueue::endPos; i++){
                std::cout << "Priority: " << TaskQueue::heapArray[i]->priority << " Seq: " << TaskQueue::heapArray[i]->seq << std::endl;
            }
        }
    private:
        void bubbleUp(int index){//Sort upwards
            if(index == 0){
                return;
            }
            int parentIndex = (index-1)/2; //Floor 2.8 => 2
            if(*TaskQueue::heapArray[parentIndex] > *TaskQueue::heapArray[index]){
                item* temp = heapArray[parentIndex];
                TaskQueue::heapArray[parentIndex] = TaskQueue::heapArray[index];
                TaskQueue::heapArray[index] = temp;
                TaskQueue::bubbleUp(parentIndex);
            }
        }
        void bubbleDown(int index){
            int leftChildIndex = 2*index + 1;
            int rightChildIndex = 2*index + 2;
            if(leftChildIndex >= TaskQueue::endPos){
                return; //index is a leaf
            }
            int minIndex = index;
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
        void push(T obj, int priority){
            item* i = new item();
            i->obj = obj;
            i->priority = priority;
            i->seq = TaskQueue::currentSeq++;
            TaskQueue::heapArray[TaskQueue::endPos++] = i;
            TaskQueue::bubbleUp(TaskQueue::endPos-1);
        }
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
        bool isEmpty(){
            if(TaskQueue::endPos == 0){
                TaskQueue::currentSeq = 0;
                return true;
            }
            return false;
        }
        virtual ~TaskQueue(){
            while(!TaskQueue::isEmpty()){
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
                while(currentItem->next){
                    if(obj == currentItem->next->obj){
                        //Found
                        item* temp = currentItem->next;
                        currentItem->next = temp->next;
                        delete temp;
                        TaskQueue::bubbleDown(i); // FIX test for up or down.
                        return true;
                    }
                    item* currentItem = currentItem->next;
                }
            }
            return false;
        }
        /*bool changePriorityOfFirstMatch(T obj){
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
                while(currentItem->next){
                    if(obj == currentItem->next->obj){
                        //Found
                        item* temp = currentItem->next;
                        currentItem->next = temp->next;
                        delete temp;
                        TaskQueue::bubbleDown(i);
                        return true;
                    }
                    item* currentItem = currentItem->next;
                }
            }
            return false;
        }*/
};

#endif // TASKQUEUE_H_INCLUDED
