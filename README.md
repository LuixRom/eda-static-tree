# Cache-Oblivious Static Tree vs BST — Benchmark de Búsquedas
 
Comparación experimental del rendimiento en búsquedas sobre enteros de 32 bits entre un **árbol binario de búsqueda con punteros (BST)** y un **cache-oblivious static tree con layout van Emde Boas (vEB)**.
 
---
 
## Resultados
 
| Experimento | Static Tree (ms) | BST (ms) | Diferencia (ms) | Speedup |
|:-----------:|:----------------:|:--------:|:---------------:|:-------:|
| 1           | 185              | 227      | 42              | 1.23x   |
| 2           | 187              | 246      | 59              | 1.32x   |
| 3           | 194              | 247      | 53              | 1.27x   |
| 4           | 187              | 234      | 47              | 1.25x   |
| 5           | 192              | 232      | 40              | 1.21x   |
| **Promedio**| **189.0**        | **237.2**| **48.2**        | **1.25x**|
 
> El static tree fue **~20% más rápido** que el BST en todos los experimentos.
 
---
 
## Metodología
 
- **Elementos:** 1,000,000 enteros de 32 bits
- **Consultas por experimento:** 1,000,000 (aleatorias)
- **Número de experimentos:** 5
Para cada experimento:
1. Se construyó el static tree a partir de los elementos **ordenados**.
2. Se construyó el BST insertando los mismos elementos en **orden aleatorio**.
3. Se generaron consultas aleatorias.
4. Se midió el tiempo total de búsqueda en ambas estructuras.
---
 
## Complejidad
 
| Estructura         | Construcción           | Búsqueda          |
|--------------------|------------------------|-------------------|
| BST con punteros   | O(n log n) esperado    | O(log n) esperado |
| Static tree (vEB)  | O(n) sobre arreglo ordenado | O(log n)     |
 
---
 
## Análisis
 
El cache-oblivious static tree superó al BST en todos los experimentos. La razón principal es la **localidad de memoria**:
 
- **BST con punteros:** los nodos están dispersos en memoria. Cada búsqueda puede generar múltiples cache misses al seguir punteros.
- **Layout van Emde Boas:** agrupa recursivamente los nodos cercanos en memoria, mejorando la localidad espacial y reduciendo los cache misses.
Además, el static tree mostró mayor **estabilidad**:
- Static tree: entre **185 y 194 ms**
- BST: entre **227 y 247 ms**
Esto confirma que una mejor organización de memoria puede producir mejoras reales de rendimiento incluso cuando ambas estructuras tienen **complejidad asintótica similar**.
 
---
 
## Hardware
 
Los experimentos se ejecutaron en CLion con compilador local.
 
Para reproducibilidad completa se recomienda documentar:
- Procesador (modelo exacto)
- Tamaño de caché L1, L2 y L3
- Memoria RAM disponible
- Sistema operativo
- Flags de compilación (modo Release, optimizaciones)
---
 
## Autor
 
**Luis Anthony Romero Padilla** — Mayo 2026
