"""
Usage: python3 prepare-non-realizable.py A-sorted DB-sorted output-file

A-sorted:  all AOTs, lines "fingerprint:decimal-code", sorted with LANG=C sort
DB-sorted: realizable AOTs from the order-type database, lines "fingerprint:",
           sorted with LANG=C sort
OUTPUT:    the decimal codes of the AOTs in A-sorted that are not in DB-sorted

Lines that are not of the expected form (such as the informational messages
of the generating program) are skipped and counted.
The program aborts with an error message if the files are not sorted,
if a fingerprint appears twice, if the fingerprints have different lengths,
or if a fingerprint of DB-sorted does not appear in A-sorted.
"""
import sys, re

if len(sys.argv) != 4:
    sys.exit(__doc__)

RECORD_A = re.compile(r"[A-Za-z0-9+-]+:[1-9][0-9]*(\.[1-9][0-9]*)*\n?$")
RECORD_DB = re.compile(r"[A-Za-z0-9+-]+:\n?$")

def error(message):
    sys.exit(f"Error: {message} Aborting.")

def records(fname, pattern):
    "yield (line number, fingerprint, code) for the records of the file"
    previous = None
    skipped = 0
    with open(fname) as f:
        for num, line in enumerate(f, 1):
            if not pattern.match(line):
                skipped += 1
                continue
            key, code = line.rstrip("\n").split(":")
            if previous is not None:
                if len(key) != len(previous):
                    error(f"{fname}, line {num}: fingerprint {key} has a different length.")
                if key == previous:
                    error(f"{fname}, line {num}: duplicate fingerprint {key}.")
                if key < previous:
                    error(f"{fname}, line {num}: file is not sorted (use LANG=C sort).")
            previous = key
            yield num, key, code
    if skipped:
        print(f"{skipped} lines without a record were skipped in {fname}.",
              file=sys.stderr)

all_records = records(sys.argv[1], RECORD_A)
realizable = records(sys.argv[2], RECORD_DB)
count_all = count_nonr = count_realizable = 0
with open(sys.argv[3], "w") as f_nonr:
    rec2 = next(realizable, None)
    for num1, key1, code1 in all_records:
        count_all += 1
        if rec2 is not None and len(rec2[1]) != len(key1):
            error("the fingerprints in the two files have different lengths.")
        if rec2 is not None and rec2[1] < key1:
            error(f"{sys.argv[2]}, line {rec2[0]}: fingerprint {rec2[1]} "
                  f"does not occur in {sys.argv[1]}.")
        if rec2 is not None and rec2[1] == key1:
            count_realizable += 1
            rec2 = next(realizable, None)
        else: # in the first file but not in the second
            f_nonr.write(code1 + "\n")
            count_nonr += 1
    if rec2 is not None:
        error(f"{sys.argv[2]}, line {rec2[0]}: fingerprint {rec2[1]} "
              f"does not occur in {sys.argv[1]}.")

print(f"{count_all} AOTs, {count_realizable} realizable, "
      f"{count_nonr} non-realizable written to {sys.argv[3]}.")
