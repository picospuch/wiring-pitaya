# compiler
#TOOLCHAIN_ROOT := /home/spuch/opt/gcc-arm-8.3-2019.03-x86_64-arm-linux-gnueabihf
#CC := $(TOOLCHAIN_ROOT)/bin/arm-linux-gnueabihf-gcc
INCLUDE = -I.
CFLAGS = $(DEFS) $(INCLUDE) -pipe -fPIC $(EXTRA_CFLAGS)
LIBS    = -lpthread

STATIC = libwiringpitaya.a

# code
SRC =	wiring-pitaya.c					\
		soft-pwm.c						\
		piHiPri.c						\
		gpio.c

OBJ	= $(SRC:.c=.o)

OUT_FILES = $(OBJ) $(STATIC) test.o test

all: $(STATIC)

$(STATIC): $(OBJ)
	for i in $(OBJ); do echo $(AR) rcs $(STATIC) $$i; $(AR) rcs $(STATIC) $$i; done

LDFLAGS_TEST = -L.
LDLIBS_TEST = -lwiringpitaya

test.exe: test.o $(STATIC)
	$(CC) -o $@ $< $(LDFLAGS_TEST) $(LDLIBS_TEST) $(LIBS)

gpio.exe: gpio.o $(STATIC)
	$(CC) -o $@ $< $(LDFLAGS_TEST) $(LDLIBS_TEST) $(LIBS)

%.o: %.c
	@echo [Compile] $<
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OUT_FILES)

.PHONY:	depend
depend:
	makedepend -Y -f makefile $(SRC) $(SRC_I2C)

# DO NOT DELETE

wiring-pitaya.o: wiring-pitaya.h gpio.h
soft-pwm.o: soft-pwm.h wiring-pitaya.h gpio.h
piHiPri.o: wiring-pitaya.h gpio.h
gpio.o: gpio.h
