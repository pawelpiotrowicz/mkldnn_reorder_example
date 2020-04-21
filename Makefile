MKL=mkl-dnn


CXX=clang++-4.0


main: main.cpp
	$(CXX) -std=c++0x -Wall -g -o prog main.cpp -I./$(MKL)/build/include  -I./$(MKL)/include -L$(MKL)/build/src -lmkldnn -ldnnl -Wl,-rpath,$(MKL)/build/src


