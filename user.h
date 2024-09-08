#ifndef LAB_1_USER_H
#define LAB_1_USER_H

#include <iostream>
#include <string>

class User {
    int id;
    std::string username;
    int age;
    int group;

public:
    User(int userId, std::string userUsername, int userAge, int userGroup) : id(userId), username(userUsername), age(userAge), group(userGroup) {}
    ~User() {}

    int getId();
    void setId(int newId);

    std::string getUsername();
    void setUsename(std::string newUsername);

    int getAge();
    void setAge(int newAge);

    int getGroup();
    void setGroup(int newGroup);


};

void createUser(std::vector<User>& users, int id, std::string username, int age, int group);
void readUsers(const std::vector<User>& users);
void updateUser(std::vector<User>& users, int id, std::string newName, int newAge, int newGroup);
void deleteUser(std::vector<User>& users, int id);

#endif //LAB_1_USER_H
