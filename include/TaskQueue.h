#ifndef TASKQUEUE_H_INCLUDED
#define TASKQUEUE_H_INCLUDED

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
            item* next;
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
            T ret = res->obj;
            delete res;
            TaskQueue::heapArray[0] = TaskQueue::heapArray[TaskQueue::endPos-1];
            TaskQueue::endPos--;
            TaskQueue::bubbleDown(0);
            return ret;
        }

};

#endif // TASKQUEUE_H_INCLUDED
