
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

def getmethod(ofile, gbobj, prefix, numstr, vard, inoutstr) :
    if vard == '' :
        ostr = gbobj
        vard = gbobj
    else :
        ostr = gbobj+'_'+inoutstr+vard
    ofile.write('\n'+prefix+'_'+vard+' *All'+ostr+'s['+numstr+'];\n')
    ofile.write('\nvoid get_'+ostr+'(int index, '+prefix+'_'+vard+' *obj)\n{\n')
    if gbobj == 'Descriptor' :
        ofile.write('  if ((index >= 1) && (index < '+numstr+'))\n')
    else :
        ofile.write('  if ((index >= 0) && (index < '+numstr+'))\n')
    ofile.write('    *obj = *All'+ostr+'s[index];\n  else *obj = NULL;\n}\n')

def preamble(ofile, gbobj, prefix, numstr, num) :
    ofile.write('/*\n    Copyright 2020 by Lucata Corporation.\n')
    ofile.write('    Lucata grants a free license for noncommercial use and requires that this\n')
    ofile.write('    notice not be removed from the source files.\n\n')
    ofile.write('    GraphBLAS C Test Suite\n')
    ofile.write('    DESCRIPTION: built-in object database file\n*/\n')
    ofile.write('\n#include "GraphBLAS.h"\n')
    ofile.write('\n#define ' + numstr + ' ' + str(num)+'\n')
    ofile.write('\nint num_'+gbobj+'s() { return '+numstr+'; }\n')
    getmethod(ofile, gbobj, prefix, numstr, '', '')
    ofile.write('\nint find_'+gbobj+'('+prefix+'_'+gbobj+' obj)\n{\n')
    ofile.write('  for (int i = 0; i < '+numstr+'; i++)\n')
    ofile.write('    if (*All'+gbobj+'s[i] == obj) return i;\n')
    ofile.write('  return -1;\n}\n')

# write a list
def writelist(ofile, olist) :
    ofile.write('{\n')
    for s in olist :
        if s == 'GrB_NULL' :
            ofile.write('  '+s+',\n')
        else :
            ofile.write('  &'+s+',\n')
    ofile.write('};\n')

def gennovars(gbobj, prefix, olist) :
    numstr = 'NUM_'+gbobj.upper()+'S'
    ofile = open(gbobj+'s.c', 'w')
    preamble(ofile, gbobj, prefix, numstr, len(olist))
    ofile.write('\n'+prefix+'_'+gbobj+' *All'+gbobj+'s['+numstr+'] = ')
    writelist(ofile, olist)
    ofile.close()

def genunop() :
    ofile = open('UnaryOps.c', 'w')
    preamble(ofile, 'UnaryOp', 'GrB', 'NUM_UNARYOPS', NUM_UNARYOPS)
    getmethod(ofile, 'UnaryOp', 'GrB', 'NUM_UNARYOPS', 'Type', '')
    ofile.write('\nGrB_UnaryOp *AllUnaryOps[NUM_UNARYOPS] = ')
    writelist(ofile, ALLUNOPS)
    ofile.write('\nGrB_Type *AllUnaryOp_Types[NUM_UNARYOPS] = ')
    writelist(ofile, UNTYPE);
    ofile.close()

def genbinop() :
    ofile = open('BinaryOps.c', 'w')
    preamble(ofile, 'BinaryOp', 'GrB', 'NUM_BINARYOPS', NUM_BINARYOPS)
    getmethod(ofile, 'BinaryOp', 'GrB', 'NUM_BINARYOPS', 'Type', 'in')
    getmethod(ofile, 'BinaryOp', 'GrB', 'NUM_BINARYOPS', 'Type', 'out')
    ofile.write('\nGrB_BinaryOp *AllBinaryOps[NUM_BINARYOPS] = ')
    writelist(ofile, ALLBINOPS)
    ofile.write('\nGrB_Type *AllBinaryOp_inTypes[NUM_BINARYOPS] = ')
    writelist(ofile, BINTYPE);
    ofile.write('\nGrB_Type *AllBinaryOp_outTypes[NUM_BINARYOPS] = ')
    writelist(ofile, BINOTYPE);
    ofile.close()

def genmon() :
    ofile = open('Monoids.c', 'w')
    preamble(ofile, 'Monoid', 'GrB', 'NUM_MONOIDS', NUM_MONOIDS)
    getmethod(ofile, 'Monoid', 'GrB', 'NUM_MONOIDS', 'Type', '')
    getmethod(ofile, 'Monoid', 'GrB', 'NUM_MONOIDS', 'BinaryOp', '')
    ofile.write('\nGrB_Monoid *AllMonoids[NUM_MONOIDS] = ')
    writelist(ofile, ALLMONS);
    ofile.write('\nGrB_Type *AllMonoid_Types[NUM_MONOIDS] = ')
    writelist(ofile, MONTYPE);
    ofile.write('\nGrB_BinaryOp *AllMonoid_BinaryOps[NUM_MONOIDS] = ')
    writelist(ofile, MONOP);
    ofile.close()

def gensemi() :
    ofile = open('Semirings.c', 'w')
    preamble(ofile, 'Semiring', 'GrB', 'NUM_SEMIRINGS', NUM_SEMIRINGS)
    getmethod(ofile, 'Semiring', 'GrB', 'NUM_SEMIRINGS', 'Monoid', '')
    getmethod(ofile, 'Semiring', 'GrB', 'NUM_SEMIRINGS', 'BinaryOp', '')
    ofile.write('\nGrB_Semiring *AllSemirings[NUM_SEMIRINGS] = ')
    writelist(ofile, ALLSEMIS)
    ofile.write('\nGrB_Monoid *AllSemiring_Monoids[NUM_SEMIRINGS] = ')
    writelist(ofile, SEMIMON);
    ofile.write('\nGrB_BinaryOp *AllSemiring_BinaryOps[NUM_SEMIRINGS] = ')
    writelist(ofile, SEMIOP);
    ofile.close()

def getGBobj(olist, item) :
    if (item.isdigit()) :
        print(olist[int(item)]);
    else :
        val = [ind for ind, x in enumerate(olist) if x == item]
        print(val[0])

import sys

if __name__ == '__main__' :

    if (len(sys.argv) == 1) :
        gennovars('Type', 'GrB', ALLTYPES)
        gennovars('Descriptor', 'GrB', ALLDESC)
        gennovars('SelectOp', 'GxB', ALLSELECT)
        unoplist()
        genunop()
        binoplist()
        genbinop()
        monlist()
        genmon()
        semilist()
        gensemi()
    else :
        if (sys.argv[1] == 'Type') :
            getGBobj(ALLTYPES, sys.argv[2]);
        elif (sys.argv[1] == 'Descriptor') :
            getGBobj(ALLDESC, sys.argv[2]);
        elif (sys.argv[1] == 'SelectOp') :
            getGBobj(ALLSELECT, sys.argv[2]);
        elif (sys.argv[1] == 'UnaryOp') :
            unoplist()
            getGBobj(ALLUNOPS, sys.argv[2]);
        elif (sys.argv[1] == 'BinaryOp') :
            binoplist()
            getGBobj(ALLBINOPS, sys.argv[2]);
        elif (sys.argv[1] == 'Monoid') :
            monlist()
            getGBobj(ALLMONS, sys.argv[2]);
        elif (sys.argv[1] == 'Semiring') :
            semilist()
            getGBobj(ALLSEMIS, sys.argv[2]);
