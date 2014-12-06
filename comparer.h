#ifndef COMPARER_H
#define COMPARER_H

#include <string>
#include "person.h"


using namespace std;

class Comparer
{
public:
    Comparer();
    Comparer(string ord);
    bool operator () (Person first, Person second);

private:
    string order;
};

#endif // COMPARER_H
