/*
Alexander Zhang
*/
#ifndef BST_h
#define BST_h

#include <iostream>
#include "Customer.h"
#include "StacksandQueue.h"

//predeclaration for the overloaded ostream operator due to the class being a template class
template <typename U>
class BST;


template <typename T> //reused the LinkNode.h class for this lab.
class BST
{
protected:
    int count;
    int searchType; //1:PreOrder, 2:InOrder. 3:PostOrder, 4:Breadth

    LinkNode<T> *root; //pointer to the root


    void printAllPreOrderInnerOSTREAM(LinkNode<T> *, std::ostream &); //PreOrder
    void printAllInOrderInnerOSTREAM(LinkNode<T> *, std::ostream &); //InOrder
    void printAllPostOrderInnerOSTREAM(LinkNode<T> *, std::ostream &); //PostOrder

    void printAllTreeFormat(LinkNode<T>* ptr, std::ostream& os, int level);

    void printAllBreadth(std::ostream &); //Breadth-First
    void primeForOutputInner(LinkNode<T> *);

    void insertInner(T, LinkNode<T> *&); //inner function to insert
    bool deleteInner(T, LinkNode<T> *&); //inner function to delete
    LinkNode<T> *findLargest(LinkNode<T> *); //finds the largest under the node. Used to find Inorder Predecessor
    void clearTreeInner(LinkNode<T> *&); //deletes the nodes and frees the memory
    LinkNode<T> *searchInfoInner(T&, LinkNode<T> *);

public:
    BST(); //constructor
    ~BST(); //destructor which calls clearTreeInner to free memory
    int getCount(); //has count

    void insert(T); //outer function to insert T data
    bool deleteNode(T); //outer function to delete T data
    void clearTree(); //out function to delete everything from the tree and frees the memory
    LinkNode<T> *searchInfo(T&);//searches for data and outputs the one data
    void primeForOutput();



    BST<T> &choice(int); //returns BST with the choice of which printAll to use. Used with overloaded ostream operator

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, BST<U>&); //overloaded ostream operator

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, LinkNode<U> *); //used for search data

};

//======================================================================================
// PUBLIC FUNCTIONS TO LET PROGRAMMER CHOOSE TYPE OF PRINT FOR THE OVERLOADED OSTREAM <<
//======================================================================================

/* Choice function modifies the choice of the sort. Used with overloaded ostream operator for cleaner code in the main
Pre: choice - integer of which sort type.
Post:
Return: BST by reference with the modified sort type. This is so it can be accepted as an argument for the overloaded ostream operator
*/
template<typename T>
BST<T> &BST<T>::choice(int choice)
{
    switch (choice)
    {
    case(1):
    {
        searchType = 1; //PreOrder
        return *this;
        break;
    }
    case(2):
    {
        searchType = 2; //InOrder
        return *this;
        break;
    }
    case(3):
    {
        searchType = 3; //PostOrder
        return *this;
        break;
    }
    case(4):
    {
        searchType = 4; //Breadth-First
        return *this;
        break;
    }
    case(5):
    {
        searchType = 5; //tree format
        return *this;
        break;
    }
    default:
    {
        searchType = 2; //Default incase out of bounds
        return *this;
        break;
    }
    }
}


/*Overloaded ostream operator
Pre: os - ostream by reference
tree - BST by reference
Post:
Return: ostream by reference
*/
template <typename U>
std::ostream& operator<<(std::ostream &os, BST<U> &tree)
{
    switch (tree.searchType) //Decides which function to use depending on search type. Each gives different outputs to the ostream object being passed through
    {
    case(1): //preOrder
    {
        os << std::string(70, '=') << std::endl;
        tree.printAllPreOrderInnerOSTREAM(tree.root, os);
        break;
    }
    case(2): //inOrder
    {
        os << std::string(70, '=') << std::endl;
        tree.printAllInOrderInnerOSTREAM(tree.root, os);
        break;
    }
    case(3): //postOrder
    {
        os << std::string(70, '=') << std::endl;
        tree.printAllPostOrderInnerOSTREAM(tree.root, os);
        break;
    }
    case(4): //Breadth-First
    {
        os << std::string(70, '=') << std::endl;
        tree.printAllBreadth(os);
        break;
    }
    case(5): //tree format
    {
        os << std::string(70, '=') << std::endl;
        tree.printAllTreeFormat(tree.root, os, 0);
        os << std::string(70, '=') << std::endl;
        break;
    }
    default:
    {
        break;
    }
    }
    return os;
}


/* overloaded ostream operator to output LinkNode data.
Pre: os - ostream operator by reference
data - LinkNode ptr
Post:
Return: ostream - by reference. has the output of the data.
*/
template <typename U>
std::ostream &operator<<(std::ostream &os, LinkNode<U> *data)
{
    if (data == nullptr) //if not found, data will be nullptr.
    {
        throw "Data not found.";
    }
    os << data->getData();
    return os;
}

//======================================================================================
// PROTECTED FUNTIONS USED FOR OSTREAM AND FSTREAM PRINTING
//======================================================================================

/* Functions assigns preOrder data to os object
Pre: ptr - LinkNode pointer
os - ostream operator by reference
Post: os - now modified to have the proper data. Can be used for cout or file output
Return:
*/
template <typename T>
void BST<T>::printAllPreOrderInnerOSTREAM(LinkNode<T> *ptr, std::ostream &os)
{
    if (ptr == nullptr)
    {
        return;
    }
    os << ptr->getData() << std::endl;
    printAllPreOrderInnerOSTREAM(ptr->getLeft(), os);
    printAllPreOrderInnerOSTREAM(ptr->getRight(), os);
}


/* Functions assigns InOrder data to os object
Pre: ptr - LinkNode pointer
os - ostream operator by reference
Post: os - now modified to have the proper data. Can be used for cout or file output
Return:
*/
template <typename T>
void BST<T>::printAllInOrderInnerOSTREAM(LinkNode<T> *ptr, std::ostream &os)
{
    if (ptr == nullptr)
    {
        return;
    }

    printAllInOrderInnerOSTREAM(ptr->getLeft(), os);

    os << ptr->getData() << std::endl;

    printAllInOrderInnerOSTREAM(ptr->getRight(), os);
}


/* Outputs to console the 2D tree. Root at the very left. Above are the right children; below are the left children. 'tab' indicates a level deeper into the tree
Pre: ptr - root node
os - ostream to hold output
level - integer to know when to tab, etc. Used for formatting.
Post: os - now modified to have the proper data.
Return:
*/
template <>
void BST<Customer>::printAllTreeFormat(LinkNode<Customer>* ptr, std::ostream& os, int level)
{
    if (ptr == nullptr)
    {
        return;
    }

    printAllTreeFormat(ptr->getRight(), os, level + 1);

    for (int i = 0; i < level; ++i)
    {
        os << "  ";
    }

    os << ptr->getData().getName() << std::endl;

    printAllTreeFormat(ptr->getLeft(), os, level + 1);




}



/* Functions assigns PostOrder data to os object
Pre: ptr - LinkNode pointer
os - ostream operator by reference
Post: os - now modified to have the proper data. Can be used for cout or file output
Return:
*/
template <typename T>
void BST<T>::printAllPostOrderInnerOSTREAM(LinkNode<T> *ptr, std::ostream &os)
{
    if (ptr == nullptr)
    {
        return;
    }
    printAllPostOrderInnerOSTREAM(ptr->getLeft(), os);
    printAllPostOrderInnerOSTREAM(ptr->getRight(), os);
    os << ptr->getData() << std::endl;
}




/* Functions assigns Breadth-First data to os object. Uses a queue
Pre: ptr - LinkNode pointer
os - ostream operator by reference
Post: os - now modified to have the proper data. Can be used for cout or file output
Return:
*/
template <typename T>
void BST<T>::printAllBreadth(std::ostream &os)
{
    if (root == nullptr)
    {
        return;
    }

    Queue<LinkNode<T> *> nodesQ; //queue to hold nodes

    LinkNode<T> *ptr;

    nodesQ.enqueue(root); //enter node into queue

    while (!nodesQ.isEmpty())
    {

        ptr = nodesQ.front();

        os << ptr->getData() << std::endl;

        nodesQ.dequeue();

        if (ptr->getLeft() != nullptr) //if left exists, enter left into the queue
        {
            nodesQ.enqueue(ptr->getLeft());
        }
        if (ptr->getRight() != nullptr) //if right exists, enter right into the queue
        {
            nodesQ.enqueue(ptr->getRight());
        }
    }
}

template <>
void  BST<Customer>::primeForOutputInner(LinkNode<Customer> *ptr)
{
    if (ptr == nullptr)
    {
        return;
    }

    primeForOutputInner(ptr->getLeft());

    ptr->getData().setSortType(5); //output format for file output

    primeForOutputInner(ptr->getRight());
}


//======================================================================================
// PROTECTED FUNTIONS FOR INNER BST IMPLEMENTATIONS
//======================================================================================


/* function is protected and is for inner use. Inserts data into the BST
Pre: newData - new data of type T
ptr - ptr to the roots
Post: BST is now modified with new value
Return:
*/
template <typename T>
void BST<T>::insertInner(T newData, LinkNode<T> *&ptr)
{
    if (ptr == nullptr) //if no node, create one in the right spot.
    {
        ptr = new LinkNode<T>(newData);
        ++count;
    }
    else //comparing data to decide whether to go deeper to the left or right
    {
        if (newData < ptr->getData())
        {
            insertInner(newData, ptr->getLeft());
        }
        else if (newData > ptr->getData())
        {
            insertInner(newData, ptr->getRight());
        }
    }
}


/* deletes a node from the BST. Protected because it is for inner use
Pre: delData - T data to be deleted
ptr - ptr to the roots. will point to root member initially
Post:  BST is now modified with the data deleted
Return: bool - true if deleted, false if not found
*/
template <typename T>
bool BST<T>::deleteInner(T delData, LinkNode<T> *&ptr)
{
    if (ptr == nullptr)
    {
        return false;
    }
    else if (delData < ptr->getData()) //go left if data is less than ptr data
    {
        return deleteInner(delData, ptr->getLeft());
    }
    else if (delData > ptr->getData()) //go right if data is less than ptr data
    {
        return deleteInner(delData, ptr->getRight());
    }
    else //data is now found!
    {
        if (ptr->getLeft() == nullptr && ptr->getRight() == nullptr) // if no children
        {
            delete ptr;
            ptr = nullptr;
            return true;
        }
        else if (ptr->getLeft() == nullptr) //if left is nullptr, then we can't assign current ptr to left, we assign to right
        {
            LinkNode<T> *temp = ptr;
            ptr = ptr->getRight();
            delete temp;
            return true;
        }
        else if (ptr->getRight() == nullptr) //same as above. If neither, it will become nullptr regardless.
        {
            LinkNode<T> *temp = ptr;
            ptr = ptr->getLeft();
            delete temp;
            return true;
        }
        else //Finds the inorder predecessor
        {
            LinkNode<T> *temp = findLargest(ptr->getLeft());
            ptr->getData() = temp->getData(); //assigns predecessor data to current root ptr
            return deleteInner(temp->getData(), ptr->getLeft()); //delete the leaf
        }
    }
    return ptr;
}



/* finds largest. Used to find inorder predecessor
Pre: ptr - LinkNode pointer
Post:
Return: LinkNode pointer
*/
template <typename T>
LinkNode<T> *BST<T>::findLargest(LinkNode<T> *ptr)
{
    if (ptr->getRight() == nullptr) //if all the way to the right, return
    {
        return ptr;
    }
    return findLargest(ptr->getRight()); //go all the way to the right

}


/* deletes everything in the tree
Pre: ptr - LinkNode pointer by reference. Initially passed the root member
Post: BST is now empty with memory freed
Return:
*/
template <typename T>
void BST<T>::clearTreeInner(LinkNode<T> *&ptr)
{

    if (ptr == nullptr) //if empty, return
    {
        return;
    }
    clearTreeInner(ptr->getLeft());
    clearTreeInner(ptr->getRight());
    --count;
    delete ptr;
    ptr = nullptr;
}


/* inner searchInfo function
Pre: data - T by reference
ptr - LinkNode<T> pointer
Post:
Return: LinkNode<T> * - will be passed through outer to use as argument for overloaded ostream
*/
template <typename T>
LinkNode<T> *BST<T>::searchInfoInner(T& data, LinkNode<T> *ptr)
{
    if (ptr == nullptr) //if empty or reached bottom without finding data
    {
        return nullptr;
    }


    if (data < ptr->getData()) //go left if data is less than ptr data
    {
        return searchInfoInner(data, ptr->getLeft());
    }
    else if (data > ptr->getData()) //go right if data is less than ptr data
    {
        return searchInfoInner(data, ptr->getRight());
    }
    else //found the data
    {
        return ptr;
    }

}

//======================================================================================
// PUBLIC FUNCTIONS
//======================================================================================


/* Default constructor
Pre:
Post: default output type is InOrder. Root set to nullptr
Return:
*/
template <typename T>
BST<T>::BST() : count(0), root(nullptr)
{
    searchType = 2; //inorder by default
}


/* Destructor
Pre:
Post: memory freed
Return:
*/
template <typename T>
BST<T>::~BST()
{
    clearTreeInner(root); //calls functions. Deletes everything root and under
}


/* gets the count
Pre:
Post:
Return: int - count
*/
template <typename T>
int BST<T>::getCount()
{
    return count;
}


/* out insert function. Used in the main
Pre: newData - T data to be inserted
Post:
Return:
*/
template <typename T>
void BST<T>::insert(T newData)
{
    insertInner(newData, root); //starts the inner function. Passes root member to function
}



/* outer delete function
Pre: delData - T data to be deleted
Post:
Return: bool - true if deleted, false otherwise
*/
template <typename T>
bool BST<T>::deleteNode(T delData)
{
    if (deleteInner(delData, root)) //passes root to start search for node to be deleted
    {
        count -= 1;
        return true;
    }
    else
        return false;
}


/* outer clearTree function
Pre:
Post:
Return:
*/
template <typename T>
void BST<T>::clearTree()
{
    clearTreeInner(root); //passes root to start clearing out the tree
}


/* outer function for searchInfo
Pre: data - data to be looked for. holds the phone number
Post:
Return: LinkNode<T> * - will be used as an argument for overloaded ostream operator
*/
template <typename T>
LinkNode<T> *BST<T>::searchInfo(T& data)//searches for data and returns pointer to the node
{
    return searchInfoInner(data, root);
}

template <>
void BST<Customer>::primeForOutput()
{
    primeForOutputInner(root);
}

#endif /* BST_h */

