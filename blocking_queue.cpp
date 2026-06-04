#include <queue>
#include <mutex>
#include <semaphore>
#include <atomic>
#include <thread>

using namespace std;

class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity) : empty_slots(capacity), filled_slots(0), cap_so_far(0), capacity(capacity) {}

    void enqueue(int element) {
        empty_slots.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            q.push(element);
            cap_so_far++;
        }
        filled_slots.release();
    }

    void dequeue() {
        filled_slots.acquire();
        {
            std::lock_guard<std::mutex> lock(mtx);
            q.pop();
            cap_so_far--;
        }
        empty_slots.release();
    }
private:
    queue<int> q;
    mutex mtx;
    std::counting_semaphore<> empty_slots;
    std::counting_semaphore<> filled_slots;
    atomic<int> cap_so_far;
    int capacity;
};

int main() {
    BoundedBlockingQueue queue(5);
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    queue.dequeue();
    queue.dequeue();
    
    return 0;
}
