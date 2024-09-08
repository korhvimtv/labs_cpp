#ifndef LAB_1_FUNC_H
#define LAB_1_FUNC_H

#include "libs.h"

void printMenu();
void enterUserInfo(std::vector<User>& users);
void updateUserInfo(std::vector<User>& users);
void deleteUserInfo(std::vector<User>& users);
void enterUserMarks(User* user);
User* findUser(std::vector<User>& users, int id);
void readAllUserInfo(const std::vector<User>& users);

#endif //LAB_1_FUNC_H
