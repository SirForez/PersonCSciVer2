#include "PersonRepository.h"
#include <fstream>
#include <string>
#include <algorithm>
#include "comparer.h"
#include <iomanip>


using namespace std;

PersonRepository::PersonRepository() {
    ifstream inFile("PersonFile.txt");

    if(inFile.is_open()) {
        string  line1, line2, line3, line4;

        while(getline(inFile, line1) &&
              getline(inFile, line2) &&
              getline(inFile, line3) &&
              getline(inFile, line4)) {

            Person temp;
            temp.setName(line1);
            temp.setGender(line2);
            temp.setDayOfBirth(line3);
            temp.setDayOfDeath(line4);
            plist.push_back(temp);
        }

    }

    inFile.close();
}

bool PersonRepository::add(Person p) {
    plist.push_back(p);
    return true;
}

vector<Person> PersonRepository::getSortedPersons(string sortOrder) {
    Comparer comp = Comparer(sortOrder);
    try {
        sort(plist.begin(),plist.end(), comp);
    } catch(...) {
        throw;
    }
    return plist;
}

bool PersonRepository::save() {
    ofstream outFile("PersonFile.txt");
    bool saved = true;
    string tempLine;

    if(outFile.is_open()) {

        for(unsigned int i = 0; i < plist.size(); i++) {
            outFile << plist[i].getName() << endl;
            outFile << plist[i].getGender() << endl;
            outFile << plist[i].getDayOfBirth() << endl;
            outFile << plist[i].getDayOfDeath() << endl;
        }
        saved = true;
    } else {
        saved = false;
    }

    outFile.close();
    return saved;
}

bool PersonRepository::erase(vector<Person> results, string answer) {
    if (answer == "all") {
        plist.erase(plist.begin(),plist.end());
        return true;

    } else if (answer == "specific") {
        int failCounter = 0;
        for(int i = 0; i < results.size(); i++) {
            for(int j = 0; j < plist.size(); j++) {
                if(results[i].getName() == plist[j].getName()
                   && results[i].getGender() == plist[j].getGender()
                   && results[i].getDayOfBirth() == plist[j].getDayOfBirth()
                   && results[i].getDayOfDeath() == plist[j].getDayOfDeath()) {

                    plist.erase(plist.begin()+j);

                } else {
                    failCounter++;
                }
            }
        }

        if(failCounter == results.size()) {
            return false;
        } else {
            return true;
        }
    } else {
        throw;
    }
}


vector<Person> PersonRepository::search(string input, string word) {
    int index;
    vector<Person> temp;
    for(index = 0; index < plist.size(); index++) {
       if((word == "name" && input == plist[index].getName())
       || (word == "gender" && input == plist[index].getGender())
       || (word == "dayOfBirth" && input == plist[index].getDayOfBirth())
       || (word == "dayOfDeath" && input == plist[index].getDayOfDeath())) {

            temp.push_back(plist[index]);
        }
    }
    return temp;
}




double PersonRepository::getSize() {
    return plist.size();
}
