#ifndef LIST_H
#define LIST_H

#include <stdexcept>
#include <iostream>
#include <fstream>

#include "IList.h"

template <typename T>
class List : public IList<T>{
	private:
		typedef struct Node{
			T data;
			Node* pNext;
			Node* pPrev;
		} Node;

		Node* __head;
		Node* __tail;

	public:
		List() : __head(nullptr), __tail(nullptr), IList<T>(){}
		List(int n);
		~List();

		T pop(int n);
		void push_tail(T& data);
		void push(T& data, int n);
		T pop_tail();
		unsigned index(T& data);
		T& operator[](int n);
		const T& operator[](int n) const;
		unsigned size();

		friend std::ostream& operator<<(std::ostream& output, const List<T>& list){
			if(!list._size)	
				output<<(const char*)"<void>";
			else
				for(int i=0; i<list._size; i++){
					output<<list[i];
					if((i+1)!=list._size) output << std::endl;
				}
			return output;
		}

		friend std::ofstream& operator<<(std::ofstream& output, const List<T>& list){
			if(!list._size)	
				output<<(const char*)"<void>";
			else
				for(int i=0; i<list._size; i++){
					output<<list[i];
					if((i+1)!=list._size) output << std::endl;
				}
			return output;
		}
};

template <typename T>
void List<T>::push(T& data, int n){
    if (n < 0 || n > this->_size) {
        throw std::out_of_range("Index out of range");
    }

    Node* newNode = new Node;
    newNode->data = data;

    if (this->_size == 0) {
        __head = newNode;
        __tail = newNode;
        newNode->pNext = nullptr;
        newNode->pPrev = nullptr;
    } else if (n == 0) {
        newNode->pNext = __head;
        newNode->pPrev = nullptr;
        __head->pPrev = newNode;
        __head = newNode;
    } else if (n == this->_size) {
        newNode->pNext = nullptr;
        newNode->pPrev = __tail;
        __tail->pNext = newNode;
        __tail = newNode;
    } else {
        Node* current = __head;
        for (int i = 0; i < n; ++i) {
            current = current->pNext;
        }
        
        newNode->pNext = current;
        newNode->pPrev = current->pPrev;
        
        if (current->pPrev) {
            current->pPrev->pNext = newNode;
        }
        current->pPrev = newNode;
        
        if (newNode->pPrev == nullptr) {
            __head = newNode;
        }
    }

    this->_size++;
}

template <typename T>
unsigned List<T>::size(){
	return this->_size;
}

template <typename T>
List<T>::List(int n) : __head(nullptr), __tail(nullptr), IList<T>(n) {
	if (n <= 0){
		std::logic_error("len list cannot be negative");
	}
	__head = new Node;
	__head->pPrev=nullptr;
	__head->data=nullptr;
	__tail = __head;

	for (int i = 1; i < n; ++i) {
		Node* newNode = new Node;
		newNode->data=nullptr;
		__tail->pNext = newNode;
		newNode->pPrev = __tail;
		__tail = newNode;
	}
	__tail->pNext=nullptr;
}


template <typename T>
T List<T>::pop_tail(){
	T data=__tail->data;
	if(__tail->pPrev==__head){
		delete __tail;
		__tail=nullptr;
	}
	else{
		Node* temp=__tail->pPrev;
		delete __tail;
		__tail=temp;
	}
	this->_size--;
	return data;
}

template <typename T>
unsigned List<T>::index(T& data){
	Node* temp=__head;
	int ind=0;
	while(temp){
		if(temp->data==data)
			return ind;
		temp=temp->pNext;
		ind+=1;
	}
	return -1;
}

template <typename T>
T& List<T>::operator[](int n){
	n=(n<0) ? this->_size+n : n;
	if(n<0){
		std::logic_error("index list out of range");
	}
	
	Node* temp=__head;
	for(int i=0; i++!=n; temp=temp->pNext);
	return temp->data;
}

template <typename T>
const T& List<T>::operator[](int n) const {
	n=(n<0) ? this->_size+n : n;
	if(n>=this->_size || n<0){
		throw std::logic_error("index out of range");
	}
	Node* temp=__head;
	for(int i=0; i!=n; i++) temp=temp->pNext;
	return temp->data;
}

template <typename T>
T List<T>::pop(int n) {
    if (__head == nullptr || n < 0 || n>=this->_size) {
        throw std::out_of_range("Index out of range");
    }
    Node* temp = __head;
    for (int i = 0; i < n; ++i) {
        temp = temp->pNext;
    }

    if (temp->pNext) {
        temp->pNext->pPrev = temp->pPrev;
    } else {
        __tail = temp->pPrev;
    }

    if (temp->pPrev) {
        temp->pPrev->pNext = temp->pNext;
    } else {
        __head = temp->pNext;
    }

    if (__head == __tail) {
        __tail = nullptr;
    }

    T data = temp->data;
    delete temp;
    this->_size--; 

    return data; 
}


template <typename T>
List<T>::~List(){
	Node* temp=__head;
	while(__head){
		temp=temp->pNext;
		delete __head;
		__head=temp;
	}
}

template <typename T>
void List<T>::push_tail(T& data){
	this->_size+=1;
	if(!__head){
		__head=new Node;
		__head->data=data;
		__head->pNext=nullptr;
		__head->pPrev=nullptr;
		return ;
	}
	if(!__tail){
		__tail=new Node;
		__tail->data=data;
		__tail->pNext=nullptr;
		__tail->pPrev=__head;
		__head->pNext=__tail;
		return ;
	}
	Node* new_node=new Node;
	new_node->data=data;
	__tail->pNext=new_node;
	new_node->pPrev=__tail;
	__tail=new_node;
	return ;
}

#endif