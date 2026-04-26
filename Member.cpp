#include "Member.h"
#include <iostream>

using namespace std;

const double RegularUser::HOURLY_RATE = 80.0;

RegularUser::RegularUser(int id, const string& name, const string& contact, double balance)
    : User(id, name, contact, balance) {}

string RegularUser::getUserType()    const { return "Regular"; }
double RegularUser::getHourlyRate()  const { return HOURLY_RATE; }

void RegularUser::displayInfo() const {
    User::displayInfo();
}

const double VIPUser::HOURLY_RATE = 60.0;

VIPUser::VIPUser(int id, const string& name, const string& contact,
                 const string& expiry, double balance)
    : User(id, name, contact, balance),
      totalHoursPlayed(0),
      membershipExpiry(expiry) {}

string VIPUser::getUserType()const
    { return "VIP"; }
double VIPUser::getHourlyRate()const
    { return HOURLY_RATE; }

int VIPUser::getTotalHoursPlayed()const
    { return totalHoursPlayed; }
string VIPUser::getMembershipExpiry()const
    { return membershipExpiry; }
void VIPUser::addHours(int hours)
    { totalHoursPlayed += hours; }

void VIPUser::displayInfo()const {
    User::displayInfo();
    cout << "      VIP Expiry: " << membershipExpiry
         << "  |  Total Hours: " << totalHoursPlayed << "\n";
}
