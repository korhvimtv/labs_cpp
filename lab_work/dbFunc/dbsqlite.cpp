#include "../libs.h"

std::vector<int> stringToVector(const std::string& marksStr) {
    std::vector<int> marks;
    std::stringstream ss(marksStr);
    int mark;
    char separator;

    while (ss >> mark) {
        marks.push_back(mark);
        ss >> separator;
    }

    return marks;
}

std::string vectorToString(const std::vector<int>& marks) {
    std::stringstream ss;
    for (size_t i = 0; i < marks.size(); ++i) {
        ss << marks[i];
        if (i < marks.size() - 1) {
            ss << ",";
        }
    }
    return ss.str();
}

void dbCreate (sqlite3* db){
    std::string createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS USERS (
            id INTEGER,
            username TEXT NOT NULL,
            age INTEGER,
            group_id INTEGER,
            organisations TEXT,
            marks TEXT,
            name TEXT,
            address TEXT,
            phone TEXT
        );
    )";

    if (sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, nullptr) != SQLITE_OK) {
        std::cerr << "TABLE ERROR!: " << sqlite3_errmsg(db) << std::endl;
    }
}

void saveToDatabase(const Student* obj ,sqlite3* db) {
    std::string marksStr = obj->marksToString();

    std::string sql = "INSERT INTO USERS (id, username, age, group_id, organisations, "
                      "marks, name, address, phone) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, obj->getId());
        sqlite3_bind_text(stmt, 2, obj->getUsername().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, obj->getAge());
        sqlite3_bind_int(stmt, 4, obj->getGroup());
        sqlite3_bind_text(stmt, 5, obj->getOrg().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, marksStr.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, obj->getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 8, obj->getAddress().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 9, obj->getPhone().c_str(), -1, SQLITE_STATIC);


        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "WRITE ERROR!: " << sqlite3_errmsg(db) << std::endl;
            _getch();
        }
    } else {
        std::cerr << "Error preparing SQL-query: " << sqlite3_errmsg(db) << std::endl;
        _getch();
    }
    sqlite3_finalize(stmt);
}

void updateUserInDatabase(const Student* obj, sqlite3* db) {
    std::string sql = "UPDATE USERS SET username = ?, age = ?, group_id = ?, organisations = ?, name = ?, "
                      "address = ?, phone = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, obj->getUsername().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 2, obj->getAge());
        sqlite3_bind_int(stmt, 3, obj->getGroup());
        sqlite3_bind_text(stmt, 4, obj->getOrg().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, obj->getName().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 6, obj->getAddress().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 7, obj->getPhone().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 8, obj->getId());

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "UPDATE ERROR!: " << sqlite3_errmsg(db) << std::endl;
        }
    } else {
        std::cerr << "Error preparing SQL-query: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void loadAllUsersFromDatabase(std::vector<Student>& users, sqlite3* db) {
    const std::string sql =
            "SELECT id, username, age, group_id, organisations, marks, name, address, phone FROM USERS;";
    sqlite3_stmt* stmt;

    users.clear();

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing SQL-query: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int age = sqlite3_column_int(stmt, 2);
        int group = sqlite3_column_int(stmt, 3);
        std::string org = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        std::string marksStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        std::string address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        std::string phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));

        std::vector<int> marks;
        std::istringstream iss(marksStr);
        std::string token;
        while (std::getline(iss, token, ',')) {
            marks.push_back(std::stoi(token));
        }

        users.emplace_back(id, username, age, group, marks, org, name, address, phone);
    }

    sqlite3_finalize(stmt);
}

void addMarksToUser(int userId, const std::vector<int>& marks, sqlite3* db) {
    std::string marksStr = vectorToString(marks);

    std::string sql = "UPDATE USERS SET marks = ? WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing SQL-query: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, marksStr.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, userId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error updating marks: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}

void deleteUserById(int userId, sqlite3* db) {
    std::string sql = "DELETE FROM USERS WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing SQL-query: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, userId);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Error deleting user: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}