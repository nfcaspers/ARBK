//
// Created by noelc on 03/01/2026.
//

#ifndef P5_SEMAPHORE_H
#define P5_SEMAPHORE_H
#include <condition_variable>
#include <mutex>


class Semaphore {
    int count;
    std::mutex mutex;
    std::condition_variable condition_variable;
public:
    explicit Semaphore(const int count): count(count) {};
    void wait() {
        std::unique_lock lock(mutex);
        //Wenn count ≤ 0 → Keine Kapazität verfügbar
        //Warten bevor Zugriff auf critical region
        if (count <= 0) {
            //Monitor: Ausführender Thread wird so lange blockiert, bis Benachrichtigung zur Freigabe
            condition_variable.wait(lock);
        }
        //Wenn count > 0 → Kapazität verfügbar
        //Zugriff auf critical region
        if (count > 0) {
            count--;
        }
    }
    void signal() {
        std::unique_lock lock(mutex);
        count++;
        //Falls mit Verlassen der critical region jetzt wieder Kapazität verfügbar ist,
        //benachrichtige einen der wartenden Threads
        if (count > 0) {
            condition_variable.notify_one();
        }
    }


};


#endif //P5_SEMAPHORE_H