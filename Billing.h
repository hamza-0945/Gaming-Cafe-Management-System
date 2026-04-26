#ifndef BILLING_H
#define BILLING_H

#include "User.h"
#include "Session.h"

class Billing {
public:
    static double calculateCost(User* user, double hours);

    static void generateBill(User* user, Session* session);
};

#endif
