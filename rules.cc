#include "rules.h"
#include "observer.h"

Rules::Rules(std::string ruleName) : ruleName{ruleName} {}

std::string Rules::getRuleName() const {
    return ruleName;
}
