build.bin:uart.elf
	arm-linux-objcopy -O binary $< $@.tmp
	./tool $@.tmp $@

uart.elf:uart.o start.o
	arm-linux-ld -Ttext=0xD0020010 -o $@ $^
	
%.o:%.c
	arm-linux-gcc -Wall -c -o $@ $<

%.o:%.S
	arm-linux-gcc -Wall -c -o $@ $<


clean:
	rm *.o *.elf *.tmp *.bin






