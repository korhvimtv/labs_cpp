#include "libs.h"

int main() {
    std::cin.clear();
    std::vector<Student> users;
    std::vector<StudentCollection> studCounter;
    std::vector<InfoProvider*> info;
    std::string filename;
    LowAverageList<Student> studList;
    int menuChoice;
    int id;
    std::string orgHelp;
    Student* tempUser;

    sqlite3* db;
    if (sqlite3_open("students.sqlite", &db) != SQLITE_OK) {
        std::cerr << "DB ERROR!: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    loadAllUsersFromDatabase(users, db);

   while(true) {
       system("cls");
       printMenu();
       std::cout << "\n > ";
       std::cin >> menuChoice;
       switch (menuChoice) {
           case 1:
               system("cls");
               enterUserInfo(users, db, info);

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
           case 8:
               system("cls");
               enterOrganisation(users, db);
               break;
           case 9:
               system("cls");
               std::cout << "Enter organisation name: ";
               std::cin >> orgHelp;
               countUsersInOrganisation(info, orgHelp);
               _getch();
               break;
           case 10:
               sortDescending(users, [](const Student& a, const Student& b) {
                   return a.getAverage() > b.getAverage();
               });

               std::cout << "Students sorted by average score (descending):\n";
               for (const auto& student : users) {
                   std::cout << student.getInfo() << std::endl;
               }

               _getch();

               break;
           case 11:
               findLowAverageStudents(users, studList);
               lowAverageOptions(studList);
               break;
           case 12:
               system("cls");
               std::cout << "Enter filename: ";
               std::cin >> filename;
               saveStudentsToJson(users, filename);
               std::cout << "Success!";
               _getch();
               break;
           case 13:
               system("cls");
               allStudents (users, studCounter);
               _getch();
               break;
           case 14:
               system("cls");
               readUsers(users);
               enterPersonInfo(users, db);
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

