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
    std::cout << "1. Create new user\n2. Read all users info\n3. Update user info\n4. Delete user\n5. Enter marks\n"
                 "6. Display full user info (ID)\n7. Search the best student\n8. Edit organisations info\n"
                 "9. Find organisations' members\n10. Sort\n11. Open low average list\n12. Upload to .json file\n0. Exit";
}

void enterUserInfo(std::vector<Student>& users, sqlite3* db, std::vector<InfoProvider*>& info) {
    int id;
    int age;
    int group;
    std::string username;
    std::string org;
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
    createUser(users, id, username, org, age, group, db, info);
}

void updateUserInfo(std::vector<Student>& users, int id, sqlite3* db, std::vector<InfoProvider*> info) {
    int age;
    int group;
    std::string username;

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter age: ";
    std::cin >> age;
    std::cout << "Enter group: ";
    std::cin >> group;
    updateUser(users, id, username, age, group, db, info);
}

Student* findUser(std::vector<Student>& users, int id){
    for(auto& user: users) {
        if(user.getId() == id) {
            return &user;
        }
    }
    return nullptr;
}

void enterUserMarks(Student* user, sqlite3* db){
    int mark;

    std::vector<int> newMarks;
    std::cout << "Enter marks (-1 to exit): ";


    while (true) {
        try {
            if (!(std::cin >> mark)) {
                throw UserInputException("Invalid value (expected int)");
            }

            if (mark == -1) {
                addMarksToUser(user->getId(), newMarks, db);
                break;
            }

            if (mark < 0 || mark > 10) {
                throw UserInputException("Invalid value (from 0 to 10)");
            }

            newMarks.push_back(mark);
        }
        catch (const UserInputException& e) {
            std::cerr << "Error: " << e.what() << "\nTry again: ";
            std::cin.clear();
            std::cin.ignore(33000, '\n');
        }
    }

    std::cin.clear();
    user->setMarks(newMarks);
}

void readIdAndName(const std::vector<Student>& users) {
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

void readAllUserInfo(const std::vector<Student>& users){
    int id;

    readIdAndName(users);
    std::cout << "Enter users' ID you want to check: ";
    std::cin >> id;

    for (const auto& user : users) {
        if (user.getId() == id) {
            std::cout << user.getInfo() << std::endl;
            break;
        }
    }
    _getch();
}