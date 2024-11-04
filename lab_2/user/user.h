#ifndef LAB_1_USER_H
#define LAB_1_USER_H

#include "../libs.h"
#include <fstream>
#include <sstream>
#include "sqlite3.h"

class User {

    friend User* findUser(std::vector<User>& users, int id);

private:
    int id;
    std::string username;
    int age;
    int group;
    std::vector<int> marks;

public:
    User(int userId, const std::string& userUsername, int userAge, int userGroup, const std::vector<int>& userMarks) : id(userId), username(userUsername), age(userAge), group(userGroup), marks(userMarks) {}
    ~User() = default;
      
    int getId() const;
    void setId(int newId);

    std::string getUsername() const;
    void setUsername(std::string_view newUsername);

    int getAge() const;
    void setAge(int newAge);

    int getGroup() const;
    void setGroup(int newGroup);

    std::vector<int> getMarks() const;
    void setMarks(const std::vector<int>& newMarks);

    double getAverage() const {
        if (marks.empty()) return 0.0;
        double sum = 0;
        for (auto mark : marks) {
            sum += mark;
        }
        return sum / static_cast<double>(marks.size());
    }

    auto operator<=>(const User& other) const {
        if (getAverage() < other.getAverage()) {
            return -1;
        }
        else if (getAverage() == other.getAverage()) {
            return 0;
        }
        else {
            return 1;
        }
    }

    bool operator==(const User& other) const {
        return getAverage() == other.getAverage();
    }

    std::string marksToString() const {
        std::ostringstream oss;
        for (size_t i = 0; i < marks.size(); ++i) {
            if (i != 0) {
                oss << ",";
            }
            oss << marks[i];
        }
        return oss.str();
    }
};

void createUser(std::vector<User>& users, int id, const std::string& username, int age, int group, const std::vector<int>& marks, sqlite3* db);
void createUserFromFile(std::vector<User>& users, int id, const std::string& username, int age, int group, const std::vector<int>& marks);
bool readUsers(const std::vector<User>& users);
void updateUser(std::vector<User>& users, int id, const std::string& newName, int newAge, int newGroup, sqlite3* db);
void deleteUser(std::vector<User>& users, int id, sqlite3* db);

User* findBestUser(std::vector<User>& users);


#endif //LAB_1_USER_H
