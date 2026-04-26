#include "CafeManager.h"
#include "Member.h"
#include "Billing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <ctime>
using namespace std;

const string CafeManager::USERS_FILE    = "users.txt";
const string CafeManager::PCS_FILE      = "pcs.txt";
const string CafeManager::SESSIONS_FILE = "sessions.txt";
CafeManager::CafeManager() : nextUserID(1), nextSessionID(1) {
    loadData();
}

CafeManager::~CafeManager() {
    saveData();
    for (auto u : users)  
	    delete u;
    for (auto p : pcs)  
	    delete p; 
    for (auto s : sessions) 
    	delete s;
}

User* CafeManager::findUser(int id) {
    for (auto u : users)
        if (u->getID() == id) return u;
    return nullptr;
}

PC* CafeManager::findPC(int id) {
    for (auto p : pcs)
        if (p->getID() == id) return p;
    return nullptr;
}

Session* CafeManager::findActiveSessionByPC(int pcID) {
    for (auto s : sessions)
        if (s->getPCID() == pcID && s->isActive()) return s;
    return nullptr;
}

string CafeManager::getCurrentTime() const {
    time_t now = time(nullptr);
    char buf[20];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", localtime(&now));
    return string(buf);
}

static int getIntInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) { cin.ignore(); return val; }
        cout << "  Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static double getDoubleInput(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= 0) { cin.ignore(); return val; }
        cout << " Invalid input. Please enter a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


void CafeManager::addRegularUser() {
    cout << "\n  --- Add Regular User ---\n";
    string name, contact;
    double balance;

    cout << "  Name    : "; getline(cin, name);
    if (name.empty()) throw invalid_argument("Name cannot be empty.");

    cout << "  Contact : "; getline(cin, contact);
    if (contact.empty()) throw invalid_argument("Contact cannot be empty.");

    balance = getDoubleInput("  Initial Balance (Rs.): ");

    User* u = new RegularUser(nextUserID++, name, contact, balance);
    users.push_back(u);
    cout << " Regular user added with ID: " << u->getID() << "\n";
}

void CafeManager::addVIPUser() {
    cout << "\n  --- Add VIP User ---\n";
    string name, contact, expiry;
    double balance;

    cout << "  Name              : "; getline(cin, name);
    if (name.empty()) throw invalid_argument("Name cannot be empty.");

    cout << "  Contact           : "; getline(cin, contact);
    if (contact.empty()) throw invalid_argument("Contact cannot be empty.");

    cout << "  Membership Expiry : "; getline(cin, expiry);
    if (expiry.empty()) throw invalid_argument("Expiry date cannot be empty.");

    balance = getDoubleInput("  Initial Balance (Rs.): ");

    User* u = new VIPUser(nextUserID++, name, contact, expiry, balance);
    users.push_back(u);
    cout << " VIP user added with ID: " << u->getID() << "\n";
}

void CafeManager::updateUser() {
    cout << "\n  --- Update User ---\n";
    int id = getIntInput("  Enter User ID: ");
    User* u = findUser(id);
    if (!u) throw runtime_error("User not found.");

    string name, contact;
    cout << "  New Name    (leave blank to keep): "; getline(cin, name);
    cout << "  New Contact (leave blank to keep): "; getline(cin, contact);

    if (!name.empty())    u->setName(name);
    if (!contact.empty()) u->setContact(contact);
    cout << " User updated.\n";
}

void CafeManager::deleteUser() {
    cout << "\n--- Delete User ---\n";
    int id = getIntInput("Enter User ID: ");

    for (int i = 0; i < users.size(); i++) {
        if (users[i]->getID() == id) {
            delete users[i];                         
            users.erase(users.begin() + i);        
            cout << "User deleted.\n";
            return;
        }
    }

    cout << "User not found.\n";
}
void CafeManager::searchUser() {
    cout << "\n  --- Search User ---\n";
    cout << "  1. Search by ID\n  2. Search by Name\n";
    int choice = getIntInput("  Choice: ");

    if (choice == 1) {
        int id = getIntInput("  Enter User ID: ");
        User* u = findUser(id);
        if (!u) throw runtime_error("User not found.");
        cout << "\n  " << left << setw(6) << "ID" << setw(18) << "Name"
             << setw(15) << "Contact" << setw(10) << "Type" << "Balance\n";
        cout << "  " << string(60, '-') << "\n  ";
        u->displayInfo();
    } else if (choice == 2) {
        string name;
        cout << "  Enter Name: "; getline(cin, name);
        bool found = false;
        cout << "\n  " << left << setw(6) << "ID" << setw(18) << "Name"
             << setw(15) << "Contact" << setw(10) << "Type" << "Balance\n";
        cout << "  " << string(60, '-') << "\n";
        for (auto u : users) {
            if (u->getName().find(name) != string::npos) {
                cout << "  "; u->displayInfo(); found = true;
            }
        }
        if (!found) cout << "  No users found.\n";
    } else {
        throw invalid_argument("Invalid choice.");
    }
}

void CafeManager::listAllUsers() {
    cout << "\n--- All Users ---\n";

    if (users.empty()) {
        cout << "No users registered.\n";
        return;
    }

    for (int i = 0; i < users.size(); i++) {
        users[i]->displayInfo();
    }
}

void CafeManager::addPC() {
    cout << "\n  --- Add PC ---\n";
    string specs;
    cout << "  PC Specs (e.g. i7, RTX3060, 16GB RAM): "; getline(cin, specs);
    if (specs.empty()) throw invalid_argument("Specs cannot be empty.");

    int id = (pcs.empty() ? 1 : pcs.back()->getID() + 1);
    PC* p = new PC(id, specs);
    pcs.push_back(p);
    cout << "  [OK] PC added with ID: " << id << "\n";
}

void CafeManager::updatePC() {
    cout << "\n  --- Update PC Specs ---\n";
    int id = getIntInput("  Enter PC ID: ");
    PC* p = findPC(id);
    if (!p) throw runtime_error("PC not found.");
    string specs;
    cout << "  New Specs: "; getline(cin, specs);
    if (specs.empty()) throw invalid_argument("Specs cannot be empty.");
   
    throw runtime_error("Direct specs update not supported. Delete and re-add the PC.");
}

void CafeManager::deletePC() {
    cout << "\n  --- Delete PC ---\n";
    int id = getIntInput("  Enter PC ID: ");
    for (auto it = pcs.begin(); it != pcs.end(); ++it) {
        if ((*it)->getID() == id) {
            if ((*it)->getStatus() == PCStatus::OCCUPIED)
                throw runtime_error("Cannot delete an occupied PC. End the session first.");
            delete *it;
            pcs.erase(it);
            cout << "  [OK] PC deleted.\n";
            return;
        }
    }
    throw runtime_error("PC not found.");
}

void CafeManager::listAllPCs() {
    cout << "\n--- All PCs ---\n";

    if (pcs.empty()) {
        cout << "No PCs registered.\n";
        return;
    }

    for (int i = 0; i < pcs.size(); i++) {
        pcs[i]->displayInfo();
    }
}

void CafeManager::setPCMaintenance() {
    cout << "\n  --- Toggle PC Maintenance ---\n";
    int id = getIntInput("  Enter PC ID: ");
    PC* p = findPC(id);
    if (!p) throw runtime_error("PC not found.");
    if (p->getStatus() == PCStatus::OCCUPIED)
        throw runtime_error("Cannot set an occupied PC to maintenance.");
    if (p->getStatus() == PCStatus::MAINTENANCE) {
        p->setStatus(PCStatus::AVAILABLE);
        cout << "  [OK] PC " << id << " is now Available.\n";
    } else {
        p->setStatus(PCStatus::MAINTENANCE);
        cout << "  [OK] PC " << id << " is now in Maintenance.\n";
    }
}


void CafeManager::startSession() {
    cout << "\n  --- Start Session ---\n";
    listAllPCs();

    int pcID = getIntInput("  Enter PC ID: ");
    PC* p = findPC(pcID);
    if (!p) throw runtime_error("PC not found.");
    if (p->getStatus() != PCStatus::AVAILABLE)
        throw runtime_error("PC is not available.");

    int userID = getIntInput("  Enter User ID: ");
    User* u = findUser(userID);
    if (!u) throw runtime_error("User not found.");

    string startTime = getCurrentTime();
    Session* s = new Session(nextSessionID++, userID, pcID, startTime);
    sessions.push_back(s);

    p->setStatus(PCStatus::OCCUPIED);
    p->setCurrentUserID(userID);

    cout << "  [OK] Session started.\n";
    cout << "  Session ID : " << s->getSessionID() << "\n";
    cout << "  Start Time : " << startTime << "\n";
}

void CafeManager::endSession() {
    cout << "\n  --- End Session ---\n";
    int pcID = getIntInput("  Enter PC ID to end session: ");
    PC* p = findPC(pcID);
    if (!p) throw runtime_error("PC not found.");

    Session* s = findActiveSessionByPC(pcID);
    if (!s) throw runtime_error("No active session on this PC.");

    User* u = findUser(s->getUserID());
    if (!u) throw runtime_error("User linked to session not found.");

    double hours = getDoubleInput("  Hours played: ");
    if (hours <= 0) throw invalid_argument("Hours must be greater than 0.");

    double cost = Billing::calculateCost(u, hours);

    if (u->getBalance() < cost) {
        cout << "  [!] Insufficient balance. Balance: Rs. "
             << fixed << setprecision(2) << u->getBalance()
             << "  |  Required: Rs. " << cost << "\n";
        throw runtime_error("Insufficient balance to end session.");
    }

    u->deductBalance(cost);

    VIPUser* vip = dynamic_cast<VIPUser*>(u);
    if (vip) vip->addHours((int)hours);

    string endTime = getCurrentTime();
    s->endSession(endTime, hours, cost);

    p->setStatus(PCStatus::AVAILABLE);
    p->setCurrentUserID(-1);

    Billing::generateBill(u, s);
}

void CafeManager::listActiveSessions() {
    cout << "\n--- Active Sessions ---\n";

    bool found = false;

    for (int i = 0; i < sessions.size(); i++) {
        if (sessions[i]->isActive()) {
            cout << "Session ID: " << sessions[i]->getSessionID() << endl;
            cout << "User ID: " << sessions[i]->getUserID() << endl;
            cout << "PC ID: " << sessions[i]->getPCID() << endl;
            cout << "Start Time: " << sessions[i]->getStartTime() << endl;
            cout << "------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No active sessions.\n";
    }
}
void CafeManager::listAllSessions() {
    cout << "\n--- All Sessions ---\n";

    if (sessions.empty()) {
        cout << "No sessions recorded.\n";
        return;
    }

    for (int i = 0; i < sessions.size(); i++) {
        sessions[i]->displayInfo();
    }
}
void CafeManager::saveData() {

    ofstream uf(USERS_FILE);
    for (auto u : users) {
        VIPUser* vip = dynamic_cast<VIPUser*>(u);
        if (vip)
            uf << "VIP|" << vip->getID() << "|" << vip->getName() << "|"
               << vip->getContact() << "|" << vip->getMembershipExpiry() << "|"
               << vip->getBalance() << "|" << vip->getTotalHoursPlayed() << "\n";
        else
            uf << "REG|" << u->getID() << "|" << u->getName() << "|"
               << u->getContact() << "|" << u->getBalance() << "\n";
    }
    uf.close();
    ofstream pf(PCS_FILE);
    for (auto p : pcs)
        pf << p->getID() << "|" << p->getSpecs() << "|"
           << (int)p->getStatus() << "|" << p->getCurrentUserID() << "\n";
    pf.close();

    ofstream sf(SESSIONS_FILE);
    for (auto s : sessions)
        sf << s->getSessionID() << "|" << s->getUserID() << "|"
           << s->getPCID() << "|" << s->getStartTime() << "|"
           << s->getEndTime() << "|" << s->getHoursUsed() << "|"
           << s->getTotalCost() << "|" << s->isActive() << "\n";
    sf.close();
}

void CafeManager::loadData() {
    ifstream uf(USERS_FILE);
    if (uf.is_open()) {
        string line;
        while (getline(uf, line)) {
            if (line.empty()) continue;
            istringstream ss(line);
            string token;
            vector<string> tokens;
            while (getline(ss, token, '|')) tokens.push_back(token);

            try {
                if (tokens[0] == "REG" && tokens.size() == 5) {
                    int id      = stoi(tokens[1]);
                    double bal  = stod(tokens[4]);
                    users.push_back(new RegularUser(id, tokens[2], tokens[3], bal));
                    if (id >= nextUserID) nextUserID = id + 1;
                } else if (tokens[0] == "VIP" && tokens.size() == 7) {
                    int id      = stoi(tokens[1]);
                    double bal  = stod(tokens[5]);
                    int hrs     = stoi(tokens[6]);
                    VIPUser* v  = new VIPUser(id, tokens[2], tokens[3], tokens[4], bal);
                    v->addHours(hrs);
                    users.push_back(v);
                    if (id >= nextUserID) nextUserID = id + 1;
                }
            } catch (...) { }
        }
        uf.close();
    }

    ifstream pf(PCS_FILE);
    if (pf.is_open()) {
        string line;
        while (getline(pf, line)) {
            if (line.empty()) continue;
            istringstream ss(line);
            vector<string> tokens;
            string token;
            while (getline(ss, token, '|')) tokens.push_back(token);

            try {
                if (tokens.size() == 4) {
                    int id     = stoi(tokens[0]);
                    PCStatus s = (PCStatus)stoi(tokens[2]);
                    int uid    = stoi(tokens[3]);
                    PC* p      = new PC(id, tokens[1]);
                    p->setStatus(s);
                    p->setCurrentUserID(uid);
                    pcs.push_back(p);
                }
            } catch (...) {  }
        }
        pf.close();
    }

    ifstream sf(SESSIONS_FILE);
    if (sf.is_open()) {
        string line;
        while (getline(sf, line)) {
            if (line.empty()) continue;
            istringstream ss(line);
            vector<string> tokens;
            string token;
            while (getline(ss, token, '|')) tokens.push_back(token);

            try {
                if (tokens.size() == 8) {
                    int sid    = stoi(tokens[0]);
                    int uid    = stoi(tokens[1]);
                    int pid    = stoi(tokens[2]);
                    double hrs = stod(tokens[5]);
                    double cst = stod(tokens[6]);
                    bool active= (tokens[7] == "1");

                    Session* s = new Session(sid, uid, pid, tokens[3]);
                    if (!active) s->endSession(tokens[4], hrs, cst);
                    sessions.push_back(s);
                    if (sid >= nextSessionID) nextSessionID = sid + 1;
                }
            } catch (...) { }
        }
        sf.close();
    }
}
