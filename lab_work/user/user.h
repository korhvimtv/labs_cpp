#ifndef LAB_WORK_USER_H
#define LAB_WORK_USER_H

#include "../libs.h"
#include "infoProvider.h"
#include <fstream>
#include <sstream>
#include <utility>
#include "sqlite3.h"

class User {

private:
    int id;
    std::string username;
    int age;

public:
    User(int userId, std::string  userUsername, int userAge)
            : id(userId), username(std::move(userUsername)), age(userAge) {}

    ~User() = default;

    [[nodiscard]] int getId() const {
        return id;
    }

    [[nodiscard]] std::string getUsername() const {
        return username;
    }

    void setUsername(std::string_view newUsername) {
        username = std::string(newUsername);
    }

    [[nodiscard]] int getAge() const {
        return age;
    }

    void setAge(int newAge) {
        age = newAge;
    }

    [[nodiscard]] virtual std::string getInfo() const {
        std::ostringstream oss;
        oss << "User [ID: " << id << ", Username: " << username
            << ", Age: " << age << "], " ;
        return oss.str();
    }

    [[nodiscard]] std::string to_json() const {
        std::ostringstream oss;
        oss << R"({"id": )" << id
            << R"(, "username": ")" << username
            << R"(", "age": )" << age << "}";
        return oss.str();
    }
};

class Person {
private:
    std::string name;
    std::string address;
    std::string phone;

public:
    Person(std::string personName, std::string personAddress, std::string personPhone)
            : name(std::move(personName)), address(std::move(personAddress)), phone(std::move(personPhone)) {}

    [[nodiscard]] std::string getName() const {
        return name;
    }

    void setName(std::string_view newName) {
        name = std::string(newName);
    }

    [[nodiscard]] std::string getAddress() const {
        return address;
    }

    void setAddress(std::string_view newAddress) {
        address = std::string(newAddress);
    }

    [[nodiscard]] std::string getPhone() const {
        return phone;
    }

    void setPhone(std::string_view newPhone) {
        phone = std::string(newPhone);
    }

    [[nodiscard]] std::string to_json() const {
        std::ostringstream oss;
        oss << R"({"name": ")" << name
            << R"(", "address": ")" << address
            << R"(", "phone": ")" << phone << R"("})";
        return oss.str();
    }

    [[nodiscard]] virtual std::string getInfo() const {
        std::ostringstream oss;
        oss << "Person [Name: " << name << ", Address: " << address
            << ", Phone: " << phone << "], " ;
        return oss.str();
    }
};

class Student : public InfoProvider, public User, public Person {
    friend Student* findUser(std::vector<Student>& users, int id);

private:
    int group;
    std::vector<int> marks;
    std::string org;

public:
    Student(int userId, std::string  userUsername, int userAge, int studGroup,
            const std::vector<int>& studMarks, std::string studOrg, std::string personName,
            std::string personAddress, std::string personPhone)
            : User(userId, userUsername, userAge), Person(personName, personAddress, personPhone),
            group(studGroup), marks(studMarks), org(std::move(studOrg)) {}

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
        marks = newMarks;
    }

    [[nodiscard]] std::string getOrg() const {
        return org;
    }

    void setOrg(std::string_view newOrg) {
        org = std::string(newOrg);
    }

    [[nodiscard]] std::string marksToString() const {
        std::ostringstream oss;
        for (size_t i = 0; i < marks.size(); ++i) {
            if (i != 0) {
                oss << ", ";
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
        return getAverage() <=> other.getAverage();
    }

    [[nodiscard]] std::string getInfo() const override {
        std::ostringstream oss;

        oss << User::getInfo() << "\n";
        oss << Person::getInfo() << "\n"
            << "Student [Organisation: " << org
            << ", Group: " << group
            << ", Marks: [" << marksToString()
            << "], Average: " << getAverage() << "]\n";
        return oss.str();
    }

    [[nodiscard]] virtual std::string to_json() const {
        std::ostringstream oss;
        oss << "{";
        oss << R"("user": )" << User::to_json() << ", ";
        oss << R"("person": )" << Person::to_json() << ", ";
        oss << R"("group": )" << group << ", ";
        oss << R"("organisation": ")" << org << R"(", )";
        oss << R"("marks": [)";
        for (size_t i = 0; i < marks.size(); ++i) {
            if (i != 0) {
                oss << ", ";
            }
            oss << marks[i];
        }
        oss << "]}";
        return oss.str();
}

};

class StudentCounter {
public:
    [[nodiscard]] virtual int countStudents() const = 0;
    virtual ~StudentCounter() = default;
};

class StudentCollection : public StudentCounter {
private:
    std::vector<Student> students;

public:
    explicit StudentCollection(const std::vector<Student>& st) {
        for (const auto& student : st) {
            students.push_back(student);
        }
        std::cout << "Created StudentCollection with " << students.size() << " students." << std::endl;
    };

    [[nodiscard]] int countStudents() const override {
        return static_cast<int>(students.size());
    }

    void displayAllStudents() const {
        for (const auto& student : students) {
            std::cout << student.getInfo() << std::endl;
        }
    }
};


void createUser(std::vector<Student>& users, int id, const std::string& username, const std::string& org,
                int age, int group, const std::string& name, const std::string& address, const std::string& phone, sqlite3* db);
bool readUsers(const std::vector<Student>& users);
void updateUser(std::vector<Student>& users, int id, const std::string& newName, int newAge, int newGroup,
                sqlite3* db);
void deleteUser(std::vector<Student>& users, int id, sqlite3* db);
void updateUserOrganisation(std::vector<Student>& users, int id, const std::string& newOrg, sqlite3* db);
User* findBestUser(std::vector<Student>& users);

#endif //LAB_WORK_USER_H
