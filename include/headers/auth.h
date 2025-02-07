#ifndef AUTH_H
#define AUTH_H

#include <iostream>
#include <string>
#include "fileio.h"
#include "user.h"

bool login(const std::string& username, const std::string& password);
bool signUp(const std::string& username, const std::string& password);

#endif // AUTH_H