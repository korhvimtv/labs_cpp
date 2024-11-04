#ifndef LAB_2_DBSQLITE_H
#define LAB_2_DBSQLITE_H

void dbCreate (sqlite3* db);
void saveToDatabase(const User* obj ,sqlite3* db);
void updateUserInDatabase(const User* obj, sqlite3* db);
void loadAllUsersFromDatabase(std::vector<User>& users, sqlite3* db);
void addMarksToUser(int userId, const std::vector<int>& marks, sqlite3* db);
void deleteUserById(int userId, sqlite3* db);

std::vector<int> stringToVector(const std::string& marksStr);

#endif //LAB_2_DBSQLITE_H
