#ifndef BST_H
#define BST_H

#include <memory>  // std::shared_ptr
#include <utility> // std::pair
#include "BST_Node.cpp"
template <typename KEY, typename VALUE>
class BST
{
    public:
        // Constructors, Destructor, Copy Assignment Operator
        BST() : _root(nullptr), _size(0) {}
        //BST(BST<KEY, VALUE> rhs);

        // Traversal Functions
        void Preorder();
        void Inorder();
        void Postorder();

        // Modifiers
        void Insert(const std::pair<KEY, VALUE>&);
        void Remove(const KEY&);


    private:
        std::shared_ptr <BST_Node<KEY, VALUE> > _root;
        std::size_t _size;

        // Helper Functions
        void Preorder (std::shared_ptr<BST_Node<KEY, VALUE> >);
        void Inorder  (std::shared_ptr<BST_Node<KEY, VALUE> >);
        void Postorder(std::shared_ptr<BST_Node<KEY, VALUE> >);

        std::shared_ptr<BST_Node<KEY, VALUE> > Search(KEY);
        void RemoveZeroOrOneChild(std::shared_ptr<BST_Node<KEY, VALUE> >);

};

#endif //BST_H
