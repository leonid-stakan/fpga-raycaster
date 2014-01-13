
all: main.c ray_generator.c
#	gcc -Wall main.c ray_generator.c -Xlinker -lm -o main.elf
	gcc -Wall  -o main.elf main.c ray_generator.c -lm

##CC_FLAGS = -Wall
##LD_FLAGS = -Xlinker -lm
##-e main -lm -lc -A i386

##all: main.elf

##main.o: main.c
##	gcc $(CC_FLAGS) -c $<

#ray_generator.o: ray_generator.c
#	gcc $(CC_FLAGS) -c $<

#main.elf: main.o ray_generator.o
#	gcc $(LD_FLAGS) main.o ray_generator.o
## -o $@

