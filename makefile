all: test clean

objects = test.o controller.o usercontroller.o wordcontroller.o datacontroller.o configuration.o worddata.o userdata.o exception.o userdatabase.o worddatabase.o data.o logging.o database.o consts.o

test: $(objects)
	g++ -o test -std=c++11 -g $(objects)
test.o: test.cpp
	g++ test.cpp -c -std=c++11 -g
controller.o:controller.cpp
	g++ controller.cpp -c -std=c++11 -g
usercontroller.o:usercontroller.cpp
	g++ usercontroller.cpp -c -std=c++11 -g
datacontroller.o:datacontroller.cpp
	g++ datacontroller.cpp -c -std=c++11 -g
wordcontroller.o:wordcontroller.cpp
	g++ wordcontroller.cpp -c -std=c++11 -g
worddata.o:worddata.cpp
	g++ worddata.cpp -c -std=c++11 -g
userdata.o:userdata.cpp
	g++ userdata.cpp -c -std=c++11 -g
exception.o:exception.cpp
	g++ exception.cpp -c -std=c++11 -g
userdatabase.o:userdatabase.cpp
	g++ userdatabase.cpp -c -std=c++11 -g
worddatabase.o:worddatabase.cpp
	g++ worddatabase.cpp -c -std=c++11 -g
data.o:data.cpp
	g++ data.cpp -c -std=c++11 -g
logging.o:logging.cpp
	g++ logging.cpp -c -std=c++11 -g
database.o:database.cpp
	g++ database.cpp -c -std=c++11 -g
configuration.o:configuration.cpp
	g++ configuration.cpp -c -std=c++11 -g
consts.o:consts.cpp
	g++ consts.cpp -c -std=c++11 -g
clean:
	rm *.o
