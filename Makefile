CC           = gcc
CFLAGS       = -Wall -std=c99 -pedantic
LDFLAGS      = -Ofast
LDLIBS       = -lm -lmvec

SRC          = getargs.c \
	       print_usage.c \
	       initialize.c \
	       iterate.c \
	       write_to_file.c \
	       main.c
DEPS         = definitions_and_headers.h
EXECUTABLE   = OregonatorSolve


.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(SRC) -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)

.PHONY: rmall
rmall:
	rm -f *.png *.csv *.log



