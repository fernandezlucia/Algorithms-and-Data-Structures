def solve(i, j):
    if(i == 0):
        return j == 400
    
    if M[i][j+offset] == None:
        sumar = solve(i-1, j+v[i-1])
        restar = solve(i-1, j-v[i-1])
        
        if(sumar):
            VG[i-1][0] = True
        
        if(restar):
            VG[i-1][1] = True

        M[i][j+offset] = sumar or restar
    return M[i][j+offset]


v = [200, 200, 200, 200, 200]
offset = 100000
n = len(v)
VG = [[False, False] for _ in range(n)]
M = [[None for _ in range(2*n*offset)] for _ in range(n+1)]
w = 600

print(solve(n, 0))
print(VG)
aux = []
for t in VG:
    if(t[0] and not t[1]):
        aux.append('+')
    elif(not t[0] and t[1]):
        aux.append('-')
    else:
        aux.append('?')
print(aux)