BOOST_DIR=C:/boost/boost_1_69_0
CXX=g++
CFLAGS=-I$(BOOST_DIR)

debug: CFLAGS+=-DDEBUG -g
debug: BUILD_DIR=../debug
debug: libGraph.a

release: CFLAGS+=-O3
release: BUILD_DIR=../release
release: libGraph.a

libGraph.a: *.cpp *.h
	$(CXX) -c Graph.cpp GraphAlgo.cpp GraphWriter.cpp $(CFLAGS)
	ar rvs libGraph.a Graph.o GraphAlgo.o GraphWriter.o
	rm -f *.o
	mv libGraph.a $(BUILD_DIR)
	