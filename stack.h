#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "array_list.h"

template <typename Object>
class Stack {
   // TODO(student): implement Stack
	
	 private:
		size_t StackSize;
		Object *data;

	public:

		Stack(): StackSize(0), data(new Object[0]){

		}

		Stack(const Stack& copier){
			data = new Object[copier.StackSize];
    		for(size_t i = 0; i < copier.StackSize; i++){
  				//garbage
  				data[i] = copier.data[i];
  			}
    		StackSize = copier.StackSize;
		}

		~Stack(){
			delete[] data;
		}

		Stack& operator=(const Stack& copier){
			//apparently attempts a double free
			if(this != &copier){
				StackSize = copier.StackSize;
				delete[] data;
				data = new Object[copier.StackSize];
				for(size_t i = 0; i < copier.StackSize; i++){
  					data[i] = copier.data[i];
  				}
    		StackSize = copier.StackSize;
			}
			return *this;
		}

		void push(const Object& Newt){
			Object* tempList = new Object[StackSize+1];
			for(size_t i = 0; i < StackSize; i++){
				tempList[i] = data[i];
			}
			tempList[StackSize] = Newt;
			delete[] data;
			data = tempList;
			StackSize++;
		}

		Object pop(){
			if(StackSize==0){
				throw std::out_of_range("The Stack is... empty??? Find some more plates!");
			}
			Object* tempList = new Object[StackSize-1];
			for(size_t i = 0; i < StackSize-1; i++){
				tempList[i] = data[i];
			}
			Object x = data[StackSize-1];
			delete[] data;
			data = tempList;
			StackSize--;
			return x;
		}
		
		Object& top(){
			//need to return reference
			if(StackSize==0){
				throw std::out_of_range("The queue is... empty??? Find some more plates!");
			}
			return data[StackSize-1];
		}		

	/*
	private:
		size_t StackSize;
		ArrayList<Object> *data;

	public:

		Stack(): StackSize(0), data(new ArrayList<Object>){

		}

		Stack(const Stack& copier){
			ArrayList<Object> data;
    		for(size_t i = 0; i < copier.StackSize; i++){
  				Object x = copier.data -> access(i);
  				data.insertNonRef(i, x);
  			}
    		StackSize = copier.StackSize;
		}

		~Stack(){
			delete data;
		}

		Stack& operator=(const Stack& copier){
			//apparently attempts a double free
			if(this != &copier){
				StackSize = copier.StackSize;
				delete data;
				ArrayList<Object> data;
				for(size_t i = 0; i < copier.StackSize; i++){
  					data -> insert(i, copier.data -> return_reference(i));
  				}
    		StackSize = copier.StackSize;
			}
			return *this;
		}

		void push(const Object& Newt){
			data -> insert(StackSize, Newt);
			StackSize++;
		}

		Object pop(){
			if(StackSize==0){
				throw std::out_of_range("The Stack is... empty??? Find some more plates!");
			}
			Object b;
			b = data -> access(StackSize-1);
			data -> remove(StackSize-1);
			StackSize--;
			return b;
		}
		
		Object& front(){
			//need to return reference
			if(StackSize==0){
				throw std::out_of_range("The queue is... empty??? Find some more plates!");
			}
			return data -> return_reference(StackSize-1);
		}		
	*/
};

#endif  // STACK_H