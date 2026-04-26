#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"

class RegularUser : public User {
private:
    static const double HOURLY_RATE;

public:
    RegularUser(int id, const string& name, const string& contact, double balance = 0.0);

    string getUserType() const override;
    double getHourlyRate() const override;
    void displayInfo() const override;
};

class VIPUser : public User {
private:
    static const double HOURLY_RATE;
    int totalHoursPlayed;
    string membershipExpiry;

public:
    VIPUser(int id, const string& name, const string& contact, const string& expiry, double balance = 0.0);

    string getUserType() const override;
    double getHourlyRate() const override;
    void displayInfo() const override;

    int getTotalHoursPlayed() const;
    void addHours(int hours);
    string getMembershipExpiry() const;
};

#endif
