#ifndef LAB_WORK_TEMPLATES_H
#define LAB_WORK_TEMPLATES_H

#include "../libs.h"

template<typename Container, typename Comparator>
void sortDescending(Container& container, Comparator comp) {
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < container.size(); ++i) {
            if (!comp(container[i - 1], container[i])) {
                std::swap(container[i - 1], container[i]);
                swapped = true;
            }
        }
    } while (swapped);
}

template <typename T>
class LowAverageList {
private:
    std::vector<T> items;

public:
    void add(const T& item) {
        if (item.getAverage() <= 3.0) {
            items.push_back(item);
        }
    }

    [[nodiscard]] size_t size() const {
        std::cout << "Amount of students: " << items.size();
        return items.size();
    }

    void printAll() const {
        if (items.empty()) {
            std::cout << "No students with an average score of 3 or below.\n";
            return;
        }
        for (const auto& item : items) {
            std::cout << item.getInfo() << "\n";
        }
    }

    [[nodiscard]] const T& get(size_t index) const {
        if (index >= items.size()) {
            throw std::out_of_range("Index out of range");
        }
        return items[index];
    }

    void remove(size_t index) {
        if (index >= items.size()) {
            throw std::out_of_range("Index out of range");
        }
        items.erase(items.begin() + index);
    }
};

template <typename T>
void findLowAverageStudents(const std::vector<Student>& users, LowAverageList<T>& lowAverageList) {
    for (const auto& user : users) {
        lowAverageList.add(user);
    }
}

void lowAverageOptions (LowAverageList<Student> studList);

#endif //LAB_WORK_TEMPLATES_H