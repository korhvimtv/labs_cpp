#include "libs.h"

int main() {
    std::cin.clear();
    std::vector<User> users;
    int menuChoice;
    int id;
    User* tempUser;

    sqlite3* db;
    if (sqlite3_open("students.sqlite", &db) != SQLITE_OK) {
        std::cerr << "DB ERROR!: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    dbCreate(db);
    loadAllUsersFromDatabase(users, db);

   while(true) {
       system("cls");
       printMenu();
       std::cout << "\n > ";
       std::cin >> menuChoice;
       switch (menuChoice) {
           case 1:
               system("cls");
               enterUserInfo(users, db);

               break;
           case 2:
               system("cls");
               readUsers(users);
               _getch();
               break;
           case 3:
               system("cls");
               if (readUsers(users)) {
               std::cout << "\nEnter users' ID you want update for: ";
               isIntNumber(id);
               updateUserInfo(users, id, db);
               }
               break;
           case 4:
               system("cls");
               if (readUsers(users)){
                   std::cout << "Enter users' ID you want to delete: ";
                   isIntNumber(id);
                   deleteUser(users, id, db);
               }
               break;
           case 5:
               system("cls");
               readUsers(users);
               if (users.empty()) {
                   std::cout << "List of users is empty!";
                   _getch();
                   break;
               }
               std::cout << "\nEnter users' ID you want update marks for: ";
               isIntNumber(id);
               tempUser = findUser(users, id);
               if (tempUser != nullptr) {
                   enterUserMarks(tempUser, db);
               } else {
                   std::cout << "\nUser with such ID doesn't exist";
                   _getch();
                   break;
               }
               break;
           case 6:
               system("cls");
               readAllUserInfo(users);
               break;
           case 7:
               system("cls");
               findBestUser(users);
               break;
           case 0:
               sqlite3_close(db);
               return 0;
           default:
               system("cls");
               std::cout << "Invalid value.";
               break;
       }
   }
}

