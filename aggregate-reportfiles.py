import sys
from collections import defaultdict

namepattern = "halving-results-11-S8-part_%d_of_100.txt"
N = 100
#namepattern = sys.argv[1]
#N = int(sys.argv[2])

result = defaultdict(int)
for num in range(N):
    fname = namepattern % num
    infile = open(fname, "r")
    head = next(infile)
    
    patt = f"part {num} of {N}"
    headerlines = [head[:head.index(patt)]+f"aggregated from {N} parts"]

    for line in infile:
        if line[0] in "TP":
            numbers = [int(x) for x in line[2:].split()]
            NUM = numbers[-1]
            KEYS = tuple(numbers[:-1])
            if line[0] == "T":
                if KEYS in result:
                    assert result[KEYS] == NUM
                else:
                    result[KEYS] = NUM
            else:
                result[KEYS] += NUM
        elif line.startswith("EOF"):
            break
        else:
            headerlines.append(line.rstrip())
    else:
        print("file without EOF marker:", fname)
        exit(1)

for l in headerlines:
    print(l)
for k,v in sorted(result.items()):
    print("T",*k,"",v)
print("EOF")
