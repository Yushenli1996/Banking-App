/*main.cpp*/

//
// Banking program in modern C++.
//
// <<Yushen Li>>
// U. of Illinois, Chicago
// CS 341: Spring 2018
// Project 01
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>

#include "customer.h"

using namespace std;


int main()
{
    string  customerFilename, transactionsFilename;
    
    cin >> customerFilename; //customers01.csv
    cout << customerFilename << endl;


    cin >> transactionsFilename; //transactions01.csv
    cout << transactionsFilename << endl;
    
    ifstream  custFile(customerFilename); //open customer file
    ifstream  txFile(transactionsFilename); //open transcation file
    
    cout << std::fixed;
    cout << std::setprecision(2);
    
    //read file to see if file is good to open
    if (!custFile.good())
    {
        cout << "**ERROR: cannot open customers file: '" << customerFilename << "'" << endl;
        return -1;
    }
    if (!txFile.good())
    {
        cout << "**ERROR: cannot open transactions file: '" << transactionsFilename << "'" << endl;
        return -1;
    }
    
    std::vector<Customer> customers; //setup the customers vector
    string line1, line2, name, customerID1, customerID2, accountBalance, transactionsValue; //setup pasring value
    while(getline(custFile,line1))
    {
        stringstream ss1(line1);
        getline(ss1, name, ',');
        getline(ss1, customerID1, ',');
        getline(ss1, accountBalance);
        Customer C(name, stoi(customerID1), stod(accountBalance)); //organize the parsing result
        customers.push_back(C); //push them on the vector
    }
    
    
    //Sort customers based on their name in ascending order
    sort(customers.begin(),
         customers.end(),
         [](Customer &c1, Customer &c2)
         {
             if(c1.getName() < c2.getName())
                 return true;
             else
                 return false;
         }
         );
    
    //print out the Customer list before transaction action.
    cout << ">> Customers before: " << endl;
    for(Customer&c : customers)
    {
        cout << c.getName() << " ("<< c.getcustomerID() << "): $"<< c.getAccountBalance() << endl;
        
    }
    
    //print out the processing stage
    cout << ">> Processing..." << endl;
    
    while(getline(txFile,line2))
    {
        stringstream ss2(line2);
        getline(ss2, customerID2, ',');
        getline(ss2, transactionsValue);
        
        bool isFound = false; //to Check if the name is find
        
        for(Customer &C : customers)
        {
            if(C.getcustomerID() == stoi(customerID2)) //comparing the Customer ID in vector with the Ids in transaction file
            {
                isFound = true; //if it's found, do the adding
                if(transactionsValue[0] == '+') //check the first index of the parsing material, if it's a "+", do adding
                {
                    double Value = C.getAccountBalance() + stod(transactionsValue); //add the transaction value
                    C.setAccountBalance(Value); //update the account balance
                }
                else
                {
                    double Value = C.getAccountBalance() + stod(transactionsValue); //stod automatically figure out "-", so do subtracting
                    if(Value < 0) //if the account doesn't have enough balance to do transaction
                    {
                        cout << "**Rejected Tx: " << C.getcustomerID() << "," << stod(transactionsValue) <<endl; //print out rejected list
                    }
                    else
                        C.setAccountBalance(Value); //update the new account balance
                }
                break; //if it's found, break;
            }
        }
        
        if(!isFound) //if it's out of bound and still can't find the ID
        {
            cout << "**Invalid Tx: " << customerID2 << "," << stod(transactionsValue) <<endl; //Output ID doesn't exist
        }
    }
    
    //Sort once again by Total balance in bank in deascending order
    sort(customers.begin(),
         customers.end(),
         [](Customer &c1, Customer &c2)
         {
             if(c1.getAccountBalance() > c2.getAccountBalance())
                 return true;
             else
                 return false;
         }
         );
    
    //Output the final updated Vector with correct ID and balance
    cout << ">> Customers after: " << endl;
    for(Customer&c : customers)
    {
        cout << c.getName() << " ("<< c.getcustomerID() << "): $"<< c.getAccountBalance() << endl;
        
    }
    
    return 0;
}

