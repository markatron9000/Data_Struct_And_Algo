#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>


//still under construction, but mostly there...

template <typename Comparable>
class RedBlackTree {
 	public:
        enum Color {RED, BLACK};
        struct nodeRB { 
            public:
                Comparable value; 
                nodeRB* left;
                nodeRB* right;
                nodeRB* Parent;
                Color color;
        };

		nodeRB* carrot; //the ROOT node
        bool dupe = false;
        bool DubBlack = false;
        nodeRB* holder=nullptr;

    RedBlackTree() : carrot(nullptr){}
    RedBlackTree(const RedBlackTree& amogus) : carrot(nullptr){
        carrot = clone(amogus.carrot);
    }
    Color color(const nodeRB* node) const{
    	if(node != nullptr){
    		return node -> color;
    	}
    	else{
    		//null nodes ARE seen as black
            return BLACK;    	
        }
    }
    const nodeRB* get_root() const{
    	if(carrot != nullptr){
    		return carrot;
    	}
    	else{
    		return nullptr;
    	}
    }
    nodeRB* clone(nodeRB* curr) const {
        if(curr == nullptr){
            return nullptr;
        }
        else{
            nodeRB* x = new nodeRB;
            x->value = curr->value;
            x->color = curr->color;
            x->Parent = curr->Parent;
            x->left = clone(curr->left);
            x->right = clone(curr->right);
            return x;
            
        }
    }
    ~RedBlackTree(){
        if(carrot != nullptr){
            removeAll(carrot);
        }
    }
    bool is_empty(){
        if(carrot==nullptr){
            return true;
        }
        return false;
    }
    void make_empty(){
        if(carrot != nullptr){
            removeAll(carrot);
        } 
        carrot=nullptr;
    }
    void removeAll(nodeRB* curr){
        if(curr != nullptr){
            if(curr -> left != nullptr){
                removeAll(curr->left);
            }
            if(curr -> right != nullptr){
                removeAll(curr->right);
            }
            delete curr;
        }
    }
    RedBlackTree& operator=(const RedBlackTree& amogus){
        if(this!= &amogus){
            removeAll(carrot);
            carrot = nullptr;
            carrot = clone(amogus.carrot);
        }
        return *this;
    }
    bool contains(const Comparable& search) const{
        return containsHelper(search, carrot);
    }
    bool containsHelper(const Comparable& search, nodeRB* temp) const{
        if((temp==nullptr)){
            return false;
        }
        else if(search < temp->value){
            return containsHelper(search, temp->left);
        }
        else if(search > temp->value){
            return containsHelper(search,temp->right);
        }
        else{
            return true;
        }
    }
    void insert(const Comparable& newt) //- insert the given value into the tree
    {
        if(carrot == nullptr){
            nodeRB* b = new nodeRB;
            b -> value = newt;
            b -> left = nullptr;
            b -> right = nullptr;
            b -> Parent = nullptr;
            b -> color = BLACK;
            carrot = b;
        }
        else{
            nodeRB* x = new nodeRB;
            x -> value = newt;
            x -> left = nullptr;
            x -> right = nullptr;
            x -> color = RED;
            insertHelp(carrot, x);
            if(dupe != true){
                insertRebal(x);
            }
            dupe = false;
        }
    }
    nodeRB* Rotateright(nodeRB* ancient){
        nodeRB* repper = ancient->left;
        if(ancient == carrot){
            if(ancient->Parent != nullptr){
                //new stuff
                if(ancient==ancient->Parent->left){
                    ancient->Parent->left = repper;
                }
                else{
                    ancient->Parent->right = repper;
                }
            }
            ancient->Parent = repper;
            repper->Parent = nullptr;
            ancient->left = repper->right;
            repper->right = ancient;
            carrot = repper;
        }
        else{
            if(ancient->Parent != nullptr){
                //new stuff
                if(ancient==ancient->Parent->left){
                    ancient->Parent->left = repper;
                }
                else{
                    ancient->Parent->right = repper;
                }
            }
            repper->Parent = ancient->Parent;
            ancient->Parent = repper;
            ancient->left = repper->right;
            repper->right = ancient;
        }
        
        return repper;
    }
    nodeRB* Rotateleft(nodeRB* ancient){
        nodeRB* repper = ancient->right;
        if(ancient == carrot){
            if(ancient->Parent != nullptr){
                //new stuff
                if(ancient==ancient->Parent->left){
                    ancient->Parent->left = repper;
                }
                else{
                    ancient->Parent->right = repper;
                }
            }
            ancient->Parent = repper;
            repper->Parent = nullptr;
            ancient->right = repper->left;
            repper->left = ancient;
            carrot = repper;
        }
        else{
            if(ancient->Parent != nullptr){
                //new stuff
                if(ancient==ancient->Parent->left){
                    ancient->Parent->left = repper;
                }
                else{
                    ancient->Parent->right = repper;
                }
            }
            repper->Parent = ancient->Parent;
            ancient->Parent = repper;
            ancient->right = repper->left;
            repper->left = ancient;
        }
        return repper;
    }
    nodeRB* insertHelp(nodeRB* newt, nodeRB* bu) //- insert the given value into the tree
    {
        if(newt == nullptr){
            return bu;
        }
        else{
            if(newt->value > bu->value){
                newt->left = insertHelp(newt->left,bu);
                newt->left->Parent = newt;
            }
            else if(newt->value < bu -> value){
                newt->right = insertHelp(newt->right, bu);
                newt->right->Parent = newt;
            }
            else{
                //tricky, tricky dupes
                delete bu;
                bu = nullptr;
                dupe = true;
                return newt;
            }
        }  
        return newt;
    }
    void insertRebal(nodeRB* bu){
        if(bu == nullptr){
            return;
        }
        else if(bu == carrot){
            carrot->color = BLACK;
            return;
        }
        while (bu != carrot && color(bu) == RED && color(bu->Parent) == RED) {
            nodeRB* parent = bu->Parent;
            nodeRB* grandparent = bu->Parent->Parent;
            if (parent == grandparent->left) {
                nodeRB* uncle = grandparent->right;
                if (color(uncle) == RED) {
                    uncle->color = BLACK;
                    parent->color =BLACK;
                    grandparent ->color = RED;
                    bu = grandparent;
                } 
                else {
                    if (bu == parent->right) {
                        grandparent -> left = Rotateleft(parent);
                        if(grandparent->Parent != nullptr){
                            if(grandparent->Parent->right == grandparent){
                                grandparent->Parent->right = Rotateright(grandparent);
                            }
                            else{
                                grandparent->Parent->left = Rotateright(grandparent);
                            }
                            
                        }
                        else{
                            Rotateright(grandparent);
                        }
                        bu->color = BLACK;
                        grandparent->color = RED;
                    }
                    else{
                        if(grandparent->Parent != nullptr){
                           if(grandparent->Parent->right == grandparent){
                                grandparent->Parent->right = Rotateright(grandparent);
                            }
                            else{
                                grandparent->Parent->left = Rotateright(grandparent);
                            }
                        }
                        else{
                            Rotateright(grandparent);
                        }
                        parent->color = BLACK;
                        grandparent->color = RED;

                    }
                }
            } 
            else {
                nodeRB* uncle = grandparent->left;
                if (color(uncle) == RED) {
                    uncle ->color = BLACK;
                    parent ->color = BLACK;
                    grandparent ->color = RED;
                    bu = grandparent;
                } 
                else {
                    if (bu == parent->left) {
                        grandparent -> left = Rotateright(parent);
                        if(grandparent->Parent != nullptr){
                            if(grandparent->Parent->right == grandparent){
                                grandparent->Parent->right = Rotateleft(grandparent);
                            }
                            else{
                                grandparent->Parent->left = Rotateleft(grandparent);
                            }
                        }
                        else{
                            Rotateleft(grandparent);
                        }
                        bu->color = BLACK;
                        grandparent->color = RED;
                    }
                    else{  
                        if(grandparent->Parent != nullptr){
                            if(grandparent->Parent->right == grandparent){
                                grandparent->Parent->right = Rotateleft(grandparent);
                            }
                            else{
                                grandparent->Parent->left = Rotateleft(grandparent);
                            }
                        }
                        else{
                            Rotateleft(grandparent);
                        }
                        grandparent->color = RED;
                        parent->color = BLACK;
                    }
                }
            }
        carrot ->color = BLACK;
        }
    }
    void remove(const Comparable& newt) {
       if(carrot != nullptr){
            if(carrot->right == nullptr && carrot->left == nullptr){
                if(carrot->value == newt){
                    std::cout << std::endl<<"carrot to be deleted " << carrot->value << std::endl;
                    delete carrot;
                    carrot=nullptr;
                }
            }
            else if ((carrot->value == newt) && (carrot->left != nullptr)&&(carrot->right == nullptr)){
                nodeRB* z = carrot->left;
                delete carrot;
                carrot = z;
                carrot->color = BLACK;
            }
            else if ((carrot->value == newt) && (carrot->right != nullptr)&&(carrot->left == nullptr)){
                nodeRB* z = carrot->right;
                delete carrot;
                carrot = z;
                carrot->color = BLACK;
            }
            else{
                if(carrot->value == newt){
                    removeHelp(newt,carrot);
                    removeRebal(holder);
                    holder = nullptr;
                }
                else{
                    removeHelp(newt,carrot);
                    removeRebal(holder);
                    holder = nullptr;
                }
            }
        }
    }
    nodeRB* removeHelp(const Comparable& newt, nodeRB* temp)
    {
        nodeRB* checkN;
        if(temp == nullptr){
            return nullptr;
        }
        else if(newt == temp-> value && temp->left != nullptr && temp->right != nullptr)
        {
            checkN = find_min_node(temp->right);
            temp->value = checkN->value;
            temp->right = removeHelp(temp->value, temp->right);
        }
        else if(newt > temp->value){
            temp->right = removeHelp(newt, temp->right);
        }
        else if(newt < temp->value){
            temp->left = removeHelp(newt, temp->left);
        }
        else
        {
            if(temp->left == nullptr){
                checkN = temp;
                if(holder == nullptr){
                    holder = temp;
                    
                }
            }
            else if(temp->right == nullptr){
                checkN = temp;
                if(holder == nullptr){
                    holder = temp;
                    
                }
            }
            else{
                if(holder == nullptr){
                    holder = temp;
                    
                }
            }
        }

        return temp;
        
    }
    void removeRebal(nodeRB* bu){
        if(bu == nullptr){
            return;
        }
        if(bu == carrot){
            if(bu -> left != nullptr && bu->right == nullptr){
                nodeRB* z = carrot->left;
                delete carrot;
                carrot = z;
                carrot->color = BLACK;
            }
            else if(bu->right != nullptr && bu->left == nullptr){
                nodeRB* z = carrot->right;
                delete carrot;
                carrot = z;
                carrot->color = BLACK;
            }
            else if(bu->right == nullptr && bu->left == nullptr){
                delete carrot;
                carrot = nullptr;
                return;
            }
            else{

            }
        }
        if (color(bu) == RED || color(bu->left) == RED || color(bu->right) == RED) {
            nodeRB* child;
            if(bu->left != nullptr){
                child = bu->left;
            }
            else{
                child = bu->right;
            }

            if (bu == bu->Parent->right) {
                bu->Parent->right = child;
                if (child != nullptr){
                    child->Parent = bu->Parent;
                    child->color = BLACK;
                }
                delete (bu);
            } 
            else {
                bu->Parent->left = child;
                if (child != nullptr){
                    child->Parent = bu->Parent;
                    child->color = BLACK;
                }
                delete (bu);
            }
        } 
        else {
            
            nodeRB*sibling = nullptr;
            nodeRB*parent = nullptr;
            nodeRB* tempsy = bu;
            tempsy->color = BLACK;
            DubBlack = true;
            while (tempsy != carrot && DubBlack == true) {
                parent = tempsy->Parent;
                if (tempsy == parent->left) {
                    sibling = parent->right;
                    if (color(sibling) == RED) {
                        sibling->color = BLACK;
                        parent->color = RED;
                        Rotateleft(parent);
                        DubBlack = false;
                    } 
                    else {
                        
                        if (color(sibling->left) == BLACK && color(sibling->right) == BLACK) {
                            sibling->color= RED;
                            if(color(parent) == RED){
                                parent->color = BLACK;
                            }
                            else{}
                            tempsy = parent;
                        } 
                        else {
                            if (color(sibling->right) == BLACK) {
                                sibling->left->color = BLACK;
                                sibling->color = RED;
                                Rotateright(sibling);
                                sibling = parent->right;
                            }
                            sibling->color =  parent->color;
                            parent->color = BLACK;
                            sibling->right -> color = BLACK;
                            Rotateleft(parent);
                            DubBlack = false;
                        }
                    }
                } 
                else {
                    sibling = parent->left;
                    if (color(sibling) == RED) {
                        sibling ->color = BLACK;
                        parent->color = RED;
                        Rotateright(parent);
                        DubBlack = false;
                    } 
                    else {
                        if(sibling == nullptr){
                            parent->color = BLACK;
                            Rotateright(parent);
                            DubBlack = false;
                        }
                        else if (color(sibling->left) == BLACK && color(sibling->right) == BLACK) {
                            //here, removing 60
                            sibling->color = RED;
                            if (color(parent) == RED){
                                parent->color= BLACK;
                            }
                            else{}
                            tempsy = parent;
                        } 
                        else {
                            if (color(sibling->left) == BLACK && color(sibling->right) == BLACK) {
                                sibling->right->color = BLACK;
                                sibling->color = RED;
                                Rotateleft(sibling);
                                sibling = parent->left;
                            }
                            sibling ->color = parent->color;
                            parent->color = BLACK;
                            sibling->left->color = BLACK;
                            Rotateright(parent);
                            DubBlack = false;
                        }
                    }
                }
            }

            if (bu == bu->Parent->left){
                if(bu->right != nullptr && bu->left == nullptr){
                    bu->Parent->left = bu->right;
                }
                else if(bu->right == nullptr && bu->left != nullptr){
                    bu->Parent->left = bu->left;
                }
                else{
                bu->Parent->left = nullptr;
                }
            }
            else{
                if(bu->right != nullptr && bu->left == nullptr){
                    bu->Parent->right = bu->right;
                }
                else if(bu->right == nullptr && bu->left != nullptr){
                    bu->Parent->right = bu->left;
                }
                else{
                bu->Parent->right = nullptr;
                }
            }
            delete(bu);
            carrot ->color = BLACK;
        
        }
    }
    const Comparable& find_min() const //- return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    {
        if(carrot != nullptr){
            return find_minHelper(carrot);
        }
        else{
            throw std::invalid_argument("o-tree-san");
        }
    }
    const Comparable& find_minHelper(nodeRB* temp) const //- return the minimum value in the tree or throw std::invalid_argument if the tree is empty
    {
        if(temp==nullptr){
             throw std::invalid_argument("o-tree-san");
        }
        if(temp->left == nullptr){
            return temp->value;
        }
        else{
            return find_minHelper(temp->left);
        }
    }
    nodeRB* find_min_node(nodeRB* temp){
            return find_min_nodeHelper(temp);
    }
    nodeRB* find_min_nodeHelper(nodeRB* temp){
        if(temp->left == nullptr){
            return temp;
        }
        else{
            return find_min_nodeHelper(temp->left);
        }
    }
    const Comparable& find_max() const {
        if(carrot != nullptr){
            return find_maxHelper(carrot);
        }
        else{
            throw std::invalid_argument("o-tree-san");
        }
    }
    const Comparable& find_maxHelper(nodeRB* temp) const {
       if(temp==nullptr){
             throw std::invalid_argument("o-tree-san");
        }
       if(temp->right == nullptr){
            return temp->value;
        }
        else{
            return find_maxHelper(temp->right);
        }
    }
    void print_tree(std::ostream& Stream = std::cout) const 
    {
        //Stream is outstream
        if(carrot != nullptr){
            print_tree_helper(Stream,0,carrot);
        }
        else{
            Stream << "<empty>\n";
        }
    }
    Comparable& returnParent(nodeRB* look){
        if(look != nullptr){
            return look->Parent->value;
        }
        else{
         throw std::out_of_range("yo");   
        }
    }
    void print_tree_helper(std::ostream& Stream, int spaces, nodeRB* temp) const 
    {
        //Stream is outstream
        if(temp != nullptr) {
            
            print_tree_helper(Stream,spaces + 2, temp->right);
            for(int i = 0; i < spaces; i++){
                Stream << " ";
            }
            Stream<< temp->value << "\n";
            print_tree_helper(Stream,spaces+  2, temp->left);
            
        }
    }
    void print_tree_pretty(std::ostream& Stream = std::cout) const 
    {
        //Stream is outstream
        if(carrot != nullptr){
            print_tree_pretty_helper(Stream,0,carrot);
        }
        else{
            Stream << "<empty>\n";
        }
    }
    void print_tree_pretty_helper(std::ostream& Stream, int spaces, nodeRB* temp) const 
    {
        //Stream is outstream
        if(temp != nullptr) {
            print_tree_pretty_helper(Stream,spaces + 2, temp->right);
            if(temp->color == BLACK){
                Stream<< "\033[1m\033[34m";
            }
            else{
                Stream <<"\033[1m\033[31m";
            }
            for(int i = 0; i < spaces; i++){
                Stream << " ";
            }
            if(temp->color == BLACK){
            	Stream<<temp->value << "\033[0m\n";
            }
            else{
            	Stream << temp->value << "\033[0m\n";
            }
            
            print_tree_pretty_helper(Stream,spaces+  2, temp->left);
            
        }
    }

};

#endif  // RED_BLACK_TREE_H