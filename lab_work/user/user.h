#ifndef LAB_1_USER_H
#define LAB_1_USER_H

#include "../libs.h"
#include "infoProvider.h"
#include <fstream>
#include <sstream>
#include <utility>
#include "sqlite3.h"

class User : public InfoProvider {

private:
    int id;
    std::string username;
    int age;

public:
    User(int userId, std::string  userUsername, int userAge) : id(userId), username(std::move(userUsername)), age(userAge) {};
    virtual ~User() = default;

    [[nodiscard]] int getId() const {
        return id;
    }

    [[nodiscard]] std::string getUsername() const {
        return username;
    }

    void setUsername(std::string_view newUsername) {
        username = newUsername;
    }

    [[nodiscard]] int getAge() const {
        return age;
    }

    void setAge(int newAge) {
        age = newAge;
    }

    [[nodiscard]] std::string getInfo() const override {
        std::ostringstream oss;
        oss << "User [ID: " << id << ", Username: " << username << ", Age: " << age << "]";
        return oss.str();
    }

    std::string to_json() const {
        std::ostringstream oss;
        oss << "{"
            << "\"id\": " << id << ", "
            << "\"username\": \"" << username << "\", "
            << "\"age\": " << age
            << "}";
        return oss.str();
    }
};

class Organisation {
private:
    std::string org;

public:
    explicit Organisation(std::string orgName) : org(std::move(orgName)) {};
    ~Organisation() = default;

    [[nodiscard]] std::string getOrg() const {
        return org;
    }

    void setOrg(std::string_view newOrg) {
        org = newOrg;
    }

    std::string to_json() const {
        std::ostringstream oss;
        oss << "{"
            << "\"organisation\": \"" << org << "\""
            << "}";
        return oss.str();
    }
};

class Student : public User, public Organisation {

    friend Student* findUser(std::vector<Student>& users, int id);

private:
    int group;
    std::vector<int> marks;

public:

    Student(int userId, const std::string& userUsername, int userAge, const std::string& orgName,
            int studGroup, const std::vector<int>& studMarks)
            : User(userId, userUsername, userAge), Organisation(orgName), group(studGroup), marks(studMarks) {};

    ~Student() override = default;

    [[nodiscard]] int getGroup() const {
        return group;
    }

    void setGroup(int newGroup) {
        group = newGroup;
    }

    [[nodiscard]] std::vector<int> getMarks() const {
        return marks;
    }

    void setMarks(const std::vector<int>& newMarks) {
        this->marks = newMarks;
    }

    [[nodiscard]] std::string marksToString() const {
        std::ostringstream oss;
        for (size_t i = 0; i < marks.size(); ++i) {
            if (i != 0) {
                oss << ",";
            }
            oss << marks[i];
        }
        return oss.str();
    }

    [[nodiscard]] double getAverage() const {
        if (marks.empty()) return 0.0;
        double sum = 0;
        for (auto mark : marks) {
            sum += mark;
        }
        return sum / static_cast<double>(marks.size());
    }

    bool operator==(const Student& other) const {
        return getAverage() == other.getAverage();
    }

    auto operator<=>(const Student& other) const {
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


    [[nodiscard]] std::string getInfo() const override {
        std::ostringstream oss;
        oss << User::getInfo() << ", Organisation: " << getOrg()
            << ", Group: " << group << ", Marks: [" << marksToString()
            << "], Average: " << getAverage();
        return oss.str();
    }

    std::string to_json() const {
        std::ostringstream oss;
        oss << "{"
            << "\"user\": " << User::to_json() << ", "
            << "\"organisation\": " << Organisation::to_json() << ", "
            << "\"group\": " << group << ", "
            << "\"marks\": [";

        for (size_t i = 0; i < marks.size(); ++i) {
            oss << marks[i];
            if (i < marks.size() - 1) oss << ", ";
        }

        oss << "]}";
        return oss.str();
    }

};

void createUser(std::vector<Student>& users, int id, const std::string& username, const std::string& org,
                int age, int group, sqlite3* db, std::vector<InfoProvider*>& info);
bool readUsers(const std::vector<Student>& users);
void updateUser(std::vector<Student>& users, int id, const std::string& newName, int newAge, int newGroup,
                sqlite3* db, std::vector<InfoProvider*> info);
void deleteUser(std::vector<Student>& users, int id, sqlite3* db);
User* findBestUser(std::vector<Student>& users);

#endif //LAB_1_USER_H
