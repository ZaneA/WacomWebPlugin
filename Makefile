npWacomWebPlugin.so : src/*
	gcc -DDEBUG -std=gnu99 -fPIC -o npWacomWebPlugin.so -shared src/*.c -I/usr/include/npapi-sdk -lpthread
