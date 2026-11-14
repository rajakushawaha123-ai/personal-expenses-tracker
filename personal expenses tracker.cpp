#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

class Transaction {
public:
    int id;
    string type;
    string category;
    double amount;
    string date;

    void input(int transactionId) {
        id = transactionId;

        cout << "Enter Type (Income/Expense): ";
        cin >> type;

        cout << "Enter Category: ";
        cin >> category;

        cout << "Enter Amount: ";
        cin >> amount;

        cout << "Enter Date (DD-MM-YYYY): ";
        cin >> date;
    }

    void display() const {
        cout << left << setw(8) << id
             << setw(12) << type
             << setw(15) << category
             << setw(12) << amount
             << date << endl;
    }
};

class ExpenseTracker {
private:
    vector<Transaction> transactions;
    int nextId = 1;

public:

    void addTransaction() {
        Transaction t;

        t.input(nextId++);
        transactions.push_back(t);

        cout << "\nTransaction Added Successfully!\n";
    }

    void viewTransactions() {
        if (transactions.empty()) {
            cout << "\nNo Transactions Found!\n";
            return;
        }

        cout << "\nID      Type        Category       Amount      Date\n";
        cout << "-------------------------------------------------------\n";

        for (const auto &t : transactions) {
            t.display();
        }
    }

    void calculateBalance() {
        double income = 0;
        double expense = 0;

        for (const auto &t : transactions) {
            if (t.type == "Income" || t.type == "income") {
                income += t.amount;
            }
            else {
                expense += t.amount;
            }
        }

        cout << "\nTotal Income: " << income;
        cout << "\nTotal Expenses: " << expense;
        cout << "\nRemaining Balance: "
             << income - expense << endl;
    }

    void saveToFile() {
        ofstream file("expenses.txt");

        for (const auto &t : transactions) {
            file << t.id << " "
                 << t.type << " "
                 << t.category << " "
                 << t.amount << " "
                 << t.date << endl;
        }

        file.close();

        cout << "\nData Saved Successfully!\n";
    }

    void loadFromFile() {
        ifstream file("expenses.txt");
        Transaction t;

        while (file >> t.id >> t.type
                    >> t.category >> t.amount >> t.date) {

            transactions.push_back(t);

            if (t.id >= nextId) {
                nextId = t.id + 1;
            }
        }

        file.close();
    }
};

int main() {
    ExpenseTracker tracker;

    tracker.loadFromFile();

    int choice;

    do {
        cout << "\n================================\n";
        cout << "     PERSONAL EXPENSE TRACKER\n";
        cout << "================================\n";

        cout << "1. Add Income/Expense\n";
        cout << "2. View Transactions\n";
        cout << "3. Calculate Balance\n";
        cout << "4. Save Data\n";
        cout << "5. Exit\n";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tracker.addTransaction();
                break;

            case 2:
                tracker.viewTransactions();
                break;

            case 3:
                tracker.calculateBalance();
                break;

            case 4:
                tracker.saveToFile();
                break;

            case 5:
                tracker.saveToFile();
                cout << "\nThank You For Using Expense Tracker!\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 5);

    return 0;
}

