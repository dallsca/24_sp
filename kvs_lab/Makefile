# Source files
SRCS = main.c
LIBSRCS = open.c close.c put.c get.c
TARG_STATIC = kvs_static
TARG_DYNAMIC = kvs_dynamic

# Compiler and flags
CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

# Object files
OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LDYN = libkvs.so

# All targets
all: static dynamic

# Static library
static: $(TARG_STATIC)

$(TARG_STATIC): $(OBJS) $(LARS)
	$(CC) -o $(TARG_STATIC) $(OBJS) $(LIBS) -static

$(LARS): $(LOBJS)
	ar rs $(LARS) $(LOBJS)

# Dynamic library
dynamic: $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS) $(LDYN)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) $(LIBS)

$(LDYN): $(LOBJS)
	$(CC) -shared -o $(LDYN) $(LOBJS)

# Compile object files
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(LDYN) $(TARG_STATIC) $(TARG_DYNAMIC)

