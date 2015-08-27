/*
 * Account.cpp
 *
 *  Created on: Aug 20, 2015
 *      Author: vladimir
 */

#include "Account.h"

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

void Account::create_account(){
	cout << "Enter the account number: ";
	acno = validNumericInput();
	cout << "Enter the name of the account holder: ";
	name = validStringInput();
	cout << "Enter the type (C/S): ";
	type = validStringInput();
	cout << "Enter the initial amount: ";
	deposite = validNumericInput();
	cout << "Account created..." << endl;
}

void Account::report(){
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << " " << deposite << endl;
}

void Account::modify(){
	cout << "Enter the account details: " << endl;
	cout << "Account number: " << acno << endl;
	cout << "Account holder name: ";
	cin>>name;
	cout << "Type of account (C/S): ";
	cin >> type;
	cout << "Balance amount: ";
	cin >> deposite;
}

void Account::show_account(){
	cout << "Account number: " << acno << endl;
	cout << "Holder name: " << name << endl;
	cout << "Accout type: " << type << endl;
	cout << "Balance amount: " << deposite << endl;
}

void Account::dep(int amt){
	deposite += amt;
}

void Account::draw(int amt){
	deposite -= amt;
}

int Account::acnumber(){
	return acno;
}

int Account::getDeposit(){
	return deposite;
}

string Account::getType(){
	return type;
}

string Account::getName(){
	return name;
}

istream& operator>>(istream& is, Account& ac){
    is >> ac.acno;
    is >> ac.deposite;
    is >> ac.name;
    is >> ac.type;
    return is;
}

ostream& operator<<(ostream& os, const Account& ac){
    os << ac.acno << " " << ac.deposite << " " << ac.name << " " << ac.type;
    return os;
}

int validNumericInput(){
    int x;
    cin >> x;
    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Bad entry. Enter a NUMBER: ";
        cin >> x;
    }
    return x;
}

string validStringInput(){
	string s;
	bool valid;

	for (;;){
		cin >> s;
		valid = true;

		for (char & c : s)
		{
			if(!isalpha(c)){
				cout << "Bad entry, valid chars A-Za-z. Try again: ";
				valid = false;
			}
		}

		if (valid)
			break;
	}

	return s;
}
