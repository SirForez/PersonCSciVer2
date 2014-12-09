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

    char searchFor();
    bool isValidSearchColumn(char in);
    vector<Person> searchSwitch(char searchColumn);

    void displayPerson(vector<Person> results);
    void displayAllPersons(vector<Person> vec);

    void getComputerInput(Computer &c);
    void displayAllComputers(vector<Computer> vec);
    void displayComputer(vector<Computer> results);
private:
    PersonService Pservice;
    computerservice Cservice;
};

#endif // UI_H_INCLUDED
