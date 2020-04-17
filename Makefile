ARCH ?= x86_64
CFLAGS = -g -Wall -Wextra -Werror -nostdlib -nodefaultlibs -nostartfiles
CFLAGS_32 = -m32 -fno-pie
ENTRY = $(ARCH)/entry.S
OBJS = shell.o strings.o heap.o mylib.o

all: shell

shell: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(ENTRY)
	$(MAKE) clean-objs

%.o: %.c
	$(CC) $(CFLAGS) -I./$(ARCH) -c $< -o $@

.PHONY: shell32 clean clean-objs

shell32:
	$(MAKE) ARCH="x86" CFLAGS="$(CFLAGS) -m32 -DARCH32" shell

shell.unity: unity.c
	gcc $(CFLAGS) -I./$(ARCH) $< $(ENTRY) -o $@

clean-objs:
	rm -f $(OBJS)

clean: clean-objs
	rm -f shell shell.unity