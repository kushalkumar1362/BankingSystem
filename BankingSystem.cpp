#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;
#define MIN_BALANCE 1000

class Account
{
private:
    long accountNumber;
    string firstName;
    string lastName;
    float balance;
    static long NextAccountNumber;

public:
    Account() {}
    Account(string fname, string lname, float balance);
    long getAccountNumber() { return accountNumber; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    float getBalance() { return balance; }
    void Deposit(float amount);
    void Withdraw(float amount);

    static void setLastAccountNumber(long accountNumber);
    static long getLastAccountNumber();

    friend ofstream &operator<<(ofstream &ofs, Account &acc);
    friend ifstream &operator>>(ifstream &ifs, Account &acc);
    friend ostream &operator<<(ostream &os, Account &acc);
};
long Account ::NextAccountNumber = 0;

class Bank
{
private:
    map<long, Account> accounts;

public:
    Bank();
    Account OpenAccount(string fname, string lname, float balance);
    Account BalanceEnquiry(long accountNumber);
    Account Deposit(long accountNumber, float amount);
    Account Withdraw(long accountNumber, float amount);
    void CloseAccount(long accountNumber);
    void ShowAllAccounts();
    ~Bank();
};
int main()
{
    Bank b;
    Account acc;

    int choice;
    string fname, lname;
    long accountNumber;
    float balance;
    float amount;
    cout << "-->> Banking System <<--" << endl;
    do
    {
        cout << "\n\tSelect One Option below ";
        cout << "\n\t1.Open an Account ";
        cout << "\n\t2.Balance Enquiry ";
        cout << "\n\t3.Deposit";
        cout << "\n\t4.Withdrawal";
        cout << "\n\t5.Close an Account";
        cout << "\n\t6.Show All Accounts";
        cout << "\n\t7.Quit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Minimun balance to open an account is " << MIN_BALANCE << endl;
            cout << "Enter first name : ";
            cin >> fname;
            cout << "Enter last name : ";
            cin >> lname;
            cout << "Enter Initial Balance : ";
            cin >> balance;
            acc = b.OpenAccount(fname, lname, balance);
            cout << "\nCongratulations Account is Created" << endl;
            cout << acc;
            break;
        case 2:
            cout << "Enter Account Number : ";
            cin >> accountNumber;
            acc = b.BalanceEnquiry(accountNumber);
            cout << endl
                 << "Your Account Details : " << endl;
            cout << acc;
            break;
        case 3:
            cout << "Enter Account Number : ";
            cin >> accountNumber;
            cout << "Enter Amount that you want to Deposit : ";
            cin >> amount;
            acc = b.Deposit(accountNumber, amount);
            cout << endl
                 << "Amount is Deposit : " << endl;
            cout << acc;
            break;
        case 4:
            cout << "Enter Account Number : ";
            cin >> accountNumber;
            cout << "Enter balance : ";
            cin >> amount;
            acc = b.Withdraw(accountNumber, amount);
            cout << endl
                 << "Amount Withdrawan : " << endl;
            cout << acc;
            break;
        case 5:
            cout << "Enter Account Number : ";
            cin >> accountNumber;
            b.CloseAccount(accountNumber);
            cout << "Account is Closed" << endl;
            break;
        case 6:
            b.ShowAllAccounts();
            break;
        case 7:
            break;
        default:
            cout << "Enter correct Choice";
            exit(0);
        }
    } while (choice != 7);
    return 0;
}
Account ::Account(string fname, string lname, float balance)
{
    NextAccountNumber++;
    accountNumber = NextAccountNumber;
    firstName = fname;
    lastName = lname;
    this->balance = balance;
}
void Account::Deposit(float amount)
{
    if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully." << endl;
        } else {
            cout << "Invalid amount. Deposit failed." << endl;
        }
}
void Account::Withdraw(float amount)
{
     if (amount > 0) {
            if (balance >= amount) {
                balance -= amount;
                cout << "Amount withdrawn successfully." << endl;
            } else {
                cout << "Insufficient balance. Withdrawal failed." << endl;
            }
        } else {
            cout << "Invalid amount. Withdrawal failed." << endl;
        }
}
void Account ::setLastAccountNumber(long accountNumber)
{
    NextAccountNumber = accountNumber;
}
long Account ::getLastAccountNumber()
{
    return NextAccountNumber;
}
ofstream &operator<<(ofstream &ofs, Account &acc)
{
    ofs << acc.accountNumber << endl;
    ofs << acc.firstName << endl;
    ofs << acc.lastName << endl;
    ofs << acc.balance << endl;
    return ofs;
}
ifstream &operator>>(ifstream &ifs, Account &acc)
{
    ifs >> acc.accountNumber;
    ifs >> acc.firstName;
    ifs >> acc.lastName;
    ifs >> acc.balance;
    return ifs;
}
ostream &operator<<(ostream &os, Account &acc)
{
    os << "First Name : " << acc.getFirstName() << endl;
    os << "Last Name : " << acc.getLastName() << endl;
    os << "Account Number : " << acc.getAccountNumber() << endl;
    os << "Balance : " << acc.getBalance() << endl;
    return os;
}
Bank::Bank()
{
    Account account; 
    ifstream infile; 
    infile.open("Bank.data");
    if (!infile)             
    {
        // cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    while (!infile.eof())
    {
        infile >> account;
        accounts.insert(pair<long, Account>(account.getAccountNumber(), account));
    }
    Account::setLastAccountNumber(account.getAccountNumber());

    infile.close();
}
Account Bank ::OpenAccount(string fname, string lname, float balance)
{
    ofstream outfile;
    Account account(fname, lname, balance); 
    accounts.insert(pair<long, Account>(account.getAccountNumber(), account));

    outfile.open("Bank.data", ios ::trunc); 

    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
    return account;
}
Account Bank ::BalanceEnquiry(long accountNumber)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    return itr->second;
}
Account Bank ::Deposit(long accountNumber, float amount)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Deposit(amount);
    return itr->second;
}
Account Bank :: Withdraw(long accountNumber, float amount)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    itr->second.Withdraw(amount);
    return itr->second;
}
void Bank ::CloseAccount(long accountNumber)
{
    map<long, Account>::iterator itr = accounts.find(accountNumber);
    cout << "Account Deleted" << endl << itr->second << endl;
    accounts.erase(accountNumber);
}
void Bank ::ShowAllAccounts()
{
    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        cout << "Account : " << itr->first << endl
             << itr->second << endl;
    }
}
Bank ::~Bank()
{
    ofstream outfile;
    outfile.open("Bank.data", ios ::trunc);

    map<long, Account>::iterator itr;
    for (itr = accounts.begin(); itr != accounts.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
}