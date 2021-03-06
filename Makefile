CC = gcc

CFLAGS = -I.

LDFLAGS = -L/usr/local/lib -lm -lpthread

OBJ = hack03.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

gen_app: $(OBJ)
	@echo "----Compiling----"
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean: 
	@echo "----Cleaning----"
	rm *.o
	rm gen_app




