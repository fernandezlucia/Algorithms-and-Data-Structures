def choris(i, S):

    if(i==n):
        return evaluar(S), S
    
    agregar = S.copy()
    agregar.append(puestos[i])

    
    poner_costo, poner_asignacion = choris(i+1, agregar)
    noPoner_costo, noPoner_asignacion = choris(i+1, S)

    if(poner_costo < noPoner_costo):
        return poner_costo, poner_asignacion
    else:
        return noPoner_costo, noPoner_asignacion


def evaluar(provedurias):
    if(len(provedurias) > k):
        return 100000000000
    if(len(provedurias) == 0):
        return 100000000000
    costo = 0
    actual = 0 
    for puesto in puestos:
        distanciaActual = abs(puesto-provedurias[actual])
        if(actual+1 == len(provedurias)):
            siguiente = actual
        else:
            siguiente = actual+1
        distanciaSiguiente = abs(puesto-provedurias[siguiente])

        if(distanciaActual <= distanciaSiguiente):
            costo += distanciaActual
        else:
            costo += distanciaSiguiente
    return costo
            

puestos = [4, 5, 6, 7]
n = len(puestos)
k = 1
S = []
min_global = 0
print(choris(0, S))
