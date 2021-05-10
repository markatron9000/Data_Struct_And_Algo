#ifndef HEAP_H
#define HEAP_H

#include <functional>
#include <vector>
#include <iostream>

template <class Container>
void swap(Container* sheep, int& x, int& y){
    typename Container::value_type temp = sheep->at(x);
    sheep->at(x) = sheep->at(y);
    sheep->at(y) = temp;
} 
template <class Container, class Compare=std::less<typename Container::value_type>>
int getMinIndex(Container* sheep, int index1, int leftChild, int rightChild, Compare comp = std::less<typename Container::value_type>{}) {
	int max_index = sheep->size()-1;
	if(max_index < leftChild){
		return index1;
	}
	bool isLeftSmaller = (comp(sheep->at(index1),sheep->at(leftChild)));
	if (max_index < rightChild) { 
    	if(isLeftSmaller){
    		return index1;
    	}
    	return leftChild;
  	} 
  	else if (isLeftSmaller) {
    	if(comp(sheep->at(index1), sheep->at(rightChild))){
    		return index1;
    	}
    	return rightChild;
  	} 
  	else {
  		if(comp(sheep->at(leftChild), sheep->at(rightChild))){
  			return leftChild;
  		}
  		return rightChild;
  }
  return -1;
}
template <class Container>
int childFind(Container* sheep, int check){
	if (sheep->size() <= 1 || 2 * (size_t)check >= sheep->size()){ 
    	return -1; 
  	}
    return (2 * check);
}
template <class Container>
int parentFind(Container* sheep, int check){
	if (sheep->size() <= 1){ 
    	return -1; 
  	}
  	if(check == 1){
  		return -1;
  	}
    return (check/2);
}
template <class Container, class Compare=std::less<typename Container::value_type>>
void percolate_down(Container* sheep, int index, Compare comp = std::less<typename Container::value_type>{}){
	int child = childFind(sheep,index);
	if (child == -1){ 
		return;
	}
	int minIndex = getMinIndex(sheep, index, child, child + 1, comp);
	if (minIndex != index) {
		swap(sheep, minIndex, index);
	    percolate_down(sheep, minIndex,comp);
	}
}
template <class Container, class Compare=std::less<typename Container::value_type>>
void percolate_up(Container* sheep, int index, Compare comp = std::less<typename Container::value_type>{}){
	int parentIndex = parentFind(sheep, index);
 	if (parentIndex == -1){
 		return;
 	}
 	if (comp(sheep->at(index), sheep->at(parentIndex))) {
		swap(sheep, parentIndex, index);
   		percolate_up(sheep, parentIndex,comp);
  	} 
}
template <class Container, class Compare=std::less<typename Container::value_type>>
void heapify(Container* sheep, Compare comp = std::less<typename Container::value_type>{}){
	const typename Container::value_type nothing{};
	sheep->insert(sheep->begin(), nothing);
	for(int i = sheep -> size(); i > 0; i--){
		percolate_down(sheep,i,comp);
	}

}


template <class Container, class Compare=std::less<typename Container::value_type>>
void heap_insert(Container* sheep, const typename Container::value_type& ins, Compare comp = std::less<typename Container::value_type>{}){
	sheep->push_back(ins);
  	percolate_up(sheep, sheep->size()-1, comp);
}



template <class Container>
const typename Container::value_type& heap_get_min(const Container& sheep){
	if(sheep.size() <= 1){
		throw std::invalid_argument("Can't peek minimum of an empty heap!");
	}
	return sheep.at(1);
}

template <class Container, class Compare=std::less<typename Container::value_type>>
void remove(Container* sheep, int index, Compare comp = std::less<typename Container::value_type>{}) {
 	if (index < 1) {
 		return;
 	}
 	int lastInd = sheep->size()-1;
 	swap(sheep, index, lastInd); 
 	sheep->pop_back();
 	percolate_down(sheep,index,comp);
}
template <class Container, class Compare=std::less<typename Container::value_type>>
void heap_delete_min(Container* sheep, Compare comp = std::less<typename Container::value_type>{}){
	if(sheep->size() <= 1){
		throw std::invalid_argument("Can't delete minimum from an empty heap!");
	}
	remove(sheep, 1, comp);
}
template <class Container>
void heap_delete_all(Container* sheep){
	if(sheep->size() < 2){
		return;
	}
	sheep->clear();
	const typename Container::value_type nothing{};
	sheep->push_back(nothing);
}


#endif  // HEAP_H