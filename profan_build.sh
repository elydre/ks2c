CC_FLAG="-g -ffreestanding -fno-exceptions -m32 -I ../profanOS/include/zlibs -c"
LDFLAGS="-T ../profanOS/tools/zlink.ld -m elf_i386"

gcc $CC_FLAG -o o_src/main.o o_src/main.c
gcc $CC_FLAG -o o_src/fcm.o o_src/fcm.c
gcc $CC_FLAG -o o_src/tools.o o_src/tools.c
gcc $CC_FLAG -o o_src/zentry.o ../profanOS/tools/zentry.c

ld $LDFLAGS -o prog.out o_src/zentry.o o_src/main.o o_src/fcm.o o_src/tools.o
objcopy -O binary prog.out ../profanOS/out/zapps/fatpath/prog.bin

make clean
