/*
Alexander Zhang
*/

#ifndef HashTable_h
#define HashTable_h
#include "Customer.h"
#include <string>

void clarityLineHT(std::ostream &os)
{
    os << std::string(70, '=');
}

template <typename U>
class HashNode;

template <typename T>
class HashNode
{
public:
    T data;

    HashNode(T data)
    {
        this->data = data;
    }
};


template <typename T>
class HashTable
{
private:
    HashNode<T> **table;
    int collisions;
    int longestCollisionPath;
    int load;
    int tableSize;
    int limitor;

protected:
    bool isInteger(char);
    void quadraticProbeInsert(int &, int &);
    void quadraticProbeSearch(int &, int &, std::string);
    void linearProbeInsert(int &, int &);
    void linearProbeSearch(int &, int &, std::string);
    int findLimitor();
    int hashFunct(std::string key);

public:
    HashTable(int);

    int getLimitor();
    int getCollisions();
    int getLongestCollisionPath();
    int getLoad();
    int getTableSize();
    void insert(T);
    HashNode<T> *search(std::string key);
    bool remove(std::string key);
    ~HashTable();

    //Functions for outputting
    void hashPrint(std::ostream &);
    template <typename U>
    friend std::ostream &operator << (std::ostream &, HashTable<U> &);

};
//======================================================================================
// FUNCTIONS FOR OUTPUTTING
//======================================================================================

/* overloaded ostream operator
Pre: htable has values
Post: outputs contents of the hash table. 'x' for empty node
Return: ostream - for output and holds contents
*/
template <typename U>
std::ostream &operator << (std::ostream &os, HashTable<U> &htable)
{
    htable.hashPrint(os);
    return os;
}


/* prints; used for ostream operator. x for empty spot
Pre: os - ostream operator
Post: os has data of the hash table
Return: os is modified. no returns
*/
template <>
void HashTable<Customer>::hashPrint(std::ostream &os)
{
    clarityLineHT(os);
    os << std::endl;
    for (int i = 0; i < tableSize; i++)
    {
        if (table[i] == nullptr)
        {
            os << "X" << std::endl;
            clarityLineHT(os);
            os << std::endl;
        }
        else
        {
            os << table[i]->data << std::endl;
        }
    }
}

//======================================================================================
// PROTECTED FUNCTIONS FOR INTERNAL USE
//======================================================================================

/* checks if character is integer or not
Pre: test - character to test if integer
Post:
Return: bool - true if integer, false if not
*/
template <typename T>
bool HashTable<T>::isInteger(char test)
{
    if (test >= '0' && test <= '9') //if integer
        return true;
    else
        return false;
}


/* quadratic probing for the insert function. Adds to the new home address
Pre: probeNum - int by reference. Number of probes that have been done
home - int by reference. Holds the home address.
Post: probeNum and home are modified unless home address is already on an empty space
Return:
*/
template <typename T>
void HashTable<T>::quadraticProbeInsert(int &probeNum, int &home)
{
    while (table[home] != nullptr)
    {
        ++collisions;
        ++probeNum;

        home = (home + (probeNum * probeNum)) % tableSize; //quadratic probing.

        if (probeNum >= limitor) // stops when cycling seems to be occuring
        {
            break;
        }
    }
}


/* linear probing for the insert function
Pre: probeNum - int by reference. Number of probes that have been done
home - int by reference. Holds the home address
Post: probeNum and home are modified unless already on an empty space
Return:
*/
template <typename T>
void HashTable<T>::linearProbeInsert(int &probeNum, int &home)
{
    while (table[home] != nullptr) //linear resolution after quadratic begins signs of cycling
    {
        ++collisions;
        ++probeNum;

        home = (home + 1) % tableSize; //linear probe

        if (probeNum > tableSize + limitor) //if load is fully searched, stops cycling if entire hash table is traversed. + limitor is to account for previous quadratic probing
        {
            break;
        }
    }
}


/* quadratic probe for searching. stops when key is found
Pre: probeNum - int by reference. Number of probes that have been done
home - int by reference. Holds the home address
key - string that holds phone number key
Post: probeNum and home are modified unless already on an empty space
Return:
*/
template <>
void HashTable<Customer>::quadraticProbeSearch(int &probeNum, int &home, std::string key)
{
    while (table[home] != nullptr && table[home]->data.getPhoneNo() != key)
    {
        ++probeNum;

        home = (home + (probeNum * probeNum)) % tableSize; //quadratic probe

        if (probeNum >= limitor) //prevents cyclic hashing
        {
            break;
        }
    }
}


/* linear probe for searching. stops when key is found
Pre: probeNum - int by reference. Number of probes that have been done
home - int by reference. Holds the home address
key - string that holds phone number key
Post: probeNum and home are modified unless already on an empty space
Return:
*/
template <>
void HashTable<Customer>::linearProbeSearch(int &probeNum, int &home, std::string key)
{
    while (table[home] != nullptr && table[home]->data.getPhoneNo() != key)
    {
        ++probeNum;

        home = (home + 1) % tableSize; //linear probe

        if (probeNum > tableSize + limitor) //if load is full, stops cycling if entire hash table is traversed;
        {
            return;
        }
    }
}


/* finds the limitor. Value of the squareroot of number smallest but closest to the size
Improves efficiency of quadratic search to cover most of the table
Pre:
Post:
Return: int - the limitor. this will affect probing
*/
template <typename T>
int HashTable<T>::findLimitor()
{
    double a = 0;
    double b = tableSize;

    double mid = 4;
    while (b - a >= .00001)
    {
        mid = (a + b) / 2; //finds the middle

        if ((mid * mid) < tableSize)
        {
            a = mid; //increase bounds
        }
        else if ((mid * mid) > tableSize)
        {
            b = mid; //lower bounds
        }
    }
    // mid holds square root of size or closest one if mid does not have one
    return mid;
}




/* hash function which adds the integers in the birthday until it becomes less than 9
Pre: key - has birthday
Post:
Return: int - home address which is less than 9.
*/
template <>
int HashTable<Customer>::hashFunct(std::string key)
{
    long length = key.length();

    int sum = 0;

    for (int i = 0; i < length; i++)
    {
        if (isInteger(key[i]))
        {
            sum += key[i] - '0'; //initial sum
        }
        else if (key[i] != '-')
        {
            return false;
        }
    }

    //pseudorandom generation
    int address = (7 * sum + 11) % tableSize;

    return address;
}



//======================================================================================
// PUBLIC FUNCTIONS
//======================================================================================

/* constructor. initializes values to 0.
Pre:
Post: values have 0. table becomes the hash table of size tableSize. holds pointers to nodes
Return:
*/
template <typename T>
HashTable<T>::HashTable(int tSize)
{
    tableSize = tSize;
    collisions = 0;
    longestCollisionPath = 0;
    load = 0;
    limitor = findLimitor(); //finds the limitor
    table = new HashNode<T> *[tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        table[i] = nullptr;
    }
}


/* returns the limitor
Pre:
Post:
Return: int - square root of size or closest lower value
*/
template <typename T>
int HashTable<T>::getLimitor()
{
    return limitor;
}


/* get number of collisions
Pre:
Post:
Return: int - number of collisions
*/
template <typename T>
int HashTable<T>::getCollisions()
{
    return collisions;
}

/* gets longest collision path
Pre:
Post:
Return: int - longest collision path
*/
template <typename T>
int HashTable<T>::getLongestCollisionPath()
{
    return longestCollisionPath;
}


/* gets the load, count, of the hash table
Pre:
Post:
Return: int - number of data within has table.
*/
template <typename T>
int HashTable<T>::getLoad()
{
    return load;
}


/* gets size of table. This is determined already because the lab said to make it match input data
Pre:
Post:
Return: int - size of table
*/
template <typename T>
int HashTable<T>::getTableSize()
{
    return tableSize;
}


/* insert function. uses quadratic probing for collision resolution up to two times before linear
Pre: data - holds data
Post: table has a node which contains the data
Return:
*/
template <typename T>
void HashTable<T>::insert(T data)
{
    if (load >= tableSize) //end if table is already full
    {
        return;
    }
    int home = hashFunct(data);
    int probeNum = 0; //number of probes; used for quadratic collision resolution increments

    quadraticProbeInsert(probeNum, home);

    linearProbeInsert(probeNum, home);

    if (table[home] == nullptr) //add new data
    {
        ++load; //add one to load
        table[home] = new HashNode<Customer>(data);
    }

    if (probeNum > longestCollisionPath)
    {
        longestCollisionPath = probeNum;
    }
}

/* insert function. uses quadratic probing for collision resolution up to two times before linear
Pre: data - Person type that holds the name and birthday
Post: table has a node which contains the data
Return:
*/
template <>
void HashTable<Customer>::insert(Customer data)
{
    if (load >= tableSize) //end if table is already full
    {
        return;
    }
    int home = hashFunct(data.getPhoneNo());
    int probeNum = 0; //number of probes; used for quadratic collision resolution increments

    quadraticProbeInsert(probeNum, home);

    linearProbeInsert(probeNum, home);

    if (table[home] == nullptr) //add new data
    {
        ++load; //add one to load
        table[home] = new HashNode<Customer>(data);
    }

    if (probeNum > longestCollisionPath)
    {
        longestCollisionPath = probeNum;
    }
}


/* looks for data. bool determines whether it was found or not. outputs data if found.
Pre: key - string that holds birthday
Post:
Return: HashNode * - pointer to hashnode so we can use operators on it in the main.
*/
template <>
HashNode<Customer> *HashTable<Customer>::search(std::string key)
{
    int probeNum = 0;
    int home = hashFunct(key);
    //matches the insert functions except does not change collisions. follows path of insertion

    quadraticProbeSearch(probeNum, home, key);
    linearProbeSearch(probeNum, home, key);

    if (probeNum > tableSize + limitor) //if load is full, stops cycling if entire hash table is traversed;
    {
        return nullptr;
    }

    if (table[home] == NULL)
        return nullptr; //not found
    else
        return table[home];
}


/* deletes data
Pre: key - holds bday
Post: table has node with data pointing to nullptr
Return: bool - true if deleted, false if not
*/
template <>
bool HashTable<Customer>::remove(std::string key)
{
    if (load <= 0) //end if table is already empty
    {
        return false;
    }
    int home = hashFunct(key);
    int probeNum = 0; //number of probes; used for quadratic collision resolution increments

    quadraticProbeSearch(probeNum, home, key);

    linearProbeSearch(probeNum, home, key);

    if (probeNum > tableSize + limitor) //if load is full, stops cycling if entire hash table is traversed;
    {
        return false;
    }

    if (table[home] == nullptr) //not found
    {
        return false;
    }
    else if (table[home] != nullptr && table[home]->data.getPhoneNo() == key)
    {
        delete table[home];
        table[home] = nullptr;
        --load;
        return true;
    }
    else
    {
        return false;
    }
}


/* Destructor
Pre:
Post: table is empty. everything is deleted and set to nullptr
Return:
*/
template <typename T>
HashTable<T>::~HashTable()
{
    for (int i = 0; i < tableSize; i++)
    {
        if (table[i] != nullptr)
        {
            delete table[i]; //free data
            table[i] = nullptr;
        }
    }
    delete[] table;
}


#endif /* HashTable_h */
