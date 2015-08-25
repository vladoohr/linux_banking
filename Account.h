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
	int acno;
	int deposite;
	string name;
	string type;

public:
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

#endif /* ACCOUNT_H_ */
