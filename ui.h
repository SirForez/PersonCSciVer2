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

    //handles the given commands from user
    void commandCenter(string input);

    char searchFor(string type);
    bool isValidSearchColumn(char in);

    void displayPerson(vector<Person> results);
    void displayAllPersons(vector<Person> vec);

    void getComputerInput(Computer &c);
    void displayAllComputers(vector<Computer> vec);
    void displayComputer(vector<Computer> results);

    //Decides what column to search for(name, gender, day of birth or day of death)
    vector<Computer> computerSearchSwitch(char searchColumn);
    //Decides what column to search for(name, yearbuilt, type, built?(0/1))
    vector<Person> personSearchSwitch(char searchColumn);

    //displays all the scientist and all the computers they are connected to
    void displayConnections(vector<Person> sortedPersons);
    void handleHelpCommand();
    void handleAddCommand();
    void handleSearchCommand();
    void handleDisplayCommand();

private:
    PersonService Pservice;
    computerservice Cservice;
};

#endif // UI_H_INCLUDED
