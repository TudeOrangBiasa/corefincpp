#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "../include/headers/user.h"
#include "../include/headers/finance.h"
#include "../include/headers/fileio.h"
#include "../include/headers/auth.h"
#include "../include/headers/clearScreen.h"
#include "../include/extlib/color.h"

using namespace std;

vector<User> users;

void displayMainMenu() {
    cout << fgCyan() << "================================================" << reset() << endl;
    cout << bgBlue() << fgWhite() << bold() << "           PERSONAL FINANCE MANAGER           " << reset() << endl;
    cout << fgCyan() << "================================================" << reset() << endl << endl;
    cout << fgCyan() << "1. " << fgWhite() << "Login" << reset() << endl;
    cout << fgCyan() << "2. " << fgWhite() << "Sign Up" << reset() << endl;
    cout << fgCyan() << "3. " << fgWhite() << "Exit" << reset() << endl;
    cout << endl << fgCyan() << "================================================" << reset() << endl;
    cout << endl << fgYellow() << "Enter choice: " << reset();
}

void displayUserMenu() {
    cout << fgCyan() << "================================================" << reset() << endl;
    cout << bgBlue() << fgWhite() << bold() << "              TRANSACTION MENU               " << reset() << endl;
    cout << fgCyan() << "================================================" << reset() << endl << endl;
    cout << fgCyan() << "1. " << fgWhite() << "Add Transaction" << reset() << endl;
    cout << fgCyan() << "2. " << fgWhite() << "View Report" << reset() << endl;
    cout << fgCyan() << "3. " << fgWhite() << "Reset Report" << reset() << endl;
    cout << fgCyan() << "4. " << fgWhite() << "Save Report" << reset() << endl;
    cout << fgCyan() << "5. " << fgWhite() << "Edit Transaction" << reset() << endl;
    cout << fgCyan() << "6. " << fgWhite() << "Delete Transaction" << reset() << endl;
    cout << fgCyan() << "7. " << fgWhite() << "Exit to Main Menu" << reset() << endl;
    cout << fgCyan() << "8. " << fgWhite() << "Exit" << reset() << endl;
    cout << endl << fgCyan() << "================================================" << reset() << endl;
    cout << endl << fgYellow() << "Enter choice: " << reset();
}

void userMenu(User* currentUser) {
    int choice;
    while (true) {
        displayUserMenu();
        cin >> choice;
        cin.ignore(); // Ignore the newline character left in the buffer
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the rest of the input
            cout << fgRed() << "Invalid input. Please enter a number." << reset() << endl;
            cout << "Press Enter to continue...";
            cin.get();
            clearScreen();
            continue;
        } else {
            switch (choice) {
                case 1: {
                    clearScreen();
                    string transactionName, category, date;
                    double amount;
                    cout << bgBlue() << fgWhite() << bold() << "              ADD TRANSACTION               " << reset() << endl << endl;
                    cout << fgYellow() << "Enter transaction name: " << reset();
                    getline(cin, transactionName);
                    cout << fgYellow() << "Enter category (pengeluaran/pemasukan): " << reset();
                    getline(cin, category);
                    cout << fgYellow() << "Enter amount: " << reset();
                    cin >> amount;
                    cin.ignore();
                    cout << fgYellow() << "Enter date (YYYY-MM-DD): " << reset();
                    getline(cin, date);
                    addTransaction(*currentUser, users, transactionName, amount, date, category);
                    cout << "Press Enter to continue...";
                    cin.get();
                    clearScreen();
                    break;
                }
                case 2:
                    clearScreen();
                    viewReport(*currentUser);
                    cout << "Press Enter to continue...";
                    cin.get();
                    clearScreen();
                    break;
                case 3:
                    clearScreen();
                    resetReport(*currentUser, users);
                    cout << "Press Enter to continue...";
                    cin.get();
                    clearScreen();
                    break;
                case 4:
                    saveReport(*currentUser);
                    displayTransactions(*currentUser);
                    cout << "Press Enter to continue...";
                    cin.get();
                    clearScreen();
                    break;
                case 5: {
                    clearScreen();
                    string transactionName, newTransactionName, newCategory, newDate;
                    double newAmount;
                    cout << bgBlue() << fgWhite() << bold() << "             EDIT TRANSACTION              " << reset() << endl << endl;
                    displayTransactions(*currentUser);
                    cout << fgYellow() << "Enter transaction name to edit: " << reset();
                    getline(cin, transactionName);
                    cout << fgYellow() << "Enter new transaction name: " << reset();
                    getline(cin, newTransactionName);
                    cout << fgYellow() << "Enter new category (pengeluaran/pemasukan): " << reset();
                    getline(cin, newCategory);
                    cout << fgYellow() << "Enter new amount: " << reset();
                    cin >> newAmount;
                    cin.ignore();
                    cout << fgYellow() << "Enter new date (YYYY-MM-DD): " << reset();
                    getline(cin, newDate);
                    if (!editTransaction(*currentUser, users, transactionName, newTransactionName, newAmount, newDate, newCategory)) {
                        cout << fgRed() << "Transaction not found." << reset() << endl;
                    }
                    cout << "Press Enter to continue...";
                    cin.get();
                    clearScreen();
                    break;
                }
                case 6: {
                    clearScreen();
                    string transactionName;
                    cout << bgBlue() << fgWhite() << bold() << "            DELETE TRANSACTION             " << reset() << endl << endl;
                    displayTransactions(*currentUser);
                    cout << fgYellow() << "Enter transaction name to delete: " << reset();
                    getline(cin, transactionName);
                    if (!deleteTransaction(*currentUser, users, transactionName)) {
                        cout << fgRed() << "Transaction not found." << reset() << endl;
                    }
                    cout << "Press Enter to continue...";
                    cin.get();
                    clearScreen();
                    break;
                }
                case 7:
                    clearScreen();
                    return;
                case 8:
                    cout << fgGreen() << "Thank you for using Personal Finance Manager!" << reset() << endl;
                    exit(0);
                default:
                    cout << fgRed() << "Invalid choice. Please try again." << reset() << endl;
                    cout << "Press Enter to continue...";
                    cin.get();
                    clearScreen();
            }
        }
    }
}

int main() {
    string username, password;
    int choice;
    int invalidAttempts = 0;
    const int maxInvalidAttempts = 3;

    while (true) {
        clearScreen();
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << fgRed() << "Invalid input. Please enter a number." << reset() << endl;
            cout << "Press Enter to continue...";
            cin.get();
            invalidAttempts++;
        } else {
            switch (choice) {
                case 1: {
                    clearScreen();
                    cout << bgBlue() << fgWhite() << bold() << "                  LOGIN                    " << reset() << endl << endl;
                    cout << fgYellow() << "Enter username: " << reset();
                    getline(cin, username);
                    cout << fgYellow() << "Enter password: " << reset();
                    getline(cin, password);
                    User currentUser;
                    if (login(username, password)) {
                        if (loadUser(username, currentUser)) {
                            cout << fgGreen() << "Login successful for user: " << username << reset() << endl;
                            cout << "User balance: " << currentUser.balance << endl;
                            cout << "User transactions loaded: " << currentUser.transactions.size() << endl;
                            cout << "Press Enter to continue...";
                            cin.get();
                            clearScreen();
                            userMenu(&currentUser);
                        }
                    } else {
                        cout << fgRed() << "Invalid login credentials." << reset() << endl;
                        cout << "Press Enter to continue...";
                        cin.get();
                    }
                    invalidAttempts = 0;
                    break;
                }
                case 2: {
                    clearScreen();
                    cout << bgBlue() << fgWhite() << bold() << "                 SIGN UP                   " << reset() << endl << endl;
                    cout << fgYellow() << "Enter username: " << reset();
                    getline(cin, username);
                    cout << fgYellow() << "Enter password: " << reset();
                    getline(cin, password);
                    if (signUp(username, password)) {
                        cout << fgGreen() << "User signed up successfully." << reset() << endl;
                    } else {
                        cout << fgRed() << "Username already exists." << reset() << endl;
                    }
                    cout << "Press Enter to continue...";
                    cin.get();
                    invalidAttempts = 0;
                    break;
                }
                case 3:
                    saveUserData(users);
                    cout << fgGreen() << "Thank you for using Personal Finance Manager!" << reset() << endl;
                    return 0;
                default:
                    cout << fgRed() << "Invalid choice. Please try again." << reset() << endl;
                    cout << "Press Enter to continue...";
                    cin.get();
                    invalidAttempts++;
            }
        }

        if (invalidAttempts >= maxInvalidAttempts) {
            cout << fgRed() << "Too many invalid attempts. Exiting program." << reset() << endl;
            break;
        }
    }

    return 0;
}