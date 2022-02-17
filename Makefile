##
# Tilin Window Manager
#
# @file
# @version 0.1

PREFIX?=/usr/X11R6
FLAGS?=-Os -pedantic -Wall

install:
	$(CC) $(CFLAGS) -I$(PREFIX)/include tilin.c -L$(PREFIX)/lib -lX11 -o tilin
	mkdir -p /usr/local/bin
	cp -f tilin /usr/local/bin/

reinstall: clean
	$(CC) $(CFLAGS) -I$(PREFIX)/include tilin.c -L$(PREFIX)/lib -lX11 -o tilin
	mkdir -p /usr/local/bin
	cp -f tilin /usr/local/bin/

clean:
	rm -f tilin
	rm -f /usr/local/lib/tilin

# end
