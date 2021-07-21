main.exe: main.o merge.o
	g++ -o main.exe main.o merge.o

main.o: main.cpp merge.h
	g++ -c main.cpp

merge.o: merge.cpp merge.h
	g++ -c merge.cpp

debug:
	g++ -g -o mainDebug.exe main.cpp merge.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups