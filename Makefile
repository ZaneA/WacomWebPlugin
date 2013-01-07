npWacomWebPlugin.so : src/*
	gcc -DDEBUG -fPIC -o npWacomWebPlugin.so -shared src/*.c -I/usr/include/npapi-sdk
