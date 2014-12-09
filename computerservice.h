#ifndef COMPUTERSERVICE_H
#define COMPUTERSERVICE_H
#include "computerrepository.h"
#include <vector>

using namespace std;

class computerservice {

public:
    computerservice();
    bool add(Computer c);
    vector<Computer> getSortedComputers(string sortOrder);
    vector<Computer> search(string input, string word);
    vector<Computer> getComputersFromScientist(Person scientist);
    bool connectComputerToScientist(int PersonID, int ComputerID);
private:
    computerRepository compRepo;
};

#endif // COMPUTERSERVICE_H
