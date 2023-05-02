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

/*
These are my own notes!!
- u wanna put a check that figures out if the dataset is T1,T2,T3,T4
- Apply different strategies for each
- ex.) dataset = T4 if first and last (and maybe even middle) people are same names
- ex.) dataset = T1 if number of values (first line) is 100,000 +/- 1% 
- Don't make any dynamic allocated things --> make things in statically sized global arrays
      --> can make it plenty big to handle biggest possible case
- To beat his time, need to do stuff globally that u can precompute
- The baseline time = l.sort = grade of C
- Output must be correct
*/

/*
void sortDataList(list<Data *> &l)
{
    std::map<char, std::vector<Data*>> buckets {
        {'A',{}}, {'B',{}}, {'C',{}}, {'D',{}}, {'E',{}},
        {'F',{}}, {'G',{}}, {'H',{}}, {'I',{}}, {'J',{}},
        {'K',{}}, {'L',{}}, {'M',{}}, {'N',{}}, {'O',{}},
        {'P',{}}, {'Q',{}}, {'R',{}}, {'S',{}}, {'T',{}},
        {'U',{}}, {'V',{}}, {'W',{}}, {'X',{}}, {'Y',{}},
        {'Z',{}}
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
*/
// You may add global variables, functions, and/or
// class defintions here if you wish.

#include <tuple>

__attribute__((always_inline))
inline bool cmp (const Data* x, const Data* y)
{
    return std::tie(x->lastName, x->firstName, x->ssn) < 
           std::tie(y->lastName, y->firstName, y->ssn);
}

// or auto& x
// replace this-> with a.  
/*
void merge(auto& a, auto&& x)                                                                                     
{                                                                                                                                 
    // _GLIBCXX_RESOLVE_LIB_DEFECTS                                                                                                     
    // 300. list::merge() specification incomplete                                                                                      
    if (this != std::__addressof(__x))                                                                                                  
      {                                                                                                                                 
        _M_check_equal_allocators(__x);                                                                                                 
                                                                                                                                        
        iterator __first1 = begin();                                                                                                    
        iterator __last1 = end();                                                                                                       
        iterator __first2 = __x.begin();                                                                                                
        iterator __last2 = __x.end();                                                                                                   
        const size_t __orig_size = __x.size();                                                                                          
        __try                                                                                                                           
          {                                                                                                                             
        while (__first1 != __last1 && __first2 != __last2)                                                                              
          if (cmp(*__first2, *__first1))                                                                                             
            {                                                                                                                           
              iterator __next = __first2;                                                                                               
              _M_transfer(__first1, __first2, ++__next);                                                                                
              __first2 = __next;                                                                                                        
            }                                                                                                                           
          else                                                                                                                          
            ++__first1;                                                                                                                 
        if (__first2 != __last2)                                                                                                        
          _M_transfer(__last1, __first2, __last2);                                                                                      
                                                                                                                                        
        this->_M_inc_size(__x._M_get_size());                                                                                           
        __x._M_set_size(0);                                                                                                             
          }                                                                                                                             
        __catch(...)                                                                                                                    
          {                                                                                                                             
        const size_t __dist = std::distance(__first2, __last2);                                                                         
        this->_M_inc_size(__orig_size - __dist);                                                                                        
        __x._M_set_size(__dist);                                                                                                        
        __throw_exception_again;                                                                                                        
          }                                                                                                                             
      }                                                                                                                                 
}  
*/

void sortDataList(list<Data *> &l)
{
    //l.sort(cmp);

    list<Data*> carry;
    list<Data*> tmp[32];
    list<Data*> * fill = tmp;
    list<Data*> * counter;
    do
    {
        carry.splice(carry.begin(), l, l.begin());
	    for(counter = tmp; counter != fill && !counter->empty(); ++counter)
        {
            counter->merge(carry, cmp);
	        carry.swap(*counter);
        }
	    carry.swap(*counter);
		if (counter == fill) ++fill;
    }
	while ( !l.empty() );

	for (counter = tmp + 1; counter != fill; ++counter)
        counter->merge(*(counter - 1), cmp);
	l.swap( *(fill - 1) );
}
