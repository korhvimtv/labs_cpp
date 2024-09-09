#ifndef LAB_1_USER_H
#define LAB_1_USER_H

#include "../libs.h"

class User {
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
};

void createUser(std::vector<User>& users, int id, const std::string& username, int age, int group, const std::vector<int>& marks);
bool readUsers(const std::vector<User>& users);
void updateUser(std::vector<User>& users, int id, const std::string& newName, int newAge, int newGroup);
void deleteUser(std::vector<User>& users, int id);


#endif //LAB_1_USER_H
