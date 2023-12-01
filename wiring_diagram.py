def print_wiring_diagram(n,SUCC, ipe=False):
    # ipe=False: ASCII, horizontal
    # ipe=True: wiring diagram with smooth curves, written to an IPE-file
    # Each wiring diagram occupies a separate page
  
    next_crossing = [0]+[SUCC[j+1,0] for j in range(n)]
                                # current crossing on each line
    # crossing $\#0$ with line 0 ``at $\infty$'' is not considered.
    
    line_at=list(range(1,n+1)) #which line is on the $p$-th track, $0\le p<n$
    # tracks are numbered $p=0\ldots n-1$ from top to bottom.
    
    current_column=[1]*(n+1) # how far has line $i$ been drawn so far

    # maintain a stack "crossings" of available crossings
    # $p\in$ crossings means that tracks $p$ and $p+1$ are ready to cross
    crossings = [p for p in range(n-1)
                 for i,j in [(line_at[p], line_at[p+1])]
                 if i<j and next_crossing[i]>i and 0<next_crossing[j]<j]
    # Line i wants to cross down and line j wants to cross up.
    # (In this case, we must actually have next_crossing[i]==j and next_crossing[j]==i.)
    
    if ipe:
        Paths = [[f"0 {i-1.5} m"] for i in range(n+1)] # Paths[0] is not used
    else:
        Tracks = [" "] * (2*n-1)
        for i in range(1,n+1):
            Tracks[2*i-2] += code(i)
        intermediate_length =[0]*(n-1) # length of intermediate rows between the tracks
    
    n_crossings = 0;
    while crossings:
        n_crossings+=1
        p = y = crossings.pop()
        i = line_at[p];
        j = line_at[p+1];
        column = x = max(current_column[i], current_column[j])

        # DRAW the crossing
        if ipe:
            if current_column[i]!=x or x==1:
                Paths[i].append(f"{x-0.5} {y-0.5} l")
            Paths[i].append(f"{x} {y-0.5}\n{x} {y+0.5}\n{x+0.5} {y+0.5} c")
            if current_column[j]!=x or x==1:
                Paths[j].append(f"{x-0.5} {y+0.5} l")
            Paths[j].append(f"{x} {y+0.5}\n{x} {y-0.5}\n{x+0.5} {y-0.5} c")
        else:
            Tracks[2*p] +=   ("-"+code(i))*(x-current_column[i])+" "+code(j)
            Tracks[2*p+2] += ("-"+code(j))*(x-current_column[j])+" "+code(i)
            Tracks[2*p+1] += " "*(2*(x-intermediate_length[p])-1) + "X"
            intermediate_length[p] = x
            
        # update the data structures to CARRY OUT the crossing
        current_column[i] = current_column[j] = column+1
        next_crossing[i] = SUCC[i,next_crossing[i]];
        next_crossing[j] = SUCC[j,next_crossing[j]];
        line_at[p] = j;
        line_at[p+1] = i;

        # discover new crossings:
        if p>0:
            jj = line_at[p-1]
            if jj<j and next_crossing[jj]>jj and 0<next_crossing[j]<j:
                crossings.append(p-1)
        if p<n-2:
            ii = line_at[p+2]
            if i<ii and next_crossing[i]>i and 0<next_crossing[ii]<ii:
                crossings.append(p+1)

        
    assert(n_crossings*2 == n*(n-1))
    width = max(current_column)
    if ipe:
        # right boundary
        for i in range(1,n+1):
            Paths[i].append(f"{width} {n-i-0.5} l")
        draw_ipe(n,Paths,width)
    else:
        for p in range(n):
            i = line_at[p]
            Tracks[2*p] += ("-"+code(i))*(width-current_column[i])
        for t in Tracks:
            print(t)
        print("=========")
                    
from ipestart import ipestart

def code(i):
    if i<10: return str(i)
    return chr(ord('A')-10+i)

def IPE_start(filename="wire.ipe"):        
    global WRITE_IPE
    global ipefile
    WRITE_IPE = True
    ipefile = open(filename,"w")
    ipefile.write(ipestart)
        
def draw_ipe(n,Paths,width):
    if not WRITE_IPE:
        IPE_start()
        
    ipefile.write("<page>\n")
    ipefile.write(f'<group matrix="20 0 0 -20 32 {20*n+12}">\n')
      # turn upside down. Line 1 has the HIGHEST coordinates
    ipefile.write(f'<path stroke="black">\n0 -1 m\n{width} -1 l\n'
                  f'{width} {n-1} l\n0 {n-1} l\nh\n</path>\n')  # box       
    for P in Paths[1:]:
        ipefile.write('<path stroke="black">\n'
                      + "\n".join(P) + "\n</path>\n")
    ipefile.write("</group>\n")
    ipefile.write("</page>\n")
        
def IPE_end():
    if WRITE_IPE:
        ipefile.write("</ipe>\n")
        ipefile.close()

WRITE_IPE = False
    
