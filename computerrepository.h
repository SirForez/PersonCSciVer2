#ifndef COMPUTERREPOSITORY_H
#define COMPUTERREPOSITORY_H

#include <vector>
#include <QtSql>
#include "computer.h"

using namespace std;

class computerRepository {

public:
    computerRepository();
    ~computerRepository();

    vector<Computer> search(string input, string word);
    vector<Computer> getSortedComputers(string sortOrder);

    bool add(Computer c);

private:
    QSqlDatabase db;
};

#endif // COMPUTERREPOSITORY_H
