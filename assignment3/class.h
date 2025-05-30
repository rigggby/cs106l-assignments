#ifndef CLASS_H
#define CLASS_H

#include <chrono>
#include <iostream>
#include <algorithm>

template <typename T>
concept Printable = requires(T t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
};

template <Printable T>
class DataWithAccessCounter {
    public:
        explicit DataWithAccessCounter() = default;
        
        DataWithAccessCounter(T data) {
            this->data = data;
            accessCount = 0;
            instantiateTime = std::chrono::system_clock::now();
        }
        
        T getData() {
            incrementAccessCount();
            return data;
        }

        void setData(T newData) {
            this->data = newData;
            accessCount = 0;
            instantiateTime = std::chrono::system_clock::now();
        }

        void print() const {
            std::cout << "Data: " << data << ", Access Count: " << accessCount << std::endl;
        }

    private:
        T data;
        double accessCount;
        std::chrono::time_point<std::chrono::system_clock> instantiateTime;

        void incrementAccessCount() {
            auto elapsed = std::chrono::system_clock::now() - instantiateTime;
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count();
            accessCount += 1.0 / std::max(1.0, static_cast<double>(elapsedSeconds));
        }
};

#endif // CLASS_H
