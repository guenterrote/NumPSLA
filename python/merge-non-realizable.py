"""
Usage: python3 merge-non-realizable.py short-file long-file output-file

Merges two exclude-files, each sorted lexicographically by the decimal codes
(as numbers) and prefix-free.
Codes that have a prefix in the other file are dropped,
so that the output is again sorted and prefix-free.

The program aborts with an error message if an input line is not a
decimal code or if an input file is not sorted or not prefix-free.
"""
import sys

if len(sys.argv) != 4:
    sys.exit(__doc__)

def error(message):
    sys.exit(f"Error: {message} Aborting.")

def codes(fname):
    "yield the codes of the file as tuples of numbers, checking the order"
    previous = None
    with open(fname) as f:
        for num, line in enumerate(f, 1):
            line = line.strip()
            if not line:
                continue
            try:
                code = tuple(int(x) for x in line.split("."))
            except ValueError:
                code = ()
            if not code or min(code) < 1 or not all(x.isdigit() for x in line.split(".")):
                error(f"{fname}, line {num}: {line!r} is not a decimal code.")
            if previous is not None:
                if code == previous:
                    error(f"{fname}, line {num}: duplicate code {line}.")
                if code[:len(previous)] == previous:
                    error(f"{fname}, line {num}: the previous code is a prefix of {line}.")
                if code < previous:
                    error(f"{fname}, line {num}: file is not sorted.")
            previous = code
            yield code

def is_prefix(a, b):
    return b[:len(a)] == a

short_codes = codes(sys.argv[1])
long_codes = codes(sys.argv[2])
key1 = next(short_codes, None)
key2 = next(long_codes, None)
dropped = written = 0
with open(sys.argv[3], "w") as f_merged:
    while key1 is not None or key2 is not None:
        if key1 is not None and key2 is not None and is_prefix(key1, key2):
            key2 = next(long_codes, None) # drop key2
            dropped += 1
        elif key1 is not None and key2 is not None and is_prefix(key2, key1):
            key1 = next(short_codes, None) # drop key1
            dropped += 1
        elif key2 is None or (key1 is not None and key1 < key2):
            f_merged.write(".".join(map(str, key1)) + "\n")
            key1 = next(short_codes, None)
            written += 1
        else:
            f_merged.write(".".join(map(str, key2)) + "\n")
            key2 = next(long_codes, None)
            written += 1

print(f"{written} codes written to {sys.argv[3]}, {dropped} codes with a prefix dropped.")
