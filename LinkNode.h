/*
Alexander Zhang
*/

#ifndef LinkNode_h
#define LinkNode_h

template <typename T>
class LinkNode
{
private:
    //ADT data
    T data;
    //pointer to next node
    LinkNode *next;
    LinkNode *left;
    LinkNode *right;
public:
    //construtor
    LinkNode();
    LinkNode(T);


    //setter for data
    void setData(T);
    //getter for a data
    T& getData();


    //setter for pointer to a next node
    void setNext(LinkNode *node);

    //getter for a pointer to a next node
    LinkNode *getNext() const;
    LinkNode *&getLeft();
    LinkNode *&getRight();


};


/*Constructor for LinkNode. Sets next to null
Pre:
Post: next - set to null
Return:
*/
template <typename T>
LinkNode<T>::LinkNode()
    : next(nullptr), left(nullptr), right(nullptr)
{
}

template <typename T>
LinkNode<T>::LinkNode(T newData)
{
    next = nullptr;
    left = nullptr;
    right = nullptr;

    data = newData;
}



/*
Pre:dataArg - data to set in a node
Post: assign given data to a node
Return:
*/
template <typename T>
void LinkNode<T>::setData(T dataArg)
{
    data = dataArg;
    left = nullptr;
    right = nullptr;
}
/*
Pre:
Post:
Return: data in a node
*/
template <typename T>
T& LinkNode<T>::getData()
{
    return data;
}

/*
Pre: node - address of a next node
post: assign th egiven address to a next pointer
Return:
*/
template <typename T>
void LinkNode<T>::setNext(LinkNode *node)
{
    next = node;
}

/*
Pre:
Post:
Return: return pointer
*/
template <typename T>
LinkNode<T> *LinkNode<T>::getNext() const
{
    return next;
}

template <typename T>
LinkNode<T> *&LinkNode<T>::getLeft()
{
    return left;
}

template <typename T>
LinkNode<T> *&LinkNode<T>::getRight()
{
    return right;
}
#endif /* LinkNode_h */
