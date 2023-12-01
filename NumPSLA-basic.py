"The basic framework of NumPSLA, python version"
import sys
# from wiring_diagram import print_wiring_diagram #, IPE_end

def LINK(j, k1,k2): # make crossings with k1 and k2 adjacent on line j
    SUCC[j,k1] = k2
    PRED[j,k2] = k1
    
def Process_PSLA(n): # insert your code for processing the PSLA here
    countPSLA[n]+=1
    # print(n,  countPSLA[n], ".".join(str(x) for x in localCountPSLA[3:n+1]))
    # print_wiring_diagram(n, SUCC, ipe=False)
                
def recursive_generate_PSLA(entering_edge, k_right, n):
    j = entering_edge;
    jplus = k_right;
    while jplus>j: # find right vertex of the current cell F
        jplus_old = jplus;
        jplus = SUCC[jplus,j];
        j = jplus_old;
    # the right vertex is at the crossing of j and jplus
    if (jplus==0): # F is unbounded
        if (j==n-1): # F is the top face.
            LINK(n, entering_edge,0) # complete the insertion of line n
            localCountPSLA[n]+=1
            Process_PSLA(n)
            if (n<n_max):
                localCountPSLA[n+1]=0 # reset child counter
                recursive_generate_PSLA_start(n+1) # thread the next pseudoline
            return;
        else: # jump to the upper bounding ray of F
            jplus=j+1; j = 0;
    while (True):
        # scan the upper edges of F from right to left and try them out.
        k_right = j;
        j = exiting_edge = jplus;
        k_left = jplus = PRED[j,k_right];
        LINK(exiting_edge, k_left,n); # prepare for the recursive call
        LINK(exiting_edge, n,k_right);
        LINK(n, entering_edge,exiting_edge);
        
        recursive_generate_PSLA(exiting_edge, k_right, n) # enter the recursion
        
        LINK(exiting_edge, k_left,k_right); # undo the changes
        if jplus <= j: return
        #terminate at left endpoint of the face F or at unbounded ray (jplus=0)

def recursive_generate_PSLA_start(n):
    LINK(0, n-1,n); # insert line n on line 0
    LINK(0, n,1);
    recursive_generate_PSLA(0, 0, n);
    LINK(0, n-1,1); # undo the insertion of line n
          
n_max = int(sys.argv[1])

# Start the generation proper: 
PRED = {}; SUCC = {} 
LINK(1, 0,0);
LINK(0, 1,1);
  
countPSLA = [0]*(n_max+1)
localCountPSLA = [0]*(n_max+1)
recursive_generate_PSLA_start(2)
# IPE_end() # finish and close ipe-file, in case it was used.
print ("Number of PSLAs:", *countPSLA[2:])
