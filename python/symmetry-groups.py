# Count symmetric AOTs by symmetry group from a NumPSLA report file.
# Report lines: "T n hull period mirror count"; rotation order k = hull/period,
# group D_k if mirror-symmetric (mirror type 1 or 2), else C_k. C_1 (no symmetry) is omitted.
import sys, collections
for fn in sys.argv[1:]:
    c = collections.Counter()
    for l in open(fn):
        p = l.split()
        if not p or p[0] != 'T': continue
        n, h, per, m, cnt = map(int, p[1:])
        c[(n, ('D' if m else 'C') + str(h // per))] += cnt
    print(fn)
    for (n, g), v in sorted(c.items()):
        if g != 'C1': print(f"  n={n:2d} {g:4s} {v}")
