#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename Object>
struct node { 
    public:
	    Object data; 
	    node* next;
	    node* previous;
	    
}; 
template <typename Object>
class DoublyLinkedList {
    private:
		node<Object>* head;
		node<Object>* tail;
		size_t bsize;

    public:
    	DoublyLinkedList():  head(nullptr), tail(nullptr), bsize(0){
    
    	}

    	//rule of three
	    DoublyLinkedList(const DoublyLinkedList& lis){
	    	bsize = lis.bsize;
	    	if(lis.head == nullptr){
	    		head = nullptr;
	    	}
	    	else{

	    		head = new node<Object>;
	    		tail = head;
	    		head->previous=nullptr;
	    		
	    		node<Object>* curr = lis.head;
	    		head -> data = curr -> data;
	    		curr = curr -> next;
	    		if(curr == nullptr){
	    			head -> next = nullptr;
	    		}
	    		else{
	    			node<Object>* toadd = head;
	    			while(curr != nullptr){
	    				toadd->next = new node<Object>;
	    				toadd->next->previous = toadd;

	    				toadd = toadd->next;

	    				toadd -> data = curr -> data;
	    				curr = curr -> next;
	    			}
	    			toadd -> next = nullptr;
	    			tail = toadd;


	    		}


	    	}
	    }

	    ~DoublyLinkedList(){
	    	if(head!= nullptr){
	    		node<Object>* curr = head;
	    		while(curr != nullptr){
	    			node<Object>* temp = curr;
	    			curr = curr -> next;
	    			delete temp;
	    		}

	    	}
	    }
		DoublyLinkedList& operator=(const DoublyLinkedList& lis){
				//this one brought some pain
				bsize = lis.bsize;
				if(this!= &lis){
					if(head != nullptr){

						node<Object>* checker = head;
						while(checker!= nullptr){
							node<Object>* Crushed = checker;
							checker = checker -> next;
							delete Crushed;
						}

						head = nullptr;
						tail = nullptr;
					}
					//if empty stop here
					if(lis.head == nullptr){
						head = nullptr;
					}
					//now can copy
					else{
						node<Object>* curr = lis.head;
						head = new node<Object>;
						tail = head;
						head -> data =  curr -> data;
						head -> previous = nullptr;
						curr = curr -> next;
						if(curr == nullptr){
                    		head -> next  = nullptr;
						}
						else{
							node<Object>* toadd = head;
		    				while(curr != nullptr){
			    				toadd->next = new node<Object>;
			    				toadd->next->previous = toadd;

			    				toadd = toadd->next;

			    				toadd -> data = curr -> data;
			    				curr = curr -> next;
		    				}
			    			toadd -> next = nullptr;
			    			tail = toadd;
			    		}
					}
				}
				return *this;
		}
		size_t size() const{
	 		return bsize;
		}
		Object& operator[](size_t index){
				if(index >= bsize){
					throw std::out_of_range("out of range cuh ");
				}
				node<Object>* temp = head;
				for(size_t i = 0; i < index; i++){
					temp = temp -> next;
				}
				return temp -> data;
			}
		Object taily(){
				return tail -> data;
			}	
		void insert(size_t b, const Object& x){
			node<Object>* temp = new node<Object>;

			temp -> data = x;
			if(b > bsize){
				 throw std::out_of_range("outtie");
			}
			if(head == nullptr){
				head = temp;
				temp -> next = nullptr;
				temp -> previous = nullptr;
			}
			else if(b==0){
				node<Object>* prev = head;
					temp -> next = prev;
					temp -> previous = nullptr;
					head = temp;
				}
			else{
				node<Object>* prev = head;
				for(size_t i = 0; i < b-1;i++){
					prev = prev->next;
				}
				if(prev == nullptr){

				}
				
				if(prev->next != nullptr){
					prev->next->previous = temp;
					temp->next = prev->next;
					prev->next = temp;
					temp->previous = prev;
				}
				else{
					temp->next = nullptr;
					prev->next = temp;
					temp->previous = prev;
					tail = temp;
				}

			}
			if(b == bsize){
				tail = temp;
			}
			bsize++;

		}
		void remove(size_t index){
			node<Object>* temp = head;
			if(bsize==0){
				throw std::out_of_range("MT List chief");
			}
			else if(index >= bsize || index < 0){
			 	throw std::out_of_range("outtie");
			}
			else if(bsize == 1 && index == 0){
				head = nullptr;
				tail = nullptr;
				delete temp;
				bsize--;
			}
			else if(index == 0 && head->next != nullptr){
				head = head -> next;
				delete temp;
				bsize--;
			}
			else if(index == 1 && head->next != nullptr){
				if(head->next->next != nullptr){
				temp = head->next;
				head->next = head->next->next;
				delete temp;
				bsize--;
				}
			}
			else{
				for(size_t i = 0; i < index; i++){
					temp = temp->next;
				}
				if(temp == nullptr){
					return;
				}
				else if(temp -> next == nullptr){
					tail = temp->previous;
					tail -> next = nullptr;;
				}
				else if(temp == head){
					head = head -> next;
                    if (head == nullptr){
                        tail = nullptr;
                    }
                    else{
                        head -> previous = nullptr;
                    }
				}
				if(temp->previous != nullptr){
					if(temp->next != nullptr){
						temp -> next -> previous = temp -> previous;
						temp -> previous -> next = temp -> next;
					}
					else{
						temp->previous->next = nullptr;
					}
				}
				
				delete temp;
				bsize--;
			}
		}

	

};

#endif  // DOUBLY_LINKED_LIST_H
