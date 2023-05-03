// THIS IS THE PROVIDED CODE FOR PROGRAM #3, DSA 1, SPRING 2023

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	   << pData->firstName << " " 
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename = "sample2.txt";
  // cout << "Enter name of input file: ";
  // cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  //cout << "Data loaded.\n";

  //cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  //cout << "Enter name of output file: ";
  //cin >> filename;
  //writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

// try to copy-paste the list::merge() function and modify it to be faster
/*
void merge(list<Data*>& a, list<Data*>&& x)                                                                                     
{                                                                                                                                 
    if (&a == std::__addressof(x)) {return;}
    list<Data*>::iterator first1 = a.begin();                                                                                                    
    list<Data*>::iterator last1 = a.end();                                                                                                       
    list<Data*>::iterator first2 = x.begin();                                                                                                
    list<Data*>::iterator last2 = x.end();                                                                                                   
    const size_t orig_size = x.size();                                                                                          
    while (first1 != last1 && first2 != last2)
    {
        if (cmp(*first2, *first1))                                                                                             
        {
            list<Data*>::iterator next = first2;
            _M_transfer(first1, first2, ++next);
            first2 = next;
        }
        else { ++first1; }
    }
    if (first2 != last2) { M_transfer(last1, first2, last2); }
    a._M_inc_size(x._M_get_size());                                                                                           
    x._M_set_size(0);                                                                                                             
}
*/

// try to copy-paste the list::sort() function and modify it to be faster
/*
    list<Data*> carry;
    list<Data*> tmp[32];
    list<Data*>* fill = tmp;
    list<Data*>* counter;
    do
    {
        carry.splice(carry.begin(), l, l.begin());
	    for(counter = tmp; counter != fill && !counter->empty(); ++counter)
        {
            counter->merge(carry, cmp);
            //merge(counter, std::move(carry));
	        carry.swap(*counter);
        }
	    carry.swap(*counter);
		if (counter == fill) ++fill;
    }
	while ( !l.empty() );

	for (counter = tmp + 1; counter != fill; ++counter)
        counter->merge(*(counter - 1), cmp);
        //merge(counter, std::move(*(counter - 1)));
	l.swap( *(fill - 1) );
*/

#pragma GCC optimize("Ofast")
//#include <tuple>
#include <map>

bool cmp (const Data* x, const Data* y)
{
//    return std::tie(x->lastName, x->firstName, x->ssn) < 
//           std::tie(y->lastName, y->firstName, y->ssn);
    if (x->lastName < y->lastName) {return true;}
    if (x->lastName > y->lastName) {return false;}
    if (x->firstName < y->firstName) {return true;}
    if (x->firstName > y->firstName) {return false;}
    if (x->ssn < y->ssn) {return true;}
    return false;
}

void sortDataList(list<Data *> &l) 
{
//    l.sort(cmp);
    std::map<char, std::vector<Data*>> buckets {
        {'A', {}}, {'B', {}}, {'C', {}}, {'D', {}}, {'E', {}},
        {'F', {}}, {'G', {}}, {'H', {}}, {'I', {}}, {'J', {}},
        {'K', {}}, {'L', {}}, {'M', {}}, {'N', {}}, {'O', {}},
        {'P', {}}, {'Q', {}}, {'R', {}}, {'S', {}}, {'T', {}},
        {'U', {}}, {'V', {}}, {'W', {}}, {'X', {}}, {'Y', {}},
        {'Z', {}}
    };
    for (auto& data : l)
    {
        buckets[data->lastName[0]].push_back(data);
    }
    l.clear();
    for (auto& bucket : buckets)
    {
        std::sort(bucket.second.begin(), bucket.second.end(), cmp);
    }
    for (auto& bucket : buckets)
    {
        for (auto& data : bucket.second)
        {
            l.push_back(data);
        }
    }
}
