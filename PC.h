#ifndef PC_H
#define PC_H

#include <string>
using namespace std;

enum class PCStatus { AVAILABLE, OCCUPIED, MAINTENANCE };

class PC {
private:
    int pcID;
    string specs;
    PCStatus status;
    int currentUserID; 

public:
    PC(int id, const string& specs);

    int getID() const;
    string getSpecs() const;
    PCStatus getStatus() const;
    string getStatusString() const;
    int getCurrentUserID() const;

    void setStatus(PCStatus s);
    void setCurrentUserID(int uid);

    void displayInfo() const;
};

#endif
