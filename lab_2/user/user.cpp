#include "../libs.h"

int User::getId() const {
    return id;
}

void User::setId(int newId) {
    this->id = newId;
}

std::string User::getUsername() const {
    return username;
}

void User::setUsername(std::string_view newUsername) {
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
    this->marks = newMarks;
}

void createUser(std::vector<User>& users, int id, const std::string& username, int age, int group, const std::vector<int>& marks, sqlite3* db) {
    User newUser(id, username, age, group, marks);
    users.push_back(newUser);
    saveToDatabase(&newUser, db);
    std::cout << "\nUser created" << std::endl;
}

bool readUsers(const std::vector<User>& users) {
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

void updateUser(std::vector<User>& users, int id, const std::string& newName, int newAge, int newGroup, sqlite3* db) {
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

void deleteUser(std::vector<User>& users, int id, sqlite3* db) {
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

User* findBestUser(std::vector<User>& users) {
    if (users.empty()) return nullptr;

    User* bestUser = &users[0];
    for (auto& user: users) {
        if (user > *bestUser) {
            bestUser = &user;
        }
    }
    std::cout << "Best student: " << bestUser->getId() << " " << bestUser->getUsername() << "\nAverage score: " << bestUser->getAverage();
    _getch();
    return bestUser;
}



