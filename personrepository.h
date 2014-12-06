#ifndef PERSONREPOSITORY_H_INCLUDED
#define PERSONREPOSITORY_H_INCLUDED

#include <iostream>
#include <vector>
#include <algorithm>
#include "comparer.h"
#include "person.h"

class PersonRepository {
public:
    PersonRepository();

    bool add(Person p);
    bool save();

    double getSize();


    vector<Person> search(string input, string word);
    bool erase(vector<Person> results, string answer);
    vector<Person> getSortedPersons(string sortOrder);

private:
    vector<Person> plist;
    void displayPerson(const int index);
    char searchFor();

};

#endif // PERSONREPOSITORY_H_INCLUDED
