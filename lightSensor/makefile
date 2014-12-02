CC=arm-linux-gcc
light: light2.o luxcalc.o
	$(CC) light2.o luxcalc.o -s -o light2
light.o: light2.c
	$(CC) -c light2.c
luxcalc.o: luxcalc.c
	$(CC) -c luxcalc.c -o luxcalc.o
clean:
	rm -rf *.o light2
