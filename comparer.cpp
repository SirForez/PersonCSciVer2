#include "comparer.h"
#include "person.h"

Comparer::Comparer() {
    order = "";
}

Comparer::Comparer(string ord) {
    order = ord;
}

bool Comparer::operator ()(Person first, Person second) {
    if(order == "name") {
        return first.getName() < second.getName();
    } else if(order == "gender") {
        return first.getGender() < second.getGender();
    } else if(order == "date of birth") {
        return first.getDayOfBirth() < second.getDayOfBirth();
    } else if(order == "date of death") {
        return first.getDayOfDeath() < second.getDayOfDeath();
    }
    throw;
}
