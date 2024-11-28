#ifndef LAB_1_FUNC_H
#define LAB_1_FUNC_H

#include "../libs.h"

int isIntNumber(int& check);
void printMenu();
void enterUserInfo(std::vector<Student>& users, sqlite3* db, std::vector<InfoProvider*>& infoProviders);
void updateUserInfo(std::vector<Student>& users, int id, sqlite3* db, std::vector<InfoProvider*> info);
void enterUserMarks(Student* user, sqlite3* db);
void readAllUserInfo(const std::vector<Student>& users);

#endif //LAB_1_FUNC_H
