	
TARGET = test.elf
CC_FLAGS = -Wall -O3
LD_FLAGS =
LD_LIB = -lm -lc
OBJ_FILES = ray_generator.o test_loop.o intersect_f.o

### Compiling ###

all: $(TARGET)

test_loop.o: test_loop.c
	gcc $(CC_FLAGS) -c $<

ray_generator.o: ray_generator.c
	gcc $(CC_FLAGS) -c $<

intersect_f.o: intersect_f.c
	gcc $(CC_FLAGS) -c $<

### Linking ###

$(TARGET): $(OBJ_FILES)
	gcc $(LD_FLAGS) $(OBJ_FILES) $(LD_LIB) -o $@

clean:
	rm $(TARGET) $(OBJ_FILES)

