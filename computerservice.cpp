#include "computerservice.h"
#include <vector>
#include <string>

using namespace std;
computerservice::computerservice() {
    compRepo = computerRepository();
}

bool computerservice::add(Computer c) {
    return compRepo.add(c);
}

vector<Computer> computerservice::getSortedComputers(string sortOrder) {
    return compRepo.getSortedComputers(sortOrder);
}

vector<Computer> computerservice::search(string input, string word) {
    return compRepo.search(input, word);
}

vector<Computer> computerservice::getComputersFromScientist(Person scientist) {
    return compRepo.getComputersFromScientist(scientist);
}
