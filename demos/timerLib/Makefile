all: libTimer.a

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

libTimer.a: clocksTimer.o sr.o
	$(AR) crs $@ $^

install: libTimer.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

installProject: libTimer.a
	mkdir -p ../../project/h ../../project/lib
	mv $^ ../../project/lib
	cp *.h ../../project/h

clean:
	rm -f timerLib.a *.o
