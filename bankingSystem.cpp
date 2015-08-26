/*
 * bankingSystem.cpp

 *
 *  Created on: Aug 20, 2015
 *      Author: vladimir
 */

// bankingSystem.cpp : Defines the entry point for the console application.
//

#include "functions.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{
	char ch;
    int num;
    string oldname;

    for(;;){
    	if(is_file_locked()){
    		cout << "App locked! Press any key to try again!" << endl;

    		cin.ignore();
            cin.get();
            continue;
        } else {
       		cout << "App unlocked!" << endl;
       		break;
      	}
    }

	do
    {
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t01. NEW ACCOUNT";
        cout<<"\n\n\t02. DEPOSIT AMOUNT";
        cout<<"\n\n\t03. WITHDRAW AMOUNT";
        cout<<"\n\n\t04. BALANCE ENQUIRY";
        cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout<<"\n\n\t06. CLOSE AN ACCOUNT";
        cout<<"\n\n\t07. MODIFY AN ACCOUNT";
        cout<<"\n\n\t08. EXIT";
        cout<<"\n\n\tSelect Your Option (1-8) ";
        cin>>ch;

        //keep sha if file is changed later
        oldname = "/tmp/" + checksumFile() + ".txt";;

		switch(ch)
        {
			case '1':
				write_account();
				break;
			case '2':
				cout<<"\n\n\tEnter The account No. : "; cin>>num;
				deposit_withdraw(num, 1);
				break;
			case '3':
				cout<<"\n\n\tEnter The account No. : "; cin>>num;
				deposit_withdraw(num, 2);
				break;
			case '4':
				cout<<"\n\n\tEnter The account No. : "; cin>>num;
				display_sp(num);
				break;
			case '5':
				display_all();
				break;
			case '6':
				cout<<"\n\n\tEnter The account No. : "; cin>>num;
				delete_account(num);
				break;
			 case '7':
				cout<<"\n\n\tEnter The account No. : "; cin>>num;
				modify_account(num);
				break;
			 case '8':
				cout<<"\n\n\tThanks for using bank managemnt system";
				break;
			 default :cout<<"\a";
        }

		//update sha filw
		update_sha(oldname.c_str());

        cin.ignore();
        cin.get();
    }while(ch!='8');

	delete_sha_file();

    return 0;
}



