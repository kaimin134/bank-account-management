#include "Account.h"
#include "Date.h"
#include <iostream>
using namespace std;
//mutator used to set account information
void Account::setAccount( int accountNumber_, int numOwners_)
{
    accountNumber = accountNumber_;
    numOwners = numOwners_;
    ownerPtr = new Person[ numOwners ];
    balance = 0;
}
//mutator used to set owner (name, DOB, address)
void Account::setOwner( int ind, Person p)
{
    ownerPtr[ ind ].name = p.name;
    ownerPtr[ ind ].DOB = p.DOB;
    ownerPtr[ ind ].address = p.address;
}
//accessor used to get owner
Person Account::getOwner(int ind) const
{
    return ownerPtr[ ind ];
}
//accessor used to get account number
int Account::getAccountNumber() const
{
    return accountNumber;
}
//accessor used to get number of owners
int Account::getNumOwners() const
{
    return numOwners;
}
//mutator used to set transaction
void Account::setTransacPtr( Transaction * transacPtr_ )
{
    transacPtr = transacPtr_;
}

int Account::getNumTransactions() const
{
    return numTransactions;
}

void Account::setNumTransactions( int numTransactions_ )
{
    numTransactions = numTransactions_;
}

Transaction Account::getTransaction( int ind ) const
{
    return transacPtr[ind];
}

Account::Account()
{
    int accountNumber = 0;
    int numOwners = 0;
    Person *ownerPtr = nullptr;
    double balance = 0;
    int numTransactions = 0;
    Transaction *transacPtr = nullptr;
}

