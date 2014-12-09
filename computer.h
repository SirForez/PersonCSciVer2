#ifndef COMPUTER_H
#define COMPUTER_H
#include <string>

using namespace std;
class Computer
{
public:
    Computer();

    string getName();
    void setName(string s);

    string getBuildYear();
    void setBuildYear(string s);

    string getType();
    void setType(string s);

    bool getBuilt();
    void setBuilt(bool b);

    int getID();
    void setID(int id);

    bool isValidComputer();

private:
    string name;
    string buildYear;
    string type;
    bool built;
    int ID;

};

#endif // COMPUTER_H
