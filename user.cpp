#include "libs.h"

int User::getId() const {
    return id;
}

void User::setId(int newId) {
    id = newId;
}

std::string User::getUsername() const {
    return username;
}

void User::setUsername(const std::string& newUsername) {
    username = newUsername;
}

int User::getAge() const {
    return age;
}

void User::setAge(int newAge) {
    age = newAge;
}

int User::getGroup() const {
    return group;
}

void User::setGroup(int newGroup) {
    group = newGroup;
}

std::vector<int> User::getMarks() const {
    return marks;
}

void User::setMarks(const std::vector<int>& newMarks) {
    marks = newMarks;
}

void createUser(std::vector<User>& users, int id, const std::string& username, int age, int group, const std::vector<int>& marks) {
    User newUser(id, username, age, group, marks);
    users.push_back(newUser);
    std::cout << "\nUser created" << std::endl;
}

void readUsers(const std::vector<User>& users) {
    system("cls");
    if(users.empty()){
        std::cout << "List of users is empty!";
        _getch();
        return;
    }
    std::cout << "List of users:" << std::endl;
    for (auto& user : users) {
        std::cout << "ID: " << user.getId() << ", Name: " << user.getUsername() << ", Age: " << user.getAge()
                  << ", Group: " << user.getGroup() << std::endl;
    }
}

void updateUser(std::vector<User>& users, int id, const std::string& newName, int newAge, int newGroup) {
    for (auto& user : users) {
        if (user.getId() == id) {
            user.setUsername(newName);
            user.setAge(newAge);
            user.setGroup(newGroup);
            std::cout << "User updated: " << newName << std::endl;
            _getch();
            return;
        }
    }
    std::cout << "User with ID " << id << " not found." << std::endl;
    _getch();
}

void deleteUser(std::vector<User>& users, int id) {
    if(users.empty()){
        std::cout << "List of users is empty!";
        _getch();
        return;
    }


    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->getId() == id) {
            std::cout << "User deleted: " << it->getUsername() << std::endl;
            users.erase(it);
            _getch();
            return;
        }
    }
}