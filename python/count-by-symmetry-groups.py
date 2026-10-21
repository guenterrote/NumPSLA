# Count symmetric AOTs by symmetry group from a NumPSLA report file.
# Report lines: "T n hull period mirror count"; rotation order k = hull/period,
# group D_k if mirror-symmetric (mirror type 1 or 2), else C_k.
import sys, collections
for fn in sys.argv[1:]:
    c = collections.Counter()
    tot = collections.Counter()
    for l in open(fn):
        p = l.split()
        if not p or p[0] != 'T': continue
        n, h, per, m, cnt = map(int, p[1:])
        tot[n] += cnt
        c[(n, (not m, h//per), ('D' if m else 'C') + str(h // per))] += cnt
    print(fn)
    n_old = None
    for (n, _, g), v in sorted(c.items()):
        if n != n_old:
            print(f"*n={n:2d} total={tot[n]}")
            n_old = n
        print(f"  n={n:2d} {g:4s} {v}")
