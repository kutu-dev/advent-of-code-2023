CC:=gcc
CFLAGS:=-Wall -Wextra -Werror -Wpedantic -O2
BUILD:=./build
OUT_FILENAMES:=p1d1 p2d1 p1d2 p2d2
OUT_FILENAMES:=$(foreach out_filename,$(OUT_FILENAMES),$(out_filename).out)

.DELETE_ON_ERROR:
.PHONY: all build clear

all: build

build: $(OUT_FILENAMES)

run: $(OUT_FILENAMES)
	@cd build; for day in *; do cd $$day; for part in *.out;do ./$$part; done; cd ..; done

clear:
	@rm -r build

$(wildcard *.c):

p1d1.out: day-1/part-1.c common/logger.c
	@mkdir -p $(BUILD)/day-1
	@cp day-1/input.txt $(BUILD)/day-1
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-1/$@

p2d1.out: day-1/part-2.c common/logger.c
	@mkdir -p $(BUILD)/day-1
	@cp day-1/input.txt $(BUILD)/day-1
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-1/$@

p1d2.out: day-2/part-1.c common/logger.c
	@mkdir -p $(BUILD)/day-2
	@cp day-2/input.txt $(BUILD)/day-2
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-2/$@
	
p2d2.out: day-2/part-2.c common/logger.c
	@mkdir -p $(BUILD)/day-2
	@cp day-2/input.txt $(BUILD)/day-2
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-2/$@

p1d3.out: day-3/part-1.c common/logger.c
	@mkdir -p $(BUILD)/day-3
	@cp day-3/input.txt $(BUILD)/day-3
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-3/$@

p2d3.out: day-3/part-2.c common/logger.c
	@mkdir -p $(BUILD)/day-3
	@cp day-3/input.txt $(BUILD)/day-3
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-3/$@
