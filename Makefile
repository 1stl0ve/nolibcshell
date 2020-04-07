OBJS = shell.o syscall.o strings.o 

shell: $(OBJS)
	gcc -g -nostdlib -nodefaultlibs -nostartfiles -o shell $(OBJS) entry.S
	$(MAKE) clean-objs

%.o: %.c
	gcc -g -nostdlib -nodefaultlibs -nostartfiles -c $< -o $@

.PHONY: clean clean-objs

clean-objs:
	rm -f $(OBJS)

clean: clean-objs
	rm -f shell