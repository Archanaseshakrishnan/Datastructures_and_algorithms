#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>

using namespace std;

class DiningPhilosophers {
private:
    mutex mtx[5];
    
public:
    DiningPhilosophers() { }
    void wantsToEat(int philosopher, function<void()> pickLeftFork, function<void()> pickRightFork, function<void()> eat, function<void()> putLeftFork, function<void()> putRightFork) {
        int left = philosopher;
        int right = (philosopher + 1) % 5;
        
        unique_lock<mutex> lck1(mtx[left], defer_lock); // defer_lock: init lck1 without locking mtx
        unique_lock<mutex> lck2(mtx[right], defer_lock);
        
        if(philosopher % 2 == 0){
            lck1.lock(); // do NOT use std::lock(lck1, lck2)
            lck2.lock();
            pickLeftFork(); pickRightFork();
        }
		else{
            lck2.lock();
            lck1.lock();
            pickRightFork(); pickLeftFork();
        }
        eat(); putRightFork(); putLeftFork();
        // lck1 & lck2 are auto released after this line
    }
};

int main() {
    DiningPhilosophers dp;
    
    vector<thread> threads;
    
    // Lambda functions for fork and eating actions
    auto pickLeftFork = []() { cout << "Picks left fork\n"; };
    auto pickRightFork = []() { cout << "Picks right fork\n"; };
    auto eat = []() { cout << "Eats\n"; };
    auto putLeftFork = []() { cout << "Puts left fork\n"; };
    auto putRightFork = []() { cout << "Puts right fork\n"; };
    
    cout << "Dining Philosophers Problem - Deadlock Free Solution\n";
    cout << "======================================================\n\n";
    
    // Create threads for each philosopher
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&dp, i, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork]() {
            cout << "Philosopher " << i << " starts thinking\n";
            dp.wantsToEat(i, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork);
            cout << "Philosopher " << i << " finishes eating\n";
        });
    }
    
    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    
    cout << "\nAll philosophers have finished eating. No deadlock!\n";
    
    return 0;
}
