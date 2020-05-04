COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include
CC              = msp430-elf-gcc
AS              = msp430-elf-as  -mcpu=msp430  --traditional-format -mP


all: main.elf
install: libLcd.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

main.elf: ${COMMON_OBJECTS} p1_interrupt_handler.o led.o switches.o main.o buzzer.o stateMachine.o wdInterruptHandler.o assembly_code.o lcddraw.o lcdutils.o font-11x16.o font-5x7.o font-8x12.o ../lib/libTimer.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: main.elf
	msp430loader.sh main.elf
clean:
	rm -f *.o *.elf

led.o: led.h led.c
wdInterruptHandler.o: stateMachine.h
stateMachine.o: led.h stateMachine.h
buzzer.o: buzzer.h buzzer.c
switches.o: switches.h switches.c
main.o: led.h buzzer.h switches.h main.c
lcddraw.o: lcddraw.h lcddraw.c main.c main.o
