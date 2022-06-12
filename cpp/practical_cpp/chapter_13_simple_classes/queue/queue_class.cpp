/*****************************************************************************************************
* purpose
*     implement a queue as a C++ class
*
* operation
*     defines class for queue, then runs little test in main()
*
* requirements
*     iostream library
*
* returns
*     basic implementation and testing of queue
*****************************************************************************************************/


////////////////////////////// preprocessor directives //////////////////////////////

#include<iostream>


////////////////////////////// define variables //////////////////////////////

const uint MAX_SIZE = 100;


////////////////////////////// define classes //////////////////////////////

class queue
{
    public:
        // constructor
        queue( void );

        // push new item onto queue
        void  push( const int item );

        // pop item off front of queue
        int   pop( void );

    private:
        // index of first item in queue
        uint  prev_idx;

        // index of next open spot in queue
        uint  next_idx;

        // array of data in queue, with space for more
        int   data[ MAX_SIZE ];
};


////////////////////////////// define functions //////////////////////////////

queue::queue( void )
{
    /* construct queue object with prev_idx = -1 and next_idx = 0 */

    prev_idx  =  -1;
    next_idx   =  0;
}


void queue::push( const int item )
{
    /*
    purpose
        push new item onto queue by assigning data[ back_idx ],
        then incrementing

    arguments
        int  item  --  item to add to queue

    returns
        nothing, adds item to queue
    */

    std::cout << "added in " << item << "\n";
    data[ next_idx ]  =  item;
    next_idx  =  ( next_idx + 1 )  %  MAX_SIZE  ;
}


int  queue::pop( )
{
    /*
    purpose
        pop item off front of queue

    arguments
        none

    returns
        item that was popped, and removes that item from queue
    */

    prev_idx  =  ( prev_idx + 1 )  %  MAX_SIZE ;

    int  popped_val  =  data[ prev_idx ];
    std::cout << "popped out " << popped_val << "\n";

    return( popped_val );
}


////////////////////////////// main function //////////////////////////////

int main()
{
    queue my_queue;

    for( int i = 0; i < 10; ++i )
    {
      my_queue.push( i*3 );
    }

    for( int i = 0; i < 5; ++i )
    {
      my_queue.pop( );
    }

    return( 0 );
}
