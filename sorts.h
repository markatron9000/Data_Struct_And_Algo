#ifndef SORTS_H
#define SORTS_H
#include <vector>
#include <iostream>
#include <functional>
#include <utility>


template <class Comparable>
void insertion_sort(std::vector<Comparable>& arr){
    std::cout << arr << std::endl;
    if(arr.empty()){
        return;
    }
    Comparable curr;
    int second_i;
    for(size_t i = 1; i < arr.size(); i++){
        curr = arr[i];
        second_i = i - 1;
        while (second_i >= 0 && arr[second_i] > curr){
            arr[second_i + 1] = arr[second_i];
            second_i--;
        }
        arr[second_i + 1] = curr;
        std::cout << arr << std::endl;
    }
}




int findHibbard(int x){
    std::vector<int> hibs = {32767, 16383, 8191, 4095, 2047, 1023, 511, 255, 127, 63, 31, 15, 7, 3, 1, 0};
    int size = 15;
    int index = 0;
    for(int i = 0; i < hibs.size(); i++){
        if(hibs[i] < x){
           index = i;
           break;
        }
    }
    return hibs[index];
}
template <class Comparable>
void shell_sort(std::vector<Comparable>& arr){
    if(arr.size() < 1){
        std::cout << arr << std::endl;
        return;
    }
    std::cout << arr << std::endl;
    for(int z = findHibbard((arr.size())); z > 0; z = findHibbard(z)){
        for( int i = z; i < arr.size( ); ++i )
        {
            Comparable tmp = std::move( arr[ i ] );
            int j = i;
            for( ; j >= z && tmp < arr[ j - z ]; j -= z ){
                arr[ j ] = std::move( arr[ j - z ] );
            }
            arr[ j ] = std::move( tmp );
        }
        std::cout << arr << std::endl;
    }
}


//heap functions for heap sort
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
        if(comp(sheep->at(rightChild), sheep->at(leftChild))){
            return rightChild;
        }
        return leftChild;
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
template <class Container>
void remove(Container* sheep, int index) {
    if (index < 1) {
        return;
    }
    int lastInd = sheep->size()-1;
    swap(sheep, index, lastInd); 
    sheep->pop_back();
    percolate_down(sheep,index);
}
template <class Container>
void heap_delete_min(Container* sheep){
    if(sheep->size() <= 1){
        throw std::invalid_argument("Can't delete minimum from an empty heap!");
    }
    remove(sheep, 1);
}
template <class Comparable>
void heap_sort(std::vector<Comparable>& arr){
    if(arr.size() < 1){
        std::cout<<arr<<std::endl;
        return;
    }
    std::cout << arr << std::endl;
    std::vector<Comparable> heapy = arr;
    heapify(&heapy);
    std::cout << heapy << std::endl;
    std::vector<Comparable> fin;
    for(int i = 0; i < arr.size(); i++){
        fin.push_back(heap_get_min(heapy));
        heap_delete_min(&heapy);
        std::cout << heapy << std::endl;
        std::cout <<fin<<std::endl;
    }
    arr = fin;
}




template <typename Comparable>
void mergeSortHelper(std::vector<Comparable>& arr, std::vector<Comparable>& tmpArray, int left, int right);
template <class Comparable>
void merge_sort(std::vector<Comparable>& arr){
    std::cout << arr << std::endl;
    std::vector<Comparable> tmpArray(arr.size());
    mergeSortHelper(arr, tmpArray, 0, arr.size() - 1);
}
template <typename Comparable>
void merge(std::vector<Comparable> & arr, std::vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd);
template <typename Comparable>
void mergeSortHelper(std::vector<Comparable>& arr, std::vector<Comparable>& tmpArray, int left, int right){
    if(left < right){
        int center = (left + right) / 2;
        mergeSortHelper(arr, tmpArray, left, center);
        mergeSortHelper(arr, tmpArray, center + 1, right);
        merge(arr, tmpArray, left, center + 1, right);
        std::cout << arr << std::endl;
    }
}
template <typename Comparable>
void merge(std::vector<Comparable> & arr, std::vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd){
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    while(leftPos <= leftEnd && rightPos <= rightEnd){
        if(arr[leftPos] <= arr[rightPos]){
            tmpArray[tmpPos++] = std::move(arr[leftPos++]);
        }
        else{
            tmpArray[tmpPos++] = std::move(arr[rightPos++]);
        }
    }
    while(leftPos <= leftEnd){
        tmpArray[tmpPos++] = std::move(arr[leftPos++]);
    }
    while(rightPos <= rightEnd){
        tmpArray[tmpPos++] = std::move(arr[rightPos++]);
    }
    for(int i = 0; i < numElements; ++i, --rightEnd){
        arr[rightEnd] = std::move(tmpArray[rightEnd]);
    }
}




void bucket_sort(std::vector<unsigned>& arr){
    unsigned maxVal = 0;
    if(arr.size() < 1){
        std::cout << arr << std::endl;
        return;
    }
    for(int i = 0; i < arr.size(); i++){
        if(arr[i] > maxVal){
            maxVal = arr[i];
        }
    }
    int n = arr.size();
    std::vector<unsigned> b[n];
    std::vector<unsigned> nums;
    for(int i = 0; i < maxVal; i++){
        nums.push_back(0);
    }
    std::cout << arr << std::endl;
    for (int i = 0; i < n; i++) {
        int bi = n * arr[i] / (maxVal+1);
        b[bi].push_back(arr[i]);
        nums[arr[i]] = nums[arr[i]] + 1;
    }
    std::string startToPrint = "[";
    bool cont = false;
    for(int i = 0; i < nums.size(); i++){
        startToPrint = startToPrint + std::to_string(nums[i]) + ", "; 
    }
    std::cout <<  startToPrint.substr(0, startToPrint.size()-2)  << "]" << std::endl;
    for (int i = 0; i < n; i++){
        std::sort(b[i].begin(), b[i].end());
    }
    
    std::string midToPrint = "[";
    int index = 0;
    auto prev = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < b[i].size(); j++){
            arr[index++] = b[i][j];
            midToPrint += std::to_string(b[i][j]);
            midToPrint += ", ";
        }
        if(b[i].size() > 0){
            std::cout << midToPrint.substr(0, midToPrint.size()-2) << "]" << std::endl;
        }
    }
}
#endif  // SORTS_H