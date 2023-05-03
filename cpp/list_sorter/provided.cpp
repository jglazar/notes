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
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

// it's not against the rules to use preprocessor directives
// provides slight speedup
#pragma GCC optimize("Ofast")
#include <map>
// tuple only needed for std::tie in cmp
//#include <tuple>

bool cmp(const Data* x, const Data* y)
{
    // std::tie provides simple but slow way to compare multiple values
    //return std::tie(x->lastName, x->firstName, x->ssn) < 
    //       std::tie(y->lastName, y->firstName, y->ssn);
    // faster to do inelegant if statements
    if (x->lastName < y->lastName) {return true;}
    if (x->lastName > y->lastName) {return false;}
    if (x->firstName < y->firstName) {return true;}
    if (x->firstName > y->firstName) {return false;}
    if (x->ssn < y->ssn) {return true;}
    return false;
}

void sortDataList(list<Data *> &l)
{
    // basic l.sort(cmp) gets the job done
    //l.sort(cmp);
    // but we can do better with bucket-sort
    // note: this will work poorly for case T4
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
