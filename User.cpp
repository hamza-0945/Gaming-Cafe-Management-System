#include "User.h"
#include <iostream>
using namespace std;

User::User(int id, const string& n, const string& c, double bal)
    : userID(id), name(n), contact(c), balance(bal) {}

int User::getID() const 
{ 
   return userID;
   }
string User::getName()const 
{ return name;
 }
string User::getContact() const
 { return contact; 
 }
double User::getBalance()const
{ return balance;
 }

void User::setName(const string& n) 
 {
  name = n; 
  }
void User::setContact(const string& c)
 {
  contact = c;
   }

void User::addBalance(double amount)
 {
    balance += amount;
}

bool User::deductBalance(double amount)
 {
    if (balance < amount) return false;
    balance -= amount;
    return true;
}

void User::displayInfo() const {
    cout << "User ID: " << userID << endl;
    cout << "Name: " << name << endl;
    cout << "Contact: " << contact << endl;
    cout << "Type: " << getUserType() << endl;
    cout << "Balance: Rs. " << balance << endl;
    cout << "------------------------" << endl;
}