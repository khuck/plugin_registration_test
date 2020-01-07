CC=gcc
CFLAGS=-O0 -g -fPIC -Werror -Wall

UNAME_S := $(shell uname -s)
LDFLAGS_WHOLE :=
SHARED_SUFFIX :=
CFLAGS_STATIC :=
LDFLAGS :=

ifeq ($(UNAME_S),Darwin)
    LDFLAGS_WHOLE:=-Wl,-all_load libtool1.a -Wl,-all_load libtool2.a
    SHARED_SUFFIX :=dylib
    CFLAGS_STATIC:=
    CFLAGS_DYNAMIC:=-shared
    LDFLAGS:=-undefined dynamic_lookup
else
    LDFLAGS_WHOLE:=-Wl,--whole-archive libtool1.a libtool2.a -Wl,--no-whole-archive
    SHARED_SUFFIX :=so
    CFLAGS_STATIC:=-static
    CFLAGS_DYNAMIC:=-shared
endif

default: program_static_notool program_static program_dynamic program_dynamic_notool

program_static: main.o libplugin.a libtool1.a libtool2.a
	$(CC) $(CFLAGS) -o program_static main.o libplugin.a $(LDFLAGS_WHOLE) $(CFLAGS_STATIC)

program_static_notool: main.o libplugin.a
	$(CC) $(CFLAGS) -o program_static_notool main.o libplugin.a $(CFLAGS_STATIC)

program_dynamic: main.o libplugin.$(SHARED_SUFFIX) libtool1.$(SHARED_SUFFIX) libtool2.$(SHARED_SUFFIX)
	$(CC) $(CFLAGS) -o program_dynamic main.o -L. -lplugin -ltool1 -ltool2

program_dynamic_notool: main.o libplugin.$(SHARED_SUFFIX)
	$(CC) $(CFLAGS) -o program_dynamic_notool main.o -L. -lplugin

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

libtool1.a: tool1.o
	ar -crs libtool1.a tool1.o

libtool1.$(SHARED_SUFFIX): tool1.o
	gcc $(CFLAGS_DYNAMIC) $(LDFLAGS) -o libtool1.$(SHARED_SUFFIX) tool1.o

libtool2.a: tool2.o
	ar -crs libtool2.a tool2.o

libtool2.$(SHARED_SUFFIX): tool2.o
	gcc $(CFLAGS_DYNAMIC) $(LDFLAGS) -o libtool2.$(SHARED_SUFFIX) tool2.o

libplugin.a: plugin.o
	ar -crs libplugin.a plugin.o

libplugin.$(SHARED_SUFFIX): plugin.o
	gcc $(CFLAGS_DYNAMIC) $(LDFLAGS) -o libplugin.$(SHARED_SUFFIX) plugin.o

clean:
	rm -rf *.o *.a *.$(SHARED_SUFFIX) program_static* program_dynamic*