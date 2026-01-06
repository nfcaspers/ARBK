#include <iostream>
#include <thread>
#include <mutex>
#include "semaphore.h"

std::mutex m;
Semaphore s(1);

void a1_print_lowercase() {
    for(char c = 'a'; c <= 'z'; ++c) {
        std::cout << c << std::endl;
    }
}

void a1_print_numbers() {
    for (int i = 0; i < 33; i++) {
        std::cout << i << std::endl;
    }
}

void a1_print_uppercase() {
    for(char c = 'A'; c <= 'Z'; ++c) {
        std::cout << c << std::endl;
    }
}

void aufgabe_1() {
    std::thread t1(a1_print_lowercase);
    std::thread t2(a1_print_numbers);
    std::thread t3(a1_print_uppercase);

    t1.join();
    t2.join();
    t3.join();
}

void a2_print_lowercase() {
    m.lock();
    a1_print_lowercase();
    m.unlock();
}

void a2_print_numbers() {
    m.lock();
    a1_print_numbers();
    m.unlock();
}

void a2_print_uppercase() {
    m.lock();
    a1_print_uppercase();
    m.lock();
}

void aufgabe_2() {
    std::thread t1(a2_print_lowercase);
    std::thread t2(a2_print_numbers);
    std::thread t3(a2_print_uppercase);

    t1.join();
    t2.join();
    t3.join();
}

void a3_print_lowercase() {
    s.wait();
    a1_print_lowercase();
    s.signal();
}

void a3_print_numbers() {
    s.wait();
    a1_print_numbers();
    s.signal();
}

void a3_print_uppercase() {
    s.wait();
    a1_print_uppercase();
    s.signal();
}

void aufgabe_3() {
    std::thread t1(a3_print_lowercase);
    std::thread t2(a3_print_numbers);
    std::thread t3(a3_print_uppercase);

    t1.join();
    t2.join();
    t3.join();
}

int main() {
    int aufgabe = 1;
    std::cout << "Aufgabe: ";
    std::cin >> aufgabe;
    switch(aufgabe) {
        case 1:
            aufgabe_1();
            break;
        case 2:
            aufgabe_2();
            break;
        case 3:
        default:
            aufgabe_3();
            break;
    }
    return 0;
}