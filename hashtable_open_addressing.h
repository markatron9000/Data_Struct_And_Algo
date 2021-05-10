#ifndef HASHTABLE_OPEN_ADDRESSING_H
#define HASHTABLE_OPEN_ADDRESSING_H

#include <iostream>
#include <vector>
#include <functional>

template <class Key, class Hash=std::hash<Key>>
class HashTable {
    private:
    	enum Status{Empty, Active, Del};
        struct node{ 
            Key data;
            Status status;
        };
        std::vector<node*> tayble;
        size_t buckets;
        float loadFactor;
        int currentEntries;
        
    public:
    	HashTable() : buckets(11), loadFactor(0.5), currentEntries(0){
    		for(int i = 0; i < 11; i++){
    			node* x = new node();
    			x -> status = Empty;
                Key nothing{};
                x->data = nothing;
    			tayble.push_back(x);
    		}
    	} 
    	explicit HashTable(size_t setter) : buckets(setter), loadFactor(0.5), currentEntries(0){ 
    		for(size_t i = 0; i < setter; i++){
    			node* x = new node();
    			x -> status = Empty;
                Key nothing{};
                x->data = nothing;
    			tayble.push_back(x);
    		}
    	}
        HashTable(const HashTable& amogus){
            buckets = amogus.buckets;
            decimate();
            loadFactor = amogus.loadFactor;
            currentEntries = amogus.currentEntries;
            for(int i = 0; i < amogus.tayble.size(); i++){
            	node* x = new node;
                x ->data = amogus.tayble.at(i)->data;
                x->status = amogus.tayble.at(i)->status;
                tayble.push_back(x);
            }
        }
        HashTable& operator=(const HashTable& amogus){
            if(this != &amogus){
                tayble.clear();
                buckets = amogus.buckets;
                loadFactor = amogus.loadFactor;
                currentEntries = amogus.currentEntries;
                for(int i = 0; i < amogus.tayble.size(); i++){
                	//std::cout << "check";
                	node* x = new node;
                	x ->data = amogus.tayble.at(i)->data;
                	x->status = amogus.tayble.at(i)->status;
                    tayble.push_back(x);
                }
            }
            return *this;
        }
        ~HashTable(){
            for(node* b : tayble){
                if(b != nullptr){
                	delete b;
            	}
            }
        }
        void decimate(){
            for(node* b : tayble){
                if(b != nullptr){
                	delete b;
            	}
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
    		}
    		currentEntries = 0;
    	}
    	bool insert(const Key& newt){
    		size_t hashValue = Hash{}(newt);
    		size_t index = hashValue % buckets;
    		if(tayble.at(index)->data == newt && tayble.at(index)->status == Active){
    			return false;
    		}
    		if(tayble.at(index) -> status == Empty){
    			tayble.at(index) -> data = newt;
    			tayble.at(index) -> status = Active;
    		}
    		else{
    			int tracker = index;
    			node* x = tayble.at(index);
    			while(x->status != Empty){
    				tracker++;
    				if(tracker >= buckets){
    					tracker = 0;
    				}
    				x = tayble.at(tracker);
    				if(x->status == Del && x->data == newt){
    					break;
    				}
    				else if(x->data == newt){
    					return false;
    				}
    			}
    			x -> data = newt;
    			x -> status = Active;
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
    	bool insert_spec(const Key& newt, std::vector<node*>* z){
    		size_t hashValue = Hash{}(newt);
    		size_t index = hashValue % buckets;
    		if(z->at(index) -> status == Empty){
    			z->at(index) -> data = newt;
    			z->at(index) -> status = Active;
    		}
    		else{
    			int tracker = index;
    			node* x = z->at(index);
    			while(x->status != Empty){
    				tracker++;
    				if(tracker >= buckets){
    					tracker = 0;
    				}
    				x = z->at(tracker);
    				if(x->status == Del && x->data == newt){
    					break;
    				}
    			}
    			x -> data = newt;
    			x -> status = Active;
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
    		if(index > buckets){
    			return 0;
    		}
    		if(tayble.at(index) -> status == Active && tayble.at(index)->data == looker){
    			tayble.at(index) -> status = Del;
    		}
    		else{
    			int tracker = index;
    			int orig = index;
    			node* x = tayble.at(index);
    			while(x->data != looker){
    				tracker++;
    				if(tracker == orig){
    					return 0;
    				}
    				if(tracker >= buckets){
    					tracker = 0;
    				}
    				x = tayble.at(tracker);
    				if(x->data == looker){
    					break;
    				}
    			}
    			x -> status = Del;
    		}

    		currentEntries--;
    		return 1;
    	}
    	bool contains(const Key& looker) const{
    		size_t hashValue = Hash{}(looker);
    		size_t index = hashValue % buckets;
    		if(tayble.at(index) -> status == Active && tayble.at(index)->data == looker){
    			return true;
    		}
    		else{
    			int tracker = index;
    			int orig = index;
    			node* x = tayble.at(index);
    			while(x->data != looker){
    				tracker++;
    				if(tracker == orig){
    					return false;
    				}
    				if(tracker >= buckets){
    					tracker = 0;
    				}
    				x = tayble.at(tracker);
    				if(x->data == looker && x->status == Active){
    					return true;
    				}
    			}
    		}
    		return false;
    	}
    	size_t table_size() const{
    		return buckets;
    	}
    	size_t position(const Key& looker) const{
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
    		if(setter <= 0 || setter > 0.5){
                throw std::invalid_argument("bruh come on");
            }
            loadFactor = setter;
    	}
    	void rehash(size_t setter){
            if(static_cast<float>(currentEntries) / static_cast<float>(setter) > loadFactor){
                setter = currentEntries / loadFactor;
            }
            std::vector<node*> newVec;
            for(int i = 0; i < setter; i++){
                node* x = new node();
                x -> status = Empty;
                Key nothing{};
                x->data = nothing;
                newVec.push_back(x);
            }
    		currentEntries = 0;
    		buckets = setter;
    		for(node* n : tayble){
    			if(n->status == Active){
    				insert_spec(n->data, &newVec);
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
    				Stream << "    "<<currInd << " | " << n->data << "\n";
    				
    			}
    			currInd++;
    		}
    		Stream << "-------------\nThanks for using the MatisHashTable, chief!\n";

    	}

};
#endif  // HASHTABLE_OPEN_ADDRESSING_H