#include "../libs.h"

void createUser(std::vector<Student>& users, int id, const std::string& username, const std::string& org,
                int age, int group, const std::string& name, const std::string& address, const std::string& phone, sqlite3* db) {
    std::vector<int> marks;
    auto newUser = std::make_unique<Student>(id, username, age,group,
                                             marks, org, name, address, phone);
    users.push_back(*newUser);
    saveToDatabase(newUser.get(), db);
    std::cout << "\nUser created" << std::endl;
}

bool readUsers(const std::vector<Student>& users) {
    system("cls");
    if(users.empty()){
        std::cout << "List of users is empty!";
        _getch();
        return false;
    }
    std::cout << "List of users:" << std::endl;
    for (auto& user : users) {
        std::cout << "ID: " << user.getId() << ", Name: " << user.getUsername() << ", Age: " << user.getAge()
                  << ", Group: " << user.getGroup() << std::endl;
    }

    return true;
}

void updateUser(std::vector<Student>& users, int id, const std::string& newName, int newAge,
                int newGroup, sqlite3* db) {
    for (auto& user : users) {
        if (user.getId() == id) {
            user.setUsername(newName);
            user.setAge(newAge);
            user.setGroup(newGroup);
            std::cout << "User updated: " << newName << std::endl;
            updateUserInDatabase(&user, db);
            _getch();
            return;
        }
    }
    std::cout << "User with ID " << id << " not found." << std::endl;
    _getch();
}

void deleteUser(std::vector<Student>& users, int id, sqlite3* db) {
    size_t usersLen = users.size();

    for (auto i  = 0; i < usersLen; i++) {
        if (users[i].getId() == id) {
            std::cout << "User deleted: " << users[i].getUsername() << std::endl;
            deleteUserById(id, db);
            users.erase(users.begin() + i);
            _getch();
            return;
        }
    }
    std::cout << "User not found";
    _getch();
}

User* findBestUser(std::vector<Student>& users) {
    if (users.empty()) return nullptr;

    Student* bestUser = &users[0];
    for (auto& user: users) {
        if (user > *bestUser) {
            bestUser = &user;
        }
    }
    std::cout << "Best student: " << bestUser->getId() << " " << bestUser->getUsername() << "\nAverage score: " << bestUser->getAverage();
    _getch();
    return bestUser;
}

void updateUserOrganisation(std::vector<Student>& users, int id, const std::string& newOrg, sqlite3* db) {
    for (auto& user : users) {
        if (user.getId() == id) {
            std::cout << user.getName() << "\n\n";
            _getch();
            user.setOrg(newOrg);
            std::cout << user.getName() << "\n\n";
            _getch();
            std::cout << "User organisation updated: " << user.getId() << std::endl;
            updateUserInDatabase(&user, db);
            _getch();
            return;
        }
    }
}

