# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: toy.elf 

#additional rules for files
toy.elf: ${COMMON_OBJECTS} projectMain.o stateMachines.o led.o buzzer.o p2_interrupt_handler.o switches.o wdInterruptHandler.o littleLamb.o statesAssembly.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: toy.elf
	msp430loader.sh toy.elf

clean:
	rm -f *.o *.elf

led.o: led.c led.h

wdInterruptHandler.o: stateMachines.h

stateMachines.o: led.h stateMachines.h

buzzer.o: buzzer.c buzzer.h

switches.o: switches.c switches.h

littleLamb.o: littleLamb.c littleLamb.h

statesAssembly.o: statesAssembly.s statesAssembly.h
