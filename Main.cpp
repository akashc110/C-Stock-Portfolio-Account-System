/**************************************************************************************************************************************
Date of submission: 13th December, 2015
Name: Akash Chitnis
Course: 16:332:503
RuId: 167003791

Project Name: Account Management System
References: Lecture slides, internet and course reference book
**************************************************************************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include"Account.h"																//include standard library and header files 
#include"BankAccount.h"
#include"StockAccount.h"
using namespace std;

void Stock_menu();																//function to display stock menu
void Bank_menu();																//function to display bank menu

int main()																		//main body starts
{
	
	int o = 0;
	while (o != 3)																	//main menu display
	{

		cout << "\nWelcome to the Account Management System.\n";
		cout << "\nPlease select an account to access:\n";
		cout << "1. Stock Portfolio Account\n2. Bank Account\n3. Exit\n";
		cin >> o;
		while (o<1 || o>3 || cin.fail())												//input condition check
		{
			cin.clear();
			cin.ignore(5000, '\n');
			cout << "\nInvalid Input. Re-enter:\t";
			cin >> o;
		}

		switch (o)
		{
		case 1:
		{
			Stock_menu();														//call to stock menu display function													
			break;
		}

		case 2:
		{
			Bank_menu();														//call to bank menu display function
			break;
		}

		}
	}
	system("pause");																//holds the result screen
	return 0;
}																				//main body ends

void Stock_menu()																//stock menu display function
{
	Stock s;
	BankAccount B;																//bank account object
	string symbol_stock;
	int o = 0;
	while (o != 7)
	{
		cout << "\nStock Portfolio Account\n";
		cout << "\nPlease select an option:\n";										//display menu
		cout << "\n1. Display the price for a stock symbol\n2. Display the current portfolio\n3. Buy shares\n4. Sell Shares";
		cout << "\n5. View a graph for the protfolio value\n6. View Transaction History\n7. Return to previous menu\n";
		cin >> o;
		while (o<1 || o>7 || cin.fail())											//input condition check
		{
			cin.clear();
			cin.ignore(5000, '\n');
			cout << "\nInvalid Input. Re-enter:\t";
			cin >> o;
		}
		switch (o)
		{
		case 1:																		//case to display stock price
		{
			cout << "\nPlease enter the stock symbol: ";
			cin >> symbol_stock;
			while (cin.fail() || (symbol_stock.size()>4))						//input condition check
			{
				cin.clear();
				cin.ignore(5000, '\n');
				cout << "\nInvalid input. Re-enter:";
				cin >> symbol_stock;
			}

			s.flag = 1;
			cout << "\n\n\n****************************************************************\n" << endl;
			s.display_price(symbol_stock);										//function call to display price
			cout << "\n****************************************************************" << endl;
			break;
		}
		case 2:																		//case to display current portfolio 
		{
			cout << "\n\n\n*****************Current Portfolio*********************************\n" << endl;
			s.display_portfolio();												//function call to display portfolio 
			cout << "\n*********************************************************************\n" << endl;
			break;
		}
		case 3:																		//case to buy shares
		{
			s.buy_share();														//function call to buy shares
			break;
		}
		case 4:																		//case to sell shares
		{
			s.sell_share();														//function call to sell shares
			break;
		}
		case 5:																		//case to plot graph of portfolio values
		{
			s.mat_graph();										//function call to plot graph
			break;
		}
		case 6:																		//case to display stock transaction history
		{
			cout << "\n\n\n*****************Stock Transaction History*********************************\n" << endl;
			s.tran_hist();														//function call to display stock transaction history		
			cout << "\n*********************************************************************\n" << endl;
			break;
		}

		}

	}
}

void Bank_menu()																//Bank menu display function
{
	//Account A;
	Stock s;
	BankAccount B;																//bank account object
	int o = 0;
	while (o != 5)
	{
		cout << "\nBank Account\n";
		cout << "\nPlease select an option:\n";										//display menu
		cout << "\n1. View Account Balance\n2. Deposit Money\n3. Withdraw Money";
		cout << "\n4. Print out history\n5. Return to previous menu\n";
		cin >> o;
		while (o<1 || o>5 || cin.fail())												//input condition check
		{
			cin.clear();
			cin.ignore(5000, '\n');
			cout << "\nInvalid Input. Re-enter:\t";
			cin >> o;
		}
		switch (o)
		{
		case 1:																		//case to display current bank balance
		{
			cout << "\n\n\n*****************Bank Account Balance*********************************\n" << endl;
			B.display();														//function call to display current bank balance
			cout << "\n*********************************************************************\n" << endl;
			break;
		}
		case 2:																		//case to deposit money in the bank account
		{
			B.deposit();														//function call to deposit money in the bank account
			s.function_call();
			break;
		}
		case 3:																		//case to withdraw money in the bank account
		{
			B.withdraw();														//function call to withdraw money in the bank account
			s.function_call();
			break;
		}
		case 4:																		//case to view bank account history
		{
			cout << "\n\n\n*****************Transaction History*********************************\n" << endl;
			B.history();														//function call to view bank account history
			cout << "\n*********************************************************************\n" << endl;

			break;
		}


		}

	}



}