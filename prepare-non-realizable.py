import sys
f_all = open(sys.argv[1]) # all AOTs, sorted by fingerprint

f_realizable = open(sys.argv[2])
# realizable AOTs from the Order-type database, sorted by fingerprint

f_nonr = open(sys.argv[3],"w")
# OUTPUT: difference of the two files. lists only the Dewey decimal notations

def get1():
    line1 = ''
    while not ":" in line1:
        try:
            line1 = next(f_all)
        except StopIteration:
            return 0
    return line1
def get2():
    line = ''
    while not line.endswith(":\n"):
        try:
            line = next(f_realizable)
        except StopIteration:
            return 0
    return line

line1 = get1()
line2 = get2()
keylength = len(line2)-2
print("first key", line1[:keylength])
while line1 and line2:
    key1 = line1[:keylength]
    key2 = line2[:keylength]
#    print(key1,key2)
    if key1 != key2: # in file1 but not in file2
        f_nonr.write(line1[keylength+1:])
    else:
        line2 = get2()
    line1 = get1()
f_nonr.close()
