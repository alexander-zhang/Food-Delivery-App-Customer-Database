/*
Alexander Zhang
*/

#ifndef Customer_H
#define Customer_H
#include <string>
#include <iostream>

class Customer
{
private:
    std::string name;
    std::string phoneNo;
    std::string email;
    double totalAmtSpent;
    int numPurchases;
    int numNearbyRestaurants;

    int sortType; //1: phoneNo USE FOR BST
                  //2: totalAmtSpent USE FOR LINKED LIST
                  //3: num nearby restaurants
                  //4: email
public:
    Customer();
    Customer(std::string);//used for deletion (phoneNo);
    Customer(Customer &);
    // name, phoneNo, email, totalAmtSpent, numPurchases, nearbyRestaurants, sortType
    Customer(std::string, std::string, std::string, double, int, int, int sortType);

    //setters
    void setName(std::string);
    void setPhoneNo(std::string);
    void setEmail(std::string);
    void setTotalAmtSpent(double);
    void setNumPurchases(int);
    void setNumNearbyRestaurants(int);
    void setSortType(int);

    //getters
    std::string getName();
    std::string getPhoneNo();
    std::string getEmail();
    double getTotalAmtSpent();
    int getNumPurchases();
    int getNumNearbyRestaurants();
    int getSortType();

    friend std::ostream& operator<<(std::ostream &, Customer &);
    friend bool operator>(Customer &, Customer &);
    friend bool operator<(Customer &, Customer &);
    friend bool operator<=(Customer &, Customer &);
    friend bool operator>=(Customer &, Customer &);
    friend bool operator==(Customer &, Customer &);
    friend bool operator!=(Customer &, Customer &);

};

#endif
