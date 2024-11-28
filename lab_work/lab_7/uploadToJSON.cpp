#include "../libs.h"

void saveStudentsToJson(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File opening error!" << std::endl;
        _getch();
        return;
    }

    file << "[\n";

    for (size_t i = 0; i < students.size(); ++i) {
        file << students[i].to_json();
        if (i < students.size() - 1) {
            file << ",";
        }
        file << "\n";
    }

    file << "]\n";
    file.close();
}