#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

struct Transaction {
    std::string name;
    double amount;
    std::string date;
    std::string category;
};

struct User {
    std::string username;
    std::string password;
    double balance;
    std::vector<Transaction> transactions;

    User() : balance(0) {}
    User(const std::string& uname, const std::string& pwd, double bal = 0)
        : username(uname), password(pwd), balance(bal) {}
};

#endif