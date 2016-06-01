/**************************************************************************************************************************************
Date of submission: 13th December, 2015
Name: Akash Chitnis
Course: 16:332:503
RuId: 167003791

Project Name: Account Management System
References: Lecture slides, internet and course reference book
**************************************************************************************************************************************/



#include"StockAccount.h"
//************************************************************************************************************************************************

//										CLASS NODE

//************************************************************************************************************************************************

class Node																//class declaration
{
	friend class DLL;													//linkedlist gets access to node data members
	friend class Stock;													//stock class gets access to node data members
public:
	Node(string& name, int no) : itemName(name), number_of_shares(no)		//assigns parameters to StockName and number of shares
	{
		this->next = NULL;
	}
	string itemName;
	int number_of_shares;													//data members
	Node *next;
	Node *prev;
}*myHead, *myTail;


//************************************************************************************************************************************************

//									CLASS DOUBLY LINKED LIST

//************************************************************************************************************************************************
class DLL : public Stock												//doubly linked list class with access to public members of class stock
{
public:
	int mySize;

	DLL()																	//constructor
	{
		myHead = myTail = 0;
		mySize = 0;
		total_value = 0;
		string line_;
		int num;
		float a, b;
		char d1, d2;
		ifstream file_("Current_Portfolio.txt");								//read only file call
		if (file_.is_open())
		{
			getline(file_, line_);
			getline(file_, line_);
			while (file_ >> line_ >> num >> d1 >> a >> d2 >> b)
			{
				if (file_.good())
				{
					Node *Node1;
					Node1 = new Node(line_, num);										//load doubly linked list with data members from text file
					List.addToEnd(Node1);
				}
			}
		}

	}
	~DLL()																	//destructor
	{
		{
			Node *ptr = myHead;
			Node *temp;
			while (ptr != 0)
			{
				temp = ptr;
				ptr = ptr->next;
				delete temp;													//clears memory
			}
		}

	}
	int size() const;														//function to check the size of the list
	void addToEnd(Node * pair)
	{
		Node *ptr1 = pair;
		if (mySize == 0)														//if list is empty, do this
		{
			myHead = myTail = ptr1;											//make myHead equal to myTail and add details to that
			ptr1->prev = NULL;
			ptr1->next = NULL;
		}
		else																//if list is not empty, make next of myTail as new entry and new entry as mytail
		{
			myTail->next = ptr1;
			ptr1->prev = myTail;
			myTail = ptr1;
			myTail->next = NULL;
		}
		write_to_file();													//write to file
		mySize++;															//increase the size after adding the element
	}

	void printList()
	{
		if (mySize == 0)														//do this if the list is empty
			cout << "\nThe list is empty." << endl;
		else
		{
			Node *start = myHead;
			cout << "Stock List" << endl << "Name\tQuantity" << endl;				//prints title
			while (start != 0)
			{
				cout << start->itemName << "\t\t" << start->number_of_shares << endl;			//prints name and number
				start = start->next;											//shifts the start position to right
			}
		}
	}
	void find_string(string z, int num)
	{

		if (myHead->itemName == z)											//checks start if the name is present in the first node
		{
			myHead->number_of_shares = myHead->number_of_shares + num;		//adds the number of shares to existing shares
			write_to_file();												//writes the change to file
			return;															//returns to the function call
		}

		if (myTail->itemName == z)											//checks myTail if the name is present in the last node
		{
			myTail->number_of_shares = myTail->number_of_shares + num;		//adds the number of shares to existing shares
			write_to_file();												//writes the change to file
			return;															//returns to the function call
		}

		Node *find;															//node find

		find = myHead->next;
		while (find != NULL)													//logic if the number is in between
		{
			if (find->itemName == z)												//do this if not found
			{
				find->number_of_shares = (find->number_of_shares) + num;			//adds the number of shares to existing shares
				write_to_file();													//writes the change to file
				return;
			}
			find = find->next;													//moves find to next node
		}

		Node *Node1;
		Node1 = new Node(z, num);												//new node creation
		List.addToEnd(Node1);												//adds the detail to this newly created node at last position
	}

	void write_to_file()													//Function to write current portfolio text file
	{
		sort();															//sorts the link list before writing
		ofstream portfolio;
		ifstream current("Current_Portfolio.txt");
		portfolio.open("Current_Portfolio.txt", ios::out);				//opens the text file for writing clearing the previous content
		portfolio << "Cash balance = $" << readfile() << endl;				//writes balance
		portfolio << "Company Symbol\t\t" << "Number\t" << "Price per share\t" << "\tTotal value\n" << endl;	//writes heading
		Node *find = myHead;											//creates node
		total_value = 0;
		while (find != NULL)  //myTail->next								//looping condition
		{
			portfolio << left << setw(25) << find->itemName << left << setw(10) << find->number_of_shares << "$" << display_price(find->itemName) << "\t\t$" << left << setw(16) << (find->number_of_shares)*(display_price(find->itemName)) << left << "\n";//display stocck details
			total_value = total_value + ((find->number_of_shares)*(display_price(find->itemName)));				//adds to total value
			find = find->next;											//increment
		}
		write_portfolio_value((total_value + readfile()));				//calculates total portfolio value 
		portfolio << "Total portfolio value: $" << (total_value + readfile()) << endl;		//writes total portfolio value
	}

	void sell_stock(string name, int shares)								//function to sell stock using linked list
	{
		//DLL();
		int x = 0;
		Node *find = myHead;
		//printList();
		while (find != NULL)  //myTail->next!= NULL							//looping condition
		{
			//printList();
			if (find->itemName == name)									//search stock name
			{
				x = 1;													//flag
				if ((find->number_of_shares)>shares)						//checks whether that many shares are available
				{
					float price = display_price(find->itemName);		//stores current price of the share
					balance = balance + ((shares)*(price));				//increases the corresponding balance
					write_cashbalance(balance);							//writes balance in the balance file
					cout << "\nYou have sold " << (shares) << " shares of " << (find->itemName) << " at $" << (price) << " each for a total of $" << (shares)*(price) << endl;//prints transaction
					write_sell((find->itemName), shares);				//writes the sell transaction to file
					(find->number_of_shares) = (find->number_of_shares) - shares;		//subtracts the sold shares from the account
					write_to_file();									//writes to text file
					writefile(1, price);									//writes to text file

				}
				else
				{
					if ((find->number_of_shares) == shares)			//checks condition to delete node if exact available shares are to be sold
					{
						float price = display_price(find->itemName);
						balance = balance + ((find->number_of_shares)*(price));		//adds balance
						write_cashbalance(balance);
						cout << "\nYou have sold " << (find->number_of_shares) << " shares of " << (find->itemName) << " at $" << price << " each for a total of $" << (find->number_of_shares)*(price) << endl;
						write_sell((find->itemName), shares);
						node_delete(name);							//node deletion
						write_to_file();
						writefile(1, price);							//writes to text file
						return;
					}
					cout << "Transaction failed. Insufficient shares.";
					return;
				}

			}

			find = find->next;											//increment
		}
		if (x == 0)															//condition if stock not found in portfolio
		{
			cout << "\nStock not found in portfolio.\n";
		}


	}

	bool removeFromStart()
	{
		if (mySize == 0)														//do this if list in empty
			return false;
		else {
			if (myHead == myTail)												//do this if only one node is present
				myHead = myTail = 0;
			else
				myHead = myHead->next;										//shift one position to the right
			mySize--;														//reduce size of list by one
			return true;
		}
	}


	void write_sell(string a, int b)										//write sell transaction text file
	{
		string dt;
		time_t seconds;
		seconds = time(NULL);
		tm * timeinfo;
		timeinfo = localtime(&seconds);										//code to get current time
		hr = timeinfo->tm_hour;
		mn = timeinfo->tm_min;
		secs = timeinfo->tm_sec;

		ofstream acc_stk;
		ifstream infile("Stock_transaction_history.txt");
		acc_stk.open("Stock_transaction_history.txt", ios::out | ios::app);		//opens file to append
		while (acc_stk.good())			//acc.eof() != 0						//writes to file
		{
			acc_stk << left << setw(6) << "Sell\t" << right << setw(5) << a << right << setw(12) << b << right << setw(8) << "$" << setw(8) << left << display_price(a) << "\t" << "$" << left << setw(16) << (b)*display_price(a) << setw(2) << hr << ":" << mn << ":" << secs << "\n";
			//acc_stk<<"Sell"<<setw(10)<<a<<right<<setw(10)<<b<<right<<setw(10)<<"$"<<display_price(a)<<right<<setw(10)<<"$"<<(b)*display_price(a)<<right<<setw(10)<<hr<<":"<<mn<<":"<<secs<<"\n";
			break;															//breaks the loop
		}
	}

	bool removeFromEnd()
	{
		if (mySize == 0)														//do this if list in empty
			return false;
		else {
			if (myHead == myTail)												//do this if only one node is present
				myHead = myTail = 0;
			else
			{

				Node *end = myTail->prev;
				myTail = end;
				myTail->next = NULL;											//removes the last node
				mySize--;													//decreases the size of the list by 1
			}

			return true;													//operation successful
		}
	}

	void node_delete(string name)
	{
		if (mySize == 0)														//do this if list is empty
		{
			cout << "\nThe list is empty." << endl; return;
		}
		if (myHead->itemName == name)										//call remove from start if the name is present in the first node
		{
			removeFromStart();	return;
		}
		if (myTail->itemName == name)										//call remove from end if the name is present in the last node
		{
			removeFromEnd();	return;
		}

		Node *find = myHead, *find1 = myHead->next;
		while (find1->itemName != name && find1->next != myTail)					//logic if the number is in between
		{
			find = find1;
			find1 = find1->next;
		}
		if (find1->itemName != name)											//do this if not found
			cout << "\nItem Not Found\n";
		else
		{
			find->next = find1->next;
			find1->next->prev = find;											//removes the node and connects the corresponding next and previous
			find1->prev->next = find1->next;
			delete find1;													//delete if found
			mySize--;														//decreases the size
		}
	}

	void sort()																//sorts the linked list in descending order
	{
		if (myHead != 0)
		{
			Node* current = myHead;
			Node* prev = 0;
			Node* tempNode = 0;												//node creation and assignment
			int changeFlag = 0;
			for (int i = 0; i < mySize; i++)								//loop
			{
				while (current->next != 0)									//loop until last node
				{
					tempNode = current->next;
					//condition to check greater value
					if ((current->number_of_shares)*(display_price(current->itemName)) < (tempNode->number_of_shares)*(display_price(tempNode->itemName)))      // (current->number_of_shares > tempNode->number_of_shares)
					{
						changeFlag = 1;
						current->next = tempNode->next;
						tempNode->next = current;
						if (prev != 0)
							prev->next = tempNode;							//swap sequence
						prev = tempNode;
						if (myHead == current)
							myHead = tempNode;
						if (current->next == 0)
							myTail = current;
					}
					else
					{
						prev = current;										//increment
						current = current->next;
					}
				}
				if (changeFlag == 0)										//breaks the loop if flag is zero
					break;
				else
				{
					prev = 0;
					current = myHead;										//makes current as myHead
					changeFlag = 0;
				}
			}
		}
	}
}List;																	//class object
																		//*****************************************************************************************************************************************

																		//							START OF CLASS STOCK 

																		//*****************************************************************************************************************************************

float Stock::display_price(string stock)								//class to display stock price
{
	int V1 = rand() % 2;													//random number generator
	string line_;
	string date;
	float num;
	float z = 0;

	if (V1 == 0)
	{
		ifstream file_("Result1.txt");
		if (file_.is_open())														//checks if file is open
		{
			while (file_ >> line_ >> num >> date)										//looks for stock name, its value and date
			{
				if (stock == line_)												//stock name search condition
				{
					z = num;														//stores value of stock price in z
					if (flag == 1)													//enters only when title is required
					{
						cout << "\nCompany Symbol \t Price per share \n" << stock << "\t\t\t" << z;
						flag++;
					}
					file_.close();												//close file
					return z;													//returns stock price
				}
			}
			cout << "\nSymbol cannot be found." << endl;							//if stock name not found
			return -1;															//returns -1 
		}

		else
		{
			cout << "unable to open";												//if file does not exist
			return 0;															//returns zero
		}

	}

	if (V1 == 1)																//same as above expect the file name is changed and so the stock prices
	{
		ifstream file_("Result2.txt");
		if (file_.is_open())
		{
			while (file_ >> line_ >> num >> date)
			{
				if (stock == line_)
				{
					z = num;
					if (flag == 1)
					{
						cout << "\nCompany Symbol \t Price per share \n" << stock << "\t\t\t" << z;
						flag++;
					}
					file_.close();
					return z;
				}
			}
			cout << "\nSymbol cannot be found." << endl;
			return -1;
		}

		else
		{
			cout << "unable to open";
			return 0;
		}
	}
	return 0;
}

void Stock::display_portfolio()										//Displays the current portfolio by reading from file																
{
	ofstream acc;														//ofstream object
	ifstream ifile("Current_Portfolio.txt");
	acc.open("Current_Portfolio.txt", ios::out | ios::app);			//opens file to append
	if (!ifile.good())	//is_open()										//do this if file doesn't exist
	{
		write_portfolio_value(readfile());								//write balance to portfolio file
		cout << "\nCash balance = $" << readfile() << endl << "No Stock Transaction" << endl;		//display this
		cout << "Total Portfolio value = $" << readfile();
		acc << "Cash balance = $" << readfile() << endl << "No Stock Transaction" << endl;		//write to file
		acc << "Total Portfolio value = $" << readfile();
		//write_portfolio_value(readfile());
	}
	else
	{
		if (ifile.is_open())
		{
			while (ifile.good())												//loop to go to the end of file
			{
				ifile.get(ch);													//get character by character
				cout << ch;														//display character by character	
			}
		}
	}
}

void Stock::buy_share()												//function to buy shares
{
	no = 2;
	readfile();															//read balance
	cout << "\nPlease enter the stock symbol you want to purchase:\t";
	cin >> symb;
	while (cin.fail() || (symb.size()>4))								//check to avoid infinite looping
	{
		cin.clear();
		cin.ignore(5000, '\n');
		cout << "\nInvalid input. Re-enter:";
		cin >> symb;
	}
	if (search(symb) == 1)													//if stock name is found do this
	{
		share_price = display_price(symb);
		cout << "\nPlease enter the number of shares:\t";
		cin >> num_shares;
		while (cin.fail() || (num_shares<0))								//check to avoid infinite looping
		{
			cin.clear();
			cin.ignore(5000, '\n');
			cout << "\nInvalid input. Re-enter:";
			cin >> num_shares;
		}
		cout << "\nPlease enter the maximum amount you are willing to pay per share:";
		cin >> user_price;
		while (cin.fail() || (user_price<0))								//check to avoid infinite looping
		{
			cin.clear();
			cin.ignore(5000, '\n');
			cout << "\nInvalid input. Re-enter:";
			cin >> user_price;
		}
		if (user_price >= share_price)									//check user price is more than or equal to current share price	
		{
			if (balance >= (share_price*num_shares))					//check if there is sufficient balance to do the transaction
			{
				balance = balance - (share_price*num_shares);				//deduct balance
				write_cashbalance(balance);									//write balance to text file
				cout << "\nYou have purchased " << num_shares << " shares of " << symb << " at $" << share_price << " each for a total of $" << (share_price*num_shares) << endl;
				write_file();												//write to file
				writefile(0, (share_price*num_shares));						//write to file

				if (myHead == NULL)										//add node if list is empty
				{
					Node *Node1;
					Node1 = new Node(symb, num_shares);
					List.addToEnd(Node1);
				}
				else { List.find_string(symb, num_shares); }		//call link list to add if already exists in the list
			}
			else { cout << "Transaction failed. Insufficient Balance." << endl; }
		}
		else { cout << "Transaction failed. Price of share is higher than your value."; }

	}
	else { cout << "\nStock not available."; }

}

void Stock::sell_share()												//function to sell shares	
{
	readfile();															//gets balance
	cout << "\nPlease enter the stock symbol you want to sell:\t";
	cin >> symb;
	while (cin.fail() || (symb.size()>4))								//check to avoid infinite looping
	{
		cin.clear();
		cin.ignore(5000, '\n');
		cout << "\nInvalid input. Re-enter:";
		cin >> symb;
	}
	share_price = display_price(symb);									//get the current price of share
	if (share_price != -1)												//check if stock is available
	{
		cout << "\nPlease enter the number of shares you want to sell:\t";
		cin >> num_shares;
		while (cin.fail() || (num_shares<0))									//check to avoid infinite looping
		{
			cin.clear();
			cin.ignore(5000, '\n');
			cout << "\nInvalid input. Re-enter:";
			cin >> num_shares;
		}
		cout << "\nPlease enter the minimum amount that you want to sell it for:\t";
		cin >> user_price;
		while (cin.fail() || (user_price<0))									//check to avoid infinite looping
		{
			cin.clear();
			cin.ignore(5000, '\n');
			cout << "\nInvalid input. Re-enter:";
			cin >> user_price;
		}
		ifstream ifile("Current_Portfolio.txt");							//read current portfolio file

		if (!ifile.is_open())
			cout << "\nNo stock to sell.\n";										//if file is not open print this
		else
		{
			if (user_price<share_price)
			{
				List.sell_stock(symb, num_shares);								//call linked list function to perform the transaction

			}
			else	cout << "\nTransaction Failed. Share price is less than the required amount.\n";
		}
	}
}


void Stock::tran_hist()												//function to print stock transaction history
{
	string line;
	ifstream infile("Stock_transaction_history.txt");				//read file
	if (!infile.is_open())											//Do this if file not open
	{
		write_file();												//write file
		cout << "\nNo transaction has been made.";
	}
	else
	{
		while (infile.good())
		{
			getline(infile, line);									//else print line by line
			cout << line << endl;
		}
	}
}



void Stock::write_file()												//function to write stock transaction history text file 
{
	string dt;
	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;														//code to get time
	timeinfo = localtime(&seconds);
	hr = timeinfo->tm_hour;
	mn = timeinfo->tm_min;
	secs = timeinfo->tm_sec;


	ofstream acc_stk;													//ofstream object
	ifstream infile("Stock_transaction_history.txt");
	acc_stk.open("Stock_transaction_history.txt", ios::out | ios::app);//open file to append
	if (!infile.is_open())												//do this if file is open
	{
		acc_stk << left << setw(5) << "Event\t" << "Company Symbol\t" << "Number\t" << "Price per share\t" << "Total Value\t" << "Time\n";
	}

	while (acc_stk.good())			//acc.eof() != 0				//condition check
	{
		acc_stk << left << setw(5) << "Buy\t" << right << setw(5) << symb << right << setw(12) << num_shares << right << setw(8) << "$" << setw(8) << left << share_price << "\t" << "$" << left << setw(16) << (num_shares)*(share_price) << setw(2) << hr << ":" << mn << ":" << secs << "\n";
		no--;
		break;															//break
	}
	acc_stk.close();												//close file
}



int Stock::search(string a)											//function to search a particular stock from stock list
{
	string line_;
	ifstream file_("Result1.txt");

	if (file_.is_open())
	{
		while (file_ >> line_)													//loop to go through entire list
		{
			if (a == line_)
			{
				file_.close();
				return 1;													//returns 1 if stock is found
			}
		}
	}
	return 0;

}

void Stock::write_portfolio_value(float value)						//function to write portfolio value to text file	
{
	string dt;
	time_t seconds;
	seconds = time(NULL);
	tm * timeinfo;
	timeinfo = localtime(&seconds);										//code to get current time
	hr = 1 + timeinfo->tm_hour;
	mn = 1 + timeinfo->tm_min;
	secs = 1 + timeinfo->tm_sec;
	//count1=1;

	ofstream acc_stk;
	ifstream infile("portfolio_value.txt");
	acc_stk.open("portfolio_value.txt", ios::out | ios::app);			//append current text file
	if (!infile.is_open())
	{
		acc_stk << "";
	}

	while (acc_stk.good())			//acc.eof() != 0
	{
		acc_stk << value << "\n";								//write value
																//count1++;
		break;
	}
	acc_stk.close();												//close file
}


void Stock::mat_graph()
{
	double a = 0, sum = 0;
	int n = 0, i = 0;

	float num;
	//	float num1;
	float z = 0;

	ifstream file_("portfolio_value.txt");
	if (file_.is_open())
	{

		while (file_ >> num)
		{
			n++;
		}

		file_.close();
	}

	else
	{
		cout << "\nunable to open\n";
	}

	double *d = new double[n];

	ifstream file("portfolio_value.txt");

	if (file.is_open())
	{

		while (file >> num)
		{
			//	cout << "hi\n";
			d[i] = num;
			i++;
			//n++;
		}

		file.close();
	}

	else
	{
		cout << "unable to open";
	}




	// creating a pointer to the engine
	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		cout << "Error: Not Found." << endl;
		exit(1);
	}
	// end

	mxArray *A;
	A = mxCreateDoubleMatrix(1, n, mxREAL);
	memcpy((void *)mxGetPr(A), (void *)d, n*sizeof(double));
	engPutVariable(ep, "xx", A);


	engEvalString(ep, "X=xx;");
	engEvalString(ep, "plot(X);");	//call plot function


	engEvalString(ep, "title('Successful!!!');");
	engEvalString(ep, "xlabel('Time');");
	engEvalString(ep, "ylabel('Portfolio Value');");

	mxDestroyArray(A);


}

float Stock::readfile()												//returns value of balance
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

void Stock::function_call()
{
	List.write_to_file();
}