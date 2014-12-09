#include "ui.h"
#include <stdlib.h>
#include <fstream>

UI::UI() {
    Pservice = PersonService();
    Cservice = computerservice();
}

void UI::start() {
    string input;
        //system("CLS");
        cout << "Good day to you, user." << endl;
        cout << "Welcome to the Great Computer Science Figure Database Ver. 2. - Now featuring SQLite! " << endl;
        cout << "GCSFD 2.0 for short." << endl;
        cout << endl;
        cout << "(Type help for a command list)" << endl;
        cout << endl;


    while(true) {

        cout << ">> ";
        getline(cin, input);
        cout << endl;

        if(isValidCommand(input)) {
            commandCenter(input);

        } else {
            cout << "Invalid command!" << endl;
            cout << endl;
            continue;
        }
    }
}

void UI::getPersonInput(Person& p) {
    string temp;

    cout << "Name: ";
    getline(cin, temp);
    p.setName(temp);

    cout << "Gender (Male/Female): ";
    getline(cin, temp);
    p.setGender(temp);

    cout << "Date of birth (YYYY/MM/DD): ";
    getline(cin, temp);
    p.setDayOfBirth(temp);

    cout << "Date of death (YYYY/MM/DD): ";
    getline(cin, temp);
    p.setDayOfDeath(temp);

    cout << endl;
}

void UI::getComputerInput(Computer& c) {
    string temp;
    bool tempbool;

    cout << "Name: ";
    getline(cin, temp);
    c.setName(temp);

    cout << "Build Year(YYYY/Never built): ";
    getline(cin, temp);
    c.setBuildYear(temp);

    cout << "Type: ";
    getline(cin, temp);
    c.setType(temp);

    cout << "Built (0(false)/1(true))? ";
    cin >> tempbool;
    c.setBuilt(tempbool);
    cin.ignore();

    cout << endl;
}

bool UI::isValidCommand(string input) {
    if (input == "help" || input == "add" || input == "display" || input == "connections" || input == "clear" || input == "search" || input == "exit") {  /*|| input == "erase"*/
        return true;
    }
    return false;
}

void UI::commandCenter(string input) {
    if (input == "help") {
        cout << "Available commands:\n";
        cout << endl;
        cout << "help\t\t ->  \t(get list of commands)\n";
        cout << "add\t\t ->  \t(add to repository)\n";
        cout << "display\t\t ->  \t(displays repository (optionally sorted))\n";
        cout << "connections\t\t ->  \t(displays all connections)\n";
        cout << "clear\t\t ->  \t(clears display)\n";
        cout << "search\t\t ->  \t(search in repository)\n";
        cout << "exit\t\t ->  \t(quit)\n";
        cout << endl << endl;
        cout << "Interaction:\n";
        cout << ">>\t\t (waiting for command)\n";
        cout << "All changes and additions are saved automatically!\n";
        cout << endl << endl;

    } else if (input == "add") {
        string answer;
        cout << "Person or computer? ";
        getline(cin, answer);
        if(answer == "person") {
            Person temp;
            getPersonInput(temp);
            if(temp.isValidPerson()) {
                bool added = Pservice.add(temp);
                if(added) {
                    cout << endl;
                    cout << "Person added!" << endl;
                    cout << endl;
                } else {
                    cout << "ERROR: Person not added!" << endl;
                }
            } else {
                cout << "ERROR: invalid person entered!" << endl;
                cout << endl;
            }
        } else if(answer == "computer") {
            Computer temp;
            getComputerInput(temp);
            if(temp.isValidComputer()) {
                bool added = Cservice.add(temp);
                if(added) {
                    cout << endl;
                    cout << "Computer added!" << endl;
                    cout << endl;
                } else {
                    cout << "ERROR: Computer not added!" << endl;
                }
            } else {
                cout << "ERROR: invalid computer entered!" << endl;
            }
        }
    } else if (input == "display") {
        string answer;
        cout << "Person or computer? ";
        getline(cin, answer);
        if(answer == "person") {
            cout << endl;
            char ans;
            string sortOrder;
            cout << "Would you like to have it sorted (y/n)? ";
            cin >> ans;
            if(ans == 'Y' || ans == 'y') {
                cout << endl;
                cout << "Sort by (name/gender/date of birth/date of death)? ";
                cin.ignore();
                getline(cin, sortOrder);
            } else {
                cin.ignore();
                sortOrder = "";
            }
            vector<Person> SortedPersons = Pservice.getSortedPersons(sortOrder);
            displayAllPersons(SortedPersons);
        } else if(answer == "computer") {
            cout << endl;
            char ans;
            string sortOrder;
            cout << "Would you like to have it sorted (y/n)? ";
            cin >> ans;
            if(ans == 'Y' || ans == 'y') {
                cout << endl;
                cout << "Sort by (name/buildyear/type/built)? ";
                cin.ignore();
                getline(cin, sortOrder);
            } else {
                cin.ignore();
                sortOrder = "";
            }
            vector<Computer> SortedComputers = Cservice.getSortedComputers(sortOrder);
            displayAllComputers(SortedComputers);
        }


    } else if (input == "clear") {
        system("cls");

    } else if (input == "erase") {
        /*string answer;
        cout << "What would you like to erase (all/specific)? ";
        getline(cin, answer);

        vector<Person> searchResults;
        if(answer == "specific") {
            searchResults = searchSwitch(searchFor());
        }
        bool erased = Pservice.erase(searchResults, answer);
        if(erased) {
            cout << endl;
            cout << "Person(s) erased!" << endl;
            cout << endl;
        }*/

    } else if (input == "connections") {
        displayConnections(Pservice.getSortedPersons("name"));

    } else if (input == "search") {
        string searchType;
        cout << "Search for a person or a computer (person/computer)? ";
        getline(cin,searchType);
        if(searchType != "person" && searchType != "computer") {
            cout << "ERROR: Invalid type for search!" << endl;
        }
        char searchColumn = searchFor(searchType);
        if(searchType == "person") {
            vector<Person> result = personSearchSwitch(searchColumn);
            if(result.size()) {
                displayPerson(result);
            } else {
                cout << endl;
                cout << "ERROR: No results found!" << endl;
                cout << endl;
            }
        } else {
            vector<Computer> result = computerSearchSwitch(searchColumn);
            if(result.size()) {
                displayComputer(result);
            } else {
                cout << endl;
                cout << "ERROR: No results found!" << endl;
                cout << endl;
            }
        }

    }  else if (input == "exit") {
        /*if((editCounter != 0)) {
            char answer;
            cout << "You have unsaved changes, would you like to save (y/n)? ";
            cin >> answer;

            if(answer == 'y' || answer == 'Y') {
                Pservice.save();
            }
        }
*/
        cout << "Thanks for using our database program!" << endl;
        cout << endl;
        exit(0);
    }

}

char UI::searchFor(string type) {

    char searchFor;
    if(type == "person") {
        cout << "1: to search for name " << endl;
        cout << "2: to search for gender " << endl;
        cout << "3: to search for birthdate " << endl;
        cout << "4: to search for deceased date " << endl;
    } else {
        cout << "1: to search for name " << endl;
        cout << "2: to search for build year " << endl;
        cout << "3: to search for type " << endl;
        cout << "4: to search for built(boolean) " << endl;
    }
    do {
        cout << "Enter value here: ";
        cin >> searchFor;
        if(!isValidSearchColumn(searchFor)) {
            cout << "Invalid command! Enter '1' '2' '3' or '4'" << endl;
        }
    } while(!isValidSearchColumn(searchFor));
    cout << endl;

    return searchFor;
}

bool UI::isValidSearchColumn(char in) {
    if (in == '1' || in == '2' || in == '3' || in == '4') {
        return true;
    }
    return false;
}

vector<Person> UI::personSearchSwitch(char searchColumn) {
    string input, word;
    switch(searchColumn){
        case '1':
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, input);
            word = "name";
            cout << endl;
            return Pservice.search(input, word);
            break;

        case '2':
            cout << "Enter gender: ";
            cin.ignore();
            getline(cin, input);
            word = "gender";
            cout << endl;
            return Pservice.search(input, word);
            break;

        case '3':
            cout << "Enter date of birth: ";
            cin.ignore();
            getline(cin, input);
            word = "dayOfBirth";
            cout << endl;
            return Pservice.search(input, word);
            break;

        case '4':
            cout << "Enter date of death: ";
            cin.ignore();
            getline(cin, input);
            word = "dayOfDeath";
            cout << endl;
            return Pservice.search(input, word);
            break;
        default:
            throw;
    }
}

vector<Computer> UI::computerSearchSwitch(char searchColumn) {
    string input, word;
    switch(searchColumn){
        case '1':
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, input);
            word = "name";
            cout << endl;
            return Cservice.search(input, word);
            break;

        case '2':
            cout << "Enter build year (YYYY/Never built): ";
            cin.ignore();
            getline(cin, input);
            word = "buildyear";
            cout << endl;
            return Cservice.search(input, word);
            break;

        case '3':
            cout << "Enter type: ";
            cin.ignore();
            getline(cin, input);
            word = "type";
            cout << endl;
            return Cservice.search(input, word);
            break;

        case '4':
            cout << "Enter whether the computer was built (0/1): ";
            cin.ignore();
            getline(cin, input);
            word = "built";
            cout << endl;
            return Cservice.search(input, word);
            break;
        default:
            throw;
    }
}

void UI::displayPerson(vector<Person> results) {
    for(int i = 0; i < results.size(); i++) {
        cout << "Name:\t\t" << results[i].getName() << endl;
        cout << "Gender:\t\t"<< results[i].getGender() << endl;
        cout << "Date of birth:\t" << results[i].getDayOfBirth() << endl;
        cout << "Date of death:\t" << results[i].getDayOfDeath() << endl;
        cout << endl;
    }
}

void UI::displayComputer(vector<Computer> results) {
    for(int i = 0; i < results.size(); i++) {
        cout << "Name:\t\t" << results[i].getName() << endl;
        cout << "Build Year:\t"<< results[i].getBuildYear() << endl;
        cout << "Type:\t\t" << results[i].getType() << endl;
        if(results[i].getBuilt() == true) {
            cout << "Built?\t\t" << "true)" << endl;
        } else {
            cout << "Built?\t\t" << "false" << endl;
        }
        cout << endl;
    }
}

void UI::displayAllPersons(vector<Person> vec) {
    cout << endl;
    cout.width(36);
    cout << left << "Name:";
    cout.width(18);
    cout << left << "Gender:";
    cout.width(18);
    cout << left << "Date of birth:";
    cout.width(25);
    cout << left << "Date of death:" << endl;
    for(int i = 0; i < 100; i++) {
        cout << "-";
    }
    cout << endl;
    for(int i = 0; i < vec.size(); i++) {

        cout.width(36);
        cout << left << vec[i].getName();
        cout.width(18);
        cout << left << vec[i].getGender();
        cout.width(18);
        cout << left << vec[i].getDayOfBirth();
        cout.width(25);
        cout << left << vec[i].getDayOfDeath();
        cout << endl << endl;
    }
    for(int i = 0; i < 100; i++) {
        cout << "-";
    }
    cout << endl;
    cout << endl;
}

void UI::displayAllComputers(vector<Computer> vec) {
    cout << endl;
    cout.width(30);
    cout << left << "Name:";
    cout.width(18);
    cout << left << "Build Year:";
    cout.width(44);
    cout << left << "Type:";
    cout.width(25);
    cout << left << "Built?" << endl;
    for(int i = 0; i < 100; i++) {
        cout << "-";
    }
    cout << endl;
    for(int i = 0; i < vec.size(); i++) {

        cout.width(30);
        cout << left << vec[i].getName();
        cout.width(18);
        cout << left << vec[i].getBuildYear();
        cout.width(44);
        cout << left << vec[i].getType();
        cout.width(25);
        cout << left << vec[i].getBuilt();
        cout << endl << endl;
    }
    for(int i = 0; i < 100; i++) {
        cout << "-";
    }
    cout << endl;
    cout << endl;
}

void UI::displayConnections(vector<Person> sortedPersons) {
    cout << endl;
    cout.width(30);
    cout << left << "Scientist Name:";
    cout.width(30);
    cout << left << "Connected computers:" << endl;
    for(int i = 0; i < 60; i++) {
        cout << "-";
    }
    cout << endl;
    for(int i = 0; i < sortedPersons.size(); i++) {
        cout.width(30);
        cout << left << sortedPersons[i].getName() + ": ";
        vector<Computer> connectedComputers = Cservice.getComputersFromScientist(sortedPersons[i]);
        if(connectedComputers.size()) {
            cout.width(30);
            string comp;
            for(int j = 0; j < connectedComputers.size(); j++) {
                if(j != connectedComputers.size() - 1) {
                    comp += connectedComputers[j].getName() + ", ";
                } else {
                    comp += connectedComputers[j].getName() + ".";
                }
            }
            cout << comp;
        } else {
            cout << "No connection in database.";
        }
        cout << endl << endl;
    }
    for(int i = 0; i < 60; i++) {
        cout << "-";
    }
    cout << endl << endl;
}
