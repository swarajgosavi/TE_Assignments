'''
LP-1
Assignment A1 (part1)

Name    : Swaraj Gosavi
Roll no : 31328
Batch   : L3
'''

from mnemonic import *

def pass1(ifname, ofname):

    SymbolTable = {}
    LiteralTable = [[], []]
    PoolTable = [0]
    poolptr = 0
    littbptr = 0
    IC = 0

    infile = open(ifname, "r")
    outfile = open(ofname, "w")
    outfile.close
    outfile = open(ofname, "a")

    Lines = infile.readlines()

    for line in Lines:
        if line[-1] == "\n":
            line = line[:-1].split(" ")
        if line == "END":
            outfile.write(str(MnemonicTab[line]) + "\n")
            if PoolTable[poolptr] >= 0:
                for i in range(PoolTable[poolptr], littbptr):
                    outfile.write(str(IC) + " ")
                    LiteralTable[1][i] = IC
                    IC += 1
                    outfile.write(str(MnemonicTab['DC']) + " " + str(['C', int(LiteralTable[0][i].strip("='"))]) + "\n")
            break

        word_count = 0
        if line[word_count] not in MnemonicTab:
            SymbolTable[line[word_count]] = IC
            word_count += 1

        if line[word_count] == "LTORG":
            if PoolTable[poolptr] >= 0:
                for i in range(PoolTable[poolptr], littbptr):
                    outfile.write(str(IC) + " ")
                    LiteralTable[1][i] = IC
                    IC += 1
                    outfile.write(str(MnemonicTab['DC']) + " " + str(['C', int(LiteralTable[0][i].strip("='"))]) + "\n")
            PoolTable.append(0)
            poolptr += 1
            PoolTable[poolptr] = littbptr

        if line[word_count] == "START":
            IC = int(line[word_count+1])
            outfile.write(str(MnemonicTab[line[word_count]]) + " " + str(["C", int(line[word_count+1])]) + "\n")
            continue

        if line[word_count] == "ORIGIN":
            if '+' in line[word_count + 1]:
                value = line[word_count + 1].split('+')
                IC = SymbolTable[value[0]] + int(value[1])
                outfile.write(str(MnemonicTab[line[word_count]]) + " " + str(['S', list(SymbolTable.keys()).index(value[0]) + 1]) + "+" + str(value[1]) + "\n")
            elif '-' in line[word_count + 1]:
                value = line[word_count + 1].split('-')
                IC = SymbolTable[value[0]] - int(value[1])
                outfile.write(str(MnemonicTab[line[word_count]]) + " " + str(['S', list(SymbolTable.keys()).index(value[0]) + 1]) + "-" + str(value[1]) + "\n")
            else:
                IC = SymbolTable[line[word_count + 1]]
                outfile.write(str(MnemonicTab[line[word_count]]) + " " + str(['S', list(SymbolTable.keys()).index(value[0]) + 1]) + "\n")
            continue

        if line[word_count] == "EQU":
            if '+' in line[word_count + 1]:
                value = line[word_count + 1].split('+')
                SymbolTable[line[word_count - 1]] = SymbolTable[value[0]] + int(value[1])
            elif '-' in line[word_count + 1]:
                value = line[word_count + 1].split('-')
                SymbolTable[line[word_count - 1]] = SymbolTable[value[0]] - int(value[1])
            else:
                SymbolTable[line[word_count - 1]] = SymbolTable[line[word_count + 1]]
            continue

        if line[word_count] in MnemonicTab and MnemonicTab[line[word_count]][0] == "DL":
            SymbolTable[line[word_count - 1]] = IC
            outfile.write(str(IC) + " ")
            IC += int(line[word_count + 1].strip("'"))
            outfile.write(str(MnemonicTab[line[word_count]]) + " " + str(['C', int(line[word_count + 1].strip("'"))]) + "\n")
            continue

        if line[word_count] in MnemonicTab and MnemonicTab[line[word_count]][0] == "IS":
            outfile.write(str(IC) + " ")
            IC += 1
            outfile.write(str(MnemonicTab[line[word_count]]) + " ")
            if line[word_count] == "STOP":
                outfile.write("\n")
            elif line[word_count] == "READ" or line[word_count] == "PRINT":
                if line[word_count + 1] not in set(SymbolTable.keys()):
                    SymbolTable[line[word_count + 1]] = 0
                outfile.write(str(['S', list(SymbolTable.keys()).index(line[word_count + 1]) + 1]) + "\n")
            else:            
                if line[word_count + 1] in set(RegisterTab.keys()):
                    outfile.write(str(RegisterTab[line[word_count + 1]]) + " ")
                else:
                    outfile.write(str(ConditionTab[line[word_count + 1]]) + " ")
                if line[word_count + 2] not in set(SymbolTable.keys()):
                    if '=' in line[word_count + 2] and (PoolTable[-1] == 0 or line[word_count + 2] not in LiteralTable[0][PoolTable[-1]:]):
                        LiteralTable[0].append(line[word_count + 2])
                        LiteralTable[1].append(0)
                        littbptr += 1
                        outfile.write(str(['L', LiteralTable[0][littbptr-1::].index(line[word_count + 2]) + littbptr]) + "\n")
                    else:
                        SymbolTable[line[word_count + 2]] = 0
                        outfile.write(str(['S', list(SymbolTable.keys()).index(line[word_count + 2]) + 1]) + "\n")
                else:
                    outfile.write(str(['S', list(SymbolTable.keys()).index(line[word_count + 2]) + 1]) + "\n")
                continue

    outfile.close()
    infile.close()

    outfile = open("symboltab.py", "w")

    print(SymbolTable, LiteralTable, PoolTable)
    outfile.write("SymbolTable = " + str(SymbolTable) + "\n")
    outfile.write("LiteralTable = " + str(LiteralTable) + "\n")
    outfile.write("PoolTable = " + str(PoolTable) + "\n")


    outfile.close
