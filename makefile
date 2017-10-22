all:

usergroup: usergroup.o
	g++ -g --std=c++11 usergroup.o -o output.out

usergroup.o: usergroup.cpp
	g++ -c usergroup.cpp

netxtern: netxtern.o
	g++ -g --std=c++11 netxtern.o -o output.out

netxtern.o: netxtern.cpp
	g++ -c netxtern.cpp

activitymonitor: activitymonitor.o
	g++ -g activitymonitor.o -o output.out

activitymonitor.o: activitymonitor.cpp
	g++ -c activitymonitor.cpp

run: output.out
	cat in.in | ./output.out

clean:
	$(RM) output.out
	rm -rf *.o
