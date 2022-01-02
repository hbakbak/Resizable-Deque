/*****************************************
 * UW User ID:  hbakbak
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2021
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#ifndef DYNAMIC_DEQUE_H
#define DYNAMIC_DEQUE_H

#include "Exception.h"

template <typename Type>
class Resizable_deque {
	public:
		Resizable_deque( int = 16 );
		Resizable_deque( Resizable_deque const & );
		Resizable_deque( Resizable_deque && );
		~Resizable_deque();

		Type front() const;
		Type back() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void swap( Resizable_deque & );
		Resizable_deque &operator=( Resizable_deque const& );
		Resizable_deque &operator=( Resizable_deque && );
		void push_front( Type const & );
		void push_back( Type const & );
		void pop_front();
		void pop_back();
		void clear();

	private:
		// Your member variables
		Type *array;
		int deque_size;
		int ifront;
		int iback;
		int initial_array_capacity;
		int array_capacity;
		// Any private member functions
		//   - helper functions for resizing your array?

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Resizable_deque<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( int n ):
deque_size(0), ifront(0), iback(0),
//check if size is less than 16 then default to creating an array of size 16 otherwise create an array of the size n 
initial_array_capacity(std::max(16, n)),
array_capacity(initial_array_capacity)
// Your initalization list
{
	array = new Type[initial_array_capacity];
		
}

// Copy Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque const &deque )
// Your initalization list
{
	int * array2 = new int[initial_array_capacity];
	//create a loop to copy each value in the array into the new array
	for (int i=0; i<initial_array_capacity; i++ ){
		array2[i] = array[i];
	}
	//assign the new array as the array
	int* array = array2; 
	//delete the old array
	delete [] array2; 
}

// Move Constructor
template <typename Type>
Resizable_deque<Type>::Resizable_deque( Resizable_deque &&deque )
// Your initalization list
{
	// OPTIONAL
}

// Destructor
template <typename Type>
Resizable_deque<Type>::~Resizable_deque() {
	delete [] array;
	
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
int Resizable_deque<Type>::size() const {
	// Number of elements stored in deque
	return deque_size;
}

template <typename Type>
int Resizable_deque<Type>::capacity() const {
	// Current capacity of the array 
	return array_capacity;
}

template <typename Type>
bool Resizable_deque<Type>::empty() const {
	// Enter your implementation here
	if (deque_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

template <typename  Type>
Type Resizable_deque<Type>::front() const {
	// Enter your implementation here
	if (size() > 0) {
		return array[ifront];
	}
	else {
		throw underflow();
	}
}

template <typename  Type>
Type Resizable_deque<Type>::back() const {
	// Enter your implementation here
		if (size() > 0) {
		return array[iback];
	}
	else {
		throw underflow();
	}
}

template <typename Type>
void Resizable_deque<Type>::swap( Resizable_deque<Type> &deque ) {
	// Swap the member variables
	//     std::swap( variable, deque.variable );
	std::swap( array, deque.array );
	//for (int i=0; i<size(); i++){
	//	array[i] = deque[i];
	//}
	//return deque[i]
	// Enter your implementation here
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> const &rhs ) {
	// This is done for you...
	Resizable_deque<Type> copy( rhs );
	swap( copy );

	return *this;
}

template <typename Type>
Resizable_deque<Type> &Resizable_deque<Type>::operator=( Resizable_deque<Type> &&rhs ) {
	// This is done for you...
	swap( rhs );

	return *this;
}

template <typename Type>
void Resizable_deque<Type>::push_front( Type const &obj ) {
	// If array is empty then add the obj as the first value
	if (size() == 0) {
		ifront = 0; 
		array[ifront] = obj; 
		deque_size ++; 
		return;
	}
	// If array is full then double its size 
	else if (size() == capacity()){
		int array_capacity2 = 2*array_capacity;
		Type * array2 = new Type[array_capacity2];
		for (int i=0; i< array_capacity; i++){
			array2[i] = array[i];
		}
		//delete old array and assign new array as the current array 
		delete [] array;
		array = array2;

		//update values of ifront, iback and array size
		ifront = 0; 
		iback = deque_size; 
		array_capacity = array_capacity2; 
	}
	// shift index value backward to replace head; using modulus ensures that a circular array is implemented 
	ifront = ((ifront + (array_capacity-1)) % array_capacity);
	//assign obj value to front 
	array[ifront] = obj; 
	//increment number of elements in array 
	deque_size++;
}

template <typename Type>
void Resizable_deque<Type>::push_back( Type const &obj ) {
		// If array is empty then add the obj as the first value
	if (size() == 0) {
		ifront = 0;
		iback = 0; 
		array[iback] = obj; 
		deque_size ++; 
		return;
	}
	// If array is full then double its size 
	else if (size() == capacity()){
		int array_capacity2 = 2*array_capacity;
		Type * array2 = new Type[array_capacity2];
		for ( int i=0; i< array_capacity; i++){
			array2[i] = array[i];
		}
		//delete old array and assign new array as the current array 
		delete [] array;
		array = array2;
		//update values of ifront, iback and array size
		ifront = 0; 
		iback = deque_size; 
		array_capacity = array_capacity2; 
	}
	// shift index value forward to replace tail; using modulus ensures that a circular array is implemented 
	iback = ((iback + (array_capacity+1)) % array_capacity);
	//assign obj value to front 
	array[iback] = obj; 
	//increment number of elements in array 
	deque_size++;
}

template <typename Type>
void Resizable_deque<Type>::pop_front() {
	//throw an underflow if array empty
	if (deque_size == 0) {
		throw underflow();
	}
	else{
		//if the array is 1/4 full (or less) and its capacity is greater than the initial array capacity then we half the array capacity
		if ( ((size() == ((array_capacity)/4)) || (size() < ((array_capacity)/4))) && (array_capacity>initial_array_capacity) ){
			int array_capacity2 = (array_capacity/2); 
			array_capacity = array_capacity2; 
		}
		//move the head forward
		ifront = ((ifront + (array_capacity+1)) % array_capacity);
		//decrease the size of array to get rid of the first value
		deque_size--;
		
	}
}

template <typename Type>
void Resizable_deque<Type>::pop_back() {
		//throw an underflow if array empty
	if (deque_size == 0) {
		throw underflow();
	}
	else{
		//if the array is 1/4 full (or less) and its capacity is greater than the initial array capacity then we half the array capacity
		if ( ((size() == ((array_capacity)/4)) || (size() < ((array_capacity)/4))) && (array_capacity>initial_array_capacity) ){
			int array_capacity2 = (array_capacity/2); 
			array_capacity = array_capacity2; 
		}
		//move the tail backward
		iback = ((iback + (array_capacity-1)) % array_capacity);
		//decrease the size of array to get rid of the last value
		deque_size--;
	}
}

template <typename Type>
void Resizable_deque<Type>::clear() {
	deque_size = 0;
	ifront = 0;
	iback = 0; 
}
/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// Enter any private member functios (helper functions) here


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Resizable_deque<T> const &list ) {
	out << "not yet implemented";

	return out;
}

#endif
