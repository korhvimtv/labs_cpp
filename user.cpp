#include "libs.h"

int User::getId() {
    return id;
}

void User::setId(int newId) {
    id = newId;
}

std::string User::getUsername() {
    return username;
}

void User::setUsename(std::string newUsername) {
    username = newUsername;
}

int User::getAge() {
    return age;
}

void User::setAge(int newAge) {
    age = newAge;
}

int User::getGroup() {
    return group;
}

void User::setGroup(int newGroup) {
    group = newGroup;
}

void createUser(std::vector<User>& users, int id, std::string username, int age, int group) {
    User newUser(id, username, age, group);
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
    for (auto user : users) {
        std::cout << "ID: " << user.getId() << ", Name: " << user.getUsername() << ", Age: " << user.getAge()
                  << ", Group: " << user.getGroup() << std::endl;
    }
}

void updateUser(std::vector<User>& users, int id, std::string newName, int newAge, int newGroup) {
    for (auto& user : users) {
        if (user.getId() == id) {
            user.setUsename(newName);
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