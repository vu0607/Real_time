import math
def MinOp(N):
    if (N <= 1):
        return N;
 
    # Stores count of
    # bits in N
    bit = (int)(math.log(N) / math.log(2)) + 1
 
    # Recurrence relation
    return ((1 << bit) - 1) - MinOp(N - (1 << (bit - 1)))
 
print(MinOp(5))