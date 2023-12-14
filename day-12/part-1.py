from pathlib import Path
from functools import cache

input_file_path = Path(__file__).parent / "input.txt"
input_lines: list[str]

with open(input_file_path, "r") as f:
    input_lines = f.readlines()

@cache
def calculate_combinations(record: str, sizes: tuple[int]) -> int:

    if not sizes:
        if "#" not in record:
            return 1
        else:
            return 0

    if not record:
        return 0

    next_char = record[0]
    next_size = sizes[0]

    def pound():
        global foo

        spring_slice = record[:next_size]
        spring_slice = spring_slice.replace("?", "#")

        if "." in spring_slice:
            return 0

        if len(spring_slice) < next_size:
            return 0

        """
        if spring_slice != next_size*"#":
            print(foo)
            foo += 1
            return 0"""

        if len(record) == next_size:
            if len(sizes) == 1:
                return 1
            else:
                return 0

        if record[next_size] in "?.":
            return calculate_combinations(record[next_size+1:], sizes[1:])

        return 0


    def dot():
        return calculate_combinations(record[1:], sizes)

    out = 0
    match next_char:
        case ".":
            out = dot()
        case "#":
            out = pound()
        case "?":
            out = dot() + pound()

    return out


sum_of_all_combinations: int = 0
for line in input_lines:
    record, sizes = line.split()

    sizes = tuple([int(size) for size in sizes.split(",")])

    print(f"Calculating combinations for record '{record}' with sizes {sizes}")

    sum_of_all_combinations += calculate_combinations(record, sizes)

print(f"Sum of all combinations {sum_of_all_combinations}")
