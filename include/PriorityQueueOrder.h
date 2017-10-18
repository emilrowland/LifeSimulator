#ifndef PRIORITYQUEUEORDER_H
#define PRIORITYQUEUEORDER_H

#include <queue>

template <class T>
class PriorityQueueOrder{
    private:
        int sequence = 0;

        struct item {
            int priority;
            T obj;
            int seq;
            bool operator<(const item& other)const{
                if(priority == other.priority){
                    return seq > other.seq;
                }
                return priority > other.priority;
            }
        };

        std::priority_queue<item> priorityQueue;
    public:
        void push(T obj, int priority){
            item i;
            i.obj = obj;
            i.priority = priority;
            i.seq = PriorityQueueOrder::sequence++;
            PriorityQueueOrder::priorityQueue.push(i);
        }

        T top(){return PriorityQueueOrder::priorityQueue.top().obj;}

        void pop(){
            PriorityQueueOrder::priorityQueue.pop();
            if(priorityQueue.empty()){
                PriorityQueueOrder::sequence = 0;
            }
        }

        bool empty(){return PriorityQueueOrder::priorityQueue.empty();}
};

#endif // PRIORITYQUEUEORDER_H
