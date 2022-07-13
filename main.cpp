/*
Author: Minh Chung
Compiler: GNU CCC
Date: 04/16/2022

Purpose of program: a program that manage bank account, allow users to create account with multiple owners, they can either deposit or withraw, anh then see the balance
*/
#include "Date.h"
#include "Account.h"
#include <fstream>
#include <sstream>
using namespace std;

int getMonthFromString( string d );
int getDayFromString( string d );
int getYearFromString( string d );
int getHourFromString( string d );
Date* getDateObj(string date);
void getAccountDetails( ifstream &infile, int &accntNum, int &numAccnts );
void getOwnerDetails( ifstream &infile, Person &person);
void swap( Transaction *xp, Transaction *yp );
void bubbleSort( Transaction arr[], int n );
bool readAccounts(string fname, Account accntPtr [], int numAccnts);

int main()
{
    string file;
    cout << "Enter the account file name:";
    getline( cin, file);
    int numAccounts = 0;
    Account *accounts = NULL;
    //new Account[ numAccounts ];

    ifstream infile( file );

    if ( !infile.good() )
    return false;

    string line;
    while ( getline( infile, line ) ) 
    {
        if ( line == "#" )
        {
            numAccounts++;
        }
    }
    accounts = new Account[ numAccounts ];
    infile.close();

    readAccounts( file, accounts, numAccounts );
    

    cout << " There are " << numAccounts << " accounts in the file" << endl << endl;

    for ( int i = 0; i < numAccounts; i++ ) 
    {
        cout << "\nAccount Number: " << accounts[ i ].getAccountNumber();
        cout << "\n===============";
        for ( int j = 0; j < accounts[ i ].getNumOwners(); j++ ) 
        {
            cout << "\nName: " << accounts[ i ].getOwner( j ).name;
            cout << ", DOB: ";
            accounts[ i ].getOwner( j ).DOB.print();
            cout << ", Address: " << accounts[ i ].getOwner( j ).address;
            cout << "\n";
        }
        int bal = 0;
        cout << "\nTransaction history:\n";
        cout << "--------------------" << endl;
        for ( int j = 0; j < accounts[ i ].getNumTransactions(); j++ ) 
        {
            cout << "Transaction #" << j + 1;
            cout << "\nDate: ";
            int type = accounts[ i ].getTransaction( j ).type;
            double amount = accounts[ i ].getTransaction( j ).amount;
            accounts[ i ].getTransaction( j ).transactionDate.print();
            cout << ", type: ";
            switch ( type ) 
            {
                case 1:
                cout << "account creation,";
                break;
                case 2:
                cout << "deposit,";
                break;
                case 3:
                cout << "withdrawal,";
                break;

                default:
                break;
            }
            cout << " amount: " << amount;
            if ( type == 3 ) 
            {
                bal -= amount;
            }
            else 
            {
                bal += amount;
            }

            cout << ", new balance: " << bal << endl;
            if(j != (accounts[ i ].getNumTransactions()-1))
            cout << endl;
        }
    }

    return 0;
}
//d=mm/dd/yyyy
/* This function takes as argument a string representing a date
in the mm/dd/yyyy/hh format and returns the month as an int
The argument string is assumed properly formatted and no input validation
is required
*/

int getMonthFromString( string d )
{
    string month = d.substr( 0, 2 );
    return atoi( month.c_str() );
}

/* This function takes as argument a string representing a date
in the mm/dd/yyyy/hh format and returns the day as an int
The argument string is assumed properly formatted and no input validation
is required
*/

int getDayFromString( string d )
{
    string day = d.substr( 3, 2 );
    return atoi( day.c_str() );
}

/* This function takes as argument a string representing a date
in the mm/dd/yyyy/hh format and returns the year as an int
The argument string is assumed properly formatted and no input validation
is required
*/

int getYearFromString( string d )
{
    string year = d.substr( 6, 4 );
    return atoi( year.c_str() );
}

/* This function takes as argument a string representing a date
in the mm/dd/yyyy/hh format and returns the hour as an int
The argument string is assumed properly formatted and no input validation
is required
*/

int getHourFromString( string d )
{
    string hour = d.substr( 11, 2 );
    return atoi( hour.c_str() );
}
//get date from string
Date* getDateObj(string date)
{
    Date *dateObj = new Date;
    dateObj->set(getMonthFromString(date), getDayFromString(date), getYearFromString(date), getHourFromString(date));
    return dateObj;
}


//get account details
void getAccountDetails( ifstream &infile, int &accntNum, int &numAccnts )
{
    string line;
    getline( infile, line ) ;
    accntNum = atoi( line.c_str() );
    getline( infile, line ) ;
    numAccnts = atoi( line.c_str() );
}
//get owner details
void getOwnerDetails( ifstream &infile, Person &person)
{
    string line;
    getline( infile, line ) ;
    person.name = line;

    getline( infile, line );
    Date dob;
    dob.set( getMonthFromString(line), getDayFromString(line), getYearFromString(line), getHourFromString(line));
    person.DOB = dob;
    
    getline( infile, line );
    person.address = line;
}
//swap
void swap( Transaction *xp, Transaction *yp )
{
    Transaction temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort( Transaction arr[], int n )
{
    int i, j;

    //get array
    for ( i = 0; i < n - 1; i++ )

    // Last i elements are already in place
    for ( j = 0; j < n - i - 1; j++ )
    if ( arr[ j + 1 ].transactionDate < arr[ j ].transactionDate ) 
    {
        swap( &arr[ j ], &arr[ j + 1 ] ) ;
    }
}

/* This function reads from an account file and populates an array of Account objects (not an array of pointers to Account) with all the owners and transactions data read from the file. The owner data is the owner’s name, DOB and address. The transaction data is the transaction date, transaction type (account creation, deposit, withdrawal), and transaction amount. For each account, the function should dynamically allocate an array of Transaction of size equal to the number of transactions, assign the array’s address to transacPtr, and populate the array with the transaction data. */

bool readAccounts(string fname, Account accntPtr [], int numAccnts)
{
  ifstream in;
    int accountNum = 0, numOwner = 0;
    string word;

    in.open(fname.c_str());

    if(!in)
        return false;

    getline(in, word);
    for(int i = 0; i < numAccnts; i++)
    {
        getline(in, word);
        accountNum = stoi(word);

        getline(in, word);
        numOwner = stoi(word);

        accntPtr[i].setAccount(accountNum, numOwner);

        for(int j = 0; j < numOwner; j++)
        {
            Person *p = new Person;

            getline(in, word);
            p->name = word;

            getline(in, word);
            Date *DOB = getDateObj(word);
            p->DOB = *DOB;

            getline(in, word);
            p->address = word;

            accntPtr[i].setOwner(j, *p);
        }

        getline(in, word);

        string personO, personTw, personT;

        accntPtr[i].setNumTransactions(stoi(word));

        Transaction *arr = new Transaction[stoi(word)];

        getline(in, word);

        int counter = 0;
        Transaction *t = new Transaction;
        while(word != "#")
        {
            if(word == "")
                break;

            //Transaction *t = new Transaction;
            personO = word.substr(0, word.find(" "));
            word = word.substr(word.find(" ") + 1);
            personTw = word.substr(0, word.find(" "));
            personT = word.substr(word.find(" ") + 1);

            t->type = stoi(personTw);
            t->amount = stod(personT);
            t->transactionDate = *(getDateObj(personO));

            arr[counter] = *t;
            getline(in, word);
            counter++;
        }
        bubbleSort(arr, counter );
        accntPtr[i].setTransacPtr(arr);
    }
    return true;
}