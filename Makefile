
#!make -f

CXX=clang++
CXXFLAGS=-std=c++11 
VALGRIND_FLAGS=-v -g --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

run: test
	./$^

main: main.o $(filter-out TestCounter.o Test.o,$(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o main

test: TestCounter.o Test.o $(filter-out main.o,$(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: main test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./main 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o main test