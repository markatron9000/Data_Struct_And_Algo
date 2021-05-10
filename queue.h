#ifndef QUEUE_H
#define QUEUE_H

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "array_list.h"

template <typename Object>
class Queue {
    private:
		size_t queueSize;
		Object *data;

	public:

		Queue(): queueSize(0), data(new Object[0]){

		}

		Queue(const Queue& copier){
			data = new Object[copier.queueSize];
    		for(size_t i = 0; i < copier.queueSize; i++){
  				data[i] = copier.data[i];
  			}
    		queueSize = copier.queueSize;
		}

		~Queue(){
			delete[] data;
		}

		size_t size(){
			return queueSize;
		}

		Queue& operator=(const Queue& copier){
			if(this != &copier){
				queueSize = copier.queueSize;
				delete[] data;
				data = new Object[copier.queueSize];
				for(size_t i = 0; i < copier.queueSize; i++){
  					data[i] = copier.data[i];
  				}
			}
			return *this;
		}

		void enqueue(const Object& Newt){
			Object* tempList = new Object[queueSize+1];
			for(size_t i = 0; i < queueSize; i++){
				tempList[i] = data[i];
			}
			tempList[queueSize] = Newt;
			delete[] data;
			data = tempList;
			queueSize++;
		}

		Object dequeue(){
			if(queueSize==0){
				throw std::out_of_range("The queue is... empty??? No line for the ride!");
			}
			Object* tempList = new Object[queueSize-1];
			for(size_t i = 0; i < queueSize-1; i++){
				tempList[i] = data[i+1];
			}
			Object x = data[0];
			delete[] data;
			data = tempList;
			queueSize--;
			return x;
		}
		
		Object& front(){
			//need to return reference
			if(queueSize==0){
				throw std::out_of_range("The queue is... empty??? No line for the ride!");
			}
			return data[0];
		}		

};

#endif  // QUEUE_H
