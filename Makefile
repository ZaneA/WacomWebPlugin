npWacomWebPlugin.so : src/*
	gcc -DDEBUG -std=gnu99 -Wall -Werror -fPIC -o npWacomWebPlugin.so -shared src/*.c -I/usr/include/npapi-sdk -I/usr/include/firefox -lpthread
