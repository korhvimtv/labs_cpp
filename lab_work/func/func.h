#ifndef LAB_WORK_FUNC_H
#define LAB_WORK_FUNC_H

#include "../libs.h"

int isIntNumber(int& check);
void printMenu();
void enterUserInfo(std::vector<Student>& users, sqlite3* db, std::vector<InfoProvider*>& infoProviders);
void updateUserInfo(std::vector<Student>& users, int id, sqlite3* db);
void enterUserMarks(Student* user, sqlite3* db);
void readAllUserInfo(const std::vector<Student>& users);
void enterOrganisation(std::vector<Student>& users, sqlite3* db);
void allStudents (const std::vector<Student>& users, std::vector<StudentCollection>& stud);
StudentCollection createStudentCollection(const std::vector<Student>& users);
void enterPersonInfo (std::vector<Student>& users, sqlite3* db);

#endif //LAB_1_FUNC_H
