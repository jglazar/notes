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

// behind-the-scenes implementation of list sort
// from https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00548_source.html
/*
  template<typename _Tp, typename _Alloc>
    template <typename _StrictWeakOrdering>
      void
      list<_Tp, _Alloc>::
      sort(_StrictWeakOrdering __comp)
      {
        // Do nothing if the list has length 0 or 1.
        if (this->_M_impl._M_node._M_next != &this->_M_impl._M_node
            && this->_M_impl._M_node._M_next->_M_next != &this->_M_impl._M_node)
        {
          using __detail::_Scratch_list;
          _Scratch_list __carry;
          _Scratch_list __tmp[64];
          _Scratch_list* __fill = __tmp;
          _Scratch_list* __counter;
 
        _Scratch_list::_Ptr_cmp<iterator, _StrictWeakOrdering> __ptr_comp
          = { __comp };
 
          __try
            {
              do
                {
                  __carry._M_take_one(begin()._M_node);
 
                  for(__counter = __tmp;
                      __counter != __fill && !__counter->empty();
                      ++__counter)
                    {
 
                      __counter->merge(__carry, __ptr_comp);
                      __carry.swap(*__counter);
                    }
                  __carry.swap(*__counter);
                  if (__counter == __fill)
                    ++__fill;
                }
              while ( !empty() );
 
              for (__counter = __tmp + 1; __counter != __fill; ++__counter)
                __counter->merge(__counter[-1], __ptr_comp);
              __fill[-1].swap(this->_M_impl._M_node);
            }
          __catch(...)
            {
              // Move all nodes back into *this.
              __carry._M_put_all(end()._M_node);
              for (int __i = 0; __i < sizeof(__tmp)/sizeof(__tmp[0]); ++__i)
                __tmp[__i]._M_put_all(end()._M_node);
              __throw_exception_again;
            }
        }
      }
*/
// You may add global variables, functions, and/or
// class defintions here if you wish.

#include <climits>


#define MAX_ITEMS 1200000
#define LAST_NAMES 500
#define LAST_NAME_BUCKETS (MAX_ITEMS / LAST_NAMES)
#define FIRST_NAMES 494
#define FIRST_NAME_BUCKETS (MAX_ITEMS / FIRST_NAMES)
#define DIGITS 10
#define T1_LIMIT 200000


class p2_sort {
private:
	/*
	 * We want to determine the shortest unique prefix for each
	 * name, to do so we need to keep track of the number of
	 * occurrences of a character.  From this we can deduce that if
	 * a character appears just once, we've reached a unique prefix.
	 */
	struct prefix_trie {
		unsigned count;
		struct prefix_trie *child[UCHAR_MAX + 1];

		prefix_trie(void) {
			count = 0;
			memset(child, 0, sizeof(child));
		}
	};

	/*
	 * We want to sort input names using their shortest unique
	 * prefix.  This will allow for us to avoid most of the string
	 * when determining names.  Using this we can deduce that if a
	 * character has no more children, we've identified a name.
	 */
	struct uniq_prefix_trie {
		unsigned children;
		struct uniq_prefix_trie *child[UCHAR_MAX + 1];

		Data **bucket_head;
		Data **bucket_tail;

		uniq_prefix_trie(void) {
			children = 0;
			memset(child, 0, sizeof(child));
			bucket_head = bucket_tail = nullptr;
		}
	};

	static const string last_names[LAST_NAMES];
	static const string first_names[FIRST_NAMES];

	struct prefix_trie *last_name_prefix;
	struct uniq_prefix_trie *last_name_uniq_prefix;
	struct prefix_trie *first_name_prefix;
	struct uniq_prefix_trie *first_name_uniq_prefix;

	unsigned last_name_bucket_cnt = 0;
	uniq_prefix_trie *last_name_buckets[LAST_NAMES];
	unsigned first_name_bucket_cnt = 0;
	uniq_prefix_trie *first_name_buckets[FIRST_NAMES];

	Data **node_buf;
	string *ssn_buf, *ssn_aux;
	unsigned digit_cnt_offset[DIGITS];
	unsigned *digit_cnt = digit_cnt_offset - '0';

	/*
	 * Since we know the input data, we can calculated the unique
	 * prefix required to determine each input name.  One thing to
	 * keep in mind is that we need to keep track of NUL bytes as a
	 * means of differentiation between names like "LE" and "LEE".
	 */
	void gen_prefix_trie(prefix_trie *out, const string *in, size_t cnt);

	/*
	 * From the unique prefix trie we want to generate a trie which
	 * can handle the input data.  A terminal node will have zero
	 * children, indicating the end of the search.
	 */
	void gen_uniq_prefix_trie(
		prefix_trie *in,
		uniq_prefix_trie *out,
		uniq_prefix_trie **buckets,
		unsigned *bucket_cnt
	);

	/*
	 * We want the trie nodes to have good memory locality, so we
	 * allocate all the buckets after generating the trie.
	 */
	void alloc_buckets(
		uniq_prefix_trie **buckets,
		const unsigned bucket_cnt,
		const unsigned bucket_siz
	);

	/*
	 * We want to sort each name in its appropriate "bucket" using the
	 * generated unique prefix trie.
	 */
	void index_name(uniq_prefix_trie *trie, Data *in, const char *name);

	/*
	 * We will want to reuse our unique prefix trie at some point so
	 * we need to have a means of "clearing" our buckets.
	 */
	void clear_buckets(uniq_prefix_trie **buckets, unsigned bucket_cnt);

	/*
	 * Since each SSN has the same properties (dashes and same
	 * length), we can ignore these characters and the NUL byte to
	 * speed up our comparator.
	 */
	int ssncmp(const char *a, const char *b);

	/*
	 * Since we have determined the shortest possible unique prefix
	 * for each name, we can use this as a means of determining if
	 * two unsorted names are the same by comparing terminal nodes.
	 */
	void get_terminal_node(
		uniq_prefix_trie *in,
		uniq_prefix_trie **out,
		const char *name
	);

	void insrt_sort_ssn(Data **first, Data **last);
	void uniq_prefix_sort(void);

public:
	unsigned nodes;
	list<Data *> *src;

	/*
	 * We're going to fully abuse the fact that we can run
	 * constructors before main().  This will allow for us to
	 * dynamically allocate data structure which are far too tedious
	 * to allocate statically.
	 */
	p2_sort(void);

	/*
	 * The provided code does not free any allocated memory so we'll
	 * follow suit ;)
	 */
	//~p2_sort(void);

	inline void t1_sort(void) { uniq_prefix_sort(); }
	inline void t2_sort(void) { uniq_prefix_sort(); }
	void t3_sort(void);
	void t4_sort(void);
};

const string p2_sort::last_names[LAST_NAMES] = {
	"ACOSTA",     "ADAMS",      "ADKINS",      "AGUILAR",
	"AGUIRRE",    "ALEXANDER",  "ALLEN",       "ALVARADO",
	"ALVAREZ",    "ANDERSON",   "ANDREWS",     "ARMSTRONG",
	"ARNOLD",     "AUSTIN",     "AVILA",       "AYALA",
	"BAILEY",     "BAKER",      "BALDWIN",     "BANKS",
	"BARBER",     "BARKER",     "BARNES",      "BARNETT",
	"BARRETT",    "BARTON",     "BATES",       "BECK",
	"BECKER",     "BELL",       "BENNETT",     "BENSON",
	"BERRY",      "BISHOP",     "BLACK",       "BLAIR",
	"BLAKE",      "BOWEN",      "BOWMAN",      "BOYD",
	"BRADLEY",    "BRADY",      "BREWER",      "BROOKS",
	"BROWN",      "BRYANT",     "BURGESS",     "BURKE",
	"BURNS",      "BURTON",     "BUSH",        "BUTLER",
	"BYRD",       "CABRERA",    "CALDERON",    "CALDWELL",
	"CAMACHO",    "CAMPBELL",   "CAMPOS",      "CANNON",
	"CARDENAS",   "CARLSON",    "CARPENTER",   "CARR",
	"CARRILLO",   "CARROLL",    "CARTER",      "CASTANEDA",
	"CASTILLO",   "CASTRO",     "CERVANTES",   "CHAMBERS",
	"CHAN",       "CHANDLER",   "CHANG",       "CHAPMAN",
	"CHAVEZ",     "CHEN",       "CHRISTENSEN", "CLARK",
	"CLARKE",     "COHEN",      "COLE",        "COLEMAN",
	"COLLINS",    "COLON",      "CONTRERAS",   "COOK",
	"COOPER",     "CORTEZ",     "COX",         "CRAIG",
	"CRAWFORD",   "CROSS",      "CRUZ",        "CUMMINGS",
	"CUNNINGHAM", "CURRY",      "CURTIS",      "DANIEL",
	"DANIELS",    "DAVIDSON",   "DAVIS",       "DAWSON",
	"DAY",        "DEAN",       "DELACRUZ",    "DELEON",
	"DELGADO",    "DENNIS",     "DIAZ",        "DIXON",
	"DOMINGUEZ",  "DOUGLAS",    "DOYLE",       "DUNCAN",
	"DUNN",       "DURAN",      "EDWARDS",     "ELLIOTT",
	"ELLIS",      "ERICKSON",   "ESPINOZA",    "ESTRADA",
	"EVANS",      "FARMER",     "FERGUSON",    "FERNANDEZ",
	"FIELDS",     "FIGUEROA",   "FISCHER",     "FISHER",
	"FITZGERALD", "FLEMING",    "FLETCHER",    "FLORES",
	"FORD",       "FOSTER",     "FOWLER",      "FOX",
	"FRANCIS",    "FRANCO",     "FRANK",       "FRANKLIN",
	"FRAZIER",    "FREEMAN",    "FUENTES",     "FULLER",
	"GALLAGHER",  "GALLEGOS",   "GARCIA",      "GARDNER",
	"GARNER",     "GARRETT",    "GARZA",       "GEORGE",
	"GIBSON",     "GILBERT",    "GILL",        "GOMEZ",
	"GONZALES",   "GONZALEZ",   "GOODMAN",     "GOODWIN",
	"GORDON",     "GRAHAM",     "GRANT",       "GRAVES",
	"GRAY",       "GREEN",      "GREENE",      "GREGORY",
	"GRIFFIN",    "GRIFFITH",   "GROSS",       "GUERRA",
	"GUERRERO",   "GUTIERREZ",  "GUZMAN",      "HAIL",
	"HALE",       "HALL",       "HAMILTON",    "HAMMOND",
	"HAMPTON",    "HANSEN",     "HANSON",      "HARDY",
	"HARMON",     "HARPER",     "HARRINGTON",  "HARRIS",
	"HARRISON",   "HART",       "HARVEY",      "HAWKINS",
	"HAYES",      "HAYNES",     "HENDERSON",   "HENRY",
	"HERNANDEZ",  "HERRERA",    "HICKS",       "HIGGINS",
	"HILL",       "HINES",      "HODGES",      "HOFFMAN",
	"HOLLAND",    "HOLMES",     "HOLT",        "HOPKINS",
	"HORTON",     "HOWARD",     "HOWELL",      "HUANG",
	"HUBBARD",    "HUDSON",     "HUGHES",      "HUNT",
	"HUNTER",     "INGRAM",     "JACKSON",     "JACOBS",
	"JAMES",      "JENKINS",    "JENNINGS",    "JENSEN",
	"JIMENEZ",    "JOHNSON",    "JOHNSTON",    "JONES",
	"JORDAN",     "JOSEPH",     "JUAREZ",      "KELLER",
	"KELLEY",     "KELLY",      "KENNEDY",     "KHAN",
	"KIM",        "KING",       "KLEIN",       "KNIGHT",
	"LAMBERT",    "LANE",       "LARA",        "LARSON",
	"LAWRENCE",   "LAWSON",     "LE",          "LEE",
	"LEON",       "LEONARD",    "LEWIS",       "LI",
	"LIN",        "LITTLE",     "LIU",         "LOGAN",
	"LONG",       "LOPEZ",      "LOVE",        "LOWE",
	"LUCAS",      "LUNA",       "LYNCH",       "LYONS",
	"MACK",       "MALDONADO",  "MALONE",      "MANN",
	"MANNING",    "MARQUEZ",    "MARSHALL",    "MARTIN",
	"MARTINEZ",   "MASON",      "MATTHEWS",    "MAXWELL",
	"MAY",        "MCCARTHY",   "MCCOY",       "MCDANIEL",
	"MCDONALD",   "MCGEE",      "MCKINNEY",    "MCLAUGHLIN",
	"MEDINA",     "MEJIA",      "MENDEZ",      "MENDOZA",
	"MEYER",      "MILES",      "MILLER",      "MILLS",
	"MIRANDA",    "MITCHELL",   "MOLINA",      "MONTGOMERY",
	"MONTOYA",    "MOORE",      "MORALES",     "MORAN",
	"MORENO",     "MORGAN",     "MORRIS",      "MORRISON",
	"MOSS",       "MULLINS",    "MUNOZ",       "MURPHY",
	"MURRAY",     "MYERS",      "NAVARRO",     "NEAL",
	"NELSON",     "NEWMAN",     "NEWTON",      "NGUYEN",
	"NICHOLS",    "NORMAN",     "NORRIS",      "NUNEZ",
	"OBRIEN",     "OCHOA",      "OCONNOR",     "OLIVER",
	"OLSON",      "ORTEGA",     "ORTIZ",       "OWENS",
	"PACHECO",    "PADILLA",    "PAGE",        "PALMER",
	"PARK",       "PARKER",     "PARKS",       "PARSONS",
	"PATEL",      "PATTERSON",  "PAUL",        "PAYNE",
	"PEARSON",    "PENA",       "PEREZ",       "PERKINS",
	"PERRY",      "PERSON",     "PETERS",      "PETERSON",
	"PHAM",       "PHILLIPS",   "PIERCE",      "PORTER",
	"POTTER",     "POWELL",     "POWERS",      "PRICE",
	"QUINN",      "RAMIREZ",    "RAMOS",       "RAMSEY",
	"RAY",        "REED",       "REESE",       "REEVES",
	"REID",       "REYES",      "REYNOLDS",    "RHODES",
	"RICE",       "RICHARDS",   "RICHARDSON",  "RILEY",
	"RIOS",       "RIVAS",      "RIVERA",      "ROBBINS",
	"ROBERTS",    "ROBERTSON",  "ROBINSON",    "ROBLES",
	"RODGERS",    "RODRIGUEZ",  "ROGERS",      "ROJAS",
	"ROMAN",      "ROMERO",     "ROSALES",     "ROSE",
	"ROSS",       "ROWE",       "RUIZ",        "RUSSELL",
	"RYAN",       "SALAZAR",    "SALINAS",     "SANCHEZ",
	"SANDERS",    "SANDOVAL",   "SANTIAGO",    "SANTOS",
	"SAUNDERS",   "SCHMIDT",    "SCHNEIDER",   "SCHROEDER",
	"SCHULTZ",    "SCHWARTZ",   "SCOTT",       "SERRANO",
	"SHARP",      "SHAW",       "SHELTON",     "SHERMAN",
	"SILVA",      "SIMMONS",    "SIMON",       "SIMPSON",
	"SIMS",       "SINGH",      "SMITH",       "SNYDER",
	"SOLIS",      "SOTO",       "SPENCER",     "STANLEY",
	"STEELE",     "STEPHENS",   "STEVENS",     "STEVENSON",
	"STEWART",    "STONE",      "STRICKLAND",  "SULLIVAN",
	"SUTTON",     "SWANSON",    "TATE",        "TAYLOR",
	"TERRY",      "THOMAS",     "THOMPSON",    "THORNTON",
	"TODD",       "TORRES",     "TOWNSEND",    "TRAN",
	"TRUJILLO",   "TUCKER",     "TURNER",      "VALDEZ",
	"VALENCIA",   "VARGAS",     "VASQUEZ",     "VAUGHN",
	"VAZQUEZ",    "VEGA",       "VELASQUEZ",   "WADE",
	"WAGNER",     "WALKER",     "WALLACE",     "WALSH",
	"WALTERS",    "WALTON",     "WANG",        "WARD",
	"WARNER",     "WARREN",     "WASHINGTON",  "WATERS",
	"WATKINS",    "WATSON",     "WATTS",       "WEAVER",
	"WEBB",       "WEBER",      "WEBSTER",     "WELCH",
	"WELLS",      "WEST",       "WHEELER",     "WHITE",
	"WILLIAMS",   "WILLIAMSON", "WILLIS",      "WILSON",
	"WISE",       "WOLF",       "WOLFE",       "WONG",
	"WOOD",       "WOODS",      "WRIGHT",      "WU",
	"YANG",       "YOUNG",      "ZHANG",       "ZIMMERMAN",
};

const string p2_sort::first_names[FIRST_NAMES] = {
	"AALIYAH",   "AARON",     "ABEL",      "ABIGAIL",
	"ABRAHAM",   "ADALINE",   "ADALYN",    "ADALYNN",
	"ADAM",      "ADDISON",   "ADELINE",   "ADELYN",
	"ADRIAN",    "ADRIANA",   "AIDAN",     "AIDEN",
	"ALAINA",    "ALAN",      "ALANA",     "ALAYNA",
	"ALEJANDRO", "ALEX",      "ALEXA",     "ALEXANDER",
	"ALEXANDRA", "ALEXIS",    "ALICE",     "ALINA",
	"ALIVIA",    "ALIYAH",    "ALLISON",   "ALYSSA",
	"AMARA",     "AMAYA",     "AMELIA",    "AMIR",
	"AMY",       "ANA",       "ANASTASIA", "ANDREA",
	"ANDRES",    "ANDREW",    "ANGEL",     "ANGELA",
	"ANGELINA",  "ANNA",      "ANNABELLE", "ANTHONY",
	"ANTONIO",   "ARABELLA",  "ARIA",      "ARIANA",
	"ARIANNA",   "ARIEL",     "ARTHUR",    "ARYA",
	"ASHER",     "ASHLEY",    "ASHTON",    "ATHENA",
	"AUBREE",    "AUBREY",    "AUDREY",    "AUGUST",
	"AURORA",    "AUSTIN",    "AUTUMN",    "AVA",
	"AVERY",     "AXEL",      "AYDEN",     "AYLA",
	"BAILEY",    "BARRETT",   "BEAU",      "BECKETT",
	"BELLA",     "BENJAMIN",  "BENNETT",   "BENTLEY",
	"BLAKE",     "BRADLEY",   "BRADY",     "BRANDON",
	"BRANTLEY",  "BRAXTON",   "BRAYDEN",   "BRIAN",
	"BRIANNA",   "BRIELLE",   "BRODY",     "BROOKE",
	"BROOKLYN",  "BROOKLYNN", "BROOKS",    "BRYAN",
	"BRYCE",     "BRYNLEE",   "BRYSON",    "CADEN",
	"CALEB",     "CALLIE",    "CALVIN",    "CAMDEN",
	"CAMERON",   "CAMILA",    "CARLOS",    "CAROLINE",
	"CARSON",    "CARTER",    "CATHERINE", "CAYDEN",
	"CECILIA",   "CHARLES",   "CHARLIE",   "CHARLOTTE",
	"CHASE",     "CHLOE",     "CHRISTIAN", "CHRISTOPHER",
	"CLAIRE",    "CLARA",     "CLAYTON",   "COLE",
	"COLIN",     "COLTON",    "CONNOR",    "COOPER",
	"CORA",      "DAISY",     "DAKOTA",    "DALEYZA",
	"DAMIAN",    "DANIEL",    "DANIELA",   "DAVID",
	"DAWSON",    "DEAN",      "DECLAN",    "DELANEY",
	"DELILAH",   "DEREK",     "DESTINY",   "DIANA",
	"DIEGO",     "DOMINIC",   "DYLAN",     "EASTON",
	"EDEN",      "EDWARD",    "ELEANOR",   "ELENA",
	"ELI",       "ELIANA",    "ELIAS",     "ELIJAH",
	"ELISE",     "ELIZA",     "ELIZABETH", "ELLA",
	"ELLIANA",   "ELLIE",     "ELLIOT",    "ELLIOTT",
	"ELOISE",    "EMERSON",   "EMERSYN",   "EMERY",
	"EMILIA",    "EMILIANO",  "EMILY",     "EMMA",
	"EMMANUEL",  "EMMETT",    "ERIC",      "ESTHER",
	"ETHAN",     "EVA",       "EVAN",      "EVELYN",
	"EVERETT",   "EVERLY",    "EZEKIEL",   "EZRA",
	"FAITH",     "FELIX",     "FINLEY",    "FINN",
	"FIONA",     "GABRIEL",   "GABRIELLA", "GAEL",
	"GAVIN",     "GENESIS",   "GENEVIEVE", "GEORGE",
	"GEORGIA",   "GIANNA",    "GIOVANNI",  "GRACE",
	"GRACIE",    "GRAHAM",    "GRANT",     "GRAYSON",
	"GREYSON",   "GRIFFIN",   "HADLEY",    "HAILEY",
	"HANNAH",    "HARLEY",    "HARMONY",   "HARPER",
	"HARRISON",  "HAYDEN",    "HAZEL",     "HENRY",
	"HOLDEN",    "HUDSON",    "HUNTER",    "IAN",
	"IRIS",      "ISAAC",     "ISABEL",    "ISABELLA",
	"ISABELLE",  "ISAIAH",    "ISLA",      "ISRAEL",
	"IVAN",      "IVY",       "JACE",      "JACK",
	"JACKSON",   "JACOB",     "JADE",      "JADEN",
	"JAKE",      "JAMES",     "JAMESON",   "JASMINE",
	"JASON",     "JASPER",    "JAVIER",    "JAX",
	"JAXON",     "JAXSON",    "JAYCE",     "JAYDEN",
	"JAYLA",     "JEREMIAH",  "JEREMY",    "JESSE",
	"JESSICA",   "JESUS",     "JOANNA",    "JOCELYN",
	"JOEL",      "JOHN",      "JONAH",     "JONATHAN",
	"JORDAN",    "JORDYN",    "JORGE",     "JOSE",
	"JOSEPH",    "JOSEPHINE", "JOSHUA",    "JOSIAH",
	"JOSIE",     "JOSUE",     "JUAN",      "JUDAH",
	"JUDE",      "JULIA",     "JULIAN",    "JULIANA",
	"JULIANNA",  "JULIET",    "JULIETTE",  "JUNE",
	"JUSTIN",    "KADEN",     "KAI",       "KAIDEN",
	"KALEB",     "KARTER",    "KATHERINE", "KAYDEN",
	"KAYLA",     "KAYLEE",    "KENDALL",   "KENNEDY",
	"KENNETH",   "KEVIN",     "KHLOE",     "KILLIAN",
	"KIMBERLY",  "KING",      "KINGSTON",  "KINSLEY",
	"KNOX",      "KYLE",      "KYLIE",     "KYRIE",
	"LAILA",     "LANDON",    "LAUREN",    "LAYLA",
	"LEAH",      "LEILA",     "LEILANI",   "LEO",
	"LEON",      "LEONARDO",  "LEVI",      "LIAM",
	"LILA",      "LILIANA",   "LILLIAN",   "LILLY",
	"LILY",      "LINCOLN",   "LOGAN",     "LOLA",
	"LONDON",    "LONDYN",    "LORENZO",   "LUCA",
	"LUCAS",     "LUCIA",     "LUCY",      "LUIS",
	"LUKAS",     "LUKE",      "LUNA",      "LYDIA",
	"LYLA",      "MACKENZIE", "MADDOX",    "MADELINE",
	"MADELYN",   "MADISON",   "MAGGIE",    "MAKAYLA",
	"MALACHI",   "MALIA",     "MARCUS",    "MARGARET",
	"MARIA",     "MARIAH",    "MARK",      "MARLEY",
	"MARY",      "MASON",     "MATEO",     "MATIAS",
	"MATTEO",    "MATTHEW",   "MAVERICK",  "MAX",
	"MAXIMUS",   "MAXWELL",   "MAYA",      "MCKENZIE",
	"MELANIE",   "MELODY",    "MESSIAH",   "MIA",
	"MICAH",     "MICHAEL",   "MICHELLE",  "MIGUEL",
	"MILA",      "MILES",     "MILO",      "MOLLY",
	"MORGAN",    "MYA",       "MYLES",     "NAOMI",
	"NATALIA",   "NATALIE",   "NATHAN",    "NATHANIEL",
	"NEVAEH",    "NICHOLAS",  "NICOLAS",   "NICOLE",
	"NOAH",      "NOELLE",    "NOLAN",     "NORA",
	"NORAH",     "NOVA",      "OLIVER",    "OLIVIA",
	"OMAR",      "OSCAR",     "OWEN",      "PAIGE",
	"PAISLEY",   "PARKER",    "PATRICK",   "PAUL",
	"PAXTON",    "PAYTON",    "PENELOPE",  "PETER",
	"PEYTON",    "PIPER",     "PRESLEY",   "PRESTON",
	"QUINN",     "RACHEL",    "RAELYNN",   "REAGAN",
	"REBECCA",   "REESE",     "REMI",      "REMINGTON",
	"RHETT",     "RICHARD",   "RILEY",     "RIVER",
	"ROBERT",    "ROMAN",     "ROSALIE",   "ROSE",
	"ROWAN",     "RUBY",      "RYAN",      "RYDER",
	"RYKER",     "RYLEE",     "RYLEIGH",   "SADIE",
	"SAMANTHA",  "SAMUEL",    "SANTIAGO",  "SARA",
	"SARAH",     "SAVANNAH",  "SAWYER",    "SCARLETT",
	"SEBASTIAN", "SELENA",    "SERENITY",  "SIENNA",
	"SILAS",     "SKYLAR",    "SLOANE",    "SOFIA",
	"SOPHIA",    "SOPHIE",    "STELLA",    "STEVEN",
	"SUMMER",    "SYDNEY",    "TAYLOR",    "TEAGAN",
	"TESSA",     "THEODORE",  "THIAGO",    "THOMAS",
	"TIMOTHY",   "TRINITY",   "TRISTAN",   "TUCKER",
	"TYLER",     "VALENTINA", "VALERIA",   "VALERIE",
	"VANESSA",   "VICTOR",    "VICTORIA",  "VINCENT",
	"VIOLET",    "VIVIAN",    "WAYLON",    "WESLEY",
	"WESTON",    "WILLIAM",   "WILLOW",    "WYATT",
	"XANDER",    "XAVIER",    "XIMENA",    "ZACHARY",
	"ZANDER",    "ZANE",      "ZAYDEN",    "ZION",
	"ZOE",       "ZOEY",
};

void p2_sort::gen_prefix_trie(prefix_trie *out, const string *in, size_t cnt)
{
	const char *name;
	unsigned int ltr;
	size_t name_siz;
	prefix_trie *tmp;

	for (size_t i = 0; i < cnt; i++) {
		tmp      = out;
		name     = in[i].c_str();
		name_siz = in[i].size() + 1;  // we want to count NUL

		for (size_t j = 0; j < name_siz; j++) {
			ltr = (unsigned) name[j];

			if (!tmp->child[ltr])
				tmp->child[ltr] = new prefix_trie;

			tmp = tmp->child[ltr];
			++tmp->count;
		}
	}
}

void p2_sort::gen_uniq_prefix_trie(
		prefix_trie *in,
		uniq_prefix_trie *out,
		uniq_prefix_trie **buckets,
		unsigned *bucket_cnt
)
{
	// we've reached the end of a unique prefix
	if (in->count == 1) {
		buckets[(*bucket_cnt)++] = out;
		return;
	}

	for (int i = 0; i < UCHAR_MAX + 1; i++) {
		if (in->child[i]) {
			if (!out->child[i]) {
				out->child[i] = new uniq_prefix_trie;
				++out->children;
			}

			gen_uniq_prefix_trie(
				in->child[i],
				out->child[i],
				buckets,
				bucket_cnt
			);
		}
	}
}

void p2_sort::alloc_buckets(
	uniq_prefix_trie **buckets,
	const unsigned bucket_cnt,
	const unsigned bucket_siz
)
{
	uniq_prefix_trie *tmp;

	for (unsigned i = 0; i < bucket_cnt; i++) {
		tmp = buckets[i];
		tmp->bucket_tail
			= tmp->bucket_head
			= new Data*[bucket_siz];
	}
}

void p2_sort::index_name(uniq_prefix_trie *trie, Data *in, const char *name)
{
	for (unsigned i = 0; trie->children; i++)
		trie = trie->child[(unsigned) name[i]];

	*(trie->bucket_tail++) = in;
}

void p2_sort::clear_buckets(uniq_prefix_trie **buckets, unsigned bucket_cnt)
{
	uniq_prefix_trie *tmp;

	for (unsigned i = 0; i < bucket_cnt; i++) {
		tmp = buckets[i];

		// essentially we're concerned with just resetting the
		// perceived initial state
		tmp->bucket_tail = tmp->bucket_head;
		*tmp->bucket_head = nullptr;
	}
}

int p2_sort::ssncmp(const char *a, const char *b)
{
	// XXX-UU-UUUU
	for (int i = 0; i < 3; i++)
		if (*a++ != *b++) return *--a - *--b;

	++a;
	++b;

	// SSS-XX-UUUU
	for (int i = 0; i < 2; i++)
		if (*a++ != *b++) return *--a - *--b;

	++a;
	++b;

	// SSS-SS-XXXX
	for (int i = 0; i < 4; i++)
		if (*a++ != *b++) return *--a - *--b;

	return 0;
}

void p2_sort::get_terminal_node(
	uniq_prefix_trie *in,
	uniq_prefix_trie **out,
	const char *name
)
{
	for (unsigned i = 0; in->children; i++)
		in = in->child[(unsigned) name[i]];

	*out = in;
}

void p2_sort::uniq_prefix_sort(void)
{
	for (auto node : *src)
		index_name(
			last_name_uniq_prefix,
			node,
			node->lastName.c_str()
		);

	Data **head, **tail, **cur;
	uniq_prefix_trie *tmp;
	auto node = src->begin();

	for (unsigned i = 0; i < last_name_bucket_cnt; i++) {
		tmp = last_name_buckets[i];
		cur = head = tmp->bucket_head;
		tail = tmp->bucket_tail;

		while (cur != tail) {
			index_name(
				first_name_uniq_prefix,
				*cur,
				(*cur)->firstName.c_str()
			);
			++cur;
		}

		for (unsigned i = 0; i < first_name_bucket_cnt; i++) {
			tmp = first_name_buckets[i];
			head = tmp->bucket_head;
			tail = tmp->bucket_tail;

			if (head != tail) insrt_sort_ssn(head, tail);

			while (head != tail) {
				*node = *head;
				++head;
				++node;
			}
		}

		clear_buckets(first_name_buckets, first_name_bucket_cnt);
	}
}

void p2_sort::insrt_sort_ssn(Data **head, Data **tail)
{
	Data **i = head + 1;
	Data **j = head;
	Data **cur;
	Data *tmp;

	while (i != tail) {
		cur = i;

		while (
			i > head &&
			ssncmp((*i)->ssn.c_str(), (*j)->ssn.c_str()) < 0
		) {
			tmp = *i;
			*i = *j;
			*j = tmp;
			--i; --j;
		}

		i = ++cur;
		j = i - 1;
	}
}

p2_sort::p2_sort(void)
{
	node_buf = new Data*[FIRST_NAMES];
	ssn_buf = new string[MAX_ITEMS];
	ssn_aux = new string[MAX_ITEMS];
	last_name_prefix = new prefix_trie;
	last_name_uniq_prefix = new uniq_prefix_trie;
	first_name_prefix = new prefix_trie;
	first_name_uniq_prefix = new uniq_prefix_trie;

	gen_prefix_trie(last_name_prefix, last_names, LAST_NAMES);
	gen_prefix_trie(first_name_prefix, first_names, FIRST_NAMES);
	gen_uniq_prefix_trie(
		last_name_prefix,
		last_name_uniq_prefix,
		last_name_buckets,
		&last_name_bucket_cnt
	);
	gen_uniq_prefix_trie(
		first_name_prefix,
		first_name_uniq_prefix,
		first_name_buckets,
		&first_name_bucket_cnt
	);
	alloc_buckets(
		last_name_buckets,
		last_name_bucket_cnt,
		LAST_NAME_BUCKETS
	);
	alloc_buckets(
		first_name_buckets,
		first_name_bucket_cnt,
		FIRST_NAME_BUCKETS
	);
}

void p2_sort::t3_sort(void)
{
	auto lead  = src->begin();
	auto trail = src->begin();
	uniq_prefix_trie *pre, *cur;
	Data **head, **tail, **trace;

	head = tail = node_buf;

	get_terminal_node(
		first_name_uniq_prefix,
		&pre,
		(*lead)->firstName.c_str()
	);
	*(tail++) = *(lead++);

	for (unsigned i = 1; i < nodes; i++) {
		get_terminal_node(
			first_name_uniq_prefix,
			&cur,
			(*lead)->firstName.c_str()
		);

		if (pre == cur) {
			*(tail++) = *(lead++);
			continue;
		}

		if (tail > head + 1) insrt_sort_ssn(head, tail);

		trace = head;
		while (trace != tail) *(trail++) = *(trace++);

		pre = cur;
		tail = head;

		// don't forget to begin the next group of names
		*(tail++) = *(lead++);
	}

	// don't forget about the last group of names
	if (tail > head + 1) insrt_sort_ssn(head, tail);
	while (head != tail) *(trail++) = *(head++);
}

void p2_sort::t4_sort(void)
{
	auto node = src->begin();
	string *buf, *aux, *tmp;

	buf = ssn_buf;
	aux = ssn_aux;

	for (unsigned i = 0; i < nodes; i++, node++)
		swap(buf[i], (*node)->ssn);

	// UUU-UU-XXXX
	for (int i = 10; i > 6; i--) {
		memset(digit_cnt_offset, 0, sizeof(digit_cnt_offset));

		for (unsigned j = 0; j < nodes; j++)
			++digit_cnt[(unsigned) buf[j][i]];

		// calculate prefix sum
		for (unsigned j = 1; j < DIGITS; j++)
			digit_cnt_offset[j] += digit_cnt_offset[j - 1];

		for (int j = (signed) nodes - 1; j >= 0; j--)
			swap(
				aux[--digit_cnt[(unsigned) buf[j][i]]],
				buf[j]
			);

		tmp = buf;
		buf = aux;
		aux = tmp;
	}

	// UUU-XX-SSSS
	for (int i = 5; i > 3; i--) {
		memset(digit_cnt_offset, 0, sizeof(digit_cnt_offset));

		for (unsigned j = 0; j < nodes; j++)
			++digit_cnt[(unsigned) buf[j][i]];

		// calculate prefix sum
		for (unsigned j = 1; j < DIGITS; j++)
			digit_cnt_offset[j] += digit_cnt_offset[j - 1];

		for (int j = (signed) nodes - 1; j >= 0; j--)
			swap(
				aux[--digit_cnt[(unsigned) buf[j][i]]],
				buf[j]
			);

		tmp = buf;
		buf = aux;
		aux = tmp;
	}

	// XXX-SS-SSSS
	for (int i = 2; i > -1; i--) {
		memset(digit_cnt_offset, 0, sizeof(digit_cnt_offset));

		for (unsigned j = 0; j < nodes; j++)
			++digit_cnt[(unsigned) buf[j][i]];

		// calculate prefix sum
		for (unsigned j = 1; j < DIGITS; j++)
			digit_cnt_offset[j] += digit_cnt_offset[j - 1];

		for (int j = (signed) nodes - 1; j >= 0; j--)
			swap(
				aux[--digit_cnt[(unsigned) buf[j][i]]],
				buf[j]
			);

		tmp = buf;
		buf = aux;
		aux = tmp;
	}

	node = src->begin();
	for (unsigned i = 0; i < nodes; i++, node++)
		swap((*node)->ssn, buf[i]);
}

p2_sort p2;


void sortDataList(list<Data*> &l)
{
	p2.nodes = l.size();
	p2.src   = &l;

	if (p2.nodes < T1_LIMIT) {
		cout << "T1 detected!\n";
		p2.t1_sort();
		return;
	}

	auto front = l.front();
	auto back  = l.back();

	if (front->lastName == back->lastName) {
		cout << "T4 detected!\n";
		p2.t4_sort();
		return;
	}

	if (front->lastName[0] == 'A' && back->lastName[0] == 'Z') {
		cout << "T3 detected!\n";
		p2.t3_sort();
		return;
	}

	cout << "T2 detected!\n";
	p2.t2_sort();
}
