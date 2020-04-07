LIBC_CFLAGS ?= -g -Wall
CFLAGS ?= -g -Wall -nostdlib -nodefaultlibs -nostartfiles
ENTRY ?= entry.S
OBJS = shell.o syscall.o strings.o stdlib.o unistd.o

shell: $(OBJS)
	gcc $(CFLAGS) -o shell $(OBJS) $(ENTRY)
	$(MAKE) clean-objs

libc:
	$(MAKE) CFLAGS="$(LIBC_FLAGS)" ENTRY="" shell

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

.PHONY: clean clean-objs

clean-objs:
	rm -f $(OBJS)

clean: clean-objs
	rm -f shell