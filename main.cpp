#include "BST.cpp"
#include <utility>
#include <ctime>
int main()
{
    BST<int, bool> myTree;
    
    // Create 10 Random numbers to Insert
    srand(time(nullptr));
    for(auto i = 0; i < 10; i++) {
        std::pair<int, bool> data(i,0);//(rand() % 1000 + 1), false); // Gen rand num from 1-1000
        if (i == 0)
            std::cout << "ROOT: " << data.first << "\n\n";
        myTree.Insert(data);
    }

    myTree.Preorder();

    myTree.Remove(3);

    myTree.Preorder();

    return 0;
}