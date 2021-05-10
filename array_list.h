#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <cstddef>
#include <stdexcept>
#include <iostream>

template <typename Object>
class ArrayList {
	private:
		size_t listSize;
		Object *data;

	public:

		ArrayList(): listSize(0), data(new Object[0]) {}

		explicit ArrayList(size_t userSize): listSize(userSize), data(new Object[userSize]) {}

		~ArrayList(){
			delete[] data;
		}


		ArrayList(const ArrayList& copier){
			data = new Object[copier.listSize];
    		for(size_t i = 0; i < copier.listSize; i++){
  				data[i] = copier.data[i];
  			}
    		listSize = copier.listSize;
		}


		ArrayList& operator=(const ArrayList& copier) {
			if(this!= &copier){
				listSize = copier.listSize;
				delete[] data;
				data = new Object[copier.listSize];
				for(size_t i = 0; i < copier.listSize; i++){
  					data[i] = copier.data[i];
  				}
			}
			return *this;
		}

		size_t size(){
			return listSize;
		}

		Object& operator[](size_t index){
			if(index >= listSize){
				throw std::out_of_range("out of range cuh ");
			}
			return data[index];
		}

		Object& return_reference(size_t index){
			if(index >= listSize){
				throw std::out_of_range("out of range cuh ");
			}
			return data[index];
		}

		Object return_nonref(size_t index){
			if(index >= listSize){
				throw std::out_of_range("out of range cuh ");
			}
			return data[index];
		}

		void insertNonRef(size_t index, Object NEW_OBJECT_BABYYYYYY){
			if(index > listSize){
				throw std::out_of_range("out of range cuh ");
			}

			Object* tempList = new Object[listSize+1];
			for(size_t i = 0; i < index; i++){
				tempList[i] = data[i];
			}
			tempList[index] = NEW_OBJECT_BABYYYYYY;
			for(size_t i = index; i < listSize; i++){
				tempList[i+1] = data[i];
			}
			delete[] data;
			data = tempList;
			listSize++;
		}

		void insert(size_t index, const Object& NEW_OBJECT_BABYYYYYY){
			if(index > listSize){
				throw std::out_of_range("out of range cuh ");
			}

			Object* tempList = new Object[listSize+1];
			for(size_t i = 0; i < index; i++){
				tempList[i] = data[i];
			}
			tempList[index] = NEW_OBJECT_BABYYYYYY;
			for(size_t i = index; i < listSize; i++){
				tempList[i+1] = data[i];
			}
			delete[] data;
			data = tempList;
			listSize++;
		}

		void remove(size_t index){
			if(index >= listSize){
				throw std::out_of_range("out of range cuh ");
			}

			Object* tempList = new Object[listSize-1];
			for(size_t i = 0; i < index; i++){
				tempList[i] = data[i];
			}
			for(size_t i = index; i < listSize-1; i++){
				tempList[i] = data[i+1];
			}
			delete[] data;
			data = tempList;

			listSize--;
		}

		Object access(size_t index){
			return data[index];
		}
};

#endif  // ARRAY_LIST_H