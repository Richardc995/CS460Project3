CFLAGS = -std=c++11 -g

P3.out : Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o
	g++ ${CFLAGS} -o P3.out Project2.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o

Project2.o : Project2.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ ${CFLAGS} -c Project2.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ ${CFLAGS} -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h
	g++ ${CFLAGS} -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ ${CFLAGS} -c SyntacticalAnalyzer.cpp

clean : 
	rm *.lst *.p1 *.p2 *.dbg *.o P2.out *.gch


submit : Project2.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile
	rm -rf ylnP3
	mkdir ylnP3
	cp Project2.cpp ylnP3
	cp SetLimits.h ylnP3
	cp SetLimits.cpp ylnP3
	cp LexicalAnalyzer.h ylnP3
	cp LexicalAnalyzer.cpp ylnP3
	cp SyntacticalAnalyzer.h ylnP3
	cp SyntacticalAnalyzer.cpp ylnP3
	cp makefile ylnP3
	tar cfvz ylnP3.tgz ylnP3
	cp ylnP3.tgz ylnP3
	tar cfvz ylnP3.tgz ylnP3
	cp ylnP3.tgz ~tiawatts/cs460drop
