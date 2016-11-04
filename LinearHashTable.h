#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

#include <iostream>
using namespace std;
#include <math.h>

/*****************************************
 * UW User ID:  dnittla
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		int count;
		int power;
		int array_size;
        int mod;
		T *array;
		state *occupied;


	public:
		LinearHashTable( int = 5 );
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable( int m ):
array_size( 1 << power ){
	count = 0;
	array_size = pow(2,m);//size is 2^m.
	array = new T [array_size];
	occupied = new state [array_size];
	for(int i=0;i<array_size;i++)
	{
		occupied[i] = EMPTY;
	}
	power = (log(array_size)) / (log(2));
}


template<typename T >
LinearHashTable<T >::~LinearHashTable() {
	//deallocates the array
	delete [] array;
    delete [] occupied;
}

template<typename T >
int LinearHashTable<T >::size() const {
    // returns number of elements in the hash table.
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
    // returns the max size of the array. 
	return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
    // load factor is number of elements/capacity of the hash table.
	return ((double) count/array_size); 
}

template<typename T >
bool LinearHashTable<T >::empty() const {
    // count counts the number of elements in the hash table. If the count is 0 there are no elements in the hash table. then it returns true.
    if(count == 0)
    {
    	return true;
    }
	return false;
}


template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
	// enter your implementation here 
	//checks if the element is present in the hash table and then returns true if it is present or else it returns false.
	int k = (int) obj;
	int m = array_size;
	int x = k % m;

	int probe = x;
	int counter = 0;

	while(occupied[probe] == OCCUPIED && counter < array_size)
	{
		if(array[probe] == obj)
		{
			return true;
			break;
		}
		probe = (probe + 1) % array_size;
		counter++;
		
	}

	return false;
}

template<typename T >
T LinearHashTable<T >::bin( int n ) const {
	return array[n];
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
	// enter your implemetation here
	int k = (int) obj;
	int m = array_size;
	int x = k % m;
	//if the load factor is less than 0.75 then you can add the element or else make a new array of double the size and copy the elements to that array.
	if(load_factor()<=0.75)
	{
		int probe = x;

		while(occupied[probe] == OCCUPIED)
		{
			probe = (probe + 1) % array_size;
		}
		array[probe] = obj;
		occupied[probe] = OCCUPIED;
		count++;
		return; 
	}
	else
	{	
		array_size=2*array_size;
		T *array2=new T[array_size];
		state *occupied2=new state[array_size];
		for(int i=0;i<array_size;i++)
		{
			occupied2[i]=occupied[i];
			array2[i]=array[i];	
		}
		//deallocate old array and save new array into old array
		delete[] array;
		delete[] occupied;
		T *array=new T[array_size];
		state *occupied=new state[array_size];
		array=array2;
		occupied=occupied2;

		for(int i=0;i<array_size;i++)
		{
			occupied2[i]=occupied[i];
			array2[i]=array[i];	
		}

		int probe = x;

		while(occupied[probe] == OCCUPIED)
		{
			probe = (probe + 1) % array_size;
		}
		array[probe] = obj;
		occupied[probe] = OCCUPIED;
		count++;
		return;
	}	
}

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
	// enter your implemetation here
	int i = (int) obj;
	int m = array_size;
	int x = i % m;
	
	if(load_factor()>0.25)
	{
		int probe = x;
		int counter = 0;
		//it probes through the hash table and checks for the element and deletes it.
		while(occupied[probe] == OCCUPIED && counter < array_size)
		{
			if(array[probe] == obj)
			{
				array[probe] = 0;
				occupied[probe] = DELETED;
				count--;
				return true;
			}
			probe = (probe + 1) % array_size;
			counter++;
		}
			return false;
	}
	else 
	{	
		//if the load factor is less than 0.25 then it allocates a new array which has a size of 0.5* the original array size.
		array_size=0.5*array_size;
		T *array2=new T[array_size];
		state *occupied2=new state[array_size];
		for(int i=0;i<array_size;i++)
		{
			occupied2[i]=occupied[i];
			array2[i]=array[i];	
		}
		//deallocates the old arrays and assigns it to the new array
		delete[] array;
		delete[] occupied;
		T *array=new T[array_size];
		state *occupied=new state[array_size];
		array=array2;
		occupied=occupied2;

		int probe = x;
		int counter = 0;
		//checks for the empty position and then adds the value to that position.
		while(occupied[probe] == OCCUPIED && counter < array_size)
		{
			if(array[probe] == obj)
			{
				array[probe] = 0;
				occupied[probe] = DELETED;
				count--;
				return true;
			}
			probe = (probe + 1) % array_size;
			counter++;
		}
		return false;
		}
}

template<typename T >
void LinearHashTable<T >::clear() {
	// enter your implementation here
	//initialize the array back to original values
	for(int i = 0; i < array_size; i++)
	{
		array[i] = 0;
		occupied[i] = EMPTY;
	}
	count = 0;
	return; 
}

template<typename T >
void LinearHashTable<T >::print() const{
	// enter your implemetation here
	for(int i=0;i<array_size;i++)
	{
		cout<<array[i]<<endl;
	}
}


#endif
