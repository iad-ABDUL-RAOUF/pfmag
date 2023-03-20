# A nice tutorial on Makefile :
# https://opensource.com/article/18/8/what-how-makefile
# This Makefile is mainly based on it. Clicks on the link above for a detailled
# explanation.

.PHONY = all clean_object clean

CC = gcc

LINKERFLAG = -lm -lgsl -lgslcblas

# Just break SOURCES in multiples lines because it is too long to fit it on one line on my screen...
SOURCES := csv.c data.c doNothingResampling.c estimates.c estimatesXYPsi.c initParticlesXYPsi.c
SOURCES := ${SOURCES} magneticMap.c moveParticlesXYPsi.c odometry.c pfmag.c
SOURCES := ${SOURCES} stateXYPsi.c weight.c writeParticles.c

OBJECTS := $(SOURCES:%.c=%.o)

all: pfmag

# Compiling each object separately is more efficient.
# If an object is already compiled and up to date, this Makefile will not create
# it again.
%.o: %.c
	${CC} -c $<

pfmag: ${OBJECTS}
	@echo "create executable "$@
	${CC} $^ -o $@ ${LINKERFLAG}

clean_object:
	@echo "Cleaning objects"
	rm *.o

clean: clean_object
	@echo "Cleaning binaries"
	rm pfmag
