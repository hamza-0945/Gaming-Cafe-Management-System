#include "PC.h"
#include <iostream>

using namespace std;

PC::PC(int id, const string& sp)
    : pcID(id), specs(sp), status(PCStatus::AVAILABLE), currentUserID(-1) {}

int  PC::getID()const {
 return pcID; }
string PC::getSpecs() const { 
 return specs; }
PCStatus PC::getStatus()const {
 return status; }
int PC::getCurrentUserID()const {
 return currentUserID; }

void PC::setStatus(PCStatus s){
 status = s; }
void PC::setCurrentUserID(int uid)  { 
currentUserID = uid; }

string PC::getStatusString() const {
    switch (status) {
        case PCStatus::AVAILABLE:    return "Available";
        case PCStatus::OCCUPIED:     return "Occupied";
        case PCStatus::MAINTENANCE:  return "Maintenance";
        default:                     return "Unknown";
    }
}

void PC::displayInfo() const {
    cout << "PC ID: " << pcID << endl;
    cout << "Specs: " << specs << endl;
    cout << "Status: " << getStatusString() << endl;

    if (status == PCStatus::OCCUPIED)
        cout << "Current User ID: " << currentUserID << endl;

    cout << "------------------------" << endl;
}