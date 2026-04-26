#include "Billing.h"
#include <iostream>
#include <iomanip>
using namespace std;

double Billing::calculateCost(User* user, double hours) {
    return user->getHourlyRate() * hours;
}

void Billing::generateBill(User* user, Session* session) {
    cout << "\n";
    cout << "  ============================================\n";
    cout << "          GAMING CAFE - SESSION BILL\n";
    cout << "  ============================================\n";
    cout << "  User ID   : " << user->getID()        << "\n";
    cout << "  Name      : " << user->getName()       << "\n";
    cout << "  User Type : " << user->getUserType()   << "\n";
    cout << "  PC ID     : " << session->getPCID()    << "\n";
    cout << "  Start     : " << session->getStartTime() << "\n";
    cout << "  End       : " << session->getEndTime()   << "\n";
    cout << "  --------------------------------------------\n";
    cout << "  Hours     : " << fixed << setprecision(2) << session->getHoursUsed() << " hrs\n";
    cout << "  Rate      : Rs. " << fixed << setprecision(2) << user->getHourlyRate() << "/hr\n";
    cout << "  --------------------------------------------\n";
    cout << "  TOTAL     : Rs. " << fixed << setprecision(2) << session->getTotalCost() << "\n";
    cout << "  Remaining : Rs. " << fixed << setprecision(2) << user->getBalance() << "\n";
    cout << "  ============================================\n\n";
}
