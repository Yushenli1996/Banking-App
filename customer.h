/*customer.h*/

//
// Customer class for banking program in modern C++.
//
// << Yushen Li >>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#include <iostream>
#include <string>

using namespace std;


class Customer
{
private:
    string Name; 
    int customerID;
    double accountBalance;
public:
    
    //default constructor:
    Customer()
    : Name(""), customerID(0), accountBalance(0)
    {}
    
    Customer(string name, int Id1, double acctBalance)
    : Name(name), customerID(Id1), accountBalance(acctBalance)
    {}
    
    ~Customer()
    {
        //delete[] ;
    }
    
    //getName function
    string getName() const
    {
        return Name;
    }
    
    //getID function
    int getcustomerID()
    {
        return customerID;
    }
    
    //getBalance
    double getAccountBalance()
    {
        return accountBalance;
    }
    
    //updateBalance
    void setAccountBalance(double value)
    {
        accountBalance = value;
    }
};

