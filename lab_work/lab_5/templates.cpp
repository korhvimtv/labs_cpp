#include "../libs.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"

void printLAMenu() {
    std::cout << "LOW AVERAGE MENU\n1. Print\n2. Amount\n0. Exit\n";
}

void lowAverageOptions (LowAverageList<Student> studList) {
    int optChoice;
    while(true) {
        system("cls");
        printLAMenu();
        std::cout << " > ";
        std::cin >> optChoice;
        switch (optChoice) {
            case 1:
                system("cls");
                studList.printAll();
                _getch();
                break;
            case 2:
                system("cls");
                studList.printAll();
                std::cout << "\n";
                studList.size();
                _getch();
                break;
            case 0:
                return;
            default:
                continue;
        }
    }
}


#pragma clang diagnostic pop