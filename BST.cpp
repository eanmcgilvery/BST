#include "BST.h"
#include <iostream> // std::cout
/*=============================================================================================
//
//                       CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR
//
=============================================================================================*/


/*=============================================================================================
//
//                                          TRAVERSALS
//
=============================================================================================*/
template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::Preorder()
{
    Preorder(_root);
}

template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::Preorder(std::shared_ptr<BST_Node<KEY, VALUE> > position)
{
// BASE CASE: Reached one level past the leaf node
    if(!position)
        return;

    std::cout << "KEY: " << position->first() << "  | VALUE: " << position->second() << "\n";
    Preorder(position->Left());
    Preorder(position->Right());
}

template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::Inorder()
{
    Preorder(_root);
}

template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::Inorder(std::shared_ptr<BST_Node<KEY, VALUE> > position)
{
// BASE CASE: Reached one level past the leaf node
    if(!position)
        return;

    Inorder(position->Left());
    std::cout << "KEY: " << position->first() << "  | VALUE: " << position->second() << "\n";
    Inorder(position->Right());
}

template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::Postorder()
{
    Preorder(_root);
}

template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::Postorder(std::shared_ptr<BST_Node<KEY, VALUE> > position)
{
// BASE CASE: Reached one level past the leaf node
    if(!position)
        return;

    Postorder(position->Left());
    Postorder(position->Right());
    std::cout << "KEY: " << position->first() << "  | VALUE: " << position->second() << "\n";
}

template <typename KEY, typename VALUE>
std::shared_ptr<BST_Node<KEY, VALUE> > BST<KEY, VALUE>::Search(KEY valToFind)
{
    std::shared_ptr<BST_Node<KEY, VALUE> > position(_root);

    while(position && (position->first() != valToFind))
    {
        if(valToFind > position->first()) // Move Right
            position = position->Right();
        else if (valToFind < position->first()) // Move Left
            position = position->Left();
    }

    return position;
}

/*=============================================================================================
//
//                                          MODIFIERS
//
=============================================================================================*/
template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::Insert(const std::pair<KEY, VALUE>& dataToInsert)
{
    if(!_root)
    {
        std::shared_ptr<BST_Node<KEY, VALUE> > insertNode (new BST_Node<KEY, VALUE>);
        insertNode ->first  (dataToInsert.first);
        insertNode ->second (dataToInsert.second);

        _root = insertNode;

        return;
    }
    std::shared_ptr<BST_Node<KEY, VALUE> > position(_root);
    std::shared_ptr<BST_Node<KEY, VALUE> > parent_pos(nullptr);

    while (position) // continue until we reach place to insert
    {
        parent_pos = position;
        if(position->first() == dataToInsert.first) // DUPLICATE KEY
            throw std::runtime_error("ERROR : KEY ALREADY EXISTS");

        else if(position->first() > dataToInsert.first) // If inseting key is less than, go left
            position = position->Left();

        else if(position->first() < dataToInsert.first) // If inseting key is greater than, go right
            position = position->Right();
    }

    // Encapsulate the value.
    position = std::shared_ptr<BST_Node<KEY, VALUE> > (new BST_Node<KEY, VALUE>); // NOTE: pos was nullptr, now we give it mem
                                                                                  //  on the heap.
    position->first(dataToInsert.first);
    position->second(dataToInsert.second);

    // Check where we need to insert
    if(parent_pos->first() > dataToInsert.first) //Insert Left
    {
        parent_pos ->Left   (position);
        position   ->Parent (parent_pos);
    }

    if(parent_pos->first() < dataToInsert.first) //Insert Right
    {
        parent_pos ->Right  (position);
        position   ->Parent (parent_pos);
    }
    _size++;
}

template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::Remove(const KEY& dataToRemove)
{
    // Find and Grab the position of the key we want to remove
    std::shared_ptr<BST_Node<KEY, VALUE> > nodeToRemove(Search(dataToRemove));

    // Check to see if it has any children
    if(!nodeToRemove->Left() || !nodeToRemove->Right())
        RemoveZeroOrOneChild(nodeToRemove);

    // There are 2 children
    else
    {
        // Grab the successor by moving 1 right, then all the way down to the left
        std::shared_ptr<BST_Node<KEY, VALUE> > temp(findMinNode(nodeToRemove));

        nodeToRemove->first  (temp->first());
        nodeToRemove->second (temp->second());
        RemoveZeroOrOneChild(temp);
    }
}

template <typename KEY, typename VALUE>
void BST<KEY, VALUE>::RemoveZeroOrOneChild(std::shared_ptr<BST_Node<KEY, VALUE>> pos)
{
    std::shared_ptr<BST_Node<KEY, VALUE>> child, parent;

    if (pos->Left())
        child = pos->Left();
    else
        child = pos->Right();

    if (pos == _root)
    {
        _root = child;
        parent  = nullptr;
    }
    else
    {
        parent = pos->Parent();
        if (parent->Left() == pos)
        {
            parent->Left(child);
        }
        else
        {
            parent->Right(child);
        }
    }

    if (child)
        child->Parent(parent);
}

template <typename KEY, typename VALUE>
std::shared_ptr<BST_Node<KEY, VALUE> > findMinNode(std::shared_ptr<BST_Node<KEY, VALUE> > postion)
{
    while(postion->Left())
        postion = postion->Left();

    return postion;
}