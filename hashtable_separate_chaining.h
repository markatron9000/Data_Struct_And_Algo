#ifndef HASHTABLE_SEPARATE_CHAINING_H
#define HASHTABLE_SEPARATE_CHAINING_H
#include <iostream>
#include <vector>
#include <functional>

template <class Key, class Hash=std::hash<Key>>
class HashTable {
    private:
    	enum Status{Empty, Active};
        struct node{ 
            Key data; 
            node* next;
            node* prev;
            Status status;
        };
        std::vector<node*> tayble;
        size_t buckets;
        float loadFactor;
        int currentEntries;
        
    public:
    	HashTable() : buckets(11), loadFactor(1), currentEntries(0){
    		for(int i = 0; i < 11; i++){
    			node* x = new node();
    			x -> status = Empty;
                Key nothing{};
                x->data = nothing;
                x->next = nullptr;
    			tayble.push_back(x);
    		}
    	} 
    	explicit HashTable(size_t setter) : buckets(setter), loadFactor(1), currentEntries(0){ 
    		for(size_t i = 0; i < setter; i++){
    			node* x = new node();
    			x -> status = Empty;
                Key nothing{};
                x->data = nothing;
                x->next = nullptr;
                x->prev = nullptr;
    			tayble.push_back(x);
    		}
    	}
        HashTable(const HashTable& amogus){
            buckets = amogus.buckets;
            loadFactor = amogus.loadFactor;
            currentEntries = amogus.currentEntries;
            for(int i = 0; i < amogus.tayble.size(); i++){
                tayble.push_back(clone(amogus.tayble[i]));
            }
        }
        HashTable& operator=(const HashTable& amogus){
            if(this!= &amogus){
                this -> make_empty();
                buckets = amogus.buckets;
                loadFactor = amogus.loadFactor;
                currentEntries = amogus.currentEntries;
                for(int i = 0; i < amogus.tayble.size(); i++){
                    tayble.push_back(clone(amogus.tayble[i]));
                }
            }
            return *this;
        }
        node* clone(node* curr) const {
            if(curr == nullptr){
                return nullptr;
            }
            else{
                node* x = new node();
                x -> status = Empty;
                Key nothing{};
                x->data = nothing;
                x->next = clone(curr->next);
                return x;
                
            }
        }
        ~HashTable(){
            for(node* b : tayble){
                recurObliteration(b);
            }
        }
        void decimate(){
            for(node* b : tayble){
                recurObliteration(b);
            }
        }
        void recurObliteration(node* b){
            if(b != nullptr){
                recurObliteration(b->next);
                delete b;
            }
        }
    	bool is_empty() const{
    		if(currentEntries != 0){
    			return false;
    		}
    		return true;
    	}
    	size_t size() const{
    		return currentEntries;
    	}
    	void make_empty(){
    		for(node* n : tayble){
    			n -> status = Empty;
    			node* checks = n;
    			while(checks -> next != nullptr){
    				checks -> status = Empty;
    				checks = checks -> next;
    			}
    			checks -> status = Empty;
    		}
    		currentEntries = 0;
    	}
    	bool insert(const Key& newt){
    		size_t hashValue = Hash{}(newt);
    		size_t index = hashValue % buckets;
    		if(tayble.at(index) -> status == Empty){
    			if(tayble.at(index) -> next == nullptr){
    				if(tayble.at(index) -> data == newt){
    					return false;
    				}
	    			tayble.at(index) -> data = newt;
	    			tayble.at(index) -> status = Active;
    			}
    			else{
    				node* checks = tayble.at(index);
	    			while(checks -> next != nullptr){
	    				if(checks -> data == newt){
	    					return false;
	    				}
	    				checks = checks -> next;
	    			}
	    			if(checks -> data == newt){
	    				return false;
	    			}
                    node* x = new node();
                    x -> data = newt;
                    x -> status = Active;
                    x -> prev = checks;
	    			checks -> next = x;
    			}
    		}
    		else{
    			node* checks = tayble.at(index);
    			while(checks -> next != nullptr){
    				if(checks -> data == newt){
    					return false;
    				}
    				checks = checks -> next;
    			}
    			if(tayble.at(index) -> data == newt){
    					return false;
    			}
    			node* x = new node();
                x -> data = newt;
                x -> status = Active;
                x -> prev = checks;
                checks -> next = x;
    		}

    		currentEntries++;

    		if(static_cast<float>(currentEntries) / static_cast<float>(buckets) >  static_cast<float>(loadFactor)){
    			size_t n = buckets * 2 + 1;
    			bool foundPrime = false;
    			while(foundPrime != true){
                    //foundPrime could be what is bogging my performance down
	    			if (n%2 == 0 || n%3 == 0){
	    				n++;
	    				break;
	   				}
				    for (int i=5; i*i<=n; i=i+6){
				        if (n%i == 0 || n%(i+2) == 0){
				           n++;
				           break;
				        }
				    }
				   
				    foundPrime = true;
				}
    			buckets = n;
    			rehash(n);
    		}
    		return true;
    	}
        bool insert_spec(const Key& newt, std::vector<node*>* z){
            size_t hashValue = Hash{}(newt);
            size_t index = hashValue % buckets;
            if(z->at(index) -> status == Empty){
                if(z->at(index) -> next == nullptr){
                    if(z->at(index) -> data == newt){
                        return false;
                    }
                    z->at(index) -> data = newt;
                    z->at(index) -> status = Active;
                }
                else{
                    node* checks = z->at(index);
                    while(checks -> next != nullptr){
                        if(checks -> data == newt){
                            return false;
                        }
                        checks = checks -> next;
                    }
                    if(checks -> data == newt){
                        return false;
                    }
                    node* x = new node();
                    x -> data = newt;
                    x -> status = Active;
                    x -> prev = checks;
                    checks -> next = x;
                }
            }
            else{
                node* checks = z->at(index);
                while(checks -> next != nullptr){
                    if(checks -> data == newt){
                        return false;
                    }
                    checks = checks -> next;
                }
                if(z->at(index) -> data == newt){
                        return false;
                }
                node* x = new node();
                x -> data = newt;
                x -> status = Active;
                x -> prev = checks;
                checks -> next = x;
            }

            currentEntries++;

            if(static_cast<float>(currentEntries) / static_cast<float>(buckets) >  static_cast<float>(loadFactor)){
                size_t n = buckets * 2;
                bool foundPrime = false;

                while(foundPrime != true){

                    if (n%2 == 0 || n%3 == 0){
                        n++;
                        break;
                    }
                    for (int i=5; i*i<=n; i=i+6){
                        if (n%i == 0 || n%(i+2) == 0){
                           n++;
                           break;
                        }
                    }
                   
                    foundPrime = true;
                }

                buckets = n;
                rehash(n);
            }
            return true;
        }
    	size_t remove(const Key& looker){
    		size_t hashValue = Hash{}(looker);
    		size_t index = hashValue % buckets;
    			if(tayble.at(index) -> data == looker){
    				tayble.at(index) -> status = Empty;
    				currentEntries--; 
    				return 1;
    			}
    			else{
    				node* checks = tayble.at(index);
	    			while(checks -> next != nullptr){
	    				checks = checks -> next;
	    				if(checks->data == looker){
	    					checks -> status = Empty;
	    					currentEntries--;
	    					return 1;
	    				}
	    			}
	    			if(checks->data == looker){
	    				checks -> status = Empty;
	    			}
    			}
    		return 0;
    	}
    	bool contains(const Key& looker) const{
    		size_t hashValue = Hash{}(looker);
    		size_t index = hashValue % buckets;
    		if(tayble.at(index)->status != Empty){
    			if(tayble.at(index) -> data == looker){
    				return true;
    			}
    		}
            node* checks = tayble.at(index);
                    while(checks -> next != nullptr){
                        checks = checks -> next;
                        if(checks->data == looker){
                            if(checks->status == Active){
                            return true;
                            }
                        }
                    }
                    if(checks->data == looker){
                        if(checks->status == Active){
                            return true;
                        }
                    }
    		return false;
    	}
    	size_t bucket_count() const{
    		return buckets;
    	}
    	size_t bucket_size(size_t setter) const{
    			size_t buckSize = 0;
    			node* checks = tayble.at(setter);
    			while(checks -> next != nullptr){
    				checks = checks -> next;
    				buckSize++;
    			}
    			buckSize++;
    			return buckSize;
    		
    	}
    	size_t bucket(const Key& looker) const{
    		size_t hashValue = Hash{}(looker);
    		size_t index = hashValue % buckets;
    		return index;
    	}
    	float load_factor() const{
    		return static_cast<float>(currentEntries) / static_cast<float>(buckets);
    	}
    	float max_load_factor() const{
    		return loadFactor;
    	}
    	void max_load_factor(float setter){
    		if(setter <= 0){
                throw std::invalid_argument("bruh come on");
            }
            if(setter < static_cast<float>(currentEntries) / static_cast<float>(buckets)){
                rehash(setter);
            }
            loadFactor = setter;
    	}
    	void rehash(size_t setter){
            if(static_cast<float>(currentEntries) / static_cast<float>(setter) > loadFactor){
                setter = (currentEntries / loadFactor)+1;
            }
            std::vector<node*> newVec;
            for(int i = 0; i < setter; i++){
                node* x = new node();
                x -> status = Empty;
                Key nothing{};
                x->data = nothing;
                x->next = nullptr;
                newVec.push_back(x);
            }
    		currentEntries = 0;
    		buckets = setter;
    		for(node* n : tayble){
    			if(n -> status == Empty){
    				node* checks = n;
		    		while(checks -> next != nullptr){
		    			if(checks -> status == Active){
		    				insert_spec(checks->data, &newVec);
		    			}
		    			checks = checks -> next;
		    		}
		    		if(checks -> status == Active){
		    			insert_spec(checks->data, &newVec);
		    		}
    			}
    			else{
                    node* checks = n;
                    while(checks -> next != nullptr){
                        if(checks -> status == Active){
                            insert_spec(checks->data, &newVec);
                        }
                        checks = checks -> next;
                    }
                    if(checks -> status == Active){
                        insert_spec(checks->data, &newVec);
                    }
    			}
    		}
            decimate();
            tayble = newVec;
    	}
    	void print_table(std::ostream& Stream = std::cout){
    		if(currentEntries == 0){
    			Stream << "<empty>\n";
    			return;
    		}
    		Stream << "\n-------------\nIndex | Values\n";
    		int currInd = 0; 
            bool flipped = false;
    		for(node* n : tayble){
    			if(n -> status == Active){
    				Stream << "    "<<currInd << " | " << n->data;
    				if(n -> next != nullptr){
    					node* checks = n->next;
		    			while(checks -> next != nullptr){
                            if(checks->status == Active){
		    				  Stream << ", " << checks -> data;
                            }
                            checks = checks->next;
		    			}
                        if(checks->status == Active){
		    			   Stream <<", "<< checks->data << "\n";
                        }
                        else{
                            Stream<<"\n";
                        }
    				}
                    else{
                        Stream << "\n";
                    }
    			}
    			else if(n -> next != nullptr){
    				node* checks = n->next;
		    		while(checks -> next != nullptr){
                        
                        if(checks->status == Active){
                           if(flipped == false){
                            Stream << "    "<<currInd << " | " << n->data;
                            flipped = true;
                           }
                           else{
		    			   Stream << ", " << checks -> data;
                            }
                        }
                        checks = checks->next;
		    		}
                    if(checks->status == Active){
		    		    if(flipped == false){
                            Stream << "    "<<currInd << " | " << checks->data;
                            flipped = true;
                           }
                           else{
                           Stream << ", " << checks -> data;
                            }
                    }
                    else{
                            Stream<<"\n";
                        }
    			}
    			currInd++;
    		}
    		Stream << "-------------\nThanks for using the MatisHashTable, chief!\n";

    	}
        Status getStatus(const Key& looker) const{
            size_t hashValue = Hash{}(looker);
            size_t index = hashValue % buckets;
            if(tayble.at(index)->status != Empty){
                if(tayble.at(index) -> data == looker){
                    return tayble.at(index)->status;
                }
            }
            node* checks = tayble.at(index);
                    while(checks -> next != nullptr){
                        checks = checks -> next;
                        if(checks->data == looker){
                            return checks->status;
                        }
                    }
                    if(checks->data == looker){
                        if(checks->status == Active){
                            return checks->status;
                        }
                    }
            return Empty;
        }

};

#endif  // HASHTABLE_SEPARATE_CHAINING_H