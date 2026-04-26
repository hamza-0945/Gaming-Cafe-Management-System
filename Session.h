#ifndef SESSION_H
#define SESSION_H

#include <string>
using namespace std;

class Session {
private:
    int sessionID;
    int userID;
    int pcID;
    string startTime;
    string endTime;
    double hoursUsed;
    double totalCost;
    bool active;

public:
    Session(int sid, int uid, int pid, const string& startTime);

    int getSessionID() const;
    int getUserID() const;
    int getPCID() const;
    string getStartTime() const;
    string getEndTime() const;
    double getHoursUsed() const;
    double getTotalCost() const;
    bool isActive() const;

    void endSession(const string& endTime, double hours, double cost);
    void displayInfo() const;
};

#endif
