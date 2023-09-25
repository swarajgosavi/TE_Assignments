'''
LP-1
Assignment A1 (part1)

Name    : Swaraj Gosavi
Roll no : 31328
Batch   : L3
'''

from mnemonic import *
from symboltab import *

def pass2(ifname, ofname):

    poolptr = 0
    littbptr = 0
    IC = 0
    size = 0
    machine_code_buffer = []
    code_area = list()

    infile = open(ifname, "r")
    outfile = open(ofname, "w")
    outfile.close
    outfile = open(ofname, "a")

    Lines = infile.readlines()

    for line in Lines:
        line = "".join(line.split())
        line = line.replace("[", " [")
        line = line.replace("]", "] ")
        line = line.strip(" ")
        line = line.replace("'", "").split()

        machine_code_buffer = []

        if line == ["[AD,2]"]:
            print("END")
            break

        if line[0] == "[AD,1]":
            IC = int(list(line[1].strip("[]").split(","))[1])
            size = 0

        if line[1].find("DL") != -1:
            token = list(line[1].strip("[]").split(","))[1]
            machine_code_buffer.append(line[0])
            if token == '1':
                machine_code_buffer.extend(["00", "0", "001"])
            print(machine_code_buffer)
            pass

        if line[1].find("IS") != -1:
            machine_code_buffer.append(line[0])
            token = list(line[1].strip("[]").split(","))[1]
            if token == '9' or token == '10':
                operand2 = list(line[2].strip("[]").split(","))[1]
                machine_code_buffer.extend([token, "0", str(list(SymbolTable.values())[int(operand2)-1])])
            elif token == '0':
                machine_code_buffer.extend(["00", "0", "000"])
            else:
                operand2 = list(line[3].strip("[]").split(","))[1]
                table = list(line[3].strip("[]").split(","))[0]
                if table == "S":
                    machine_code_buffer.extend([token, line[2], str(list(SymbolTable.values())[int(operand2)-1])])
                if table == "L":
                    machine_code_buffer.extend([token, line[2], str(LiteralTable[1][int(operand2)-1])])

            print(machine_code_buffer)
            
        code_area.append(machine_code_buffer)

    for c in code_area:
        c = " ".join(c)
        outfile.write(c)
        outfile.write("\n")

    outfile.close()
    infile.close()