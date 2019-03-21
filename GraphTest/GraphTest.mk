GTEST_INCLUDE=../Gtest
GRAPH_INCLUDE=../Graphs
BOOST_DIR=C:/boost/boost_1_69_0
GTEST_LIB=../Gtest
CXX=g++
BOOST_LINK=-LC:/boost/boost_1_69_0/stage/lib -lboost_filesystem-mgw81-mt-x64-1_69
GTEST_LINK=-L../Gtest -lgmock -lgtest
CFLAGS=-I$(GTEST_INCLUDE) -I$(GRAPH_INCLUDE) -I$(BOOST_DIR) -o GraphTest.exe $(GTEST_LINK) $(BOOST_LINK) -std=c++17

debug: CFLAGS+=-DDEBUG -g
debug: BUILD_DIR=../debug
debug: GraphTest.exe

release: CFLAGS+=-O3
release: BUILD_DIR=../release
release: GraphTest.exe

GraphTest.exe: test.cpp
	$(CXX) test.cpp -L$(BUILD_DIR) -lGraph $(CFLAGS) 
	mv GraphTest.exe $(BUILD_DIR)