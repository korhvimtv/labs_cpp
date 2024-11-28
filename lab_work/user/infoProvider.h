#ifndef LAB_3_INFOPROVIDER_H
#define LAB_3_INFOPROVIDER_H

#include "infoProvider.h"

class InfoProvider {
public:
    virtual ~InfoProvider() = default;

    [[nodiscard]] virtual std::string getInfo() const = 0;
};

#endif //LAB_3_INFOPROVIDER_H
