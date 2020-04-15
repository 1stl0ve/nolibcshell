CFLAGS ?= -g -Wall -nostdlib -nodefaultlibs -nostartfiles
ENTRY ?= entry.S
OBJS = shell.o strings.o heap.o mylib.o

shell: $(OBJS)
	gcc $(CFLAGS) -o shell $(OBJS) $(ENTRY)
	$(MAKE) clean-objs

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

.PHONY: clean clean-objs

clean-objs:
	rm -f $(OBJS)

clean: clean-objs
	rm -f shell