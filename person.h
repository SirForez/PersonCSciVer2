#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    Person();

    string getName();
    void setName(string s);

    string getGender();
    void setGender(string s);

    string getDayOfBirth();
    void setDayOfBirth(string s);

    string getDayOfDeath();
    void setDayOfDeath(string s);

    int getID();
    void setID(int id);

    bool isValidPerson();

private:
    string name;
    string gender;
    string dayOfBirth;
    string dayOfDeath;
    int ID;

};

#endif // PERSON_H_INCLUDED
