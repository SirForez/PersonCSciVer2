#include "computerrepository.h"
#include <vector>
#include "computer.h"
#include "person.h"
#include <QtSql>

using namespace std;

computerRepository::computerRepository() {
    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("PersonCompSci.sqlite");
        db.open();
    }
}
computerRepository::~computerRepository() {
    db.close();
}

bool computerRepository::add(Computer c) {
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO Computers(Name, BuildYear, Type, Built)"
                  "VALUES (:name, :buildyear, :type, :built)");
    query.bindValue(":name", QString::fromStdString(c.getName()));
    query.bindValue(":buildyear", QString::fromStdString(c.getBuildYear()));
    query.bindValue(":type", QString::fromStdString(c.getType()));
    query.bindValue(":built", QString::number(c.getBuilt()));
    query.exec();
    db.close();
    return true;

}

vector<Computer> computerRepository::getSortedComputers(string sortOrder) {
    db.open();
    QSqlQuery query;

    if(sortOrder == "name") {
        query.prepare("SELECT * FROM Computers ORDER BY Name");

    } else if(sortOrder == "buildyear") {
        query.prepare("SELECT * FROM Computers ORDER BY BuildYear");

    } else if(sortOrder == "type") {
        query.prepare("SELECT * FROM Computers ORDER BY Type");

    } else if(sortOrder == "built") {
        query.prepare("SELECT * FROM Computers ORDER BY Built");
    } else {
        query.prepare("SELECT * FROM Computers");
    }

    query.exec();

    vector<Computer> temp;

    while(query.next()) {
        Computer c;

        c.setName(query.value("Name").toString().toStdString());
        c.setBuildYear(query.value("BuildYear").toString().toStdString());
        c.setType(query.value("Type").toString().toStdString());
        c.setBuilt(query.value("Built").toInt());
        c.setID(query.value("ID").toInt());

        temp.push_back(c);
    }
    db.close();
    return temp;
}


vector<Computer> computerRepository::search(string input, string word) {
    db.open();
    vector<Computer> temp;

    QString qinput = QString::fromStdString(input);

    QString likeInput = "%" + qinput + "%";


    QSqlQuery query;

    if(word == "name") {
        query.prepare("SELECT * FROM Computers c WHERE c.Name LIKE :contains;");

    } else if(word == "buildyear") {
        query.prepare("SELECT * FROM Computers c WHERE c.BuildYear LIKE :contains");

    } else if(word == "type") {
        query.prepare("SELECT * FROM Computers c WHERE c.Type LIKE :contains");

    } else {
        query.prepare("SELECT * FROM Computers c WHERE c.Built LIKE :contains");

    }

    query.bindValue(":contains",likeInput);
    query.exec();

    while(query.next()) {
        Computer c;

        c.setName(query.value("Name").toString().toStdString());
        c.setBuildYear(query.value("BuildYear").toString().toStdString());
        c.setType(query.value("Type").toString().toStdString());
        c.setBuilt(query.value("Built").toInt());
        c.setID(query.value("ID").toInt());

        temp.push_back(c);
    }
    db.close();
    return temp;

}

vector<Computer> computerRepository::getComputersFromScientist(Person scientist) {
    db.open();
    vector<Computer> temp;
    QSqlQuery query;
    query.prepare("SELECT * FROM Computers c JOIN Linker l ON l.c_ID = c.ID AND l.p_ID = ?");
    query.addBindValue(scientist.getID());
    query.exec();
    while(query.next()) {
        Computer c;

        c.setName(query.value("Name").toString().toStdString());
        c.setBuildYear(query.value("BuildYear").toString().toStdString());
        c.setType(query.value("Type").toString().toStdString());
        c.setBuilt(query.value("Built").toInt());
        c.setID(query.value("ID").toInt());

        temp.push_back(c);
    }

    db.close();
    return temp;
}

bool computerRepository::connectComputerToScientist(int PersonID, int ComputerID) {
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO Linker(p_ID, c_ID) VALUES(:personID, :computerID)");
    query.bindValue(":personID", QString::number(PersonID));
    query.bindValue(":computerID", QString::number(ComputerID));
    if(!query.exec()) {
        return false;
    } else {
        return true;
    }
}
