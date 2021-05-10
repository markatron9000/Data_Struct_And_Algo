#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>
template <typename Comparable>
struct nodeA { 
    public:
        Comparable data; 
        nodeA* Left;
        nodeA* Right;
        int height;
}; 
template <typename Comparable>
class AVLTree {
    private:
        nodeA<Comparable>* rootbeerisgood;
    public:
    AVLTree() : rootbeerisgood(nullptr){}
    AVLTree(const AVLTree& amogus) : rootbeerisgood(nullptr){
        rootbeerisgood = clone(amogus.rootbeerisgood);
    }
    nodeA<Comparable>* clone(nodeA<Comparable>* curr) const {
        if(curr == nullptr){
            return nullptr;
        }
        else{
            nodeA<Comparable>* x = new nodeA<Comparable>;
            x->data = curr->data;
            x->height = curr->height;
            x->Left = clone(curr->Left);
            x->Right = clone(curr->Right);
            return x;
            
        }
    }
    ~AVLTree(){
        if(rootbeerisgood != nullptr){
            removeAll(rootbeerisgood);
        }
    }
    bool is_empty(){
        if(rootbeerisgood==nullptr){
            return true;
        }
        return false;
    }
    void make_empty(){
        if(rootbeerisgood != nullptr){
            removeAll(rootbeerisgood);
        } 
        rootbeerisgood=nullptr;
    }
    void removeAll(nodeA<Comparable>* curr){
        if(curr != nullptr){
            if(curr -> Left != nullptr){
                removeAll(curr->Left);
            }
            if(curr -> Right != nullptr){
                removeAll(curr->Right);
            }
            delete curr;
        }
    }
    AVLTree& operator=(const AVLTree& amogus){
        if(this!= &amogus){
            removeAll(rootbeerisgood);
            rootbeerisgood = nullptr;
            rootbeerisgood = clone(amogus.rootbeerisgood);
        }
        return *this;
    }
    bool contains(const Comparable& search) const{
        return containsHelper(search, rootbeerisgood);
    }
    bool containsHelper(const Comparable& search, nodeA<Comparable>* temp) const{
        if((temp==nullptr)){
            return false;
        }
        else if(search < temp->data){
            return containsHelper(search, temp->Left);
        }
        else if(search > temp->data){
            return containsHelper(search,temp->Right);
        }
        else{
            return true;
        }
    }
    void insert(const Comparable& newt)
    {
        if(rootbeerisgood == nullptr){
            nodeA<Comparable>* b = new nodeA<Comparable>;
            b -> data = newt;
            b -> Left = nullptr;
            b -> Right = nullptr;
            b -> height = 1;
            rootbeerisgood = b;
        }
        else{
            insertHelp(newt, rootbeerisgood);
        }
    }
    nodeA<Comparable>* RotateRight(nodeA<Comparable>* ancient)
    {
        nodeA<Comparable>* repper = ancient->Left;
        if(ancient == rootbeerisgood){
            ancient->Left = repper->Right;
            repper->Right = ancient;
            ancient->height = std::max(getHeight(ancient->Left), getHeight(ancient->Right)) + 1;
            repper->height = std::max(getHeight(repper->Left), getHeight(repper->Right)) + 1;
            rootbeerisgood = repper;
        }
        else{
            ancient->Left = repper->Right;
            repper->Right = ancient;
            ancient->height = std::max(getHeight(ancient->Left), getHeight(ancient->Right)) + 1;
            repper->height = std::max(getHeight(repper->Left), getHeight(repper->Right)) + 1;
        }
        
        return repper;
    }
    nodeA<Comparable>* RotateLeft(nodeA<Comparable>* ancient)
    {
        nodeA<Comparable>* repper = ancient->Right;
        if(ancient == rootbeerisgood){
            ancient->Right = repper->Left;
            repper->Left = ancient;
            ancient->height = std::max(getHeight(ancient->Left), getHeight(ancient->Right)) + 1;
            repper->height = std::max(getHeight(repper->Left), getHeight(repper->Right)) + 1;
            rootbeerisgood = repper;
        }
        else{
            ancient->Right = repper->Left;
            repper->Left = ancient;
            ancient->height = std::max(getHeight(ancient->Left), getHeight(ancient->Right)) + 1;
            repper->height = std::max(getHeight(repper->Left), getHeight(repper->Right)) + 1;
        }
        return repper;
    }
    nodeA<Comparable>* insertHelp(const Comparable& newt, nodeA<Comparable>* bu)
    {
        if(bu == nullptr){
            nodeA<Comparable>* temp = new nodeA<Comparable>;
            temp -> data = newt;
            temp -> Left = nullptr;
            temp -> Right = nullptr;
            temp -> height = 1;
            return temp;
        }
        else{
            if(newt > bu->data){
                bu->Right = insertHelp(newt,bu->Right);
            }
            else if(newt < bu -> data){
                bu->Left = insertHelp(newt, bu->Left);
            }
        
        }

        //adjustments.... needed?!?!?!?
        bu->height = 1 + std::max(getHeight(bu->Left), getHeight(bu->Right));
        int balANTS = getHeight(bu->Left) - getHeight(bu->Right);
        if(balANTS > 1){
            if(newt < bu->Left->data){
                return RotateRight(bu);
            }
            else{
                bu->Left = RotateLeft(bu->Left);
                return RotateRight(bu);
            }
        }
        else if(balANTS < -1){
            if(newt > bu -> Right->data){
                return RotateLeft(bu);
            }
            else{
                bu->Right = RotateRight(bu->Right);
                return RotateLeft(bu);
            }
        }

        return bu; 
    }
    int getHeight(nodeA<Comparable>* temp){
        if(temp==nullptr){
            return false;
        }
        else{
            return temp->height;
        }
    }
    void remove(const Comparable& newt) {
       if(rootbeerisgood != nullptr){
            if(rootbeerisgood->Right == nullptr && rootbeerisgood->Left == nullptr){
                if(rootbeerisgood->data == newt){
                    delete rootbeerisgood;
                    rootbeerisgood=nullptr;
                }
            }
            else{
                if(rootbeerisgood->data == newt){
                    rootbeerisgood = removeHelp(newt,rootbeerisgood);
                }
                else{
                    removeHelp(newt,rootbeerisgood);
                }
            }
        }
    }
    nodeA<Comparable>* removeHelp(const Comparable& newt, nodeA<Comparable>* temp)
    {
        nodeA<Comparable>* check;

        if(temp == nullptr){
            return nullptr;
        }
        else if(temp-> data == newt && temp->Left != nullptr && temp->Right != nullptr)
        {
            check = find_min_node(temp->Right);
            temp->data = check->data;
            temp->Right = removeHelp(temp->data, temp->Right);
        }
        else if(newt < temp->data){
            temp->Left = removeHelp(newt, temp->Left);
        }
        else if(newt > temp->data){
            temp->Right = removeHelp(newt, temp->Right);
        }
        else{
            if(temp->Left == nullptr){
                check = temp;
                temp = temp->Right;
                delete check;
            }
            else if(temp->Right == nullptr){
                check = temp;
                temp = temp->Left;
                delete check;
            }
        }

        if(temp == nullptr){
            return nullptr;
        }

        temp->height = 1 + std::max(getHeight(temp->Left), getHeight(temp->Right));
        int balANTS = getHeight(temp->Left) - getHeight(temp->Right);
        if(balANTS < -1){
            if(getHeight(temp->Right) < getHeight(temp->Left)){
                temp->Right = RotateRight(temp->Right);
                return RotateLeft(temp);
            }
            else{
                return RotateLeft(temp);
            }
        }
        else if(balANTS > 1){
            if(getHeight(temp->Left) < getHeight(temp->Right)){
                temp->Left = RotateLeft(temp->Left);
                return RotateRight(temp);
            }
            else{
                return RotateRight(temp);
            }
        }
        return temp;
    }
    const Comparable& find_min() const //- return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    {
        if(rootbeerisgood != nullptr){
            return find_minHelper(rootbeerisgood);
        }
        else{
            throw std::invalid_argument("o-tree-san");
        }
    }
    const Comparable& find_minHelper(nodeA<Comparable>* temp) const //- return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    {
        if(temp==nullptr){
             throw std::invalid_argument("o-tree-san");
        }
        if(temp->Left == nullptr){
            return temp->data;
        }
        else{
            return find_minHelper(temp->Left);
        }
    }
    nodeA<Comparable>* find_min_node(nodeA<Comparable>* temp){
            return find_min_nodeHelper(temp);
    }
    nodeA<Comparable>* find_min_nodeHelper(nodeA<Comparable>* temp){
        if(temp->Left == nullptr){
            return temp;
        }
        else{
            return find_min_nodeHelper(temp->Left);
        }
    }
    const Comparable& find_max() const {
        if(rootbeerisgood != nullptr){
            return find_maxHelper(rootbeerisgood);
        }
        else{
            throw std::invalid_argument("o-tree-san");
        }
    }
    const Comparable& find_maxHelper(nodeA<Comparable>* temp) const {
       if(temp==nullptr){
             throw std::invalid_argument("o-tree-san");
        }
       if(temp->Right == nullptr){
            return temp->data;
        }
        else{
            return find_maxHelper(temp->Right);
        }
    }
    void print_tree(std::ostream& Stream = std::cout) const 
    {
        //Stream is outstream
        if(rootbeerisgood != nullptr){
            print_tree_helper(Stream,0,rootbeerisgood);
        }
        else{
            Stream << "<empty>\n";
        }
    }
    void print_tree_helper(std::ostream& Stream, int spaces, nodeA<Comparable>* temp) const 
    {
        //Stream is outstream
        if(temp != nullptr) {
            
            print_tree_helper(Stream,spaces + 2, temp->Right);
            for(int i = 0; i < spaces; i++){
                Stream << " ";
            }
            Stream<< temp->data << "\n";
            print_tree_helper(Stream,spaces+  2, temp->Left);
            
        }
    }

};

#endif