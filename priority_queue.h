#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <functional>
#include <vector>
#include "heap.h"

template <class Comparable, class Container=std::vector<Comparable>, class Compare=std::less<typename Container::value_type>>
class PriorityQueue {
    public:
	    Compare compare;
	    Container container;

	    PriorityQueue(){
	    	const typename Container::value_type nothing{};
	    	container.push_back(nothing); //need to push back string if comparable is string
	    }
	    PriorityQueue(const Compare& inpComp, const Container& inpCont) : compare(inpComp){
	    	for(int i = 0; i < inpCont.size(); i++){
	    		container.push_back(inpCont[i]);
	    	}
	    	heapify(&container, compare);
	    }
	    explicit PriorityQueue(const Compare& inpComp) : compare(inpComp){
	    	const typename Container::value_type nothing{};
	    	container.push_back(nothing);
	    }
	    explicit PriorityQueue(const Container& inpCont){
	    	for(int i = 0; i < inpCont.size(); i++){
	    		container.push_back(inpCont[i]);
	    	}
	    	heapify(&container, compare);
	    }
	    PriorityQueue(const PriorityQueue& amogus){
	        compare = amogus.compare;
	        for(int i = 0; i < amogus.container.size(); i++){
	        	container.push_back(amogus.container[i]);
	        }
	    }
	    PriorityQueue& operator=(const PriorityQueue& amogus){
	        if(this!= &amogus){
	            compare = amogus.compare;
	            this -> make_empty();
		        for(int i = 1; i < amogus.container.size(); i++){
	        		container.push_back(amogus.container[i]);
	        	}
	        }
	        return *this;
	    }
	    typename Container::const_reference top() const{
	    	if(container.size() < 2){
	    		throw std::invalid_argument("Container MT dawg");
	    	}
	    	return heap_get_min(container);
	    }
	    bool empty() const{
	    	if(container.size() < 2){
	    		return true;
	    	}
	    	return false;
	    }
	    size_t size() const{
	    	return container.size()-1;
	    }
	    void make_empty(){
	    	heap_delete_all(&container);
	    }
	    void push(const typename Container::value_type& ins){
	    	heap_insert(&container, ins, compare);
	    }
	    void pop(){
	    	try{
	    		heap_delete_min(&container, compare);
	    	}
	    	catch(...){}
	    }
	    void print_queue(std::ostream& stream = std::cout) const{
	    	if(container.size() < 2){
	    		stream << "<empty>\n";
	    		return;
	    	}
	    	for(int x = 1; x < container.size()-1; x++){
	    		stream << container.at(x) << ", ";
	    	}
	    	stream << container.at(container.size()-1)<<"\n";
	    }
};

#endif  // PRIORITY_QUEUE_H