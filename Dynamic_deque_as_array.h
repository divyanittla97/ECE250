#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"



class Dynamic_deque_as_array
{

    public:
        Dynamic_deque_as_array( int = 10 );
        ~Dynamic_deque_as_array();

        int* array;
        int front;
        int rear;
        int array_size;
        int count = 0;
        int head() const;
        int tail() const;
        int size() const;
        bool empty() const;
        int capacity() const;

        void enqueue_head( const int & );
        void enqueue_tail( const int & );
        int dequeue_head();
        int dequeue_tail();
        void clear();

        
};


//default size of the array is 10
Dynamic_deque_as_array::Dynamic_deque_as_array( int n ) { //constructor
    //if n is less than 1 create an array of size 1 or else create an array of size n.
    if( n < 1 ){
        array = new int[1];

    }
    else {
        array = new int[n];
    }

    array_size = n;
    front = n/2 - 1;//starting from the middle of the array.
    rear = front;

}




Dynamic_deque_as_array::~Dynamic_deque_as_array() { //destructor
    delete[] array;//deallocates the memory of the array
}


int Dynamic_deque_as_array::size() const {
    //returns the number of elements in the deque in O(1)

    return count;//count holds the position of the number of elements in the queue.
}


int Dynamic_deque_as_array::capacity() const {
    //returns capacity of the deque in O(1)

    return array_size;//returns the max size of the array.
}


bool Dynamic_deque_as_array::empty() const {
    //returns true if the deque is empty or else it returns false in O(1)
    if( count == 0 )
    {
        return true;
    }
    return false;

}


int Dynamic_deque_as_array::head() const {
    //returns the integer at the head of the deque,may throw an underflow exception in O(1)
    if(Dynamic_deque_as_array::empty())
    {
        throw underflow();
    }
    return array[front];
}


int Dynamic_deque_as_array::tail() const {
    //returns the integer at the tail of the deque,may throw an underflow exception in O(1)
    if(Dynamic_deque_as_array::empty())
    {
        throw underflow();
    } 
    return array[rear];
}



void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
    //insert element at the head of the deque in O(1), if array is full create an array of size 2n and copy elements from the old array to a new one in O(n)
    if(count == array_size)
    {
        int* array2 = new int[2 * array_size];//making a new array of size 2n.
    int i = front;
    int j = array_size - 1;
    while (i!=rear) {
        array2[j] = array[i];
        if( i+1 == array_size) 
            i = 0;
        else
            i++;
        j++;
    }
    array2[j] = array[i];
    front = array_size - 1;
    rear = j;
    delete[] array;
    array=array2;
    array_size*=2;
    }

    if (front == rear) {//if the front is equal to the rear that means that there is only one element in the array.so that element is the front of the array.
        if(count!=0)
                front++;
    array[front] = obj;

    }
    

    else {
        
        if (front - 1 < 0) {        //if the front is in the position 0 of the array, so the front                              goes to the end of the circular queue.  
            front = array_size-1;
        }

        else {
            front--;
        }

        array[front] = obj;

    }

    
    count++;
    return;
}


void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
    //insert element at the tail of the deque in O(1), if array is full create an array of size 2n and copy elements from the old array to a new one in O(n)
   if(count == array_size)
    {
    
    int* array2 = new int[2 * array_size];//making a new array of size 2n.
    int i = front;
    int j = array_size - 1;
    while (i!=rear) {
        array2[j] = array[i];
        if( i+1 == array_size) 
            i = 0;
        else
            i++;
        j++;
    }
    array2[j] = array[i];
    front = array_size - 1;
    rear = j;
    delete[] array;
    int* array=array2;
    array_size*= 2;
    }

    //count++;
    //front = (front - 1) % array_size;
    //array[front] = obj;
//  if ( front == -1 )
//  {
//      front = 0 ;
//  }

    if (front == rear) {
    if(count!=0)
                rear++;
    array[rear] = obj;
    }
    

    else {
        
        if (rear==array_size) {     
            rear = 0;
        }

        else {
            rear++;
        }

        array[rear] = obj;

    }

    count++;
    return;
}


int Dynamic_deque_as_array::dequeue_head() {
    //remove element from the head of the deque in O(1).May throw an underflow exception
    if(Dynamic_deque_as_array::empty())
    {
        throw underflow();
    }
    count--;
    
    if(front==-1)//front returns to the first position.
    {
        return array[0];
    }
  
      front=front+1;
    
    return array[front-1];



}

int Dynamic_deque_as_array::dequeue_tail() {
    //remove element from the tail of the deque in O(1).This may throw an underflow exception.
    if(Dynamic_deque_as_array::empty())
    {
        throw underflow();
    }

    count--;
    if(rear==0)//if the tail is at the end,then returns the last value.
    {
        rear = array_size-1;
        return array[0];
    } 
    int temp=array[rear];
    rear=rear-1;
    return temp;

    
}


void Dynamic_deque_as_array::clear() {
    //remove all elements from the array.
    front = rear;
    count=0;
    return;
}

#endif