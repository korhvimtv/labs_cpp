#include "../libs.h"

void countUsersInOrganisation(const std::span<InfoProvider*>& users, const std::string& organisation) {
    int count = 0;

    for (const auto* user : users) {
        const auto* student = dynamic_cast<const Student*>(user);
        if (student && student->getOrg() == organisation) {
            ++count;
        }
    }

    std::cout << "There are " << count << " students in " << organisation << "." << std::endl;
}
