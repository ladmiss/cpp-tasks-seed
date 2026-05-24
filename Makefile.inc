CXX = g++
CXXFLAGS = -std=c++17 -Werror -Wpedantic -Wall
CXXFLAGS_R = $(CXXFLAGS) -O3 -DNDEBUG
CXXFLAGS_D = $(CXXFLAGS) -g  -DDEBUG
GTEST_LIBS = -lgtest -lgtest_main -lpthread
LD=$(CXX)

%.d.o : %.cpp
	$(CXX) -c $(CXXFLAGS_D) -o $@ $<

%.r.o : %.cpp
	$(CXX) -c $(CXXFLAGS_R) -o $@ $<

clean :
	- rm *.o
	- rm *.hdrdep.bak

cleanall : clean
	- rm release debug debug_test utest base85
	- echo > Makefile.hdrdep

mrproper : cleanall

astyle:
	@if command -v astyle >/dev/null 2>&1; then \
		astyle --options=../astyle.ini *.h *.cpp; \
	else \
		echo "astyle not found, skipping"; \
	fi

tidy:
	@bash ../tidy.sh

depends :
	@if command -v makedepend >/dev/null 2>&1; then \
		makedepend -f Makefile.hdrdep *.c*; \
	else \
		echo "makedepend not found, skipping header dependencies"; \
	fi
