/*
Alexander Zhang
*/
#include "Customer.h"

void clarityLineCustomer(std::ostream &os)
{
    os << std::string(70, '=');
}

Customer::Customer()
{
    this->name = "";
    this->phoneNo = "";
    this->email = "";
    this->totalAmtSpent = 0;
    this->numPurchases = 0;
    this->numNearbyRestaurants = 0;
    this->sortType = 1; //phone number by default.
}

Customer::Customer(std::string email)
{
    this->name = "";
    this->phoneNo = "";
    this->email = email;
    this->totalAmtSpent = 0;
    this->numPurchases = 0;
    this->numNearbyRestaurants = 0;

    this->sortType = 4;
}


//COPY CONSTRUCTOR
Customer::Customer(Customer &arg)
{
    name = arg.name;
    phoneNo = arg.phoneNo;
    email = arg.email;
    totalAmtSpent = arg.totalAmtSpent;
    numPurchases = arg.numPurchases;
    numNearbyRestaurants = arg.numNearbyRestaurants;
    sortType = arg.sortType;
}


//USE THIS WHEN PUTTING DATA INTO DATA STRUCTURE
Customer::Customer(std::string name, std::string phoneNo, std::string email, double totalAmtSpent, int numPurchases, int numNearbyRestaurants, int sortType)
{
    this->name = name;
    this->phoneNo = phoneNo;
    this->email = email;
    this->totalAmtSpent = totalAmtSpent;
    this->numPurchases = numPurchases;
    this->numNearbyRestaurants = numNearbyRestaurants;
    if (sortType < 1 || sortType > 4)
    {
        sortType = 1; //if out of bounds, set to sort by phone number
    }
    this->sortType = sortType;
}


void Customer::setName(std::string name)
{
    this->name = name;
}


void Customer::setPhoneNo(std::string phoneNo)
{
    this->phoneNo = phoneNo;
}

void Customer::setEmail(std::string email)
{
    this->email = email;
}

void Customer::setTotalAmtSpent(double totalAmtSpent)
{
    this->totalAmtSpent = totalAmtSpent;
}

void Customer::setNumPurchases(int numPurchases)
{
    this->numPurchases = numPurchases;
}

void Customer::setNumNearbyRestaurants(int numNearbyRestaurants)
{
    this->numNearbyRestaurants = numNearbyRestaurants;
}

void Customer::setSortType(int type)
{
    this->sortType = type;
}


std::string Customer::getName()
{
    return name;
}

std::string Customer::getPhoneNo()
{
    return phoneNo;
}

std::string Customer::getEmail()
{
    return email;
}

double Customer::getTotalAmtSpent()
{
    return totalAmtSpent;
}


int Customer::getNumPurchases()
{
    return numPurchases;
}


int Customer::getNumNearbyRestaurants()
{
    return numNearbyRestaurants;
}

int Customer::getSortType()
{
    return sortType;
}

bool operator<(Customer &arg1, Customer &arg2)
{
    if (arg1.sortType == 1 && arg2.sortType == 1)
    {
        if (arg1.getPhoneNo() < arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 2 && arg2.sortType == 2)
    {
        if (arg1.getTotalAmtSpent() < arg2.getTotalAmtSpent())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 3 && arg2.sortType == 3)
    {
        if (arg1.getNumNearbyRestaurants() < arg2.getNumNearbyRestaurants())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 4 && arg2.sortType == 4)
    {
        if (arg1.getEmail() < arg2.getEmail())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (arg1.getPhoneNo() < arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

bool operator>(Customer &arg1, Customer &arg2)
{
    if (arg1.sortType == 1 && arg2.sortType == 1)
    {
        if (arg1.getPhoneNo() > arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 2 && arg2.sortType == 2)
    {
        if (arg1.getTotalAmtSpent() > arg2.getTotalAmtSpent())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 3 && arg2.sortType == 3)
    {
        if (arg1.getNumNearbyRestaurants() > arg2.getNumNearbyRestaurants())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 4 && arg2.sortType == 4)
    {
        if (arg1.getEmail() > arg2.getEmail())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (arg1.getPhoneNo() > arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

bool operator>=(Customer &arg1, Customer &arg2)
{
    if (arg1.sortType == 1 && arg2.sortType == 1)
    {
        if (arg1.getPhoneNo() >= arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 2 && arg2.sortType == 2)
    {
        if (arg1.getTotalAmtSpent() >= arg2.getTotalAmtSpent())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 3 && arg2.sortType == 3)
    {
        if (arg1.getNumNearbyRestaurants() >= arg2.getNumNearbyRestaurants())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 4 && arg2.sortType == 4)
    {
        if (arg1.getEmail() >= arg2.getEmail())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (arg1.getPhoneNo() >= arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

bool operator<=(Customer &arg1, Customer &arg2)
{
    if (arg1.sortType == 1 && arg2.sortType == 1)
    {
        if (arg1.getPhoneNo() <= arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 2 && arg2.sortType == 2)
    {
        if (arg1.getTotalAmtSpent() <= arg2.getTotalAmtSpent())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 3 && arg2.sortType == 3)
    {
        if (arg1.getNumNearbyRestaurants() <= arg2.getNumNearbyRestaurants())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 4 && arg2.sortType == 4)
    {
        if (arg1.getEmail() <= arg2.getEmail())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (arg1.getPhoneNo() <= arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}


bool operator==(Customer &arg1, Customer &arg2)
{
    if (arg1.sortType == 1 && arg2.sortType == 1)
    {
        if (arg1.getPhoneNo() == arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 2 && arg2.sortType == 2)
    {
        if (arg1.getTotalAmtSpent() == arg2.getTotalAmtSpent())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 3 && arg2.sortType == 3)
    {
        if (arg1.getNumNearbyRestaurants() == arg2.getNumNearbyRestaurants())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 4 && arg2.sortType == 4)
    {
        if (arg1.getEmail() == arg2.getEmail())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (arg1.getPhoneNo() == arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

bool operator!=(Customer &arg1, Customer &arg2)
{
    if (arg1.sortType == 1 && arg2.sortType == 1)
    {
        if (arg1.getPhoneNo() != arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 2 && arg2.sortType == 2)
    {
        if (arg1.getTotalAmtSpent() != arg2.getTotalAmtSpent())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 3 && arg2.sortType == 3)
    {
        if (arg1.getNumNearbyRestaurants() != arg2.getNumNearbyRestaurants())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (arg1.sortType == 4 && arg2.sortType == 4)
    {
        if (arg1.getEmail() != arg2.getEmail())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (arg1.getPhoneNo() != arg2.getPhoneNo())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

std::ostream& operator<<(std::ostream &os, Customer &arg)
{
    if (arg.sortType == 1) //phone number
    {
        os << arg.getPhoneNo() << "    " << arg.getName() << "    " << arg.getEmail() << std::endl << "Total Amt Spent: " << "(" << arg.getTotalAmtSpent() << ")" << "  Num Purchases: " << "(" << arg.getNumPurchases() << ")" << "  Num Nearby Restaurants: " << "(" << arg.getNumNearbyRestaurants() << ")" << std::endl;
        os << std::string(70, '=');
    }
    else if (arg.sortType == 2) //totalAmtSpent
    {
        os << "Total Amt Spent: " << "(" << arg.getTotalAmtSpent() << ")" << "  " << "Avg Amount Spent per Purchase: " << "(" << (arg.getTotalAmtSpent() / arg.getNumPurchases()) << ")" << std::endl << arg.getEmail() << "    " << arg.getName() << "    " << arg.getPhoneNo() << std::endl;
        os << std::string(70, '=');
    }
    else if (arg.sortType == 3) // numNearbyRestaurants
    {
        os << "Nearby Restaurants: " << "(" << arg.getNumNearbyRestaurants() << ")" << "    " << arg.getName() << "    " << arg.getEmail() << std::endl;
        os << std::string(70, '=');
    }
    else if (arg.sortType == 4) // email
    {
        os << arg.getEmail() << "    " << arg.getName() << "    " << arg.getPhoneNo() << std::endl << "Total Amt Spent: " << "(" << arg.getTotalAmtSpent() << ")" << "  Num Purchases: " << "(" << arg.getNumPurchases() << ")" << "  Num Nearby Restaurants: " << "(" << arg.getNumNearbyRestaurants() << ")" << std::endl;
        os << std::string(70, '=');
    }
    else if (arg.sortType == 5) //primed for output to file
    {
        os << arg.phoneNo << " " << arg.name << " " << arg.email << " " << arg.totalAmtSpent << " " << arg.numPurchases << " " << arg.numNearbyRestaurants;
    }
    else //if neither of the above
    {
        os << arg.getPhoneNo() << "    " << arg.getName() << "    " << arg.getEmail() << std::endl << "Total Amt Spent: " << "(" << arg.getTotalAmtSpent() << ")" << "  Num Purchases: " << "(" << arg.getNumPurchases() << ")" << "  Num Nearby Restaurants: " << "(" << arg.getNumNearbyRestaurants() << ")" << std::endl;
        os << std::string(70, '=');
    }


    return os;
}
