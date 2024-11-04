#ifndef LAB_1_FUNC_H
#define LAB_1_FUNC_H

#include "../libs.h"

int isIntNumber(int& check);
void printMenu();
void enterUserInfo(std::vector<User>& users, sqlite3* db);
void updateUserInfo(std::vector<User>& users, int id, sqlite3* db);
void enterUserMarks(User* user, sqlite3* db);
void readAllUserInfo(const std::vector<User>& users);


#endif //LAB_1_FUNC_H
