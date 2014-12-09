#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <iostream>
#include <string>
#include "PersonService.h"
#include "computerservice.h"

class UI {
public:
    UI();

    void start();
    void getPersonInput(Person& p);
    bool isValidCommand(string input);

    void commandCenter(string input);

    char searchFor(string type);
    bool isValidSearchColumn(char in);

    void displayPerson(vector<Person> results);
    void displayAllPersons(vector<Person> vec);

    void getComputerInput(Computer &c);
    void displayAllComputers(vector<Computer> vec);
    void displayComputer(vector<Computer> results);

    vector<Computer> computerSearchSwitch(char searchColumn);
    vector<Person> personSearchSwitch(char searchColumn);

    void displayConnections(vector<Person> sortedPersons);
private:
    PersonService Pservice;
    computerservice Cservice;
};

#endif // UI_H_INCLUDED
