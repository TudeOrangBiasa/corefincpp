#include "../../include/headers/finance.h"

using namespace std;

// Validasi buat format tanggal
bool isValidDateFormat(const string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    try {
        int year = stoi(date.substr(0, 4));
        int month = stoi(date.substr(5, 2));
        int day = stoi(date.substr(8, 2));
        
        if (year < 1900 || year > 2100) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;
        
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
        if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeapYear ? 29 : 28)) return false;
        }
        return true;
    } catch (...) {
        return false;
    }
}

// Cek apakah transaksi sudah ada apa belum
bool isTransactionExists(const User& user, const string& transactionName) {
    return any_of(user.transactions.begin(), user.transactions.end(), [&](const Transaction& t) { return t.name == transactionName; });
}

// Cek apakah saldo masih valid atau tidak
bool isBalanceValid(double currentBalance, double amount) {
    const double MAX_BALANCE = 1e15;
    double newBalance = currentBalance + amount;
    return (newBalance >= -MAX_BALANCE && newBalance <= MAX_BALANCE);
}

// Menampilkan transaksi yang ada
void displayTransactions(const User& user) {
    // Validasi apakah user punya transaksi atau tidak
    if (user.transactions.empty()) {
        cout << fgYellow() << "No transactions found." << reset() << endl;
        return;
    } 

    cout << fgCyan() << "-------------------------------------------------------------------------" << reset() << endl;
    cout << left << setw(20) << "Name" << setw(15) << "Category" << setw(15) << "Amount" << setw(15) << "Date" << endl;
    cout << fgCyan() << "-------------------------------------------------------------------------" << reset() << endl;
    
    for (const auto& transaction : user.transactions) {
        cout << left << setw(20) << transaction.name 
             << setw(15) << transaction.category 
             << setw(15) << fixed << setprecision(2) << transaction.amount 
             << setw(15) << transaction.date << endl;
    }
    cout << fgCyan() << "--------------------------------------------------------------------------" << reset() << endl;
}

void addTransaction(User& user, vector<User>& users, const string& transactionName, double amount, const string& date, const string& category) {
    // Validasi input
    if (transactionName.empty()) {
        cout << fgRed() << "Transaction name cannot be empty." << reset() << endl;
        return;
    }

    // Cek apakah transaksi sudah ada atau belum
    if (isTransactionExists(user, transactionName)) {
        cout << fgRed() << "Transaction with this name already exists." << reset() << endl;
        return;
    }

    // Validasi kategori transaksi
    string lowerCategory = category;
    transform(lowerCategory.begin(), lowerCategory.end(), lowerCategory.begin(), ::tolower);
    if (lowerCategory != "pengeluaran" && lowerCategory != "pemasukan") {
        cout << fgRed() << "Invalid category. Please enter either 'pengeluaran' atau 'pemasukan'." << reset() << endl;
        return;
    }

    if (amount <= 0) {
        cout << fgRed() << "Invalid amount. Please enter a positive amount." << reset() << endl;
        return;
    }

    if (!isValidDateFormat(date)) {
        cout << fgRed() << "Invalid date format. Please use YYYY-MM-DD format." << reset() << endl;
        return;
    }

    double originalBalance = user.balance;
    double transactionAmount = (lowerCategory == "pengeluaran") ? -amount : amount;

    if (!isBalanceValid(user.balance, transactionAmount)) {
        cout << fgRed() << "Transaction would exceed balance limits." << reset() << endl;
        return;
    }

    user.transactions.push_back({transactionName, transactionAmount, date, lowerCategory});
    user.balance += transactionAmount;

    bool userFound = false;
    for (auto& u : users) {
        if (u.username == user.username) {
            u.balance = user.balance;
            userFound = true;
            break;
        }
    }

    // kalo user ga ada di vector users, maka user ditambahin
    if (!userFound) {
        users.push_back(user);
    }

    try {
        saveTransactions(user);
        saveUserData(users);
        cout << fgGreen() << "Transaction added successfully. Balance updated from " 
             << originalBalance << " to " << user.balance << reset() << endl;
    } catch (const exception& e) {
        cout << fgRed() << "Error saving transaction: " << e.what() << reset() << endl;
    }
}

// Ini fungsi buat nampilin report transaksi tapi beda sama displayTransactions
// Karena ini nampilin report yang lebih lengkap :D
void viewReport(const User& user) {
    double totalIncome = 0, totalExpense = 0;
    
    cout << fgCyan() << "===================================================" << reset() << endl;
    cout << bgBlue() << fgWhite() << bold() << "           Transaction Report for " << user.username << "           " << reset() << endl;
    cout << fgCyan() << "===================================================" << reset() << endl << endl;
    
    displayTransactions(user);
    
    for (const auto& transaction : user.transactions) {
        if (transaction.amount > 0) {
            totalIncome += transaction.amount;
        } else {
            totalExpense += transaction.amount;
        }
    }

    double netBalance = user.balance;
    double totalExpenseAbs = -totalExpense;
    double total = totalIncome + totalExpenseAbs;
    double incomePercentage = total > 0 ? (totalIncome / total) * 100 : 0;
    double expensePercentage = total > 0 ? (totalExpenseAbs / total) * 100 : 0;

    cout << fgCyan() << "\nFinancial Summary:" << reset() << endl;
    cout << fgGreen() << "Total Income: " << fixed << setprecision(2) << totalIncome << reset() << endl;
    cout << fgRed() << "Total Expense: " << fixed << setprecision(2) << totalExpenseAbs << reset() << endl;
    cout << (netBalance >= 0 ? fgGreen() : fgRed()) << "Net Balance: " << fixed << setprecision(2) << netBalance << reset() << endl;
    cout << fgBrightGreen() << "Income Percentage: " << fixed << setprecision(2) << incomePercentage << "%" << endl;
    cout << fgBrightRed << "Expense Percentage: " << fixed << setprecision(2) << expensePercentage << "%" << endl;
}

// ini buat reset report yang ada di user di file data <username>_transactions.txt
void resetReport(User& user, vector<User>& users) {
    viewReport(user);
    cout << fgYellow() << "\nAre you sure you want to reset the report? (y/n): " << reset();
    char confirmation;
    cin >> confirmation;
    
    if (tolower(confirmation) == 'y') {
        double originalBalance = user.balance;
        user.transactions.clear();
        user.balance = 0;

        for (auto& u : users) {
            if (u.username == user.username) {
                u.balance = user.balance;
                break;
            }
        }

        try {
            string basePath = getExecutablePath();
            ofstream transFile(basePath + "/../data/" + user.username + "_transactions.txt", ofstream::trunc);
            transFile.close();
            
            saveUserData(users);
            cout << fgGreen() << "Report has been reset. Balance changed from " 
                 << originalBalance << " to " << user.balance << reset() << endl;
        } catch (const exception& e) {
            cout << fgRed() << "Error resetting report: " << e.what() << reset() << endl;
        }
    } else {
        cout << fgYellow() << "Reset report canceled." << reset() << endl;
    }
}

// buat save report ke file <username>_report_<timestamp>.txt
void saveReport(const User& user) {
    char confirmation;
    cout << fgYellow() << "Are you sure you want to save the report? (y/n): " << reset();
    cin >> confirmation;
    if (tolower(confirmation) != 'y') {
        cout << fgYellow() << "Save report canceled." << reset() << endl;
        return;
    }else {
    
    try {
        string basePath = getExecutablePath();
        string filename = basePath + "/../reports/" + user.username + "_report_" + 
                         to_string(time(nullptr)) + ".txt";
        
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open report file for writing");
        }

        double totalIncome = 0, totalExpense = 0;
        
        file << "Transaction Report for " << user.username << endl;
        file << string(50, '=') << endl << endl;
        
        file << left << setw(20) << "Name" << setw(15) << "Category" 
             << setw(15) << "Amount" << setw(15) << "Date" << endl;
        file << string(65, '-') << endl;

        for (const auto& transaction : user.transactions) {
            file << left << setw(20) << transaction.name 
                 << setw(15) << transaction.category 
                 << setw(15) << fixed << setprecision(2) << abs(transaction.amount) // Use abs() here
                 << setw(15) << transaction.date << endl;
            
            if (transaction.amount > 0) {
                totalIncome += transaction.amount;
            } else {
                totalExpense += transaction.amount;
            }
        }

        file << string(65, '-') << endl << endl;
        file << "Financial Summary:" << endl;
        file << "Total Income: " << fixed << setprecision(2) << totalIncome << endl;
        file << "Total Expense: " << fixed << setprecision(2) << abs(totalExpense) << endl; // Use abs() here
        file << "Net Balance: " << fixed << setprecision(2) << user.balance << endl;
        
        double total = totalIncome - totalExpense;
        if (total > 0) {
            file << "Income Percentage: " << fixed << setprecision(2) 
                 << (totalIncome / total * 100) << "%" << endl;
            file << "Expense Percentage: " << fixed << setprecision(2) 
                 << (abs(totalExpense) / total * 100) << "%" << endl; // Use abs() here
        }

        file.close();
        cout << fgGreen() << "Report saved successfully to: " << filename << reset() << endl;
    } catch (const exception& e) {
        cout << fgRed() << "Error saving report: " << e.what() << reset() << endl;
    }
    }
}

// Ini buat edit transaksi yang ada
bool editTransaction(User& user, vector<User>& users, const string& transactionName, const string& newTransactionName, double newAmount, const string& newDate, const string& newCategory) {
    char confirmation;
    cout << fgYellow() << "Are you sure you want to edit this transaction? (y/n): " << reset();
    cin >> confirmation;

    if (tolower(confirmation) != 'y') {
        cout << fgYellow() << "Edit transaction canceled." << reset() << endl;
        return false;
    } else {
    if (newTransactionName.empty()) {
        cout << fgRed() << "Transaction name cannot be empty." << reset() << endl;
        return false;
    } 

    string lowerNewCategory = newCategory;
    transform(lowerNewCategory.begin(), lowerNewCategory.end(), 
    lowerNewCategory.begin(), ::tolower);
    
    if (lowerNewCategory != "pengeluaran" && lowerNewCategory != "pemasukan") {
        cout << fgRed() << "Invalid category. Please enter either 'pengeluaran' atau 'pemasukan'." 
             << reset() << endl;
        return false;
    }

    if (newAmount <= 0) {
        cout << fgRed() << "Invalid amount. Please enter a positive amount." << reset() << endl;
        return false;
    }

    if (!isValidDateFormat(newDate)) {
        cout << fgRed() << "Invalid date format. Please use YYYY-MM-DD format." << reset() << endl;
        return false;
    }

    double originalBalance = user.balance;
    bool found = false;

    for (auto& transaction : user.transactions) {
        if (transaction.name == transactionName) {
            user.balance -= transaction.amount;
            double newTransactionAmount = (lowerNewCategory == "pengeluaran") ? -newAmount : newAmount;
            
            if (!isBalanceValid(user.balance, newTransactionAmount)) {
                cout << fgRed() << "Transaction would exceed balance limits." << reset() << endl;
                return false;
            }

            transaction.name = newTransactionName;
            transaction.amount = newTransactionAmount;
            transaction.date = newDate;
            transaction.category = lowerNewCategory;
            user.balance += newTransactionAmount;
            found = true;
            break;
        }
    }

    if (found) {
        for (auto& u : users) {
            if (u.username == user.username) {
                u.balance = user.balance;
                break;
            }
        }

        try {
            saveTransactions(user);
            saveUserData(users);
            cout << fgGreen() << "Transaction updated successfully. Balance changed from " 
                 << originalBalance << " to " << user.balance << reset() << endl;
            return true;
        } catch (const exception& e) {
            cout << fgRed() << "Error updating transaction: " << e.what() << reset() << endl;
            return false;
        }
    }

    cout << fgRed() << "Transaction not found." << reset() << endl;
    return false;
    }
}

bool deleteTransaction(User& user, vector<User>& users, const string& transactionName) {
    double originalBalance = user.balance;
    char confirmation;
    cout << fgYellow() << "Are you sure you want to delete this transaction? (y/n): " << reset();
    cin >> confirmation;

    if (tolower(confirmation) != 'y') {
        cout << fgYellow() << "Delete transaction canceled." << reset() << endl;
        return false;
    } else {
    for (auto it = user.transactions.begin(); it != user.transactions.end(); ++it) {
        if (it->name == transactionName) {
            user.balance -= it->amount;
            user.transactions.erase(it);

            for (auto& u : users) {
                if (u.username == user.username) {
                    u.balance = user.balance;
                    break;
                }
            }

            try {
                saveTransactions(user);
                saveUserData(users);
                cout << fgGreen() << "Transaction deleted successfully. Balance changed from " 
                     << originalBalance << " to " << user.balance << reset() << endl;
                return true;
            } catch (const exception& e) {
                cout << fgRed() << "Error deleting transaction: " << e.what() << reset() << endl;
                return false;
            }
        }
    }
    

    cout << fgRed() << "Transaction not found." << reset() << endl;
    return false;
    }
}