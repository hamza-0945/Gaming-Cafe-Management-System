#include "Session.h"
#include <iostream>
#include <iomanip>
using namespace std;

Session::Session(int sid, int uid, int pid, const string& start)
    : sessionID(sid), userID(uid), pcID(pid),
      startTime(start), endTime(""), hoursUsed(0), totalCost(0), active(true) {}

int Session::getSessionID() const{
  return sessionID; }
int Session::getUserID()const {
 return userID; }
int Session::getPCID()const {
 return pcID; }
string Session::getStartTime() const { 
return startTime; }
string Session::getEndTime()const {
 return endTime; }
double Session::getHoursUsed() const {
 return hoursUsed; }
double Session::getTotalCost() const {
 return totalCost; }
bool Session::isActive()const {
 return active; }

void Session::endSession(const string& end, double hours, double cost) {
    endTime   = end;
    hoursUsed = hours;
    totalCost = cost;
    active    = false;
}

void Session::displayInfo() const {
    cout << "Session ID: " << sessionID << endl;
    cout << "User ID: " << userID << endl;
    cout << "PC ID: " << pcID << endl;
    cout << "Start Time: " << startTime << endl;

    if (active)
        cout << "Status: Active" << endl;
    else
        cout << "End Time: " << endTime << endl;

    cout << "Hours Used: " << hoursUsed << endl;
    cout << "Total Cost: Rs. " << totalCost << endl;
    cout << "------------------------" << endl;
}