import sys

# Calcula el costo de servir todos los puestos entre l y r con una proveeduría en pos
def cost(l, r, pos, positions):
    return sum(abs(pos - positions[i]) for i in range(l, r+1))

# Función recursiva top-down
def dp(n, k, positions, memo, parent):
    if k == 0:
        return 0 if n == 0 else sys.maxsize
    
    if n == 0:
        return sys.maxsize

    if memo[n][k] != -1:
        return memo[n][k]

    min_cost = sys.maxsize
    best_m = -1
    best_pos = -1

    for m in range(1, n+1):
        median_pos = positions[m + (n - m)//2 - 1]
        current_cost = dp(m-1, k-1, positions, memo, parent) + cost(m-1, n-1, median_pos, positions)
        if current_cost < min_cost:
            min_cost = current_cost
            best_m = m
            best_pos = median_pos

    memo[n][k] = min_cost
    parent[n][k] = (best_m, best_pos)
    return min_cost

# Función para reconstruir la solución
def reconstruct(n, k, parent):
    if k == 0:
        return []
    m, pos = parent[n][k]
    return reconstruct(m-1, k-1, parent) + [pos]

# Entrada de datos
c = int(input("Número de casos de test: "))
for _ in range(c):
    N, K = map(int, input().split())
    positions = list(map(int, input().split()))
    memo = [[-1 for _ in range(K+1)] for _ in range(N+1)]
    parent = [[(-1, -1) for _ in range(K+1)] for _ in range(N+1)]
    
    # Calculamos el costo mínimo
    min_cost = dp(N, K, positions, memo, parent)
    print(f"Costo mínimo: {min_cost}")
    
    # Reconstruimos e imprimimos la solución
    solution = reconstruct(N, K, parent)
    print("Posiciones de las proveedurías: ", solution)
