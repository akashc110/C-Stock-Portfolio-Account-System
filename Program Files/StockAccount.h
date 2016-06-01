#pragma once
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
#include<string>																//include standard library files and parent class header file
#include<fstream>
#include"Account.h"
#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )    
#pragma comment( lib, "libeng.lib" )

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
// end

#include<engine.h>
#include<cmath>

using namespace std;


#ifndef STOCKACCOUNT
#define STOCKACCOUNT															//class definition
class Stock : public Account														//parent class public members can be accessed by this class
{
public:
	friend class DLL;															//linked list class can access stock account functions 
	friend class Node;															//node class can access stock account functions
	string symb;
	float share_price, user_price, total_value;
	int num_shares, no, flag, flag1, count1;
	int hr, mn, secs;															//variable declarations
	char ch;
	float readfile();
	float display_price(string);												//displays and returns the price of stock
	void display_portfolio();													//reads and displays the current portfolio text file
	void buy_share();															//buys the share entered by user after checking various conditions
	void sell_share();															//sells the share entered by user after checking various conditions
	void write_file();															//writes the buy transaction to Stock_Transaction_History text file
	void function_call();														//function to modify the value of current portfolio when accessed through bank account via main
	void tran_hist(void);														//reads and displays the content of Stock_Transaction_History text file
	int search(string);															//finds the name of the stock from the list of available stocks
	void write_portfolio_value(float);											//writes the value of total portfolio to portfolio_value text file
	void mat_graph();
};

#endif																			//end definition
