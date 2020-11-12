#include <memory>  // shared_ptr
#include <utility> // pair

template <typename KEY, typename VALUE>
class BST_Node
{
public:
    //Constructors & Destructors
    BST_Node() = default;
    BST_Node(std::shared_ptr<BST_Node<KEY, VALUE> > parent,
             std::shared_ptr<BST_Node<KEY, VALUE> > left,
             std::pair<KEY, VALUE>&& contents,
             std::shared_ptr<BST_Node<KEY, VALUE> > right)
            : _parent(parent), _left(left), _contents(std::move(contents)),
              _right(right) {}

    //Getters
    std::shared_ptr<BST_Node<KEY, VALUE> > Parent() {return _parent;}
    std::shared_ptr<BST_Node<KEY, VALUE> > Left()   {return _left;}
    std::shared_ptr<BST_Node<KEY, VALUE> > Right()  {return _right;}

    KEY   first()  {return _contents.first;}
    VALUE second() {return _contents.second;}

    //Setters
    void Parent(std::shared_ptr<BST_Node<KEY, VALUE> > ptr) { _parent = ptr;}
    void Left(std::shared_ptr<BST_Node<KEY, VALUE> > ptr)   { _left = ptr;}
    void Right(std::shared_ptr<BST_Node<KEY, VALUE> > ptr)  { _right = ptr;}

    void first(KEY key) {_contents.first = key;}
    void second(VALUE val) {_contents.second = val;}


private:
    std::shared_ptr<BST_Node<KEY, VALUE> > _parent;
    std::shared_ptr<BST_Node<KEY, VALUE> > _left;
    std::shared_ptr<BST_Node<KEY, VALUE> > _right;

    std::pair<KEY, VALUE> _contents;
};