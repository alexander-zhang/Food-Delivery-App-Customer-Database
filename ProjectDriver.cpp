/*
Alexander Zhang
Yasuhiro Yamada
John Le


Purpose:
This program reads information from a designated file, ("InputData.txt"), and stores it into 3 types of
Data structures: Binary Search Trees, a Hash Table, and Linked List.
The program enables you to: modify customer data from the file, search for and pinpoint specific customers,
add and delete customers from the file, display customers in sorted orders (display in Tree format option included),
view the efficiency of the hash table, and store/view the edit history of the database
*/



#include <iostream>
#include "BST.h"
#include "Customer.h"
#include "HashTable.h"
#include "LinkedList.h"
#include <string>
#include <fstream>
using namespace std;

//Validity Checks
bool checkValidPhoneNum(string phoneNum);
bool checkValidEmail(string email);
bool checkValidName(string name);
void inputValidation(const char *msg);
bool isInteger(char);
bool isAlpha(char);

//Utilities
void clarityLine(ostream &);
int getSizeFile(fstream &, string);
int getDoublePrime(int);


//Menu Functions
int readData(BST<Customer> &phoneNumBST, BST<Customer> &emailBST, LinkedList<Customer> &amtSpentLL, LinkedList<Customer> &nearbyRestsLL, HashTable<Customer> &phoneNumHT, fstream &, string fileName, string &header); //reads in data
void addData(BST<Customer> &, BST<Customer> &, LinkedList<Customer> &, LinkedList<Customer> &, HashTable<Customer> &, int);
bool deleteData(BST<Customer> &, BST<Customer> &, LinkedList<Customer> &, LinkedList<Customer> &, HashTable<Customer> &);
bool modifyData(BST<Customer> &, BST<Customer> &, LinkedList<Customer> &, LinkedList<Customer> &, HashTable<Customer> &);
void searchByPhone(HashTable<Customer> &);
void searchByEmail(BST<Customer> &);
void displayHashSequence(HashTable<Customer> &);
void displayTotalAmt(LinkedList<Customer> &);
void displayNearbyRests(LinkedList<Customer> &);
void displayPhoneNums(BST<Customer> &);
void efficiency(HashTable<Customer> &);
void logMenu();

void updateFile(BST<Customer> &, fstream &, string, string);
void leaveLog(Customer tempC, char type);


/*
add new data
delete data
find and display based on key
list data in hash sequence
List data in key sequence sorted
print indented tree
efficiency
Our Choice
close
*/

//CHOICE: 1:PreOrder   2:Inorder   3:PostOrder   4:Breadth-First   5:Tree Format

void clarityLine(ostream &); //clarity line

const string logName = "HistoryLog.txt";
const string treeFile = "outputTree.txt";

int main()
{
    string fileName = "InputData.txt";
    string header;
    fstream ioFile;

    BST<Customer> phoneNumBST;
    BST<Customer> emailBST;
    LinkedList<Customer> amtSpentLL;
    LinkedList<Customer> nearbyRestsLL;

    int fileSize;
    fileSize = getSizeFile(ioFile, fileName);
    HashTable<Customer> phoneNumHT(getDoublePrime(fileSize));

    readData(phoneNumBST, emailBST, amtSpentLL, nearbyRestsLL, phoneNumHT, ioFile, fileName, header);

    bool repeat = true;
    while (repeat)
    {
        try
        {
            int choice = 0;
            clarityLine(cout);
            std::cout << "This is Main Menu\n";
            std::cout << "Enter a number to indicate the operation you wish to perform\n";
            clarityLine(cout);
            std::cout << "1: Add New Data\n";
            std::cout << "2: Delete Data\n";
            std::cout << "3: Modify Data\n";
            std::cout << "4: Search Customer (Phone Number)\n";
            std::cout << "5: Search Customer (Email Address)\n";
            std::cout << "6: List Customers in Hash Table Sequence\n";
            std::cout << "7: List Customers in Key Sequence (Total Amount Spent)\n";
            std::cout << "8: List Customers in Key Sequence (Restaurants Nearby)\n";
            std::cout << "9: List Customers in Key Sequence (Phone Number)\n";
            std::cout << "10: Print Customers by Indented Tree\n";
            std::cout << "11: Efficiency\n";
            std::cout << "12: History Log\n";
            std::cout << "0: Quit\n";
            clarityLine(cout);
            cout << "Choice (0 - 12): ";
            std::cin >> choice;
            cin.ignore(100, '\n');
            inputValidation("Invalid option.");
            if (choice < 0 || choice > 11)
            {
                cout << "Enter an option between 0 and 12." << endl;
            }
            clarityLine(cout);

            switch (choice)
            {
            case(1):
            {
                string repeat = "1";
                while (repeat == "1")
                {
                    cout << "Adding Data" << endl;
                    addData(phoneNumBST, emailBST, amtSpentLL, nearbyRestsLL, phoneNumHT, 0);
                    
                    clarityLine(cout);
                    cout << "Add another? (Type 1 to repeat, anything else to exit): ";
                    cin >> repeat;
                    cin.ignore(100, '\n');
                    clarityLine(cout);
                }

                break;
            }
            case(2):
            {
                cout << "Deleting Data" << endl;
                if (!deleteData(phoneNumBST, emailBST, amtSpentLL, nearbyRestsLL, phoneNumHT))
                {
                    cout << "Can not delete more data." << endl;
                }
                break;
            }
            case(3):
            {
                if (!modifyData(phoneNumBST, emailBST, amtSpentLL, nearbyRestsLL, phoneNumHT))
                {
                    cout << "No data to modify." << endl;
                }
                break;
            }
            case(4):
            {
                searchByPhone(phoneNumHT);
                break;
            }
            case(5):
            {
                searchByEmail(emailBST);
                break;
            }
            case(6):
            {
                displayHashSequence(phoneNumHT);
                break;
            }
            case(7):
            {
                displayTotalAmt(amtSpentLL);
                break;
            }
            case(8):
            {
                displayNearbyRests(nearbyRestsLL);
                break;
            }
            case(9):
            {
                displayPhoneNums(phoneNumBST);
                break;
            }
            case(10):
            {
                ioFile.open(treeFile);
                ioFile << phoneNumBST.choice(5);
                ioFile.close();
                cout << phoneNumBST.choice(5);
                break;
            }
            case(11):
            {
                efficiency(phoneNumHT);
                break;
            }
            case(12):
            {
                logMenu();
                break;
            }
            case(0):
            {
                repeat = false;
                break;
            }
            default:
            {
                break;
            }
            }


        }
        catch (const char *msg)
        {
            cout << msg << endl;
        }
    }

    updateFile(phoneNumBST, ioFile, fileName, header);

    system("pause");
    return 0;
}


//======================================================================================
// VALIDITY CHECKS
//======================================================================================

/* checks if phone number is valid
Pre: phoneNum - string of a phone number
Post:
Return: true - if valid, false otherwise
*/
bool checkValidPhoneNum(string phoneNum)
{
    unsigned long length;
    length = phoneNum.length();
    if (length != 12)
    {
        return false;
    }

    int currSize = 0;
    for (int i = 0; i < length; i++)
    {
        if (phoneNum[i] == ' ')
        {
            return false;
        }
        if (isInteger(phoneNum[i]))
        {
            currSize++;
        }
        else if (phoneNum[i] == '-')
        {
            if (currSize != 3)
            {
                return false;
            }
            currSize = 0;
        }
        else
        {
            return false;
        }
    }

    if (currSize > 4)
    {
        return false;
    }
    else
    {
        return true;
    }
}


/* checks if the email is valid
Pre: email - string email
Post:
Return: bool - true if valid, false otherwise
*/
bool checkValidEmail(string email)
{
    long length = email.length();
    long size = length;
    bool hasAt = false;
    bool hasCom = false;

    if (!isAlpha(email[0]) && !isInteger(email[0]))
    {
        return false;
    }
    if (email.find("@") != std::string::npos)
    {
        hasAt = true;
    }
    if (email.find(".com") != std::string::npos)
    {
        hasCom = true;
    }

    for (int i = 0; i < size; i++)
    {
        if (email[i] == ' ')
        {
            return false;
        }
    }
    if (hasAt && hasCom)
    {
        return true;
    }
    else
    {
        return false;
    }

}


/* checks if the name is valid
Pre: name - string
Post:
Return: bool - true if name is valid, false otherwise
*/
bool checkValidName(string name)
{
    long length;
    length = name.length();

    if (length <= 2)
    {
        return false;
    }
    else if (name[0] == '_')
    {
        return false;
    }
    else
    {
        int count = 0;
        for (int i = 0; i < length; i++)
        {
            if (name[i] == ' ')
            {
                return false;
            }
            if (isAlpha(name[i]))
            {
                continue;
            }
            else if (name[i] == '_')
            {
                ++count;
                if (count > 1)
                    return false;
                continue;
            }
            else
            {
                return false;
            }
        }
        if (name[length - 1] == '_')
        {
            return false;
        }
        if (count == 0)
            return false;
    }
    return true;
}



/* checks input validation for integers
Pre:
Post: can throw a msg if input failed
Return:
*/
void inputValidation(const char *msg)
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
        throw msg;
    }
}



void checkValidInput(const char *msg)
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
        throw msg; //throws message to the catch block which will display it
    }
}

bool isInteger(char test)
{
    if (test >= '0' && test <= '9')
        return true;
    else
        return false;
}

bool isAlpha(char test)
{
    if ((int(test) > 64 && test <= 90) || (int(test) > 96 && int(test) <= 122))
        return true;
    else
        return false;
}


//======================================================================================
// UTILITY
//======================================================================================

/* gives visual clarity
Pre: os - ostream object by reference
Post: os is modified
Return:
*/
void clarityLine(ostream &os)
{
    os << string(30, '=') << endl;
}


/* gets the size of the file for the Hash Table function
Pre: inFile - fstream to read in data
fileName - string name of the file
Post:
Return: int - size of the data
*/
int getSizeFile(fstream & inFile, string fileName)
{
    int fileSize = 0;
    string header;
    inFile.open(fileName, ios::in);

    if (inFile.fail())
    {
        cerr << "File not opened." << endl;
    }
    else
    {
        getline(inFile, header); //removes first line

        string phoneNo;
        string name;
        string email;
        double totalAmt;
        int numUses;
        int nearbyRests;

        //simulate read in
        while (inFile >> phoneNo && inFile >> name && inFile >> email && inFile >> totalAmt && inFile >> numUses && inFile >> nearbyRests)
        {
            ++fileSize;
        }
    }


    inFile.close(); //close file
    return fileSize;
}


/* gets the nearest prime number to double the original size of the data
Pre:
Post:
Return: int - prime number nearest to double the original size of the data
*/
int getDoublePrime(int test)
{
    if (test < 25)
    {
        return 53;
    }

    bool isPrime = false;
    int newSize = 2 * test;

    while (!isPrime)
    {
        isPrime = true;
        int half = newSize / 2;

        for (int i = 2; i < half; i++)
        {
            if (newSize % i == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (!isPrime)
        {
            ++newSize;
        }
    }
    return newSize;

}

//======================================================================================
// MENU FUNCTIONS
//======================================================================================

/* reads data into the data structures
Pre: phoneNumBST - BST that compares phone numbers
emailBST - BST that compares emails
amtSpentLL - Linked List that sorts upon insertion by amount spent
nearbyRestsLL - Linked List that sorts upon insertion by number of nearby restaurants
phoneNumHT - Hash Table that used phone numbers as the key
inFile - fstream object for input and output
fileName - string of the filename
header - string to hold the header of the file.
Post: data structures now have data
Return: int - size of the data.
*/
int readData(BST<Customer> &phoneNumBST, BST<Customer> &emailBST, LinkedList<Customer> &amtSpentLL, LinkedList<Customer> &nearbyRestsLL, HashTable<Customer> &phoneNumHT, fstream &inFile, string fileName, string & header)
{
    int fileSize = 0;
    inFile.open(fileName, ios::in);

    if (inFile.fail())
    {
        cerr << "File not opened." << endl;
    }
    else
    {
        getline(inFile, header); //removes first line
        string extra;
        getline(inFile, extra); // removes clarity line

        string phoneNo;
        string name;
        string email;
        double totalAmt;
        int numUses;
        int nearbyRests;

        while (inFile >> phoneNo && inFile >> name && inFile >> email && inFile >> totalAmt && inFile >> numUses && inFile >> nearbyRests)
        {
            ++fileSize;
            // name, phoneNo, email, totalAmtSpent, numPurchases, nearbyRestaurants, sortType
            Customer *tempPtr;

            //phone number
            tempPtr = new Customer(name, phoneNo, email, totalAmt, numUses, nearbyRests, 1);
            phoneNumBST.insert(*tempPtr);
            phoneNumHT.insert(*tempPtr);
            delete tempPtr;

            //amount spent Linked List
            tempPtr = new Customer(name, phoneNo, email, totalAmt, numUses, nearbyRests, 2);
            amtSpentLL.addData(*tempPtr);
            delete tempPtr;

            //nearbyRestaurants
            tempPtr = new Customer(name, phoneNo, email, totalAmt, numUses, nearbyRests, 3);
            nearbyRestsLL.addData(*tempPtr);
            delete tempPtr;

            //email
            tempPtr = new Customer(name, phoneNo, email, totalAmt, numUses, nearbyRests, 4);
            emailBST.insert(*tempPtr);
            delete tempPtr;
        }
    }


    inFile.close(); //close file
    return fileSize;
}


/* adds data to the structures
Pre: phoneNumBST - BST that compares phone numbers
emailBST - BST that compares emails
amtSpentLL - Linked List that sorts upon insertion by amount spent
nearbyRestsLL - Linked List that sorts upon insertion by number of nearby restaurants
phoneNumHT - Hash Table that used phone numbers as the key
m - integer that signifies if the data is being added or if it is being modified. It changes the output and history messages.
Post: added data to the data structures
Return:
*/
void addData(BST<Customer> &phoneNumBST, BST<Customer> &emailBST, LinkedList<Customer> &amtSpentLL, LinkedList<Customer> &nearbyRestsLL, HashTable<Customer> &phoneNumHT, int m)
{
    if (phoneNumHT.getLoad() >= phoneNumHT.getTableSize())
    {
        cout << "Data Table is Full!" << endl;
        return;
    }

    string phoneNum = "";
    string name = "";
    string email = "";
    double totalAmtSpent = 0;
    int numPurchases = 0;
    int numNearbyRestaurants = 0;

    while (!checkValidPhoneNum(phoneNum))
    {
        cout << "Phone Number (###-###-####): ";
        cin >> phoneNum;
        cin.ignore(100, '\n');

        if (!checkValidPhoneNum(phoneNum))
        {
            cout << "Invalid Phone Number." << endl;
        }

        if (phoneNumHT.search(phoneNum))
        {
            cout << "Customer data already exists!" << endl;
            phoneNum = "";
        }
    }

    while (!checkValidName(name))
    {
        cout << "Name (<First><Underscore><Last>): ";
        cin >> name;
        cin.ignore(100, '\n');

        if (!checkValidName(name))
        {
            cout << "Invalid Name." << endl;
        }
    }

    while (!checkValidEmail(email))
    {
        cout << "Email (<body>@<website><dot>com): ";
        cin >> email;
        cin.ignore(100, '\n');

        if (!checkValidEmail(email))
        {
            cout << "Invalid Email." << endl;
        }
    }

    bool invalid = true;
    while (invalid)
    {
        cout << "Total Amount Spent (Integer): ";
        try
        {
            cin >> totalAmtSpent;
            cin.ignore(100, '\n');
            inputValidation("Enter an integer.");
            invalid = false;
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            invalid = true;
        }
    }

    invalid = true;
    while (invalid)
    {
        cout << "numPurchases (Integer): ";
        try
        {
            cin >> numPurchases;
            cin.ignore(100, '\n');
            inputValidation("Enter an integer.");
            invalid = false;
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            invalid = true;
        }
    }

    invalid = true;
    while (invalid)
    {
        cout << "Number of Nearby Restaurants (Integer): ";
        try
        {
            cin >> numNearbyRestaurants;
            cin.ignore(100, '\n');
            inputValidation("Enter an integer.");
            invalid = false;
        }
        catch (const char *msg)
        {
            cout << msg << endl;
            invalid = true;
        }
    }


    // name, phoneNo, email, totalAmtSpent, numPurchases, nearbyRestaurants, sortType
    //1: phoneNo USE FOR BST
    //2: totalAmtSpent USE FOR LINKED LIST
    //3: num nearby restaurants
    //4: email

    Customer *temp;
    temp = new Customer(name, phoneNum, email, totalAmtSpent, numPurchases, numNearbyRestaurants, 1);

    if (m == 1)
    {
        phoneNumBST.insert(*temp);
        phoneNumHT.insert(*temp);
        delete temp;

        temp = new Customer(name, phoneNum, email, totalAmtSpent, numPurchases, numNearbyRestaurants, 2);
        amtSpentLL.addData(*temp);
        delete temp;

        temp = new Customer(name, phoneNum, email, totalAmtSpent, numPurchases, numNearbyRestaurants, 3);
        nearbyRestsLL.addData(*temp);
        delete temp;

        temp = new Customer(name, phoneNum, email, totalAmtSpent, numPurchases, numNearbyRestaurants, 4);
        emailBST.insert(*temp);
        if (m == 0)
            leaveLog(*temp, 'a');
        if (m == 1)
            leaveLog(*temp, 'c');


        delete temp;
    }
    else
    {
        string choice = "";
        //temp = new Customer(name, phoneNum, email, totalAmtSpent, numPurchases, numNearbyRestaurants, 1);
        cout << "Data:" << endl;
        cout << *temp << endl;
        cout << "Update Data? (1 to add, anything else to cancel): ";
        cin >> choice;
        cin.ignore(100, '\n');

        if (choice == "1")
        {
            phoneNumBST.insert(*temp);
            phoneNumHT.insert(*temp);
            delete temp;

            temp = new Customer(name, phoneNum, email, totalAmtSpent, numPurchases, numNearbyRestaurants, 2);
            amtSpentLL.addData(*temp);
            delete temp;

            temp = new Customer(name, phoneNum, email, totalAmtSpent, numPurchases, numNearbyRestaurants, 3);
            nearbyRestsLL.addData(*temp);
            delete temp;

            temp = new Customer(name, phoneNum, email, totalAmtSpent, numPurchases, numNearbyRestaurants, 4);
            emailBST.insert(*temp);
            if (m == 0)
                leaveLog(*temp, 'a');
            if (m == 1)
                leaveLog(*temp, 'c');


            delete temp;
        }
        else
        {
            delete temp;
        }
    }
}



/* deletes data
Pre: phoneNumBST - BST that compares phone numbers
emailBST - BST that compares emails
amtSpentLL - Linked List that sorts upon insertion by amount spent
nearbyRestsLL - Linked List that sorts upon insertion by number of nearby restaurants
phoneNumHT - Hash Table that used phone numbers as the key
Post: data deleted from the structure
Return: bool - true if data can be deleted, false otherwise
*/
bool deleteData(BST<Customer> &phoneNumBST, BST<Customer> &emailBST, LinkedList<Customer> &amtSpentLL, LinkedList<Customer> &nearbyRestsLL, HashTable<Customer> &phoneNumHT)
{
    string repeat = "1";
    while (repeat == "1")
    {
        if (phoneNumBST.getCount() <= 0)
        {
            return false;
        }
        else
        {
            string phoneNum = "";
            while (!checkValidPhoneNum(phoneNum))
            {
                cout << "Phone Number (###-###-####): ";
                cin >> phoneNum;
                cin.ignore(100, '\n');

                if (!checkValidPhoneNum(phoneNum))
                {
                    cout << "Invalid Phone Number." << endl;
                }
            }
            HashNode<Customer> *ptr;
            ptr = phoneNumHT.search(phoneNum);
            if (ptr)
            {
                string choice;
                cout << "Data:" << endl;
                cout << ptr->data << endl;
                cout << "Delete Data? (1 to delete, anything else to cancel): ";
                cin >> choice;
                cin.ignore(100, '\n');

                if (choice == "1")
                {

                    string name;
                    string phoneNum;
                    string email;
                    double amtSpent;
                    int numPurchases;
                    int nearbyRests;

                    name = ptr->data.getName();
                    phoneNum = ptr->data.getPhoneNo();
                    email = ptr->data.getEmail();
                    amtSpent = ptr->data.getTotalAmtSpent();
                    numPurchases = ptr->data.getNumPurchases();
                    nearbyRests = ptr->data.getNumNearbyRestaurants();


                    phoneNumHT.remove(phoneNum);
                    Customer *temp;
                    temp = new Customer(name, phoneNum, email, amtSpent, numPurchases, nearbyRests, 1);
                    phoneNumBST.deleteNode(*temp);
                    delete temp;

                    temp = new Customer(name, phoneNum, email, amtSpent, numPurchases, nearbyRests, 2);
                    amtSpentLL.deleteData(*temp);
                    delete temp;

                    temp = new Customer(name, phoneNum, email, amtSpent, numPurchases, nearbyRests, 3);
                    nearbyRestsLL.deleteData(*temp);
                    delete temp;

                    temp = new Customer(name, phoneNum, email, amtSpent, numPurchases, nearbyRests, 4);
                    emailBST.deleteNode(*temp);
                    leaveLog(*temp, 'd');
                    delete temp;

                    cout << "Deleted." << endl;
                }
                else
                {
                    cout << "Not Deleted." << endl;
                }
            }
            else
            {
                cout << "Data not found." << endl;
            }
        }

        clarityLine(cout);
        cout << "Delete another? (Type 1 to repeat, anything else to exit): ";
        cin >> repeat;
        cin.ignore(100, '\n');
        clarityLine(cout);
    }
    return true;
}


/* modifies the data
Pre: phoneNumBST - BST that compares phone numbers
emailBST - BST that compares emails
amtSpentLL - Linked List that sorts upon insertion by amount spent
nearbyRestsLL - Linked List that sorts upon insertion by number of nearby restaurants
phoneNumHT - Hash Table that used phone numbers as the key
Post: data srtuctures now has modified data
Return: bool - true if possible to modify, false otherwise
*/
bool modifyData(BST<Customer> &phoneNumBST, BST<Customer> &emailBST, LinkedList<Customer> &amtSpentLL, LinkedList<Customer> &nearbyRestsLL, HashTable<Customer> &phoneNumHT)
{
    string repeat = "1";
    while (repeat == "1")
    {
        if (phoneNumBST.getCount() <= 0)
        {
            return false;
        }
        else
        {
            cout << "Modifying Data" << endl;
            string phoneNum = "";
            while (!checkValidPhoneNum(phoneNum))
            {
                cout << "Phone Number of Data to Modify (###-###-####): ";
                cin >> phoneNum;
                cin.ignore(100, '\n');

                if (!checkValidPhoneNum(phoneNum))
                {
                    cout << "Invalid Phone Number." << endl;
                }
            }
            HashNode<Customer> *ptr;
            ptr = phoneNumHT.search(phoneNum);
            if (ptr)
            {
                string choice;
                cout << "Data:" << endl;
                cout << ptr->data << endl;
                cout << "Modify Data? (1 to modify, anything else to cancel): ";
                cin >> choice;
                cin.ignore(100, '\n');

                if (choice == "1")
                {

                    string name;
                    string phoneNum;
                    string email;
                    double amtSpent;
                    int numPurchases;
                    int nearbyRests;

                    name = ptr->data.getName();
                    phoneNum = ptr->data.getPhoneNo();
                    email = ptr->data.getEmail();
                    amtSpent = ptr->data.getTotalAmtSpent();
                    numPurchases = ptr->data.getNumPurchases();
                    nearbyRests = ptr->data.getNumNearbyRestaurants();


                    phoneNumHT.remove(phoneNum);
                    Customer *temp;
                    temp = new Customer(name, phoneNum, email, amtSpent, numPurchases, nearbyRests, 1);
                    phoneNumBST.deleteNode(*temp);
                    delete temp;

                    temp = new Customer(name, phoneNum, email, amtSpent, numPurchases, nearbyRests, 2);
                    amtSpentLL.deleteData(*temp);
                    delete temp;

                    temp = new Customer(name, phoneNum, email, amtSpent, numPurchases, nearbyRests, 3);
                    nearbyRestsLL.deleteData(*temp);
                    delete temp;

                    temp = new Customer(name, phoneNum, email, amtSpent, numPurchases, nearbyRests, 4);
                    emailBST.deleteNode(*temp);


                    cout << "New Data Information:" << endl;
                    leaveLog(*temp, 'b');
                    delete temp;
                    
                    addData(phoneNumBST, emailBST, amtSpentLL, nearbyRestsLL, phoneNumHT, 1);

                    cout << "Updated." << endl;
                }
                else
                {
                    cout << "Not Modified." << endl;
                }
            }
            else
            {
                cout << "Data not found." << endl;
            }
        }


        cout << "Repeat? (Type 1 to repeat, anything else not to): ";
        cin >> repeat;
        cin.ignore(100, '\n');
        clarityLine(cout);
    }
    return true;
}


/* searches data by phone number
Pre: phoneNumHT - Hash Table to get access to data
Post:
Return:
*/
void searchByPhone(HashTable<Customer> &phoneNumHT)
{
    string repeat = "1";
    while (repeat == "1")
    {
        cout << "Search (Phone Number)" << endl;
        string phoneNum = "";
        while (!checkValidPhoneNum(phoneNum))
        {
            cout << "Phone Number (###-###-####): ";
            cin >> phoneNum;
            cin.ignore(100, '\n');

            if (!checkValidPhoneNum(phoneNum))
            {
                cout << "Invalid Phone Number." << endl;
            }
        }
        HashNode<Customer> *ptr;
        ptr = phoneNumHT.search(phoneNum);
        if (ptr)
        {
            cout << endl;
            cout << ptr->data << endl;
        }
        else
        {
            cout << phoneNum << " data not found." << endl;
        }


        cout << "Repeat? (Type 1 to repeat, anything else not to): ";
        cin >> repeat;
        cin.ignore(100, '\n');
        clarityLine(cout);
    }

}


/* searches data by email
Pre: emailBST - BST that is sorted by email.
Post:
Return:
*/
void searchByEmail(BST<Customer> &emailBST)
{
    string repeat = "1";
    while (repeat == "1")
    {
        cout << "Search (Email)" << endl;
        string email = "";
        while (!checkValidEmail(email))
        {
            cout << "Email (<body>@<website><dot>com): ";
            cin >> email;
            cin.ignore(100, '\n');

            if (!checkValidEmail(email))
            {
                cout << "Invalid Email." << endl;
            }
        }
        Customer *ptr;
        ptr = new Customer(email);
        LinkNode<Customer> *temp;

        temp = emailBST.searchInfo(*ptr);
        if (temp)
        {
            cout << endl;
            cout << temp->getData() << endl;
        }
        else
        {
            cout << email << " data not found." << endl;
        }


        cout << "Repeat? (Type 1 to repeat, anything else not to): ";
        cin >> repeat;
        cin.ignore(100, '\n');
        clarityLine(cout);
    }
}


/* displays the hash table
Pre: phoneNumHT - Hash Table of customers
Post:
Return:
*/
void displayHashSequence(HashTable<Customer> &phoneNumHT)
{
    cout << phoneNumHT;
}


/* displays data in order of total amount spent
Pre: amtSpent - Linked List of customers sorted by amount spent
Post:
Return:
*/
void displayTotalAmt(LinkedList<Customer> &amtSpentLL)
{
    cout << amtSpentLL;
}


/* displays data in order of number of nearby restaurants
Pre: nearbyRestsLL - Linked List of customers sorted by number of nearby restaurants
Post:
Return:
*/
void displayNearbyRests(LinkedList<Customer> &nearbyRestsLL)
{
    cout << nearbyRestsLL;
}


/* displays data in order of phone numbers
Pre: phoneNumBST - BST of phone numbers
Post:
Return:
*/
void displayPhoneNums(BST<Customer> &phoneNumBST)
{
    cout << phoneNumBST.choice(2);
}


/* outputs efficiency data of the hash table
Pre: phoneNumHT - hash table with phone numbers as the keys
Post:
Return:
*/
void efficiency(HashTable<Customer> &phoneNumHT)
{
    cout << "Table Size: " << phoneNumHT.getTableSize() << endl;
    cout << "Load: " << phoneNumHT.getLoad() << endl;
    cout << "Load Factor: " << (static_cast<double>(phoneNumHT.getLoad()) / phoneNumHT.getTableSize()) * 100 << "%" << endl;

    cout << "Collisions: " << phoneNumHT.getCollisions() << endl;
    cout << "Longest Collisiion Path: " << phoneNumHT.getLongestCollisionPath() << endl;
}


/*
Pre: the menu for the history log. can either view or clear history
Post: the history log file is empties if that option is selected
Return:
*/
void logMenu()
{
    bool repeat = true;
    string choice = "";
    while (repeat)
    {
        cout << "1: View History Log\n";
        cout << "2: Clear History Log\n";
        cout << "Choice: (1 or 2): ";
        cin >> choice;
        cin.ignore(100, '\n');


        if (choice == "1")
        {
            ifstream inFile;
            inFile.open(logName);

            if (inFile.fail())
            {
                cout << logName << " not found." << endl;
            }
            else
            {
                string line;
                while (getline(inFile, line))
                {
                    cout << line << endl;
                }
            }
            inFile.close();
            repeat = false;
        }
        else if (choice == "2")
        {
            ofstream outFile;
            outFile.open(logName);
            outFile.close();
            repeat = false;
            cout << "History cleared." << endl;
        }
        else
        {
            cout << "Invalid Option." << endl;
            repeat = true;
        }
    }
}


/* updates the file with the current data at the end of the program
Pre: bstPhone - BST sorted by phone numbers
outFile - fstream to output to file
fileName - string of file name
header - string of the header of the file
Post:
Return:
*/
void updateFile(BST<Customer> &bstPhone, fstream &outFile, string fileName, string header)
{
    outFile.open(fileName, ios::in);
    if (outFile.fail())
    {
        cout << fileName << " not found." << endl;
    }
    else
    {
        outFile.close();
        outFile.open(fileName, ios::out);
        bstPhone.primeForOutput();
        outFile << header << endl;
        outFile << bstPhone.choice(1); //output in preorder format
        outFile.close();
    }
}



/* updates the history log
Pre: tempC - customer data
type - type of history update. a: add, d: delete, b: modify
Post: history log file is modified with information regarding data structure operations.
Return:
*/
void leaveLog(Customer tempC, char type)
{
    std::ofstream outFile;
    outFile.open(logName, std::ios_base::app);
    clarityLine(outFile);
    if (type == 'a') {//if adding
        outFile << "Customer Added\n";
        clarityLine(outFile);
        outFile << tempC << "\n";
        outFile << endl;
    }
    else if (type == 'd') {//if deleting
        outFile << "Customer Deleted\n";
        clarityLine(outFile);
        outFile << tempC << "\n";
        outFile << endl;
    }
    else if (type == 'b') {//if modify and the customer before chage
        outFile << "Cutomer Data Modified From\n";
        clarityLine(outFile);
        outFile << tempC << "\nInto" << std::endl;
    }
    else {//if modify and th ecustomer after change
        outFile << tempC << std::endl;
        outFile << "\n";
    }

    outFile.close();

}
