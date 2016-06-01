/**************************************************************************************************************************************
Date of submission: 13th December, 2015
Name: Akash Chitnis
Course: 16:332:503
RuId: 167003791

Project Name: Account Management System
References: Lecture slides, internet and course reference book
**************************************************************************************************************************************/

#include<iostream>
#include<string>
#include<fstream>															//include standard library and header files 
#include<time.h>
#include<iomanip>

using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H															//class definition
class Account 
{

public:
	int mon, day, year, call;
	float startBal, amount, balance, temp;									//variable declaration
	Account();																//class constructor- assigns value to variable balance
	virtual float readfile();														//function that returns the value of balance to other functions
	void write_cashbalance(float);											//function to write balance to text file
	void history(void);														//displays data from text file Bank_Balance
	void writefile(float, float);											//writes deposit/withdraw transaction to text file Bank_Balance

};
#endif																		//end definition#pragma once
