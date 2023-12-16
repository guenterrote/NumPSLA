# The python version of NumPSLA
from wiring_diagram import print_wiring_diagram, IPE_end

def LINK(j, k1,k2): # make crossing with k and k adjacent on line j
    SUCC[j,k1] = k2;
    PRED[j,k2] = k1;

class Done(Exception):
    pass
    
def Process_PSLA(n): # insert your procedure here
    global target
    if mode=="ENUMERATE":
        accession_number = f" AN#{countPSLA[n]}"
    else:
        accession_number = ""
    print(f"n={n}"+accession_number, "DD="+".".join(str(x) for x in localCountPSLA[3:n+1]))
    #print_wiring_diagram(n,SUCC)
    if localCountPSLA[3:n+1]==target:
        print_wiring_diagram(n,SUCC, ipe=IPE)
        if mode == "TARGET*":
            try:
                target = next_target()
            except StopIteration:
                raise Done
        else:
            raise Done
def recursive_generate_PSLA(entering_edge, k_right, n):
    j = entering_edge;
    jplus = k_right;
    while jplus>j: # find right vertex of the cell F
        jplusold = jplus;
        jplus = SUCC[jplus,j];
        j = jplusold;

    if (jplus==0): # F is unbounded
        if (j==n-1): # F is the top face.
            LINK(n,entering_edge,0);    # complete the insertion of line n
            countPSLA[n]+=1
            localCountPSLA[n]+=1
            if mode!="ENUMERATE" and localCountPSLA[3:n+1]>target[:n-2]:
                print("target",target,"not found.")
                exit(0)            
            if mode=="ENUMERATE" or localCountPSLA[3:n+1]==target[:n-2]:
                Process_PSLA(n)
                if (n<n_max):
                    localCountPSLA[n+1]=0 # reset child counter
                    recursive_generate_PSLA_start(n+1) # thread the next pseudoline
            return;
        else: # jump to the upper bounding ray of F */
            jplus=j+1; j = 0;
    while (True):
        # scan the upper edges of F from right to left and try them out.
        k_right = j;
        j = jplus;
        k_left = jplus = PRED[j,k_right];
        LINK(j,k_left,n); # prepare for the recursive call
        LINK(j,n,k_right);
        LINK(n,entering_edge,j);
        
        recursive_generate_PSLA(j, k_right, n); # enter the recursion */
        
        LINK(j,k_left,k_right); # undo the changes
        if jplus <= j: break
        #terminate at left endpoint of the face F or at unbounded ray (jplus=0)

    return;

def recursive_generate_PSLA_start(n):
    LINK(0, n-1,n); # insert line n on line 0
    LINK(0, n,1);
    recursive_generate_PSLA(0, 0, n);
    LINK(0, n-1,1); # undo the insertion of line n


def next_target():
    target = [int(x) for x in next(targets_file).split(".")]
    # trailing "\n" is ignored
    if len(target) > n_max-2:
        print("target", target, "too long. n_max =",n_max)
        exit(1)
    return target
    
if __name__ == "__main__":
    mode = "ENUMERATE"
    n_max = 6 # default
    target = ""
    IPE = False
    import sys
    if len(sys.argv)>=2:
        if sys.argv[1][0]=="-" and sys.argv[1] != "-t":
            print(f"Usage: python3 {sys.argv[0]} [n | -t targets-file | d3.d4.d5...dn ] [-ipe]")
            exit(0)
        if "." in sys.argv[1]:
            mode = "TARGET1"
            target = [int(x) for x in sys.argv[1].split(".")]
            n_max = len(target)+3
        elif len(sys.argv)>=2 and sys.argv[1] == "-t":
            mode = "TARGET*"
            n_max = 999
            targets_file = open(sys.argv[2],"r")
            # the targets must appear in sorted order                
            target = next_target()
        else:
            n_max = int(sys.argv[1])
        IPE = sys.argv[-1]=="-ipe"
    assert n_max>=2

    # Start the generation: 
    PRED = {}; SUCC = {} 
    LINK(1, 0,0);
    LINK(0, 1,1);
  
    countPSLA = [0]*(n_max+1)
    localCountPSLA = [0]*(n_max+1)
    try: 
        recursive_generate_PSLA_start(2);
    except Done:
        pass
    if mode=="ENUMERATE":
        print (countPSLA[2:])

    if IPE:
        print('Ipe-file "wire.ipe" written.')
    IPE_end() # finish and close ipe-file, in case it was used.
  
