/**************************************************************************************************************************************
Date of submission: 13th December, 2015
Name: Akash Chitnis
Course: 16:332:503
RuId: 167003791

Project Name: Account Management System
References: Lecture slides, internet and course reference book
**************************************************************************************************************************************/

#include"Account.h"

Account::Account()													//class constructor
{

	ifstream cash("Cash_Balance.txt");									//read file
	if (!cash)															//if nothing found, set balance as 10000
	{
		balance = 10000;
	}
	else
	{
		ifstream cash("Cash_Balance.txt");
		if (cash.is_open())													//do this if file is open
		{
			//getline(Hist,tran);
			while (cash >> temp)
			{
				balance = temp;													//read value of last balance from file
			}
			cash.close();													//close file
		}
	}

}

float Account::readfile()												//returns value of balance
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

void Account::write_cashbalance(float z)								//write balance to text file
{
	ofstream flow;														//file object
	ifstream in("Cash_Balance.txt");
	flow.open("Cash_Balance.txt", ios::out | ios::app);				//open to append
	flow << z << endl;														//write to file
	readfile();															//update balance
}

void Account::history()												//read transaction history
{
	ifstream Hist("Bank_Balance.txt");
	if (!Hist.good())													//if not open do this
	{
		cout << "\nNo Transaction.\n";
	}
	else
	{
		char ch;
		if (Hist.is_open())												//if file is open do this
		{
			while (Hist.good())
			{
				Hist.get(ch);													//print result character by character
				cout << ch;
			}
			Hist.close();													//close file
		}
	}
}

void Account::writefile(float y, float amount)						//write bank balance to text file Bank_Balance
{
	string dt;
	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;														//code to get current time
	timeinfo = localtime(&seconds);
	mon = 1 + timeinfo->tm_mon;
	day = timeinfo->tm_mday;
	year = 1900 + timeinfo->tm_year;


	ofstream acc;														//write file object
	ifstream ifile("Bank_Balance.txt");
	if (!ifile.good())													//if file not open do this
	{
		acc.open("Bank_Balance.txt", ios::out | ios::app);				//append file
		acc << "Event" << "\t\t" << left << "Amount" << "\t\t\t" << "Date" << setw(5) << "\t\t" << "Balance\n" << endl;			//write heading to file
		writefile(y, amount);											//write to file
	}
	if (acc)
	{
		acc.open("Bank_Balance.txt", ios::out | ios::app);					//append file
		if (y == 1)															//condition to write deposit transaction
		{
			while (acc)			//acc.eof() != 0								
			{
				acc << left << setw(10) << "Deposit\t\t" << " $ " << left << setw(12) << amount << "\t" << right << mon << " / " << day << " / " << year << "\t" << setw(5) << " $ " << balance << endl;
				break;
			}
		}
		if (y == 0)															//condition to write withdraw transaction
		{
			while (acc)			//acc.eof() != 0
			{
				acc << left << setw(12) << "Withdrawal\t" << " $ " << left << setw(12) << amount << "\t" << right << mon << " / " << day << " / " << year << "\t" << setw(5) << " $ " << balance << endl;
				break;
			}

		}
		acc.close();														//close file
	}
}
