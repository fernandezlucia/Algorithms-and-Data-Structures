def choris(i, j, k):
    if k < 0:
        return float('inf')
    if(i == n):
        if(k != 0):
            return float('inf')
        else:
            return calcularCosto(j)

    if(M[i][j][k] != -1):
        return M[i][j][k]        

    poner = choris(i+1, i, k-1) + calcularCosto2(j, i, j)
    noPoner = choris(i+1, j, k)

    if(poner <= noPoner):
        decisiones[i][j][k] = 1
    else:
        decisiones[i][j][k] = 0
        

    M[i][j][k] = min(poner, noPoner)

    return M[i][j][k]

def reconstruirSolucion():
    i, j, k = 1, 0, kG
    proveedurias = []

    while i < n:
        if decisiones[i][j][k] == 1:
            proveedurias.append(puestos[i])
            j = i
            k -= 1

        i += 1

    return proveedurias

def calcularCosto(j):
    acum = 0
    for i in range(j, n):
        distanciaActual = abs(puestos[i]-puestos[j])
        acum += distanciaActual
    return acum

def calcularCosto2(l, r, p): 
    acum = 0
    for i in range(l, r+1):
        distanciaActual = abs(puestos[i]-puestos[p])
        distanciaANueva = abs(puestos[i]-puestos[r])
        if(distanciaActual < distanciaANueva): 
            acum += distanciaActual
        else:
            acum += distanciaANueva
    return acum

puestos = [-10000000000, 1, 5, 15, 20]
n = len(puestos)
kG = 2
M = [[[-1 for _ in range(kG+1)] for _ in range(n+1)] for _ in range(n+1)]
decisiones = [[[0 for _ in range(kG+1)] for _ in range(n+1)] for _ in range(n+1)]

print(choris(1, 0, kG))
print(reconstruirSolucion())