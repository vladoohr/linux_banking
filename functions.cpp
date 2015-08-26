/*
 * functions.cpp
 *
 *  Created on: Aug 20, 2015
 *      Author: vladimir
 */

#include "functions.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "errno.h"

#pragma comment (lib, "Advapi32.lib")
#include <openssl/sha.h>

void write_account(){
	Account ac;
	ac.create_account();

	// set values in e
	ofstream out;

	errno = 0;
	try{
		out.open("account.dat", ios_base::app | ios_base::out);
		out.exceptions (std::ios::badbit | std::ios::failbit);
		out << ac;
		out << endl;
	} catch(exception &e){
		if (errno){
			cerr << "*Error: " << e.what() << "account.dat" << " - " << strerror(errno) << endl;
		}
	}

	out.close();
}

void display_all(){
	Account ac;
	ifstream inFile("account.dat");

	if(!inFile){
		cout << "File could not be open!!!" << endl;
		return;
	}

	while (!(inFile >> ac).eof()){
		cout << to_string(ac.acno) + " " + to_string(ac.deposite) + " " + ac.name + " " + ac.type << endl;
	}

	inFile.close();
}

void modify_account(int num){
	Account ac;
	std::vector<string> words;
	bool found = false;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);

	std::string str((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());

	if(!File){
		cout << "File could not be open!!!" << endl;
		return;
	}

	File.seekp(0, ios::beg);
	while(!(File >> ac).eof() && found==false){
		if ( ac.acnumber() ==  num){
			Account old_ac = ac;
			ac.modify();

			std::string line = to_string(old_ac.acno) + " " + to_string(old_ac.deposite) + " " + old_ac.name + " " + old_ac.type + "\n";
			const char* row = line.c_str();
			cout << "ROW: " << row << endl;
			size_t pos = str.find(row);
			//int pos = static_cast<int>(sizeof(ac));
			cout << "Position: " << pos << endl;
			File.seekp(pos, ios::beg);
			File << ac;
			cout << "Record updated!";
			found=true;
		}
	}
	File.close();
	if(found == false){
		cout << "Record not found!" << endl;
	}
}

void delete_account(int num){
	Account ac;
	ifstream inFile;
	ofstream outFile;

	inFile.open("account.dat", ios::binary);
	if(!inFile){
		cout << "Could not open file!!!" << endl;
		return;
	}
	outFile.open("temp.dat", ios::binary);

	while (!(inFile >> ac).eof()){
		if ( ac.acnumber() !=  num){
			outFile << ac;
			outFile << endl;
		}
	}

	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("temp.dat", "account.dat");
	cout << "Record deleted!" << endl;
}

void display_sp(int num){
	Account ac;
	bool found = false;
	ifstream inFile;

	inFile.open("account.dat", ios::binary);
	if (! inFile){
		cout << "Could not open file!!!" << endl;
		return;
	}

	cout << "BALANCE DETAILS" << endl;

	while (!(inFile >> ac).eof()){
			if ( ac.acnumber() ==  num){
				ac.show_account();
				found = true;
			}
		}

	if (found == false){
		cout << "Account number does not exist" << endl;
	}
}

void deposit_withdraw(int num, int option){
	Account ac;
	bool found = false;
	int amt;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);

	if(!File){
		cout << "File could not be open!!!" << endl;
		return;
	}

	std::string str((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
	File.seekp(0, ios::beg);
	while(!(File >> ac).eof() && found == false){
		Account old_ac = ac;
		if (ac.acnumber() ==  num){
			ac.show_account();

			if(option == 1){
				cout << "TO DEPOSITE AMOUNT" << endl;
				cout << "Enter the amount to be deposited: ";
				cin >> amt;
				ac.dep(amt);
			}

			if(option == 2){
				cout << "TO WITHDRAW AMOUNT" << endl;
				cout << "Enter the amount to be withdraw: ";
				cin >> amt;
				int balance = ac.getDeposit() - amt;
				if ((balance < 500 && ac.getType() == "S") || (balance < 1000 && ac.getType() == "C"))
					cout << "Insufficience balance" << endl;
				else
					ac.draw(amt);
			}

			std::string line = to_string(old_ac.acno) + " " + to_string(old_ac.deposite) + " " + old_ac.name + " " + old_ac.type + "\n";
		    const char* row = line.c_str();
			cout << "ROW: " << row << endl;
			size_t pos = str.find(row);

			cout << "Position: " << pos << endl;
			File.seekp(pos, ios::beg);
			File << ac;
			File << endl;
			cout << "Record updated!";
			found=true;
		}
	}

	if (found != true){
		cout << "Account cannot be found!!!" << endl;
	}
}

std::string checksumFile() {
		unsigned char hash[SHA256_DIGEST_LENGTH];
		char *filename="account.dat";
		int i;
		FILE *inFile = fopen (filename, "rb");
		SHA256_CTX sha256;
		int bytes;
		unsigned char data[1024];

		if (inFile == NULL) {
			printf ("%s can't be opened.\n", filename);
			return "";
		}

		SHA256_Init(&sha256);

		while ((bytes = fread (data, 1, 1024, inFile)) != 0)
			SHA256_Update(&sha256, data, bytes);

		SHA256_Final(hash, &sha256);

		std::stringstream ss;
		for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
		{
			ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
		}

		fclose (inFile);

		return ss.str();
}

bool is_file_locked(){
	bool locked = false;
	std::string filename = "/tmp/" + checksumFile() + ".txt";

	if(is_file_exist(filename.c_str())){
		locked = true;
	}

	ofstream myfile;
	myfile.open (filename.c_str());
	myfile.close();

	return locked;
}

bool is_file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

void delete_sha_file(){
	std::string filename = "/tmp/" + checksumFile() + ".txt";
	unlink(filename.c_str());
}

void update_sha(const char* oldname){
	std::string newname = "/tmp/" + checksumFile() + ".txt";
	int result= rename( oldname , newname.c_str() );
	if ( result != 0 )
	    perror( "Error renaming file" );
}

template <typename T>
std::string to_string(T value)
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

