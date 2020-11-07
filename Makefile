# Using prams given in csa-makefile
CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537make
SCAN_BUILD_DIR = scan-build-out

537make: 537make.o cmdLine.o graph.o makeParser.o strProcess.o
	$(CC) -o $(EXE) 537make.o cmdLine.o graph.o makeParser.o strProcess.o


537make.o: 537make.c 537make.h
	$(CC) $(WARNING_FLAGS) -c 537make.c


cmdLine.o: cmdLine.c cmdLine.h
	$(CC) $(WARNING_FLAGS) -c cmdLine.c


graph.o: graph.c graph.h
	$(CC) $(WARNING_FLAGS) -c graph.c


makeParser.o: makeParser.c makeParser.h
	$(CC) $(WARNING_FLAGS) -c makeParser.c

strProcess.o: strProcess.c strProcess.h
	$(CC) $(WARNING_FLAGS) -c strProcess.c

clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)


scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make


scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
