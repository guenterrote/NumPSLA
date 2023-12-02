NMAX = 16
import sys
from collections import defaultdict

fname = sys.argv[1]
NO_MIRROR=0
MIRROR_WITH_FIXPOINT=1
MIRROR_WITHOUT_FIXPOINT=2

result = defaultdict(int)

infile = open(fname, "r")


def process(ind,num):
    (n,k,p,t) = ind # ind is a 4-tuple
    assert k%p==0
    q = k//p
    if t==NO_MIRROR:
        group = f"C{q} "
    elif t==MIRROR_WITH_FIXPOINT:
        if k%2 == 1:
            group = f"D{q}ve" # implied
            group = f"D{q} "
        else:
            if (k//q)%2 == 1:
                group = f"D{q}vv/ee" # implied
                group = f"D{q} "
            else:
                group = f"D{q}v"
    elif t==MIRROR_WITHOUT_FIXPOINT:
        assert (k//q)%2 == 0
        group = f"D{q}e"
    else:
        assert 0
    index = (n,k,group,q,t)
    result[index] += num


for line in infile:
    if line[0]=="T":
        numbers = [int(x) for x in line[2:].split()]
        NUM = numbers[-1]
        KEYS = tuple(numbers[:-1])
        process(KEYS[:4],NUM) # take only 4 parameters; rest is ignored
    elif line.startswith("EOF"):
        break
    elif line[0]=="P":
        print("This file contains partial results. Aggregate first.")
        print(line)
        exit(1)
else:
    print("file without EOF marker:", fname)
    exit(1)


def satisfies(value,condition):
    return (condition is None or value==condition or
            (type(condition) is not int and value in condition))
def get(points=None, hull=None, period=None, mirror=None):
    res = {}
    def ok(x):
        (n,k,group,q,t) = x
        return (satisfies(n,points) and satisfies(k,hull)
                and satisfies(q,period) and satisfies(t,mirror))
    return sum(num for x,num in result.items() if ok(x))

def ranges2(tab):
    xmin = min(x for x,y in tab)
    xmax = max(x for x,y in tab)
    ymin = min(y for x,y in tab)
    ymax = max(y for x,y in tab)
    return range(xmin,xmax+1),range(ymin,ymax+1)

krange=prange=nrange=range(NMAX+1)
trange=range(3)

def numfmt(num):
    return split3(str(num))

def split3(s):
    if len(s)<=3: return s
    return split3(s[:-3])+"."+s[-3:]

def printtab2(tab):
    r1,r2 = ranges2( tab)
    print(end="  : ")
    for y in r2:
        print(y, end=", ")
    print()
    for x in r1:
        line = [tab.get((x,y),0) for y in r2]
        while line and line[-1]==0: del line[-1]
        print("%2d: "%x +
              ", ".join( "--" if val==0 else numfmt(val)
                         for val in line))


tab_nh = {(n,k):num for n in nrange
          for k in krange for num in (get(points=n,hull=k),) if num}
totk = {n:sum(num*k for k in krange for num in (get(points=n,hull=k),))
        for n in nrange}
total = {n:num for n in nrange for num in (get(points=n),) if num}


print("number of hull edges:")
printtab2(tab_nh)
print()
for n in sorted(total):
    print("n=%2d total =%15s   avg. hull size =%12.9f" %
          (n,numfmt(total[n]),totk[n]/total[n]))

tab_nh = {(n,k):num for n in nrange
          for k in krange for num in (get(points=n,hull=k,mirror=MIRROR_WITH_FIXPOINT),) if num}
print("\nmirrorsymmetric with fixpoint on the boundary: number of hull edges:")
printtab2(tab_nh)
tab_nh = {(n,k):num for n in nrange
          for k in krange for num in (get(points=n,hull=k,mirror=MIRROR_WITHOUT_FIXPOINT),) if num}
print("\nmirrorsymmetric without fixpoint on the boundary: number of hull edges:")
printtab2(tab_nh)


tab_nkp = {(i,j,k):num
          for i in nrange
          for j in krange
          for k in prange
          for num in (get(points=i,hull=j,period=k),) if num}

print("\norder of rotational symmetry:")
tab_nq = defaultdict(int)
for (n,k,q),num in tab_nkp.items():
    tab_nq[n,q] += num

for (n,q) in tab_nq:
    assert n%q in (0,1)
printtab2(tab_nq)

print("\nA006246, number of oriented AOTs:")
for n in nrange:
     val = get(points=n) + get(points=n,mirror=NO_MIRROR)
     # AOTs with t==NO_MIRROR are counted twice
     if val:
         print("%2d:%21s"%(n,numfmt(val))) 
