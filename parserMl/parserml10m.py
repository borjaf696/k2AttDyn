##Borja :)
import os
import collections

pathml10m = "/home/borja/Escritorio/Datasets/Movielens/ml-10M100K/"
nodos = ['Genre','Movie','User']
edges = ['movieGenre','rating','tag']
pathOutPut = "out/ml10m2/ml10m"
attsEdges = [[0,0,0],[2,1,0],[2,0,1]]
attsNodes = [[0,2,0],[0,0,2],[2,0,0]]
attVals = []
genreDict2 = collections.OrderedDict()
ratingsDict = dict()
tagsDict = dict()
userDict = []
movieDict = collections.OrderedDict()
users = range(71567)
userOrderedDict = collections.OrderedDict()
genreDict = ['Action','Adventure','Animation','Children','Comedy','Crime','Documentary','Drama','IMAX',
             'Fantasy','Film-Noir','Horror','Musical','Mystery','Romance','Sci-Fi','Thriller','War','Western',
             '(no genres listed)']
nodestyp = [len(genreDict)]
nodestyp2 = [len(genreDict)]
ends = [".nodes",".edges"]
ends2 = [".typ",".val",".att",".lnk"]

if __name__=="__main__":
    contEdge = 0
    with open(pathml10m+'movies.dat','r') as f:
        cont = 0
        for line in f.readlines():
            parts = line.strip().split("::")
            for i in parts[2].split("|"):
                if (parts[0] not in movieDict):
                    movieDict[parts[0]] = [(cont+nodestyp[0],parts[1],genreDict.index(i))]
                    genreDict2[contEdge] = (len(genreDict)+cont,genreDict.index(i))
                    contEdge = contEdge + 1
                else:
                    movieDict[parts[0]].append((cont+nodestyp[0],parts[1],genreDict.index(i)))
                    genreDict2[contEdge] = (len(genreDict) + cont, genreDict.index(i))
                    contEdge = contEdge + 1
            cont = cont + 1
    print(contEdge)
    attVals.append(len(genreDict2))
    nodestyp2.append(len(movieDict))
    nodestyp.append(len(movieDict)+nodestyp[0])
    with open(pathml10m+'ratings.dat','r') as f:
        cont = 0
        for line in f.readlines():
            if contEdge % 100000 == 0:
                print(contEdge)
            parts = line.strip().split('::')
            genreDict2[contEdge] = (nodestyp[1]+int(parts[0]),movieDict[parts[1]][0][0],parts[3],parts[2])
            contEdge = contEdge+1
            if contEdge == 500000:
                break
    print("End ratings")

    attVals.append(contEdge-attVals[0]-1)
    with open(pathml10m+'tags.dat','r') as f:
        cont = 0
        for line in f.readlines():
            parts = line.strip().split('::')
            if (parts[0] not in userDict):
                userDict.append(parts[0])
            genreDict2[contEdge] = (nodestyp[1] + int(parts[0]), movieDict[parts[1]][0][0], parts[3], parts[2])
            contEdge = contEdge + 1
    nodestyp2.append(len(users))
    pivote = 2
    while pivote < sum(nodestyp2):
        pivote = pivote * 2
    print(pivote)
    attVals.append(contEdge-attVals[0]-attVals[1])
    print("Writting")
    with open(pathOutPut+ends[0]+ends2[0], 'w') as f:
        for i,j in enumerate(nodos):
            f.write(j+'\t'+str(nodestyp2[i])+'\n')
    with open(pathOutPut+ends[0]+ends2[1],'w') as f:
        cont = 0
        for i in genreDict:
            f.write(str(cont) + '\t' + '-'+'\t'+i+'\t'+'-'+'\n')
            cont = cont + 1
        for i in movieDict.keys():
            f.write(str(cont)+ '\t' + '-' + '\t' + '-' + '\t' +movieDict[i][0][1]+ '\n')
            cont = cont + 1
        for i in users:
            f.write(str(cont) + '\t' + str(i) + '\t' + '-' + '\t' + '-' + '\n')
            cont = cont + 1
    with open(pathOutPut+ends[0]+ends2[2],'w') as f:
        f.write(str(len(attsNodes[0]))+'\n')
        for i in attsNodes:
            for j in i:
                f.write(str(j)+'\t')
            f.write('\n')
    with open(pathOutPut+ends[1]+ends2[0], 'w') as f:
        for j,i in enumerate(edges):
            f.write(i+'\t'+str(attVals[j])+'\n')
    with open(pathOutPut+ends[1]+ends2[1],'w') as f:
        pivot = 0
        accum = 0
        for j,i in enumerate(genreDict2.keys()):
            if j == attVals[pivot]+accum:
                accum = accum + attVals[pivot]
                pivot = pivot + 1
            if pivot == 0:
                f.write(str(j)+'\t'+'-'+'\t'+'-'+'\t'+'-'+'\n')
            if pivot == 1:
                f.write(str(j)+'\t'+str(genreDict2[i][2])+'\t'+str(genreDict2[i][3]).strip()+'\t'+'-'+'\n')
            if pivot == 2:
                f.write(str(j) + '\t' + str(genreDict2[i][2]) + '\t' +'-' + '\t' +  str(genreDict2[i][3]).strip() + '\n')
    with open(pathOutPut+ends[1]+ends2[2],'w') as f:
        f.write(str(len(attsEdges[0])) + '\n')
        for i in attsEdges:
            for j in i:
                f.write(str(j) + '\t')
            f.write('\n')
    with open(pathOutPut+ends[1]+ends2[3],'w')  as f:
        for i in genreDict2.keys():
            if genreDict2[i][0] not in userOrderedDict:
                userOrderedDict[genreDict2[i][0]] = [(i,str(genreDict2[i][1]))]
            else:
                userOrderedDict[genreDict2[i][0]].append((i,str(genreDict2[i][1])))
        '''for j,i in enumerate(genreDict2.keys()):
            f.write(str(i) + '\t' + str(genreDict2[i][0]) + '\t' + str(genreDict2[i][1]) + '\n')'''
        a = collections.OrderedDict(sorted(userOrderedDict.items()))
        vals = [(pivote/2,pivote/2),(pivote/2,pivote),(pivote,pivote/2),(pivote,pivote)]
        for val in vals:
            for i in a.keys():
                if (i < val[0]):
                    for j in a[i]:
                        if (float(j[1]) < val[1]):
                            f.write(str(j[0]) + '\t' + str(i) + '\t' + str(j[1]) + '\n')
                            a[i].remove(j)
