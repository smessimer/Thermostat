app: test.o thermostat.o
	cc -o app test.o thermostat.o

test.o: test.c thermostat.h
	cc -c test.c thermostat.h

thermostat.o: thermostat.c thermostat.h
	cc -c thermostat.c thermostat.h

.PHONY:clean
clean:
	rm -f *.o *.gch app
