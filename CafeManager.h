#ifndef CAFEMANAGER_H
#define CAFEMANAGER_H

#include "User.h"
#include "PC.h"
#include "Session.h"
#include <vector>
using namespace std;

class CafeManager {
private:
    vector<User*> users;      // dynamic memory, polymorphic
    vector<PC*> pcs;          // dynamic memory
    vector<Session*> sessions; // dynamic memory

    int nextUserID;
    int nextSessionID;

    // File names
    static const string USERS_FILE;
    static const string PCS_FILE;
    static const string SESSIONS_FILE;

    // Helper methods
    User* findUser(int id);
    PC*   findPC(int id);
    Session* findActiveSessionByPC(int pcID);
    string getCurrentTime() const;

public:
    CafeManager();
    ~CafeManager(); // releases dynamic memory

    // User management
    void addRegularUser();
    void addVIPUser();
    void updateUser();
    void deleteUser();
    void searchUser();
    void listAllUsers();

    // PC management
    void addPC();
    void updatePC();
    void deletePC();
    void listAllPCs();
    void setPCMaintenance();

    // Session management
    void startSession();
    void endSession();
    void listActiveSessions();
    void listAllSessions();

    // File handling
    void saveData();
    void loadData();
};

#endif
