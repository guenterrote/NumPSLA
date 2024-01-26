def print_wiring_diagram(n,SUCC, ipe=False, text=None):
    # ipe=False: ASCII, horizontal
    # ipe=True: wiring diagram with smooth curves, written to an IPE-file
    # Each wiring diagram occupies a separate page
  
    next_crossing = [1]+[SUCC[j+1,0] for j in range(n)]
                       # current crossing of the line at track p
    # crossing $\#0$ with line 0 ``at $\infty$'' is not considered.
    
    line_at=list(range(n+1)) #which line is on the $p$-th track, $1\le p\le n$
    # tracks are numbered $p=1\ldots n$ from top to bottom.
    
    current_column=[1]*(n+1) # how far has line $i$ been drawn so far

    if ipe:
        Paths = [[f"0 {i-1.5} m"] for i in range(n+1)] # Paths[0] is not used
    else:
        if text: print(text)
        Tracks = [" "] * (2*n-1)
        for i in range(1,n+1):
            Tracks[2*i-2] += code(i)
        intermediate_length =[0]*n # length of intermediate rows between the tracks
  
    n_crossings = 0;
    p = n
    while True:
        while next_crossing[p]< line_at[p]: # line on track p wants to cross UP.
            p -= 1
        if p==0:
            break
        while True:
            # make the exchange p <-> p+1
            n_crossings+=1
            y = p-1
            i,j = line_at[p:p+2];
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
                Tracks[2*p-2] += ("-"+code(i))*(x-current_column[i])+" "+code(j)
                Tracks[2*p]   += ("-"+code(j))*(x-current_column[j])+" "+code(i)
                Tracks[2*p-1] += " "*(2*(x-intermediate_length[p])-1) + "X"
                intermediate_length[p] = x
            
            # update the data structures to CARRY OUT the crossing
            current_column[i] = current_column[j] = column+1
            next_crossing[p:p+2] = (SUCC[j,next_crossing[p+1]],
                                    SUCC[i,next_crossing[p]])
            line_at[p:p+2] = j,i

            p += 1
            if next_crossing[p]< line_at[p]: # line on track p wants to cross UP.
                break
        p -= 2
        
    assert(n_crossings*2 == n*(n-1))
    width = max(current_column)
    if ipe:
        # right boundary
        for i in range(1,n+1):
            Paths[i].append(f"{width} {n-i-0.5} l")
        draw_ipe(n,Paths,width,text)
    else:
        for p in range(1,n+1):
            i = line_at[p]
            Tracks[2*p-2] += ("-"+code(i))*(width-current_column[i])
        for t in Tracks:
            print(t)
        print("="*(2*width))
        
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
        
def draw_ipe(n,Paths,width,text):
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

    if text:
        ipefile.write('<text transformations="translations" pos="32 16" '
                      'stroke="black" type="label" valign="baseline">'
                      +  text + '</text>\n')   
    ipefile.write("</page>\n")
        
def IPE_end():
    if WRITE_IPE:
        ipefile.write("</ipe>\n")
        ipefile.close()

WRITE_IPE = False
    
