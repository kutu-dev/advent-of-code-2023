CC:=gcc
CFLAGS:=-Wall -Wextra -Werror -Wpedantic -O3 -lm
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

p1d4.out: day-4/part-1.c common/logger.c
	@mkdir -p $(BUILD)/day-4
	@cp day-4/input.txt $(BUILD)/day-4
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-4/$@

p2d4.out: day-4/part-2.c common/logger.c
	@mkdir -p $(BUILD)/day-4
	@cp day-4/input.txt $(BUILD)/day-4
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-4/$@

p1d5.out: day-5/part-1.c common/logger.c
	@mkdir -p $(BUILD)/day-5
	@cp day-5/input.txt $(BUILD)/day-5
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-5/$@

p2d5.out: day-5/part-2.c common/logger.c
	@mkdir -p $(BUILD)/day-5
	@cp day-5/input.txt $(BUILD)/day-5
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-5/$@

p1d6.out: day-6/part-1.c common/logger.c
	@mkdir -p $(BUILD)/day-6
	@cp day-6/input.txt $(BUILD)/day-6
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-6/$@

p2d6.out: day-6/part-2.c common/logger.c
	@mkdir -p $(BUILD)/day-6
	@cp day-6/input.txt $(BUILD)/day-6
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-6/$@

p1d7.out: day-7/part-1.c common/logger.c
	@mkdir -p $(BUILD)/day-7
	@cp day-7/input.txt $(BUILD)/day-7
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-7/$@

p2d7.out: day-7/part-2.c common/logger.c
	@mkdir -p $(BUILD)/day-7
	@cp day-7/input.txt $(BUILD)/day-7
	@$(CC) $(CFLAGS) $^ -o $(BUILD)/day-7/$@
