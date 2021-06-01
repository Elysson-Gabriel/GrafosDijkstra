# convert adjacency matrix to 'digrafo'

f = open("test3.txt", "r")

matrix = []
numeroVertices = 0
numeroArestas = 0
arestas = []

for i in f:
    matrix.append([int(str(x).strip()) for x in i.replace(',\n', '').split(',')])

numeroVertices = len(matrix)

f.close()


f = open("test3.txt", "w+")

for i, vertice in enumerate(matrix):
    for j, aresta in enumerate(vertice):
        if aresta:
            numeroArestas += 1
            arestas.append([i + 1, j + 1, aresta])

f.write(f"{numeroVertices} {numeroArestas}\n")
for i in arestas:
    f.write(f"{i[0]} {i[1]} {i[2]}\n")

f.close()
