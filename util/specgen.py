
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
from itertools import cycle

def writeline(instr, nlist, sfile) :
    nstr = ' '.join([str(x) for x in nlist])
    sfile.write(instr+' '+str(len(nlist))+' '+nstr+'\n')

def specgen(testf, out, i0, i1, i2, iv, m, accstr, obj, namestr, dstr) :
    if (len(ALLBINOPS) == 0) : binoplist()
    if (len(ALLUNOPS) == 0) : unoplist()
    if (len(ALLMONS) == 0) : monlist()
    if (len(ALLSEMIS) == 0) : semilist()

    sfile = open(testf+out+'.spec', 'w')
    if (obj == 'TYPE') : llist = ALLTYPES ; tind = 1
    elif (obj == 'SELOP') : llist = ALLTYPES ; tind = 1
    elif (obj == 'UNOP') : llist = ALLUNOPS ; tind = 2
    elif (obj == 'BINOP') : llist = ALLBINOPS ; tind = 2
    elif (obj == 'MON') : llist = ALLMONS ; tind = 2
    elif (obj == 'SEMI') : llist = ALLSEMIS ; tind = 3
    else : llist = []

    acclst = accstr.split(',')
    alist = [] ; ilist = [] ; vlist = [] ; anew = []
    for ac in acclst :
        if (ac != '') :
            alist += [x for i, x in enumerate(ALLBINOPS) if (x.find(ac) != -1)]
    if (obj != '') :
        if (namestr == 'ALL') : 
            if (obj == 'SELOP') :
                sfile.write('TYPE '+str(len(ALLTYPES))+'\n')
                sfile.write('SELOP '+str(len(ALLSELECT))+'\n')
            else : sfile.write(obj+' '+str(len(llist))+'\n')
            vlist = llist
        else :
            namelst = namestr.split(',')
            for nm in namelst :
                if (nm[0] == '-') :
                    v = [(i, x) for i, x in enumerate(llist) if (x.find(nm[1:]) == -1)]
                else :
                    v = [(i, x) for i, x in enumerate(llist) if (x.find(nm) != -1)]
                il, vl = map(list, zip(*v))
                ilist += il
                vlist += vl
    if (len(ilist) > 0) : writeline(obj, ilist, sfile)
    if (len(vlist) > 0) :
        for t in vlist :
            y = t.split('_')
            if (tind < len(y)) : fstr = y[tind]
            else : fstr = 'BOOL'
            v = [x for x in alist if (x.find(fstr) != -1)]
            if (len(v) > 0) : anew += [ALLBINOPS.index(v[0])]
    else :
        v = [x for x in alist if (x.find('FP32') != -1)]
        if (len(v) > 0) : anew += [ALLBINOPS.index(v[0])]

    if (dstr == 'ALL') : sfile.write('DESC '+str(len(ALLDESC))+'\n')
    elif (dstr.isdigit()) : writeline('DESC', range(int(dstr)), sfile)
    elif (dstr != '') :
        desclst = dstr.split(",")
        il = []
        for dsc in desclist :
            il += [i for i, x in enumerate(ALLDESC) if (x.find(dsc) != -1)]
        if (len(il) != 0) : writeline('DESC', il, sfile)

    if (len(anew) > 0) : writeline('ACCUM', anew, sfile)
    if (i0 != '') : sfile.write('INPUT0 '+i0+'\n')
    if (i1 != '') : sfile.write('INPUT1 '+i1+'\n')
    if (i2 != '') : sfile.write('INPUT2 '+i2+'\n')
    if (m != '') : sfile.write('MASK '+m+'\n')
    if (iv != '') : sfile.write('INIT '+iv+'\n')
    if (out != '') : sfile.write('OUTPUT '+out+'\n')
    sfile.close()
    lfile = open(testf+'.list', 'a+')
    specstr = testf+out+'.spec'
    if not specstr in lfile.read() : lfile.write(specstr+'\n')
    lfile.close()

# four cases: no mask/no accum; mask/no accum; no mask/accum; mask/accum
def onespec(testf, out, i0, i1, i2, iv, m, acc, obj, name, d) :
    specgen(testf, out+'D', i0, i1, i2, '', '', '',
            obj, name, d)
    if (m != '') :
        specgen(testf, out+'M', i0, i1, i2, '', m, '',
                obj, name, d)
    if ((acc != '') and (iv != '')) :
        specgen(testf, out+'A', i0, i1, i2, iv, '', acc,
                obj, name, d)
    if ((m != '') and (acc != '')) :
        specgen(testf, out+'B', i0, i1, i2, iv, m, acc,
                obj, name, d)

# for operations that take either binary ops or monoids
def binmon(testf, out, i0, i1, i2, iv, m, acc, bname, mname, d) :
    onespec(testf, out+'B', i0, i1, i2, iv, m, acc, 'BINOP', bname, d)
    onespec(testf, out+'M', i0, i1, i2, iv, m, acc, 'MON', mname, d)

# for operations that take either binary ops or monoids or semirings
def binmonsem(testf, out, i0, i1, i2, iv, m, acc, bname, mname, sname, d) :
    binmon(testf, out, i0, i1, i2, iv, m, acc, bname, mname, d)
    onespec(testf, out+'S', i0, i1, i2, iv, m, acc, 'SEMI', sname, d)

# for operations that take either binary ops or unary ops
def binun(testf, out, i0, i1, i2, iv, m, acc, bname, uname, d) :
    onespec(testf, out+'B', i0, i1, i2, iv, m, acc, 'BINOP', bname, d)
    onespec(testf, out+'U', i0, i1, i2, iv, m, acc, 'UNOP', uname, d)

def fullspec(specdir) :
    fn = specdir+'testeAddM'
    binmonsem(fn,'C','A','B','','A','M','ANY_BOOL,PLUS',
              'ALL','ALL','ALL','ALL')
    fn = specdir+'testeAddV'
    binmonsem(fn,'C','V1','V2','','V2','V1','ANY_BOOL,PLUS',
              'ALL','ALL','ALL','ALL')
    fn = specdir+'testeMultM'
    binmonsem(fn,'C','A','B','','A','M','ANY_BOOL,PLUS',
              'ALL','ALL','ALL','ALL')
    fn = specdir+'testeMultV'
    binmonsem(fn,'C','V1','V2','','V2','V1','ANY_BOOL,PLUS',
              'ALL','ALL','ALL','ALL')
    fn = specdir+'testkron'
    binmonsem(fn,'C','A','B','','','','',
              'ALL','ALL','ALL','ALL')
    fn = specdir+'testMRed'
    binmon(fn,'C','A','','', 'V2','V1',"ANY_BOOL,PLUS",
           'ALL','ALL','ALL')
    fn = specdir+'testMAppl'
    onespec(fn,'C','A','','','A','M','ANY_BOOL,PLUS',
            'UNOP','ALL','ALL')
    fn = specdir+'testVAppl'
    onespec(fn,'C','V1','','','V1','V2','ANY_BOOL,PLUS',
            'UNOP','ALL','ALL')
    fn = specdir+'testMSel'
    onespec(fn,'C','A','','','A','M','ANY_BOOL,PLUS',
            'SELOP','ALL','ALL')
    fn = specdir+'testVSel'
    onespec(fn,'C','V1','','','V1','V2','ANY_BOOL,PLUS',
            'SELOP','ALL','ALL')
    fn = specdir+'testMTRed'
    onespec(fn,'C','A','','','S','A','ANY_BOOL,PLUS',
            'MON','ALL','ALL')
    fn = specdir+'testVTRed'
    onespec(fn,'C','V1','','','S','V2','ANY_BOOL,PLUS',
            'MON','ALL','ALL')
    fn = specdir+'testmxm'
    onespec(fn,'C','A','B','','A','M','ANY_BOOL,PLUS',
            'SEMI','ALL','ALL')
    fn = specdir+'testmxv'
    onespec(fn,'C','A','V2','','V2','V1','ANY_BOOL,PLUS',
            'SEMI','ALL','ALL')
    fn = specdir+'testvxm'
    onespec(fn,'C','V1','A','','V2','V1','ANY_BOOL,PLUS',
            'SEMI','ALL','ALL')
    fn = specdir+'testtran'
    onespec(fn,'C','A','','','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testCExtr'
    onespec(fn,'CD','A','A_row','A_col','CE','CE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','A','ALL','A_col','V1','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','A','I_RANGE','A_col','V1','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','A','I_STRIDE','A_col','CE','CE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','A','I_BACK','A_col','CE','CE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testVExtr'
    onespec(fn,'CD','V1','V1_ind','','VE','VE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','V1','ALL','','V2','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','V1','I_RANGE','','V2','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','V1','I_STRIDE','','VE','VE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','V1','I_BACK','','VE','VE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testMExtr'
    onespec(fn,'CD','A','A_row','A_col','ME','ME','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','A','ALL','ALL','B','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','A','I_RANGE','I_RANGE','B','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','A','I_STRIDE','I_STRIDE','ME','ME','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','A','I_BACK','I_BACK','ME','ME','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testMTAssn'
    onespec(fn,'CD','V1','A_row','A_col','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','V1','ALL','ALL','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','V1','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','V1','I_STRIDE','I_STRIDE','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','V1','I_BACK','I_BACK','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testVTAssn'
    onespec(fn,'CD','V2','V1_ind','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','V2','ALL','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','V2','I_RANGE','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','V2','I_STRIDE','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','V2','I_BACK','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testMTSubA'
    onespec(fn,'CD','V1','A_row','A_col','A','ME','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','V1','ALL','ALL','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','V1','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','V1','I_STRIDE','I_STRIDE','A','ME','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','V1','I_BACK','I_BACK','A','ME','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testVTSubA'
    onespec(fn,'CD','V2','V1_ind','','V1','VE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','V2','ALL','','V1','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','V2','I_RANGE','','V1','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','V2','I_STRIDE','','V1','VE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','V2','I_BACK','','V1','VE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testMAssn'
    onespec(fn,'CD','ME','A_row','A_col','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','MEA','ALL','ALL','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','MER','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','MES','I_STRIDE','I_STRIDE','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','MEB','I_BACK','I_BACK','A','M','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testMSubA'
    onespec(fn,'CD','ME','A_row','A_col','A','ME','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','MEA','ALL','ALL','A','MEA','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','MER','I_RANGE','I_RANGE','A','MER','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','MES','I_STRIDE','I_STRIDE','A','MES','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','MEB','I_BACK','I_BACK','A','MEB','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testCAssn'
    onespec(fn,'CD','CE','A_row','A_col','A','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','CEA','ALL','A_col','A','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','CER','I_RANGE','I_RANGE','A','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','CES','I_STRIDE','I_STRIDE','A','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','CEB','I_BACK','I_BACK','A','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testCSubA'
    onespec(fn,'CD','CE','A_row','A_col','A','CE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','CEA','ALL','A_col','A','CEA','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','CER','I_RANGE','A_col','A','CER','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','CES','I_STRIDE','A_col','A','CES','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','CEB','I_BACK','A_col','A','CEB','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testRAssn'
    onespec(fn,'CD','CE','A_row','A_col','A','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','CEA','A_col','ALL','A','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','CER','I_RANGE','I_RANGE','A','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','CES','I_STRIDE','I_STRIDE','A','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','CEB','I_BACK','I_BACK','A','V1','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testRSubA'
    onespec(fn,'CD','CE','A_row','A_col','A','CE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','CEA','A_row','ALL','A','CEA','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','CER','A_row','I_RANGE','A','CER','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','CES','A_row','I_STRIDE','A','CES','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','CEB','A_row','I_BACK','A','CEB','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testVAssn'
    onespec(fn,'CD','VE','V1_ind','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','VEA','ALL','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','VER','I_RANGE','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','VES','I_STRIDE','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','VEB','I_BACK','','V1','V2','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    fn = specdir+'testVSubA'
    onespec(fn,'CD','VE','V1_ind','','V1','VE','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CA','VEA','ALL','','V1','VEA','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CR','VER','I_RANGE','','V1','VER','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CS','VES','I_STRIDE','','V1','VES','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')
    onespec(fn,'CB','VEB','I_BACK','','V1','VEB','ANY_BOOL,PLUS',
            'TYPE','ALL','ALL')

def defaultspec(numargs, intest, specdir) :
    if ((numargs == 1) or (intest == 'eAddM')) :
        fn = specdir+'testeAddM'
        binmonsem(fn,'C','A','B','','A','M','ANY_BOOL,PLUS',
                  'PLUS','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
    if ((numargs == 1) or (intest == 'eAddV')) :
        fn = specdir+'testeAddV'
        binmonsem(fn,'C','V1','V2','','V2','V1','ANY_BOOL,PLUS',
                  'PAIR','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
    if ((numargs == 1) or (intest == 'eMultM')) :
        fn = specdir+'testeMultM'
        binmonsem(fn,'C','A','B','','A','M','ANY_BOOL,PLUS',
                  'ANY','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
    if ((numargs == 1) or (intest == 'eMultV')) :
        fn = specdir+'testeMultV'
        binmonsem(fn,'C','V1','V2','','V2','V1','ANY_BOOL,PLUS',
                  'ANY','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
    if ((numargs == 1) or (intest == 'kron')) :
        fn = specdir+'testkron'
        binmonsem(fn,'C','A','B','','','','',
                  'PLUS','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
    if ((numargs == 1) or (intest == 'MRed')) :
        fn = specdir+'testMRed'
        binmon(fn,'C','A','','', 'V2','V1',"ANY_BOOL,PLUS",
               'MIN_','-ANY','2')
    if ((numargs == 1) or (intest == 'MAppl')) :
        fn = specdir+'testMAppl'
        onespec(fn,'C','A','','','A','M','ANY_BOOL,PLUS',
                'UNOP','-MINV','4')
    if ((numargs == 1) or (intest == 'VAppl')) :
        fn = specdir+'testVAppl'
        onespec(fn,'C','V1','','','V1','V2','ANY_BOOL,PLUS',
                'UNOP','-MINV','4')
    if ((numargs == 1) or (intest == 'MSel')) :
        fn = specdir+'testMSel'
        onespec(fn,'C','A','','','A','M','ANY_BOOL,PLUS',
                'SELOP','ALL','4')
    if ((numargs == 1) or (intest == 'VSel')) :
        fn = specdir+'testVSel'
        onespec(fn,'C','V1','','','V1','V2','ANY_BOOL,PLUS',
                'SELOP','ALL','4')
    if ((numargs == 1) or (intest == 'MTRed')) :
        fn = specdir+'testMTRed'
        onespec(fn,'C','A','','','S','A','ANY_BOOL,PLUS',
                'MON','ALL','4')
    if ((numargs == 1) or (intest == 'VTRed')) :
        fn = specdir+'testVTRed'
        onespec(fn,'C','V1','','','S','V2','ANY_BOOL,PLUS',
                'MON','ALL','4')
    if ((numargs == 1) or (intest == 'mxm')) :
        fn = specdir+'testmxm'
        onespec(fn,'C','A','B','','A','M','ANY_BOOL,PLUS',
                'SEMI','ANY_PAIR_BOOL,PLUS_TIMES','4')
    if ((numargs == 1) or (intest == 'mxv')) :
        fn = specdir+'testmxv'
        onespec(fn,'C','A','V2','','V2','V1','ANY_BOOL,PLUS',
                'SEMI','ANY_PAIR_BOOL,PLUS_TIMES','4')
    if ((numargs == 1) or (intest == 'vxm')) :
        fn = specdir+'testvxm'
        onespec(fn,'C','V1','A','','V2','V1','ANY_BOOL,PLUS',
                'SEMI','ANY_PAIR_BOOL,PLUS_TIMES','4')
    if ((numargs == 1) or (intest == 'tran')) :
        fn = specdir+'testtran'
        onespec(fn,'C','A','','','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
    if ((numargs == 1) or (intest == 'CExtr')) :
        fn = specdir+'testCExtr'
        onespec(fn,'CD','A','A_row','A_col','CE','CE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','A','ALL','A_col','V1','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','A','I_RANGE','A_col','V1','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','A','I_STRIDE','A_col','CE','CE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','A','I_BACK','A_col','CE','CE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'VExtr')) :
        fn = specdir+'testVExtr'
        onespec(fn,'CD','V1','V1_ind','','VE','VE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','V1','ALL','','V2','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','V1','I_RANGE','','V2','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','V1','I_STRIDE','','VE','VE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','V1','I_BACK','','VE','VE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'MExtr')) :
        fn = specdir+'testMExtr'
        onespec(fn,'CD','A','A_row','A_col','ME','ME','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','A','ALL','ALL','B','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','A','I_RANGE','I_RANGE','B','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','A','I_STRIDE','I_STRIDE','ME','ME','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','A','I_BACK','I_BACK','ME','ME','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'MTAssn')) :
        fn = specdir+'testMTAssn'
        onespec(fn,'CD','V1','A_row','A_col','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','V1','ALL','ALL','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','V1','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','V1','I_STRIDE','I_STRIDE','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','V1','I_BACK','I_BACK','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'VTAssn')) :
        fn = specdir+'testVTAssn'
        onespec(fn,'CD','V2','V1_ind','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','V2','ALL','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','V2','I_RANGE','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','V2','I_STRIDE','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','V2','I_BACK','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'MTSubA')) :
        fn = specdir+'testMTSubA'
        onespec(fn,'CD','V1','A_row','A_col','A','ME','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','V1','ALL','ALL','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','V1','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','V1','I_STRIDE','I_STRIDE','A','ME','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','V1','I_BACK','I_BACK','A','ME','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'VTSubA')) :
        fn = specdir+'testVTSubA'
        onespec(fn,'CD','V2','V1_ind','','V1','VE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','V2','ALL','','V1','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','V2','I_RANGE','','V1','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','V2','I_STRIDE','','V1','VE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','V2','I_BACK','','V1','VE','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'MAssn')) :
        fn = specdir+'testMAssn'
        onespec(fn,'CD','ME','A_row','A_col','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','MEA','ALL','ALL','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','MER','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','MES','I_STRIDE','I_STRIDE','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','MEB','I_BACK','I_BACK','A','M','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'MSubA')) :
        fn = specdir+'testMSubA'
        onespec(fn,'CD','ME','A_row','A_col','A','ME','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CA','MEA','ALL','ALL','A','MEA','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CR','MER','I_RANGE','I_RANGE','A','MER','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CS','MES','I_STRIDE','I_STRIDE','A','MES','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
        onespec(fn,'CB','MEB','I_BACK','I_BACK','A','MEB','ANY_BOOL,PLUS',
                'TYPE','ALL','4')
    if ((numargs == 1) or (intest == 'CAssn')) :
        fn = specdir+'testCAssn'
        onespec(fn,'CD','CE','A_row','A_col','A','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CA','CEA','ALL','A_col','A','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CR','CER','I_RANGE','I_RANGE','A','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CS','CES','I_STRIDE','I_STRIDE','A','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CB','CEB','I_BACK','I_BACK','A','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
    if ((numargs == 1) or (intest == 'CSubA')) :
        fn = specdir+'testCSubA'
        onespec(fn,'CD','CE','A_row','A_col','A','CE','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CA','CEA','ALL','A_col','A','CEA','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CR','CER','I_RANGE','A_col','A','CER','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CS','CES','I_STRIDE','A_col','A','CES','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CB','CEB','I_BACK','A_col','A','CEB','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
    if ((numargs == 1) or (intest == 'RAssn')) :
        fn = specdir+'testRAssn'
        onespec(fn,'CD','CE','A_row','A_col','A','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CA','CEA','A_col','ALL','A','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CR','CER','I_RANGE','I_RANGE','A','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CS','CES','I_STRIDE','I_STRIDE','A','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CB','CEB','I_BACK','I_BACK','A','V1','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
    if ((numargs == 1) or (intest == 'RSubA')) :
        fn = specdir+'testRSubA'
        onespec(fn,'CD','CE','A_row','A_col','A','CE','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CA','CEA','A_row','ALL','A','CEA','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CR','CER','A_row','I_RANGE','A','CER','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CS','CES','A_row','I_STRIDE','A','CES','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CB','CEB','A_row','I_BACK','A','CEB','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
    if ((numargs == 1) or (intest == 'VAssn')) :
        fn = specdir+'testVAssn'
        onespec(fn,'CD','VE','V1_ind','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CA','VEA','ALL','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CR','VER','I_RANGE','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CS','VES','I_STRIDE','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CB','VEB','I_BACK','','V1','V2','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
    if ((numargs == 1) or (intest == 'VSubA')) :
        fn = specdir+'testVSubA'
        onespec(fn,'CD','VE','V1_ind','','V1','VE','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CA','VEA','ALL','','V1','VEA','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CR','VER','I_RANGE','','V1','VER','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CS','VES','I_STRIDE','','V1','VES','ANY_BOOL,PLUS',
                'TYPE','ALL','2')
        onespec(fn,'CB','VEB','I_BACK','','V1','VEB','ANY_BOOL,PLUS',
                'TYPE','ALL','2')

if __name__ == '__main__' :

    numargs = len(sys.argv)
    specdir = 'data/specfiles/'

    if (numargs == 1) : defaultspec(numargs, '', specdir)
    elif (numargs == 2) :
        if (sys.argv[1] == 'H') :
            sys.stdout.write('args: test [out i0 i1 i2 iv m acc obj name d]\n')
            sys.exit(0)
        elif (sys.argv[1] == 'FULL') : fullspec('data/fullspec/')
        else : defaultspec(numargs, sys.argv[1], specdir)
    elif (numargs == 3) : defaultspec(numargs, sys.argv[1], sys.argv[2])
    elif (numargs == 12) :
        specgen(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4],
                sys.argv[5], sys.argv[6], sys.argv[7], sys.argv[8],
                sys.argv[9], sys.argv[10], sys.argv[11])
    else : sys.stdout.write('wrong # args\n')
