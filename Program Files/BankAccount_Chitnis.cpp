/**************************************************************************************************************************************
Date of submission: 13th December, 2015
Name: Akash Chitnis
Course: 16:332:503
RuId: 167003791

Project Name: Account Management System
References: Lecture slides, internet and course reference book
**************************************************************************************************************************************/

#include"BankAccount.h"

float BankAccount::readfile()												//returns value of balance
{
	ifstream cash("Cash_Balance.txt");
	if (!cash)
	{
		balance = 10000;												//set balance
		return balance;													//return balance
	}
	else
	{
		ifstream cash("Cash_Balance.txt");										//read file
		if (cash.is_open())													//do this if open
		{
			while (cash >> temp)
			{
				balance = temp;													//set balance
			}
			cash.close();													//close file
			return balance;													//return balance
		}
	}

}

void BankAccount::display()
{
	cout << "Cash Balance: $" << endl;
	cout << readfile() << endl;																//display balance
}


void BankAccount::deposit()
{
	call = 2;
	cout << "\nCurrent Balance:" << readfile() << endl;
	cout << "\nEnter the amount of money you want to deposit:";
	cin >> amount;
	while (cin.fail() || amount < 0)														//condition to avoid infinite looping
	{
		cin.clear();
		cin.ignore(5000, '\n');
		cout << "\nInvalid input. Re-enter:";
		cin >> amount;
	}
	cout << "\nDeposited: $" << amount;
	balance = balance + amount;															//add balance
	cout << "Cash Balance" << balance << endl;
	writefile(1, amount);																//write new balance to file
	write_cashbalance(balance);															//write to text file Cash_Balance
}

void BankAccount::withdraw()
{
	call = 3;
	cout << "Current Balance:" << readfile() << endl;											//read balance
	cout << "\nEnter the amount of money you want to withdraw:";
	cin >> amount;
	while (cin.fail() || amount < 0)														//condition to avoid infinite looping
	{
		cin.clear();
		cin.ignore(5000, '\n');
		cout << "\nInvalid input. Re-enter:";
		cin >> amount;
	}
	if (amount>balance)																	//check balance availability
	{
		cout << "\nNot sufficient balance. Transaction failed.\n";
	}
	else
	{
		cout << "\nAmount withdrawn: $" << amount;
		balance = balance - amount;															//reduce balance
		cout << "Cash Balance" << balance << endl;												//dispaly balance
		writefile(0, amount);																//write to file
		write_cashbalance(balance);															//write to text file Cash_Balance						
	}
}
