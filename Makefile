
OBJS=npWacomWebPlugin.so

INCS+=-I/usr/include/$(shell ls /usr/include/ | grep xulrunner) # Fedora npapi header (Package: xulrunner-devel)
INCS+=-I/usr/include/npapi-sdk # Arch npapi header (Package: npapi-sdk)
INCS+=-I/usr/include/firefox # Ubuntu npapi header (Package: firefox-dev)

LIBS+=-lpthread

DEFS+=-DDEBUG

CC=gcc -std=gnu99 -Wall -Werror

all: ${OBJS}

npWacomWebPlugin.so: src/*
	${CC} ${DEFS} -shared -fPIC src/*.c ${INCS} ${LIBS} -o $@

clean:
	rm -rf ${OBJS}

