CFLAGS ?= -g -Wall -nostdlib -nodefaultlibs -nostartfiles
CFLAGS32 ?= -g -Wall -nostdlib -nodefaultlibs -nostartfiles -m32 -fno-pie
ENTRY ?= entry.S
ENTRY32 ?= entry_x86.S
OBJS = shell.o strings.o heap.o mylib.o

shell: $(OBJS)
	gcc $(CFLAGS) -o shell $(OBJS) $(ENTRY)
	$(MAKE) clean-objs

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

.PHONY: clean clean-objs

shell32:
	$(MAKE) ENTRY="$(ENTRY32)" CFLAGS="$(CFLAGS32) -DARCH32" shell

unity: unity.c
	gcc $(CFLAGS) unity.c entry.S -o shell.unity

clean-objs:
	rm -f $(OBJS)

clean: clean-objs
	rm -f shell