#include "../../include/headers/auth.h"
#include "../../include/headers/clearScreen.h"
#include "../../include/headers/fileio.h"

using namespace std;

// Login fungsi 
bool login(const string& username, const string& password) {
    User user;
    if (loadUser(username, user) && user.password == password) {
        cout << "Login successful!" << endl;
        return true;
    }
    cout << "Invalid login credentials for user: " << username << endl;
    return false;
}

// SignUp fungsi 
bool signUp(const string& username, const string& password) {
    vector<User> users;
    loadUserData(users);
    for (const User& user : users) {
        if (user.username == username) {
            cout << "Username already exists: " << username << endl;
            return false;
        }
    }
    User newUser(username, password, 0); // Initialize balance to 0
    users.push_back(newUser);
    saveUserData(users);
    cout << "User signed up successfully: " << username << endl;
    return true;
}