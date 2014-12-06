#ifndef PERSONSERVICE_H_INCLUDED
#define PERSONSERVICE_H_INCLUDED

#include <iostream>
#include "PersonRepository.h"

class PersonService {
public:
    PersonService();

    bool add(Person p);
    bool save();

    bool erase(vector<Person> results, string answer);
    vector<Person> search(string input, string word);

    double getSize();

    vector<Person> getSortedPersons(string order);

private:
    PersonRepository pRepo;

};

#endif // PERSONSERVICE_H_INCLUDED
