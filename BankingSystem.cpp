#include<bits/stdc++.h>
using namespace std;

// Transaction class
class Transaction {
private:
    string type;
    double amount;

public:
    Transaction(string type, double amount) : type(type), amount(amount) {}

    void display() const {
        cout << left << setw(15) << type << setw(10) << amount << endl;
    }
};

// Account class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposited: $" << amount << ". New balance: $" << balance << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance! Withdrawal failed.\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdraw", amount);
        cout << "Withdraw: $" << amount << ". New balance: $" << balance << endl;
        return true;
    }

    void displayTransactions() const {
        cout << "Transactions for Account " << accountNumber << ":\n";
        cout << left << setw(15) << "Type" << setw(10) << "Amount" << endl;
        for (const auto &transaction : transactions) {
            transaction.display();
        }
    }
};

// Customer ke class
class Customer {
private:
    string name;
    int customerId;
    vector<Account> accounts;

public:
    Customer(string name, int customerId) : name(name), customerId(customerId) {}

    string getName() const {
        return name;
    }

    int getCustomerId() const {
        return customerId;
    }

    void addAccount(int accNum, double initialBalance) {
        accounts.emplace_back(accNum, initialBalance);
        cout << "Account " << accNum << " created for " << name << " with balance $" << initialBalance << ".\n";
    }

    Account* getAccount(int accNum) {
        for (auto &account : accounts) {
            if (account.getAccountNumber() == accNum) {
                return &account;
            }
        }
        return nullptr;
    }

    void displayAccounts() const {
        cout << "Accounts for Customer: " << name << "\n";
        for (const auto &account : accounts) {
            cout << "Account Number: " << account.getAccountNumber() << ", Balance: $" << account.getBalance() << endl;
        }
    }
};

// Bank ke class
class Bank {
private:
    vector<Customer> customers;

public:
    void addCustomer(string name, int id) {
        customers.emplace_back(name, id);
        cout << "Customer " << name << " added with ID " << id << ".\n";
    }

    Customer* getCustomer(int id) {
        for (auto &customer : customers) {
            if (customer.getCustomerId() == id) {
                return &customer;
            }
        }
        return nullptr;
    }

    void transfer(int fromAccNum, int toAccNum, double amount) {
        Account *fromAccount = nullptr, *toAccount = nullptr;

        for (auto &customer : customers) {
            if (!fromAccount) fromAccount = customer.getAccount(fromAccNum);
            if (!toAccount) toAccount = customer.getAccount(toAccNum);
            if (fromAccount && toAccount) break;
        }

        if (!fromAccount || !toAccount) {
            cout << "Transfer failed! One or both accounts not found.\n";
            return;
        }

        if (fromAccount->withdraw(amount)) {
            toAccount->deposit(amount);
            cout << "Transfer successful! $" << amount << " transferred from Account " 
                 << fromAccNum << " to Account " << toAccNum << ".\n";
        }
    }
};

int main() {
    Bank bank;

    bank.addCustomer("Rohit", 101);cout<<endl;
    bank.addCustomer("Virat", 102);cout<<endl;


    Customer* rohit = bank.getCustomer(101);cout<<endl;
    Customer* virat = bank.getCustomer(102);cout<<endl;

    if (rohit) rohit->addAccount(1001, 500.0);cout<<endl;
    if (virat) virat->addAccount(2001, 1000.0);cout<<endl;

    Account* rohitAccount = rohit->getAccount(1001);cout<<endl;
    Account* viratAccount = virat->getAccount(2001);cout<<endl;

    if (rohitAccount) {
        rohitAccount->deposit(200.0);cout<<endl;
        rohitAccount->withdraw(100.0);cout<<endl;
    }

    if (viratAccount) {
        viratAccount->withdraw(300.0);cout<<endl;
    }

    bank.transfer(1001, 2001, 50.0);

    if (rohit) rohit->displayAccounts();cout<<endl;
    if (virat) virat->displayAccounts();cout<<endl;



    if (rohitAccount) rohitAccount->displayTransactions();cout<<endl;
    if (viratAccount) viratAccount->displayTransactions();cout<<endl;;

  return 0;
}