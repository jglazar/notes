/*****************************************************************************************************
* purpose
*     implement a linked list as a C++ class
*
* operation
*     defines class for linked list and class for linked list element
*     runs little test in main()
*
* requirements
*     iostream library
*
* returns
*     basic implementation and testing of linked list
*****************************************************************************************************/


////////////////////////////// preprocessor directives //////////////////////////////

#include <iostream>


////////////////////////////// define constants //////////////////////////////

int  MAX_SIZE  =  100;


////////////////////////////// define classes //////////////////////////////

class linked_element
{
    public:
        // member variables
        int              data;
        linked_element  *prior_ptr;

        // member methods
        // constructor
        linked_element( const int data, linked_element *const prior_ptr );
};

class linked_list
{
    public:
        // member variables
        // pointer to last element in list
        linked_element *last_ptr;

        // member methods
        // constructor
        linked_list( void );

        // add element to end of list
        void append( int item );

        // remove element from end of list
//        void remove( linked_element item );

        // print list in reverse order
        void print_list_reverse( void );

        // print list in forward order
        void print_list_forward( void );

        // see if list contains item
        int contains( const int item );

        // insert element into ordered linked list
        void ordered_insert( const int item );
};


////////////////////////////// define functions //////////////////////////////

linked_element::linked_element( const int data, linked_element *const prior_ptr )
{
    /* construct linked_element object with data and pointer to prior element */

    this->data       =  data;
    this->prior_ptr  =  prior_ptr;
}


linked_list::linked_list( void )
{
    /* construct linked_list object with last_ptr to NULL */

    last_ptr  =  NULL;
}


void linked_list::append( int item )
{
    /* add element to end of list */

    std::cout << "appending " << item << '\n';

    // need to use "new" because we cannot create unique names for each new element
    linked_element *next_element_ptr  =  new linked_element(item, last_ptr);

    // the new element is now the last element
    last_ptr  =  next_element_ptr;
}


void linked_list::print_list_reverse( void )
{
    /* print list in reverse order */

    std::cout << "printing list in reverse order" << '\n';

    linked_element *current_ptr  =  last_ptr;
    while ( current_ptr != NULL )
    {
        std::cout << current_ptr->data << '\n';
        current_ptr  =  current_ptr->prior_ptr;
    }
}


void linked_list::print_list_forward( void )
{

    /* print list in forward order */

    std::cout << "printing list in forward order" << '\n';

    // make array of linked_element pointers
    linked_element *reverse_list[MAX_SIZE];

    // start at last pointer + count number of steps to start
    linked_element *current_ptr  =  last_ptr;
    uint  reverse_list_index     =  0;

    while ( current_ptr != NULL )
    {
        reverse_list[reverse_list_index]  =  current_ptr;
        current_ptr  =  current_ptr->prior_ptr;
        ++reverse_list_index;
    }

    for ( int i = reverse_list_index - 1; i >= 0; --i )
    {
        std::cout << reverse_list[i]->data << '\n';
    }
}


int linked_list::contains( const int item )
{
    /* returns 1 if item is in list, 0 otherwise */

    linked_element *current_ptr  =  last_ptr;
    while ( current_ptr != NULL )
    {
        if ( current_ptr->data == item ) { return 1; }
        current_ptr  =  current_ptr->prior_ptr;
    }
    return 0;
}


void linked_list::ordered_insert( const int item )
{
    /* inserts item into ordered linked list */

    std::cout << "inserting " << item << '\n';

    // create list_element from item
    linked_element *new_element_ptr  =  new linked_element( item, NULL );

    // initialize pointer to item after current_ptr
    linked_element *next_ptr  =  NULL;

    // search backwards for first element lower than input
    linked_element *current_ptr  =  last_ptr;
    while ( current_ptr != NULL )
    {
        if ( current_ptr->data < item ) { break; }
        next_ptr  =  current_ptr;
        current_ptr  =  current_ptr->prior_ptr;
    }

    // tell new element to point to current element
    new_element_ptr->prior_ptr  =  current_ptr;

    // if new element is biggest, then tell last_ptr to point to new element
    if ( next_ptr == NULL ) { last_ptr = new_element_ptr; }

    // else, tell next element in list to point to new element
    else { next_ptr->prior_ptr  =  new_element_ptr; }
}


////////////////////////////// main function //////////////////////////////

int main()
{
    // initialize linked list with some elements
    linked_list  my_list;
    my_list.append( 2 );
    my_list.append( 4 );
    my_list.append( 5 );

    my_list.print_list_reverse();
    my_list.print_list_forward();

    std::cout << "is 5 in the list? " << my_list.contains( 5 ) << '\n';
    std::cout << "is 6 in the list? " << my_list.contains( 6 ) << '\n';

    my_list.ordered_insert( 3 );
    my_list.print_list_forward();
    my_list.ordered_insert( 1 );
    my_list.print_list_forward();
    my_list.ordered_insert( 9 );
    my_list.print_list_forward();

    return 0;
}


/*
****************************************************************************************************
old code in main() function
****************************************************************************************************

linked_element *last_ptr  =  NULL

linked_element linked_element_a( 2, NULL );
last_ptr  =  &linked_element_a;

linked_element linked_element_b( 4, &linked_element_a );
last_ptr  =  &linked_element_b;

// insert c between a and b
linked_element linked_element_c( 6, &linked_element_a );
linked_element_b.prior_ptr  =  &linked_element_c;

// print list in reverse order

std::cout << "printing list in reverse order" << '\n';

linked_element *current_ptr  =  last_ptr;
while ( current_ptr  !=  NULL )
{
    std::cout << "element is: " << current_ptr->data << '\n';
    current_ptr  =  current_ptr->prior_ptr;
}

// print list in forward order

std::cout << "printing list in forward order" << '\n';

// array of linked_element pointers
linked_element *reverse_list[MAX_SIZE];
uint  reverse_list_index  =  0;
current_ptr  =  last_ptr;

while ( current_ptr != NULL )
{
    reverse_list[reverse_list_index]  =  current_ptr;
    current_ptr  =  current_ptr->prior_ptr;
    ++reverse_list_index;
}

for ( int i = reverse_list_index-1; i >= 0; --i )
{
    std::cout << "element is: " << reverse_list[i]->data << '\n';
}

*/
