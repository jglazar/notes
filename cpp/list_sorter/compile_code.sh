# basic compile
#g++ --std=c++11 -O0 provided.cpp -o listsorter
#g++ --std=c++11 -O0 debug.cpp -o listsorter

# compile with options
# -fomit-frame-pointer does great, but I don't think there's a way to manually
# add the functionality into the code 
g++ --std=c++11 \
debug.cpp -o listsorter
#-fomit-frame-pointer \

# test compile with debugging
#g++ --std=c++11 -O0 -ggdb debug.cpp -o listsorter

# test compile with profiling
#g++ --std=c++11 -O0 -pg debug.cpp -o listsorter
#g++ --std=c++11 -O1 -pg debug.cpp -o listsorter

# test compile with profiling
#g++ --std=c++11 -O0 -finline -pg debug.cpp -o listsorter
