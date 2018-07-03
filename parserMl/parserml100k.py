##Borja :)
import os

pathml100k = "/home/borja/Escritorio/Datasets/ml/ml-100k/u."
pathOutPut = "out/ml100k/ml100k"
ends = [".nodes",".edges"]
ends2 = [".typ",".val",".att",".lnk"]
attNode = ['1 0 0 0 0 0 0 0','0 1 2 1 0 0 0 0','0 0 0 0 2 2 2 1']
attVect = [[0],[1,2,3],[4,5,6,7]]
attLine = [[0],[4,2,1],[1,2,3,4]]
attTotal = 8
append_write = ['w']*3
nodesDict = dict()
itemsDict = dict()
genreDict = dict()
countDict = dict()
for i in range(0,3):
    if os.path.exists(pathOutPut + ends[0] + ends2[i]):
        append_write[i] = 'a'

if __name__=="__main__":
    nodes = ['genre','item','user']
    with open(pathOutPut+ends[0]+ends2[2],append_write[2]) as f:
        f.write(str(attTotal)+'\n')
        for i in attNode:
            f.write(i+'\n')
    cont,lastCont = 0,0
    for j,i in enumerate(nodes):
        print pathml100k+i
        with open(pathml100k+i,'r') as f:
            for line in f.readlines():
                lineVect = line.strip().split('|')
                nodesDict[lineVect[0]+i] = cont
                if os.path.exists(pathOutPut + ends[0] + ends2[1]):
                    append_write[1] = 'a'
                if len(lineVect) >= len(attLine[j]):
                    with open(pathOutPut+ends[0]+ends2[1],append_write[1]) as f2:
                        f2.write(str(cont)+"\t")
                        cont2 = 0
                        for z in range(max(len(lineVect),attTotal)):
                            if z in attVect[j]:
                                if (lineVect[attLine[j][cont2]] != ''):
                                    v = lineVect[attLine[j][cont2]]
                                    f2.write(v+"\t")
                                else:
                                    f2.write("NONE\t");
                                cont2 = cont2 + 1
                            elif z < attTotal:
                                f2.write('-\t')
                            if i == 'item':
                                if z > 4 and int(lineVect[z]) == 1:
                                    if lineVect[0] in itemsDict.keys():
                                        itemsDict[lineVect[0]].append(z-5)
                                    else:
                                        itemsDict[lineVect[0]] = [z-5]
                                    if z-5 not in countDict.keys():
                                        countDict[z-5] = 0
                                    else:
                                        countDict[z-5] = countDict[z-5] + 1
                        f2.write('\n')
                cont = cont + 1
            if os.path.exists(pathOutPut+ends[0]+ends2[0]):
                append_write[0] = 'a'
            with open(pathOutPut+ends[0]+ends2[0],append_write[0]) as f2:
                f2.write(i+"\t"+str(cont-lastCont)+'\n')
                lastCont = cont
    numtotalEdgesGenre = sum(countDict.values())
    chain = ['genre','rating']
    with open(pathml100k+'data','r') as f:
        lines = f.readlines()
        for i in range(3):
            if os.path.exists(pathOutPut + ends[1] + ends2[2]):
                append_write[0] = 'a'
            else:
                append_write[0] = 'w'
            with open(pathOutPut + ends[1] + ends2[2], append_write[0]) as f3:
                if i == 0:
                    f3.write(str(2)+"\n");
                if i == 1:
                    f3.write("0\t0\n")
                if i == 2:
                    f3.write("2\t1")
        for i in chain:
            if os.path.exists(pathOutPut + ends[1] + ends2[0]):
                append_write[0] = 'a'
            else:
                append_write[0] = 'w'
            with open(pathOutPut+ends[1]+ends2[0],append_write[0]) as f2:
                if i == 'genre':
                    f2.write(i+"\t"+str(numtotalEdgesGenre)+"\n")
                else:
                    f2.write(i+"\t"+str(len(lines)))
        cont1 = 0
        cont = 0
        with open(pathOutPut+ends[1]+ends2[1],'w') as f2:
            with open(pathOutPut+ends[1]+ends2[3],'w') as f3:
                for i in range(numtotalEdgesGenre):
                    f2.write(str(cont1)+"\t-\t-\t\n")
                    cont1 = cont1 + 1
                for i in itemsDict.keys():
                    for j in itemsDict[i]:
                        f3.write(str(cont)+"\t"+str(nodesDict[i+"item"])+"\t"+str(j)+"\n")
                        cont = cont + 1
                for i,line in enumerate(lines):
                    lineVect = line.strip().split('\t')
                    numNode1 = nodesDict[lineVect[0]+'user']
                    numNode2 = nodesDict[lineVect[1]+'item']
                    rating = lineVect[2]
                    date = lineVect[3]
                    f2.write(str(cont1)+"\t"+rating+"\t"+date+"\n")
                    f3.write(str(cont)+"\t"+str(numNode1)+"\t"+str(numNode2)+"\n")
                    cont = cont + 1
                    cont1 = cont1 + 1

        print "Fin parser movielens"
