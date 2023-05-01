# Project 3

## Intro

Complete a program that sorts the nodes of a linked list. 

The program loads data from an input file specified by the user and creates 
a linked list of pointers to data objects using the provided C++ list class. 

## File structure

First row has is integer number of records

Data fields are separated by one space. No leading/trailing whitespace. One
Unix-style '\n' ends each row.

Each data object has 3 C++ string fields
  * last name
  * first name
    * Names have overlaps because common names are used
  * social security number (ssn) 
    * SSNs are random and unique within each dataset
    * Format ddd-dd-dddd

## Assignment

Do not change provided code!
  * Simple class to store the data objects
  * File loading routine 
  * File saving routine that writes the sorted data to an output file. 
  * Call to a sort routine 

May add functions, classes, and global variables. All added code must be
included below the spacer comment. May add header files and include in .cpp

May use standard C++ classes or routines to, including:
  * "sort" list method, which uses mergesort
  * "std::sort" function, which likely uses quicksort


## Environment

Programs are compiled and run with g++ on Ubuntu 20.04 virtual machine with 
4Gb RAM. 

No compiler optimizations -- simply g++ programname

C++11, C++14, or C++17 -- check with pre-submission if unsure

## Tests

T1 has within 1 percent of 100,000 objects. 

T2 has within 1 percent of 1,000,000 objects. 

T3 has same data objects as T2, but are already sorted by last names and first 
names, but not SSN

T4 has within 1 percent of 1,000,000 data objects. Each person's name is the
same.

## Scoring

Score = time1 + time2 + time3 + time4 

Test data is unknown, but in same format as T1-4.

Scored only on one final program. Program will not know a priori which case is
input

Submit by e-mail to carl.sable@cooper.edu as an attachment. Only send code (no 
object files, test data, or executable files). 

Due before midnight on the night of Sunday, May 7. Late penalty of 5 points
per day 

## Tips

Use different strategies for each file type
  * Need not be correct for all possible inputs, only test inputs
  * Use presubmission to check against secret test data

Try to infer the file type
