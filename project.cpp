#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;
bool accountexist(string temp1)
{
    ifstream file("bank system.txt");
    if (!file)
        return false;
    string name;
    getline(file, name);
    file.close();
    if (name == temp1)
        return true;
    return false;
}
bool createaccount(string& temp1, int& pin, int& tempo)
{
    int age;
    cout << "Enter your Name: ";
    getline(cin, temp1);
    if (accountexist(temp1))
    {
        cout << "Account already exists with this name\n";
        return false;
    }
    cout << "Enter your age: ";
    cin >> age;
    if (age < 18)
    {
        cout << "You are not eligible\n";
        return false;
    }
    do
    {
        cout << "Enter your 4 digit pin: ";
        cin >> pin;
    } while (pin < 1000 || pin > 9999);

    tempo = 0;
    return true;
}
bool login(string& temp1, int& pin, int& tempo)
{
    ifstream file("bank system.txt");
    if (!file)
    {
        cout << "No account found\n";
        return false;
    }
    getline(file, temp1);
    file >> pin >> tempo;
    file.close();
    int pin1;
    do
    {
        cout << "Enter your pin: ";
        cin >> pin1;
        if (pin != pin1)
        {
            system("color 4c");
            Beep(1000, 300);
            cout << "Incorrect pin\n";
        }
    } while (pin != pin1);
    system("color 2a");
    cout << "Login successful\n";
    Sleep(1000);
    system("color 07");
    return true;
}
void saveaccount(string temp1, int pin, int tempo)
{
    ofstream file("bank system.txt");
    file << temp1 << endl
        << pin << endl
        << tempo;
    file.close();
    cout << "Data saved successfully\n";
}
int main()
{
    int choice, pin, tempo, withdraw, amount;
    string choice1, temp1;
    tempo = 0;
    cout << "------------- Welcome to Secure Bank System ------------\n";
    cout << "Do you have an account?(Yes/No)\n";
    getline(cin, choice1);
    bool ok;
    if (choice1 == "No" || choice1 == "no")
        ok = createaccount(temp1, pin, tempo);
    else
        ok = login(temp1, pin, tempo);
    if (!ok)
        return 0;
    choice = 0;
    while (choice != 6)
    {
        cout << "\nBank Menu:\n1.Deposit Amount\n 2.Withdraw Amount\n3.Check Balance\n 4.Save Account\n5.Search Account\n 6.Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter amount: ";
            cin >> amount;
            tempo += amount;
            break;
        case 2:
            cout << "Enter withdraw amount: ";
            cin >> withdraw;
            if (withdraw > tempo)
                cout << "Insufficient balance\n";
            else
                tempo -= withdraw;
            break;
        case 3:
            cout << "Balance: " << tempo << endl;
            break;
        case 4:
            saveaccount(temp1, pin, tempo);
            break;
        case 5:
            if (accountexist(temp1))
                cout << "Account exists\n";
            else
                cout << "Account not found\n";
            break;
        case 6:
            cout << "Thank you for using bank system\n";
            break;
        }
    }
    return 0;
}
