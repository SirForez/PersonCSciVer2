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

    cout << "Build Year: ";
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
    if (input == "help" || input == "add" || input == "display" || input == "clear" || input == "search" || input == "exit") {  /*|| input == "erase"*/
        return true;
    }
    return false;
}

void UI::commandCenter(string input) {
    if (input == "help") {
        cout << "Available commands:\n";
        cout << endl;
        cout << "help\t ->  \t(get list of commands)\n";
        cout << "add\t ->  \t(add to repository)\n";
        cout << "display\t ->  \t(displays repository (optionally sorted))\n";
        cout << "clear\t ->  \t(clears display)\n";
        cout << "search\t ->  \t(search in repository)\n";
        cout << "exit\t ->  \t(quit)\n";
        cout << endl << endl;
        cout << "Interaction:\n";
        cout << ">>\t (waiting for command)\n";
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

    } else if (input == "search") {
        vector<Person> result = searchSwitch(searchFor());
        if(result.size()) {
            displayPerson(result);
        } else {
            cout << endl;
            cout << "No results found!" << endl;
            cout << endl;
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

char UI::searchFor() {

    char searchFor;
    cout << "enter 'n' to search for name " << endl;
    cout << "enter 'g' to search for gender " << endl;
    cout << "enter 'b' to search for birthdate " << endl;
    cout << "enter 'd' to search for deceased date " << endl;
    do {
        cin >> searchFor;
        if(!isValidSearchColumn(searchFor)) {
            cout << "Invalid command! Enter 'n' 'g' 'b' or 'd'" << endl;
        }
    } while(!isValidSearchColumn(searchFor));
    cout << endl;

    return searchFor;
}

bool UI::isValidSearchColumn(char in) {
    if (in == 'n' || in == 'g' || in == 'b' || in == 'd') {
        return true;
    }
    return false;
}

vector<Person> UI::searchSwitch(char searchColumn) {
    string input, word;
    switch(searchColumn){
        case 'n':
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, input);
            word = "name";
            cout << endl;
            return Pservice.search(input, word);
            break;

        case 'g':
            cout << "Enter gender: ";
            cin.ignore();
            getline(cin, input);
            word = "gender";
            cout << endl;
            return Pservice.search(input, word);
            break;

        case 'b':
            cout << "Enter date of birth: ";
            cin.ignore();
            getline(cin, input);
            word = "dayOfBirth";
            cout << endl;
            return Pservice.search(input, word);
            break;

        case 'd':
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
        cout << "Build Year:\t\t"<< results[i].getBuildYear() << endl;
        cout << "Type:\t\t" << results[i].getType() << endl;
        cout << "Built?\t\t" << results[i].getBuilt() << endl;
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
    for(int i = 0; i < 86; i++) {
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
    for(int i = 0; i < 86; i++) {
        cout << "-";
    }
    cout << endl;
    cout << endl;
}

void UI::displayAllComputers(vector<Computer> vec) {
    cout << endl;
    cout.width(36);
    cout << left << "Name:";
    cout.width(18);
    cout << left << "Build Year:";
    cout.width(18);
    cout << left << "Type:";
    cout.width(25);
    cout << left << "Built?" << endl;
    for(int i = 0; i < 86; i++) {
        cout << "-";
    }
    cout << endl;
    for(int i = 0; i < vec.size(); i++) {

        cout.width(36);
        cout << left << vec[i].getName();
        cout.width(18);
        cout << left << vec[i].getBuildYear();
        cout.width(18);
        cout << left << vec[i].getType();
        cout.width(25);
        cout << left << vec[i].getBuilt();
        cout << endl << endl;
    }
    for(int i = 0; i < 86; i++) {
        cout << "-";
    }
    cout << endl;
    cout << endl;
}
