#include "../libs.h"

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
    std::cout << "1. Create new user\n2. Read all users info\n3. Update user info\n4. Delete user\n5. Enter marks\n6. Enter full user info (ID)\n7. Search the best student\n0. Exit";
}

void enterUserInfo(std::vector<User>& users, sqlite3* db) {
    int id;
    int age;
    int group;
    std::string username;
    std::vector<int> marks;
    std::cin.clear();
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter id: ";
    isIntNumber(id);
    std::cout << "Enter age: ";
    isIntNumber(age);
    std::cout << "Enter group: ";
    std::cin >> group;
    createUser(users, id, username, age, group, marks, db);
}

void updateUserInfo(std::vector<User>& users, int id, sqlite3* db) {
    int age;
    int group;
    std::string username;

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cout << "Enter group: ";
    std::cin >> group;
    updateUser(users, id, username, age, group, db);
}

User* findUser(std::vector<User>& users, int id){
    for(auto& user: users) {
        if(user.id == id) {
            return &user;
        }
    }
    return nullptr;
}

void enterUserMarks(User* user, sqlite3* db){
    int mark;

    std::vector<int> newMarks;
    std::cout << "Enter marks (-1 to exit): ";


    while(true) {
        if(std::cin >> mark) {
            if(mark != -1) {
                newMarks.push_back(mark);
            }
            else {
                addMarksToUser(user->getId(), newMarks, db);
                break;
            }
        }
        else{
            std::cout << "Enter valid mark, to end type -1\n";
            std::cin.clear();
            std::cin.ignore(33000, '\n');
        }
    }

    std::cin.clear();

    user->setMarks(newMarks);
}

void readIdAndName(const std::vector<User>& users) {
    system("cls");
    if(users.empty()){
        std::cout << "List of users is empty!";
        _getch();
        return;
    }
    std::cout << "List of users:" << std::endl;
    for (auto& user : users) {
        std::cout << "ID: " << user.getId() << ", Name: " << user.getUsername() << std::endl;
    }
}

void readAllUserInfo(const std::vector<User>& users){
    int id;

    readIdAndName(users);
    std::cout << "Enter users' ID you want to check: ";
    std::cin >> id;

    for (auto& user : users) {
        if (user.getId() == id) {
            std::vector<int> marks;
            marks = user.getMarks();
            double sum = 0;
            size_t count = marks.size();
            for (int num: marks) {
                sum += num;
            }
            std::cout << "ID: " << user.getId() << ", Name: " << user.getUsername() << ", Age: " << user.getAge()
                      << ", Group: " << user.getGroup();
            std::cout << "\n Marks: ";
            for (const auto &mark: marks) {
                std::cout << ' ' << mark;
            }
            std::cout << " Average score: " << sum / double(count);

        }
    }
    _getch();
}