# A nice tutorial on Makefile :
# https://opensource.com/article/18/8/what-how-makefile
# This Makefile is mainly based on it. Clicks on the link above for a detailled
# explanation.
# And a Makefile cheatsheet is available here :
# https://devhints.io/makefile

.PHONY = all clean_object clean

CC = gcc
CCFLAGS = -Wall -Wextra

LINKERFLAG = -lm -lgsl -lgslcblas

# Just break SOURCES in multiples lines because it is too long to fit on my screen...
SOURCES := csv.c data.c doNothingResampling.c estimates.c estimatesXYPsi.c initParticlesXYPsi.c
SOURCES := ${SOURCES} magneticMap.c moveParticlesXYPsi.c odometry.c pfmag.c
SOURCES := ${SOURCES} stateXYPsi.c weight.c writeParticles.c

OBJECTS := $(SOURCES:%.c=%.o)

all: pfmag evaluatePfmag

# Compiling each object separately is more efficient.
# If an object is already compiled and up to date, this Makefile will not create
# it again.
%.o: %.c
	${CC} ${CCFLAGS} -c $<

pfmag: ${OBJECTS}
	@echo "create executable "$@
	${CC} $^ -o $@ ${LINKERFLAG}

evaluatePfmag: csv.o data.o evaluatePfmag.o
	@echo "create executable "$@
	${CC} $^ -o $@ ${LINKERFLAG}

clean_object:
	@echo "Cleaning objects"
	rm *.o || true
# "rm myfile" fails when the file does not already exists. It breaks the whole makefile
# "rm myfile || true" allow to keep going even in those situations

clean: clean_object
	@echo "Cleaning binaries"
	rm pfmag || true
	rm evaluatePfmag || true
