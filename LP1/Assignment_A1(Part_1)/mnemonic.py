MnemonicTab = { 
    "STOP": ["IS", 0], 
    "ADD": ["IS", 1],
    "SUB": ["IS", 2],
    "MULT": ["IS", 3],
    "MOVER": ["IS", 4],
    "MOVEM": ["IS", 5],
    "COMP": ["IS", 6],
    "BC": ["IS", 7],
    "DIV": ["IS", 8],
    "READ": ["IS", 9],
    "PRINT": ["IS", 10],
    "START": ["AD", 1],
    "END": ["AD", 2],
    "ORIGIN": ["AD", 3],
    "EQU": ["AD", 4],
    "LTORG": ["AD", 5],
    "DC": ["DL", 1],
    "DS": ["DL", 2],
}

RegisterTab = {
    "AREG" : 1,
    "BREG" : 2,
    "CREG" : 3,
    "DREG" : 4
}

ConditionTab = {
    "LT" : 1,
    "LE" : 2,
    "EQ" : 3,
    "GT" : 4,
    "GE" : 5,
    "ANY" : 6
}