
all: try_reset

clean:
	rm -f try_reset *.o *~ \#* *.lst *.hex

try_reset: try_reset.o sio_cmd.o
	$(CC) -o try_reset try_reset.o sio_cmd.o
