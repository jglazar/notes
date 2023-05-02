# basic compile
#g++ --std=c++11 -O0 provided.cpp -o listsorter
#g++ --std=c++11 -O0 debug.cpp -o listsorter

# compile with options
g++ --std=c++11 -O0 \
-finline \
-fif-conversion \
-fif-conversion2 \
-finline-functions-called-once \
-fipa-pure-const \
-fomit-frame-pointer \
debug.cpp -o listsorter

# test compile with debugging
#g++ --std=c++11 -O0 -ggdb debug.cpp -o listsorter

# test compile with profiling
#g++ --std=c++11 -O0 -pg debug.cpp -o listsorter
#g++ --std=c++11 -O1 -pg debug.cpp -o listsorter

# test compile with profiling
#g++ --std=c++11 -O0 -finline -pg debug.cpp -o listsorter
