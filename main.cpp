#include "libs.h"

int main() {
    std::vector<User> users;
    int menuChoice;
    User* tempUser;
   while(true) {
       system("cls");
       printMenu();
       std::cout << "\n > ";
       std::cin >> menuChoice;
       switch (menuChoice) {
           case 1:
               system("cls");
               enterUserInfo(users);
               break;
           case 2:
               system("cls");
               readUsers(users);
               _getch();
               break;
           case 3:
               system("cls");
               readUsers(users);
               updateUserInfo(users);
               break;
           case 4:
               system("cls");
               readUsers(users);
               deleteUserInfo(users);
               break;
           case 5:
               system("cls");
               int id;
               std::cout << "\nEnter users' ID you want update marks for: ";
               std::cin >> id;
               tempUser = findUser(users, id);
               if(tempUser!= nullptr) {
                   enterUserMarks(tempUser);
               }
               else{
                   std::cout << "\nUser with such ID doesn't exist";
                   _getch();
               }

               break;
           case 6:
               system("cls");
               readAllUserInfo(users);
               break;
           case 0:
               return 0;
           default:
               system("cls");
               std::cout << "Invalid value.";
               break;
       }
   }
}

