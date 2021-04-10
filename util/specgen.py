
#   Copyright 2020 by Lucata Corporation.
#   Lucata grants a free license for noncommercial use and requires that this
#   notice not be removed from the source files.

#   GraphBLAS C Test Suite
#   DESCRIPTION: code generator for built-in objects

# SelectOps
ALLSELECT = ["GxB_TRIL", "GxB_TRIU", "GxB_DIAG", "GxB_OFFDIAG", "GxB_NONZERO",
             "GxB_EQ_ZERO", "GxB_GT_ZERO", "GxB_GE_ZERO", "GxB_LT_ZERO",
             "GxB_LE_ZERO", "GxB_NE_THUNK", "GxB_EQ_THUNK", "GxB_GT_THUNK",
             "GxB_GE_THUNK", "GxB_LT_THUNK", "GxB_LE_THUNK"]

# Descriptors
ALLDESC = ["GrB_NULL", "GrB_DESC_T1", "GrB_DESC_T0", "GrB_DESC_T0T1",
           "GrB_DESC_C", "GrB_DESC_CT1", "GrB_DESC_CT0", "GrB_DESC_CT0T1",
           "GrB_DESC_S", "GrB_DESC_ST1", "GrB_DESC_ST0", "GrB_DESC_ST0T1",
           "GrB_DESC_SC", "GrB_DESC_SCT1", "GrB_DESC_SCT0", "GrB_DESC_SCT0T1",
           "GrB_DESC_R", "GrB_DESC_RT1", "GrB_DESC_RT0", "GrB_DESC_RT0T1",
           "GrB_DESC_RC", "GrB_DESC_RCT1", "GrB_DESC_RCT0", "GrB_DESC_RCT0T1",
           "GrB_DESC_RS", "GrB_DESC_RST1", "GrB_DESC_RST0", "GrB_DESC_RST0T1",
           "GrB_DESC_RSC", "GrB_DESC_RSCT1", "GrB_DESC_RSCT0",
           "GrB_DESC_RSCT0T1"]

# Types
ALLTYPES = ["GrB_BOOL", "GrB_INT8", "GrB_UINT8", "GrB_INT16", "GrB_UINT16",
           "GrB_INT32", "GrB_UINT32", "GrB_INT64", "GrB_UINT64", "GrB_FP32",
           "GrB_FP64"]
TYPES_N = ["INT8", "UINT8", "INT16", "UINT16", "INT32",
           "UINT32", "INT64", "UINT64", "FP32", "FP64"]

# UnaryOps
UNARYOPS_A = ["GrB_IDENTITY", "GrB_AINV", "GrB_MINV",
              "GxB_LNOT", "GxB_ONE", "GxB_ABS"]
UNARYOPS = ["GrB_LNOT"]
NUM_UNARYOPS = len(UNARYOPS_A) * len(ALLTYPES) + len(UNARYOPS)

# BinaryOps
BINARYOPS_N = ["GrB_FIRST", "GrB_SECOND", "GxB_PAIR", "GrB_MIN", "GrB_MAX",
               "GrB_PLUS", "GrB_MINUS", "GrB_TIMES", "GrB_DIV", "GxB_RDIV",
               "GxB_RMINUS", "GxB_ISEQ", "GxB_ISNE", "GxB_ISGT", "GxB_ISLT",
               "GxB_ISGE", "GxB_ISLE", "GxB_LOR", "GxB_LAND", "GxB_LXOR",
               "GrB_EQ", "GrB_NE", "GrB_GT", "GrB_LT", "GrB_GE", "GrB_LE",
               "GxB_ANY"]
BINARYOPS_OB = ["GrB_EQ", "GrB_NE", "GrB_GT", "GrB_LT", "GrB_GE", "GrB_LE"]
BINARYOPS_B = ["GxB_ANY", "GrB_FIRST", "GrB_SECOND", "GxB_PAIR", "GxB_LOR",
               "GxB_LAND", "GxB_LXOR", "GrB_EQ", "GrB_GT", "GrB_LT", "GrB_GE",
               "GrB_LE", "GrB_NE", "GrB_MIN", "GrB_MAX", "GrB_PLUS",
               "GrB_MINUS", "GrB_TIMES", "GrB_DIV", "GxB_RDIV", "GxB_RMINUS",
               "GxB_ISEQ", "GxB_ISNE", "GxB_ISGT", "GxB_ISLT", "GxB_ISGE",
               "GxB_ISLE"]
BINARYOPS = ["GrB_LOR", "GrB_LAND", "GrB_LXOR"]
NUM_BINARYOPS1 = len(BINARYOPS_N) * len(TYPES_N)
NUM_BINARYOPS = NUM_BINARYOPS1 + len(BINARYOPS_B) + len(BINARYOPS)

# Monoids
MONOIDS_N = ["GxB_MIN", "GxB_MAX", "GxB_PLUS", "GxB_TIMES", "GxB_ANY"]
MONOIDS_B = ["GxB_LOR", "GxB_LAND", "GxB_LXOR", "GxB_EQ", "GxB_ANY"]
NUM_MONOIDS = len(MONOIDS_N) * len(TYPES_N) + len(MONOIDS_B)

# Semirings
SEMIMON_N1 = ["GxB_MIN", "GxB_MAX", "GxB_PLUS", "GxB_TIMES", "GxB_ANY"]
SEMIBIN_N1 = ["FIRST", "SECOND", "PAIR", "MIN", "MAX", "PLUS", "MINUS",
              "TIMES", "DIV", "RDIV", "RMINUS", "ISEQ", "ISNE", "ISGT",
              "ISLT", "ISGE", "ISLE", "LOR", "LAND", "LXOR"]
SEMIMON_N2 = ["GxB_LOR", "GxB_LAND", "GxB_LXOR", "GxB_EQ", "GxB_ANY"]
SEMIBIN_N2 = ["EQ", "NE", "GT", "LT", "GE", "LE"]
SEMIMON_B = ["GxB_LOR", "GxB_LAND", "GxB_LXOR", "GxB_EQ", "GxB_ANY"]
SEMIBIN_B = ["FIRST", "SECOND", "PAIR", "LOR", "LAND", "LXOR", "EQ", "GT",
              "LT", "GE", "LE"]
NUM_SEMIRINGS1 = len(SEMIMON_N1) * len(SEMIBIN_N1) * len(TYPES_N)
NUM_SEMIRINGS2 = len(SEMIMON_N2) * len(SEMIBIN_N2) * len(TYPES_N)
NUM_SEMIRINGS3 = len(SEMIMON_B) * len(SEMIBIN_B)
NUM_SEMIRINGS = NUM_SEMIRINGS1 + NUM_SEMIRINGS2 + NUM_SEMIRINGS3

# generated lists
ALLUNOPS = []
UNTYPE = []
ALLBINOPS = []
BINTYPE = []
BINOTYPE = []
ALLMONS = []
MONTYPE = []
MONOP = []
ALLSEMIS = []
SEMIMON = []
SEMIOP = []

# unaryops
def unoplist() :
    for t in ALLTYPES :
        for u in UNARYOPS_A :
            ALLUNOPS.append(u+'_'+t[4:])
            UNTYPE.append(t)
    for u in UNARYOPS :
        ALLUNOPS.append(u)
        UNTYPE.append('GrB_BOOL')

# binaryops
def binoplist() :
    for b in BINARYOPS_N :
        for t in TYPES_N :
            ALLBINOPS.append(b+'_'+t)
            BINTYPE.append('GrB_'+t)
            if b in BINARYOPS_OB :
                BINOTYPE.append('GrB_BOOL')
            else :
                BINOTYPE.append('GrB_'+t)
    for b in BINARYOPS_B :
        ALLBINOPS.append(b+'_BOOL')
        BINTYPE.append('GrB_BOOL')
        BINOTYPE.append('GrB_BOOL')
    for b in BINARYOPS :
        ALLBINOPS.append(b)
        BINTYPE.append('GrB_BOOL')
        BINOTYPE.append('GrB_BOOL')

def find_binop(monval, montype) :
    if montype == 'BOOL' :
        binval = [i for i in BINARYOPS_B if monval in i]
    else :
        binval = [i for i in BINARYOPS_N if monval in i]
    return binval[0]+'_'+montype

# monoids
def monlist() :
    for t in TYPES_N :
        for m in MONOIDS_N :
            ALLMONS.append(m+'_'+t+'_MONOID')
            MONTYPE.append('GrB_'+t)
            MONOP.append(find_binop(m[3:], t))
    for m in MONOIDS_B :
        ALLMONS.append(m+'_BOOL_MONOID')
        MONTYPE.append('GrB_BOOL')
        MONOP.append(find_binop(m[3:], 'BOOL'))

# semirings
def semilist() :
    for b in SEMIBIN_N1 :
        for t in TYPES_N :
            for m in SEMIMON_N1 :
                ALLSEMIS.append(m+'_'+b+'_'+t)
                SEMIMON.append(m+'_'+t+'_MONOID')
                SEMIOP.append(find_binop('_'+b, t))
    for b in SEMIBIN_N2 :
        for t in TYPES_N :
            for m in SEMIMON_N2 :
                ALLSEMIS.append(m+'_'+b+'_'+t)
                SEMIMON.append(m+'_'+'BOOL_MONOID')
                SEMIOP.append(find_binop('_'+b, t))
    for b in SEMIBIN_B :
        for m in SEMIMON_B :
            ALLSEMIS.append(m+'_'+b+'_BOOL')
            SEMIMON.append(m+'_'+'BOOL_MONOID')
            SEMIOP.append(find_binop('_'+b, 'BOOL'))

import sys

def writeline(instr, nlist, sfile) :
    nstr = ' '.join([str(x) for x in nlist])
    sfile.write(instr+' '+str(len(nlist))+' '+nstr+'\n')

def getacclist(ilist, acc, tind) :
    alist = []
    if (acc != "") :
        if (len(ALLBINOPS) == 0) : binoplist()
        for t in ilist :
            x = t.split('_')
            astr = acc+'_'+x[tind]
            val = [ind for ind, x in enumerate(ALLBINOPS) if x == astr]
            if (len(val) > 0) : alist += [val[0]]
            else : alist += [-1]
    return alist

def specgen(testf, out, i0, i1, i2, iv, m, acc, obj, name, dlim) :
    sfile = open(testf+out+'.spec', 'w')
    if (obj[0] == '_') : objstr = obj[1:]
    else : objstr = obj
    ilist = []
    if (objstr == 'TYPE') : ilist = ALLTYPES ; tind = 1
    elif (objstr == 'UNOP') : unoplist() ; ilist = ALLUNOPS ; tind = 2
    elif (objstr == 'BINOP') : binoplist() ; ilist = ALLBINOPS ; tind = 2
    elif (objstr == 'MON') : monlist() ; ilist = ALLMONS ; tind = 2
    elif (objstr == 'SEMI') : semilist() ; ilist = ALLSEMIS ; tind = 3
    elif (objstr == 'SELOP') :
        ilist = ALLSELECT
        alist = getacclist(ALLTYPES, acc, 1)
        sfile.write('TYPE '+str(len(ALLTYPES))+'\n')

    if (name == 'ALL') :
        if (objstr != 'SELOP') : alist = getacclist(ilist, acc, tind)
        sfile.write(objstr+' '+str(len(ilist))+'\n')
    else :
        if (obj[0] == '_') :
            v = [(i, x) for i, x in enumerate(ilist) if (x.find(name) == -1)]
        else :
            v = [(i, x) for i, x in enumerate(ilist) if (x.find(name) != -1)]

        il, vl = map(list, zip(*v))
        alist = getacclist(vl, acc, tind)
        writeline(objstr, il, sfile)

    if (dlim != "") :
        if (dlim == 'ALL') : sfile.write('DESC '+dlim+'\n')
        else : writeline('DESC', range(int(dlim)), sfile)
    if (len(alist) != 0) : writeline('ACCUM', alist, sfile)
    if (i0 != "") : sfile.write('INPUT0 '+i0+'\n')
    if (i1 != "") : sfile.write('INPUT1 '+i1+'\n')
    if (i2 != "") : sfile.write('INPUT2 '+i2+'\n')
    if (m != "") : sfile.write('MASK '+m+'\n')
    if (iv != "") : sfile.write('INIT '+iv+'\n')
    if (out != "") : sfile.write('OUTPUT '+out+'\n')
    sfile.close()

if __name__ == '__main__' :

    if (len(sys.argv) < 12) :
        print('args: funct out i0 i1 i2 iv m acc obj name dlim')
    else :
        specgen(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5],
                sys.argv[6], sys.argv[7], sys.argv[8], sys.argv[9], sys.argv[10],
                sys.argv[11])
