"""
Usage: python3 aggregate-reportfiles.py fileprefix-n-Ssplitlevel-part_%d_of_N.txt N

Aggregates the report-files of a parallel run that was split into N parts,
for example:
  python3 aggregate-reportfiles.py out-11-S8-part_%d_of_100.txt 100
The %d in the name pattern is replaced by the part numbers 0,...,N-1.
The aggregated report is written to standard output.
"""
import sys
from collections import defaultdict

if len(sys.argv) != 3 or "%d" not in sys.argv[1] or not sys.argv[2].isdigit():
    sys.exit(__doc__)
namepattern = sys.argv[1]
N = int(sys.argv[2])

def error(message):
    sys.exit(f"Error: {message} Aborting.")

result = defaultdict(int)
for num in range(N):
    fname = namepattern % num
    try:
        infile = open(fname, "r")
    except OSError as e:
        error(f"cannot open report-file {fname}: {e.strerror}.")
    head = next(infile, "")

    patt = f"part {num} of {N}"
    if patt not in head:
        error(f"{fname} is not the report-file for {patt}.")
    if num == 0:
        headerlines = [head[:head.index(patt)]+f"aggregated from {N} parts"]

    for line in infile:
        if line[0] in "TP":
            numbers = [int(x) for x in line[2:].split()]
            NUM = numbers[-1]
            KEYS = tuple(numbers[:-1])
            if line[0] == "T":
                if KEYS in result:
                    if result[KEYS] != NUM:
                        error(f"{fname}: complete count for {KEYS} differs from other parts.")
                else:
                    result[KEYS] = NUM
            else:
                result[KEYS] += NUM
        elif line.startswith("EOF"):
            break
        elif num == 0:
            headerlines.append(line.rstrip())
    else:
        error(f"file without EOF marker: {fname}")

for l in headerlines:
    print(l)
for k,v in sorted(result.items()):
    print("T",*k,"",v)
print("EOF")
