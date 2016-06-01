#pragma once
/**************************************************************************************************************************************
Date of submission: 13th December, 2015
Name: Akash Chitnis
Course: 16:332:503
RuId: 167003791

Project Name: Account Management System
References: Lecture slides, internet and course reference book
**************************************************************************************************************************************/
#include<iostream>
#include<string>											//include standard library and header files 
#include<fstream>
#include"Account.h"
using namespace std;

#ifndef BANKACCOUNT_H										//class definition
#define BANKACCOUNT_H
class BankAccount : public Account							//Bank account can access public members of Account class
{
public:
	Account A;
	float readfile();
	void display(void);										//function to display balance
	void deposit(void);										//function to deposit money
	void withdraw(void);									//function to withdraw money
};

#endif#pragma once
