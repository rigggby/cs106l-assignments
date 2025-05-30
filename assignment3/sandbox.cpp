/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */

#include "class.h"
#include <thread>
#include <chrono>

void sandbox() {
    DataWithAccessCounter<int> data(42);
    data.print(); // Should print: Data: 42, Access Count: 0

    // Sleep for 2 seconds to simulate time passing
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Accessing data: " << data.getData() << std::endl;
    data.print();

    data.setData(100);
    data.print(); 

    std::cout << "Accessing data again: " << data.getData() << std::endl;
    data.print(); 
}
