import sys
f_short = open(sys.argv[1])
# exclude-file with shorter keys, sorted by Dewey decimal notations

f_long = open(sys.argv[2])
# exclude-file with longer keys, sorted by Dewey decimal notations

f_merged = open(sys.argv[3],"w")
# OUTPUT: merged output, prefix-free

def get(f):
    try:
        line = next(f)
    except StopIteration:
        return [999] # termination sentinel
    return [int(x) for x in line.split(".")] # list of numbers

key1 = get(f_short)
key2 = get(f_long)
print("first key", key1)
while not key1 == key2 == [999]:
    if key2[:len(key1)] == key1:
        key2 = get(f_long) # ignore key2
    elif key1<key2:
        f_merged.write(".".join(str(x) for x in key1)+"\n")
        key1 = get(f_short)
    else:
        f_merged.write(".".join(str(x) for x in key2)+"\n")
        key2 = get(f_long)
f_merged.close()
