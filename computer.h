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

    bool isValidComputer();

private:
    string name;
    string buildYear;
    string type;
    bool built;

};

#endif // COMPUTER_H
