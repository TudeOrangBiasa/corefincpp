#ifndef FINANCE_H
#define FINANCE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <ctime>
#include "../extlib/color.h"
#include "fileio.h"
#include "user.h"

void addTransaction(User& user, std::vector<User>& users, const std::string& transactionName, double amount, const std::string& date, const std::string& category);
void viewReport(const User& user);
void resetReport(User& user, std::vector<User>& users);
void saveReport(const User& user);
void displayTransactions(const User& user); // Add this declaration
bool editTransaction(User& user, std::vector<User>& users, const std::string& transactionName, const std::string& newTransactionName, double newAmount, const std::string& newDate, const std::string& newCategory);
bool deleteTransaction(User& user, std::vector<User>& users, const std::string& transactionName);

#endif