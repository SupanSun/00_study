led:led.elf
	arm-linux-objcopy -O binary $< $@.tmp
	./tool $@.tmp $@.bin

led.elf:start.o main.o
	arm-linux-ld -Tmap.lds -Ttext=0xD0020010 -o $@ $^

%.o:%.c
	arm-linux-gcc -Wall -c -o $@ $<
%.o:%.S
	arm-linux-gcc -Wall -c -o $@ $<

clean:
	rm *.o *.elf *.tmp *.bin
