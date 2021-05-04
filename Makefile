TARGET := imgfilter
CC := clang
SRC := $(shell find src/ -name "*.cpp")
OBJ := $(patsubst src/%.cpp,build/%.o,$(SRC))
COPTS := -Wno-switch -Wno-delete-abstract-non-virtual-dtor -std=c++17
LIBS := -lsfml-system -lsfml-window -lsfml-graphics -lstdc++

.PHONY: clean

all: pastel

$(OBJ): build/%.o: src/%.cpp
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $^ -Iinclude/ $(COPTS)

pastel: $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS)

clean:
	rm -rf build/*