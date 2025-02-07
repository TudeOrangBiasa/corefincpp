#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include <limits.h>
#include "user.h"

std::string getExecutablePath();
void loadUserData(std::vector<User>& users);
void saveUserData(const std::vector<User>& users);
void loadTransactions(User& user);
bool loadUser(const std::string& username, User& user);
void saveTransactions(const User& user);

#endif // FILEIO_H