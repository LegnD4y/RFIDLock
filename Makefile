all:
	gcc `pkg-config --cflags gtk4` RFIDLock.c -o RFIDLock `pkg-config --libs gtk4`

clean:
	rm RFIDLock
