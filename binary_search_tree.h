#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>
template <typename Comparable>
struct node { 
    public:
        Comparable data; 
        node* Left;
        node* Right;
}; 
template <typename Comparable>
class BinarySearchTree {
    private:
        node<Comparable>* rootbeerisgood;
    public:
    BinarySearchTree() : rootbeerisgood(nullptr){}
    BinarySearchTree(const BinarySearchTree& amogus) : rootbeerisgood(nullptr){
        rootbeerisgood = clone(amogus.rootbeerisgood);
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
    node<Comparable>* clone(node<Comparable>* curr) const {
        if(curr == nullptr){
            return nullptr;
        }
        else{
            node<Comparable>* x = new node<Comparable>;
            x->data = curr->data;
            x->Left = clone(curr->Left);
            x->Right = clone(curr->Right);
            return x;
        }
    }
    ~BinarySearchTree(){
        if(rootbeerisgood != nullptr){
            removeAll(rootbeerisgood);
        }  
    }
    void removeAll(node<Comparable>* curr){
        if(curr != nullptr){
            removeAll(curr->Left);
            removeAll(curr->Right);
            delete curr;
        }
    }
    BinarySearchTree& operator=(const BinarySearchTree& amogus){
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
    bool containsHelper(const Comparable& search, node<Comparable>* temp) const{
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
    void insert(const Comparable& newt){
        if(rootbeerisgood == nullptr){
            node<Comparable>* b = new node<Comparable>;
            b -> data = newt;
            b -> Left = nullptr;
            b -> Right = nullptr;
            rootbeerisgood = b;
        }
        else{
            insertHelp(newt, rootbeerisgood);
        }
    }
    void insertHelp(const Comparable& newt, node<Comparable>* bu){
            if(bu == nullptr){
                   bu = new node<Comparable>;
                   bu->data = newt;
                   bu->Left = nullptr;
                   bu->Right = nullptr;
            }
            else if(newt > bu->data){
                if(bu->Right != nullptr){
                    return insertHelp(newt,bu->Right);
                }
                else{
                    bu->Right = new node<Comparable>;
                       bu->Right->data = newt;
                    bu->Right->Left = nullptr;
                    bu->Right->Right = nullptr;
                }
            }
            else if(newt < bu->data){
                if(bu->Left != nullptr){
                    return insertHelp(newt, bu -> Left);
                }
                else{
                    bu->Left = new node<Comparable>;
                    bu->Left->data = newt;
                    bu->Left->Left = nullptr;
                    bu->Left->Right = nullptr;
                }
            }
            else if(newt == bu->data){
                //don't insert dupes
                return;
            }
    }
    void remove(const Comparable& newt){
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
    node<Comparable>* removeHelp(const Comparable& newt, node<Comparable>* temp){
        node<Comparable>* checkN;
        if(temp == nullptr){
            return nullptr;
        }
        else if(newt == temp-> data && temp->Left != nullptr && temp->Right != nullptr)
        {
            checkN = find_min_node(temp->Right);
            temp->data = checkN->data;
            temp->Right = removeHelp(temp->data, temp->Right);
        }
        else if(newt > temp->data){
            temp->Right = removeHelp(newt, temp->Right);
        }
        else if(newt < temp->data){
            temp->Left = removeHelp(newt, temp->Left);
        }
        else
        {
            if(temp->Left == nullptr){
                checkN = temp;
                temp = temp->Right;
                delete checkN;
            }
            else if(temp->Right == nullptr){
                checkN = temp;
                temp = temp->Left;
                delete checkN;
            }
        }

        return temp;
    }
    const Comparable& find_min() const {
        if(rootbeerisgood != nullptr){
            return find_minHelper(rootbeerisgood);
        }
        else{
            throw std::invalid_argument("o-tree-san");
        }
    }
    const Comparable& find_minHelper(node<Comparable>* temp) const //- return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    {
        if(temp->Left == nullptr){
            return temp->data;
        }
        else{
            return find_minHelper(temp->Left);
        }
    }
    node<Comparable>* find_min_node(node<Comparable>* temp){
            return find_min_nodeHelper(temp);
    }
    node<Comparable>* find_min_nodeHelper(node<Comparable>* temp){
        if(temp->Left == nullptr){
            return temp;
        }
        else{
            return find_min_nodeHelper(temp->Left);
        }
    }
    const Comparable& find_max() const //- return the maximum value in the tree or throw std::invalid_argument if the tree is empty
    {
        if(rootbeerisgood != nullptr){
            return find_maxHelper(rootbeerisgood);
        }
        else{
            throw std::invalid_argument("o-tree-san");
        }
    }
    const Comparable& find_maxHelper(node<Comparable>* temp) const //- return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    {
        if(temp->Right == nullptr){
            return temp->data;
        }
        else{
            return find_maxHelper(temp->Right);
        }
    }
    void print_tree(std::ostream& Stream = std::cout) const 
    {
        if(rootbeerisgood != nullptr){
            print_tree_helper(Stream,0,rootbeerisgood);
        }
        else{
            Stream << "<empty>\n";
        }
    }
    void print_tree_helper(std::ostream& Stream, int spaces, node<Comparable>* temp) const 
    {
        if(temp != nullptr) {
            
            print_tree_helper(Stream,spaces+2, temp->Right);
            for(int i = 0; i < spaces; i++){
                Stream << " ";
            }
            Stream<< temp->data << "\n";
            print_tree_helper(Stream,spaces+2, temp->Left);
            
        }
    }
};
#endif