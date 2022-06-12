/*****************************************************************************************************
* purpose
*     implement a stack as a C++ class
*
* operation
*     defines class for stack, then runs little test in main()
*
* requirements
*     iostream library
*
* returns
*     basic implementation and testing of stack
*****************************************************************************************************/


////////////////////////////// preprocessor directives //////////////////////////////

#include<iostream>


////////////////////////////// define variables //////////////////////////////

const uint MAX_SIZE = 100;


////////////////////////////// define classes //////////////////////////////

class stack
{
    public:
        // constructor
        stack( void );

        // push new item onto stack
        void  push( const int item );

        // pop item off end of stack
        int   pop( void );

    private:
        // index of next item after last currently in stack
        uint  next_idx;

        // array of data in stack, with space for more
        int   data[ MAX_SIZE ];
};


////////////////////////////// define functions //////////////////////////////

stack::stack( void )
{
    /* construct stack object with next_idx = 0 */

    next_idx  =  0;
}


void stack::push( const int item )
{
    /*
    purpose
        push new item onto stack by assigning data[ next_idx ],
        then incrementing

    arguments
        int  item  --  item to add to stack

    returns
        nothing, adds item to stack
    */

    std::cout << "added in " << item << "\n";
    data[ next_idx ]  =  item;
    ++next_idx;
}


int  stack::pop( )
{
    /*
    purpose
        pop item off end of stack

    arguments
        none

    returns
        item that was popped, and removes that item from stack
    */

    --next_idx;
    int  popped_val  =  data[ next_idx ];
    std::cout << "popped out " << popped_val << "\n";
    return( popped_val );
}



////////////////////////////// main function //////////////////////////////

int main()
{
    stack my_stack;

    my_stack.push( 2 );
    my_stack.push( 8 );
    my_stack.push( 76 );

    my_stack.pop( );
    my_stack.pop( );

    return( 0 );
}
