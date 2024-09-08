#include "libs.h"

int isIntNumber(int& check){
    while(true){
        std::cin >> check;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else {
           return check;
        }
    }
}

void printMenu(){
    std::cout << "Menu:" << "\n";
    std::cout << "1. Create new user\n2. Read all users info\n3. Update user info\n4. Delete user\n0. Exit";
}

void enterUserInfo(std::vector<User>& users){
    int id;
    int age;
    int group;
    std::string username;
    std::vector<int> marks;
    rewind(stdin);
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter id: ";
    isIntNumber(id);
    std::cout << "Enter age: ";
    isIntNumber(age);
    std::cout << "Enter group: ";
    std::cin >> group;
    createUser(users, id, username, age, group, marks);
}

void updateUserInfo(std::vector<User>& users){
    if(users.empty()){
        std::cout << "List of users is empty!";
        _getch();
        return;
    }

    int id;
    int age;
    int group;
    std::string username;
    std::cout << "Enter users' ID you want to update: ";
    std::cin >> id;

    for (auto user : users) {
        if(id != user.getId()){
            std::cout << "User with ID " << id << " not found." << std::endl;
            _getch();
            return;
        }
    }

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cout << "Enter group: ";
    std::cin >> group;
    updateUser(users, id, username, age, group);
}

void deleteUserInfo(std::vector<User>& users){
    if(users.empty()){
        std::cout << "List of users is empty!";
        _getch();
        return;
    }
    int id;
    std::cout << "Enter users' ID you want to delete: ";
    std::cin >> id;

    for (auto user : users) {
        if(id != user.getId()){
            std::cout << "User with ID " << id << " not found." << std::endl;
            _getch();
            return;
        }
    }

    deleteUser(users, id);
}

