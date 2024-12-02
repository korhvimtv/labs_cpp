#ifndef LAB_WORK_EXEPTIONS_H
#define LAB_WORK_EXEPTIONS_H

#include "../libs.h"

class UserInputException : public std::exception {
private:
    std::string message;
public:
    explicit UserInputException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif //LAB_WORK_EXEPTIONS_H
