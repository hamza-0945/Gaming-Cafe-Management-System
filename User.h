#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    int userID;
    string name;
    string contact;
    double balance;

public:
    User(int id, const string& name, const string& contact, double balance = 0.0);
    virtual ~User() {}

    int getID() const;
    string getName() const;
    string getContact() const;
    double getBalance() const;

    void setName(const string& name);
    void setContact(const string& contact);
    void addBalance(double amount);
    bool deductBalance(double amount);

    virtual string getUserType() const = 0;
    virtual double getHourlyRate() const = 0;
    virtual void displayInfo() const;
};

#endif
