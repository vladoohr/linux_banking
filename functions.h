/*
 * functions.h
 *
 *  Created on: Aug 20, 2015
 *      Author: vladimir
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "Account.h"
#include <fstream>

void write_account();
void display_all();
void modify_account(int num);
void delete_account(int num);
void display_sp(int num);
void deposit_withdraw(int num, int option);
std::string checksumFile();
bool is_file_locked();
bool is_file_exist(const char *fileName);
void delete_sha_file();
void update_sha(const char* oldname);

#endif /* FUNCTIONS_H_ */
