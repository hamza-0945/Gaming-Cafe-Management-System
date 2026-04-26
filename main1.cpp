#include "CafeManager.h"
#include <iostream>
#include <stdexcept>
#include <limits>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader() {
    cout << "\n";
    cout << "         GAMING CAFE MANAGEMENT SYSTEM      \n";
}

void printMainMenu() {
    printHeader();
    cout << "\n  ---- MAIN MENU ----\n\n";
    cout << "  1. User Management\n";
    cout << "  2. PC Management\n";
    cout << "  3. Session Management\n";
    cout << "  4. Save Data\n";
    cout << "  0. Exit\n\n";
    cout << "  Enter choice: ";
}

void userMenu(CafeManager& mgr) {
    int choice;
    do {
        clearScreen();
        printHeader();
        cout << "\n  ---- USER MANAGEMENT ----\n\n";
        cout << "  1. Add Regular User\n";
        cout << "  2. Add VIP User\n";
        cout << "  3. Update User\n";
        cout << "  4. Delete User\n";
        cout << "  5. Search User\n";
        cout << "  6. List All Users\n";
        cout << "  0. Back\n\n";
        cout << "  Enter choice: ";
        cin >> choice; cin.ignore();

        try {
            switch (choice) {
                case 1: mgr.addRegularUser(); break;
                case 2: mgr.addVIPUser();     break;
                case 3: mgr.updateUser();     break;
                case 4: mgr.deleteUser();     break;
                case 5: mgr.searchUser();     break;
                case 6: mgr.listAllUsers();   break;
                case 0: break;
                default: cout << "  Invalid choice.\n";
            }
        } catch (const exception& e) {
            cout << "\n  ERROR " << e.what() << "\n";
        }

        if (choice != 0) {
            cout << "\n  Press Enter to continue...";
            cin.get();
        }
    } while (choice != 0);
}

void pcMenu(CafeManager& mgr) {
    int choice;
    do {
        clearScreen();
        printHeader();
        cout << "\n  ---- PC MANAGEMENT ----\n\n";
        cout << "  1. Add PC\n";
        cout << "  2. Delete PC\n";
        cout << "  3. List All PCs\n";
        cout << "  4. Set Maintenance\n";
        cout << "  0. Back\n\n";
        cout << "  Enter choice: ";
        cin >> choice; cin.ignore();

        try {
            switch (choice) {
                case 1: mgr.addPC();              break;
                case 2: mgr.deletePC();           break;
                case 3: mgr.listAllPCs();         break;
                case 4: mgr.setPCMaintenance();   break;
                case 0: break;
                default: cout << " Invalid choice.\n";
            }
        } catch (const exception& e) {
            cout << "\n ERROR" << e.what() << "\n";
        }

        if (choice != 0) {
            cout << "\n  Press Enter to continue...";
            cin.get();
        }
    } while (choice != 0);
}

void sessionMenu(CafeManager& mgr) {
    int choice;
    do {
        clearScreen();
        printHeader();
        cout << "\n  ---- SESSION MANAGEMENT ----\n\n";
        cout << "  1. Start Session\n";
        cout << "  2. End Session & Generate Bill\n";
        cout << "  3. View Active Sessions\n";
        cout << "  4. View All Sessions\n";
        cout << "  0. Back\n\n";
        cout << "  Enter choice: ";
        cin >> choice; cin.ignore();

        try {
            switch (choice) {
                case 1: mgr.startSession();      break;
                case 2: mgr.endSession();        break;
                case 3: mgr.listActiveSessions();break;
                case 4: mgr.listAllSessions();   break;
                case 0: break;
                default: cout << "  Invalid choice.\n";
            }
        } catch (const exception& e) {
            cout << "\n  ERROR " << e.what() << "\n";
        }

        if (choice != 0) {
            cout << "\n  Press Enter to continue...";
            cin.get();
        }
    } while (choice != 0);
}

int main() {
    CafeManager manager;

    int choice;
    do {
        clearScreen();
        printMainMenu();
        cin >> choice; cin.ignore();

        try {
            switch (choice) {
                case 1: userMenu(manager);    break;
                case 2: pcMenu(manager);      break;
                case 3: sessionMenu(manager); break;
                case 4:
                    manager.saveData();
                    cout << "\n  Data saved successfully.\n";
                    cout << "\n  Press Enter to continue...";
                    cin.get();
                    break;
                case 0:
                    cout << "\n  Saving data...\n";
                    manager.saveData();
                    cout << "  Goodbye!\n\n";
                    break;
                default:
                    cout << "\n  Invalid choice.\n";
                    cout << "\n  Press Enter to continue...";
                    cin.get();
            }
        } catch (const exception& e) {
            cout << "\n  FATAL ERROR " << e.what() << "\n";
            cout << "\n  Press Enter to continue...";
            cin.get();
        }
    } while (choice != 0);

    return 0;
}
