/*
 * Account.h
 *
 *  Created on: Aug 20, 2015
 *      Author: vladimir
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>

using namespace std;

class Account{
public:
	int acno;
	int deposite;
	string name;
	string type;

	void create_account();
	void report();
	void modify();
	void show_account();
	void dep(int amt);
	void draw(int amt);
	int getDeposit();
	string getType();
	int acnumber();
	string getName();
};

istream& operator>>(istream& is, Account& ac);
ostream& operator<<(ostream& os, const Account& ac);

#endif /* ACCOUNT_H_ */
