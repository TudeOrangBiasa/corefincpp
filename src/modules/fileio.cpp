#include "../../include/headers/fileio.h"

using namespace std;

// buat dapet file ini di mana (path executablenya)
std::string getExecutablePath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        std::string path(result, count);
        return path.substr(0, path.find_last_of('/'));
    }
    return "";
}

// buat load data user dari file data.txt
void loadUserData(vector<User>& users) {
    users.clear(); // bersihin dulu vector users
    string basePath = getExecutablePath();
    ifstream file(basePath + "/../data/data.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << basePath << "/../data/data.txt" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        User user;
        if (iss >> user.username >> user.password >> user.balance) {
            loadTransactions(user); // Load transactions for each user
            users.push_back(user);
        }
    }
    file.close();
}

// buat load transaksi dari file <username>_transactions.txt
void loadTransactions(User& user) {
    user.transactions.clear(); // bersihin dulu transactionsnya
    string basePath = getExecutablePath();
    ifstream transFile(basePath + "/../data/" + user.username + "_transactions.txt");
    if (!transFile.is_open()) {
        return;
    }

    string line;
    while (getline(transFile, line)) {
        istringstream iss(line);
        Transaction transaction;
        string name, category, date;
        double amount;

       // Membaca semua nama transaksi sampai bertemu koma
        getline(iss, name, ',');
        if (iss >> category >> amount >> date) {
            transaction.name = name;
            transaction.category = category;
            transaction.amount = amount;
            transaction.date = date;
            user.transactions.push_back(transaction);
        }
    }
    transFile.close();
}

// buat save transaksi ke file <username>_transactions.txt
void saveTransactions(const User& user) {
    string basePath = getExecutablePath();
    ofstream transFile(basePath + "/../data/" + user.username + "_transactions.txt");
    if (!transFile.is_open()) {
        cerr << "Error: Unable to open " << basePath + "/../data/" + user.username + "_transactions.txt" << " for writing" << endl;
        return;
    }

    for (const auto& transaction : user.transactions) {
        transFile << transaction.name << "," << transaction.category << " " 
                 << transaction.amount << " " << transaction.date << endl;
    }
    transFile.close();
}

void saveUserData(const vector<User>& users) {
    string basePath = getExecutablePath();
    vector<User> existingUsers;
    
    // membaca semua user yang ada di file data.txt
    ifstream readFile(basePath + "/../data/data.txt");
    if (readFile.is_open()) {
        string line;
        while (getline(readFile, line)) {
            istringstream iss(line);
            User user;
            if (iss >> user.username >> user.password >> user.balance) {
                // Only add users that aren't in the updated users vector
                bool found = false;
                for (const auto& updatedUser : users) {
                    if (updatedUser.username == user.username) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    existingUsers.push_back(user);
                }
            }
        }
        readFile.close();
    }

    // Tulis semua user ke file data.txt
    ofstream writeFile(basePath + "/../data/data.txt");
    if (!writeFile.is_open()) {
        cerr << "Error: Unable to open " << basePath << "/../data/data.txt for writing" << endl;
        return;
    }

    // tulis semua user yang diupdate
    for (const auto& user : users) {
        writeFile << user.username << " " << user.password << " " << user.balance << endl;
    }

    // tulis semua user yang belum diupdate
    for (const auto& user : existingUsers) {
        writeFile << user.username << " " << user.password << " " << user.balance << endl;
    }

    writeFile.close();
}

// buat load user dari file data.txt
bool loadUser(const string& username, User& user) {
    string basePath = getExecutablePath();
    ifstream file(basePath + "/../data/data.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << basePath << "/../data/data.txt" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        if (iss >> user.username >> user.password >> user.balance) {
            if (user.username == username) {
                loadTransactions(user);
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}