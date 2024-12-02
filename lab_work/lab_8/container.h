#ifndef LAB_WORK_CONTAINER_H
#define LAB_WORK_CONTAINER_H

#include "../libs.h"

template <typename Y>
class Container {
private:
    std::vector<Y> data;
public:
    class Iterator {
    private:
        Y* pointer;
    public:
        explicit Iterator(Y* ptr) : pointer(ptr) {}

        Iterator& operator++() {
            pointer++; return *this;
        }

        Iterator& operator--() {
            pointer--; return *this;
        }

        Y& operator*() {
            return *pointer;
        }
        bool operator!=(const Iterator& other) const {
            return pointer != other.pointer;
        }

    };

    void add (const Y& user) {
        data.push_back(user);
    }

    void remove(int id) {
        
    }
};
#endif //LAB_WORK_CONTAINER_H
