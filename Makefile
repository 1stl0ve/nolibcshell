OBJS = shell.o syscall.o strings.o

shell: $(OBJS)
	gcc -g -nostdlib -o shell $(OBJS)

%.o: %.c
	gcc -g -nostdlib -c $< -o $@

.PHONY: clean

clean:
	rm $(OBJS)