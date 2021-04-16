
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
    else : return

    acclst = accstr.split(',')
    alist = [] ; ilist = [] ; vlist = [] ; anew = []
    for ac in acclst :
        if (ac != '') :
            alist += [x for i, x in enumerate(ALLBINOPS) if (x.find(ac) != -1)]
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
    for t in vlist :
        y = t.split('_')
        if (tind < len(y)) : fstr = y[tind]
        else : fstr = 'BOOL'
        v = [x for x in alist if (x.find(fstr) != -1)]
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

if __name__ == '__main__' :

    if ((len(sys.argv) == 2) and (sys.argv[1] == 'H')) :
        sys.stdout.write('args: test [out i0 i1 i2 iv m acc obj name d]\n')
        sys.exit(0)

    if (len(sys.argv) == 13) : specdir = 'data/'+sys.argv[12]+'/'
    else : specdir = 'data/specfiles/'

    if ((len(sys.argv) == 13) or (len(sys.argv) == 12)):
        specgen(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4],
                sys.argv[5], sys.argv[6], sys.argv[7], sys.argv[8],
                sys.argv[9], sys.argv[10], sys.argv[11])
    elif (len(sys.argv) <= 2) :
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'eAddM')) :
            fname = specdir+'testeAddM'
            binmonsem(fname,'C','A','B','','A','M','ANY_BOOL,PLUS',
                      'PLUS','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'eAddV')) :
            fname = specdir+'testeAddV'
            binmonsem(fname,'C','V1','V2','','V2','V1','ANY_BOOL,PLUS',
                      'PAIR','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'eMultM')) :
            fname = specdir+'testeMultM'
            binmonsem(fname,'C','A','B','','A','M','ANY_BOOL,PLUS',
                      'ANY','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'eMultV')) :
            fname = specdir+'testeMultV'
            binmonsem(fname,'C','V1','V2','','V2','V1','ANY_BOOL,PLUS',
                      'ANY','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'kron')) :
            fname = specdir+'testkron'
            binmonsem(fname,'C','A','B','','','','',
                      'PLUS','ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MRed')) :
            fname = specdir+'testMRed'
            binmon(fname,'C','A','','', 'V2','V1',"ANY_BOOL,PLUS",
                   'MIN_','-ANY','2')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MAppl')) :
            fname = specdir+'testMAppl'
            binun(fname,'C','A','','','A','M','ANY_BOOL,PLUS',
                  'MIN_','-MINV','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'VAppl')) :
            fname = specdir+'testeVAppl'
            binun(fname,'C','V1','','','V1','V2','ANY_BOOL,PLUS',
                  'MIN_','-MINV','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MSel')) :
            fname = specdir+'testMSel'
            onespec(fname,'C','A','','','A','M','ANY_BOOL,PLUS',
                    'SELOP','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'VSel')) :
            fname = specdir+'testVSel'
            onespec(fname,'C','V1','','','V1','V2','ANY_BOOL,PLUS',
                    'SELOP','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MTRed')) :
            fname = specdir+'testMTRed'
            onespec(fname,'C','A','','','S','A','ANY_BOOL,PLUS',
                    'MON','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'VTRed')) :
            fname = specdir+'testeVTRed'
            onespec(fname,'C','V1','','','S','V2','ANY_BOOL,PLUS',
                    'MON','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'mxm')) :
            fname = specdir+'testmxm'
            onespec(fname,'C','A','B','','A','M','ANY_BOOL,PLUS',
                    'SEMI','ANY_PAIR_BOOL,PLUS_TIMES','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'mxv')) :
            fname = specdir+'testmxv'
            onespec(fname,'C','A','V2','','V2','V1','ANY_BOOL,PLUS',
                    'SEMI','ANY_PAIR_BOOL,PLUS_TIMES','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'vxm')) :
            fname = specdir+'testvxm'
            onespec(fname,'C','V1','A','','V2','V1','ANY_BOOL,PLUS',
                    'SEMI','ANY_PAIR_BOOL,PLUS_TIMES','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'tran')) :
            fname = specdir+'testtran'
            onespec(fname,'C','A','','','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'CExtr')) :
            fname = specdir+'testCExtr'
            onespec(fname,'CD','A','A_row','A_col','CE','CE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','A','ALL','A_col','V1','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','A','I_RANGE','A_col','V1','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','A','I_STRIDE','A_col','CE','CE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','A','I_BACK','A_col','CE','CE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'VExtr')) :
            fname = specdir+'testVExtr'
            onespec(fname,'CD','V1','V1_ind','','VE','VE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','V1','ALL','','V2','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','V1','I_RANGE','','V2','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','V1','I_STRIDE','','VE','VE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','V1','I_BACK','','VE','VE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MExtr')) :
            fname = specdir+'testMExtr'
            onespec(fname,'CD','A','A_row','A_col','ME','ME','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','A','ALL','ALL','B','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','A','I_RANGE','I_RANGE','B','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','A','I_STRIDE','I_STRIDE','ME','ME','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','A','I_BACK','I_BACK','ME','ME','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MTAssn')) :
            fname = specdir+'testMTAssn'
            onespec(fname,'CD','V1','A_row','A_col','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','V1','ALL','ALL','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','V1','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','V1','I_STRIDE','I_STRIDE','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','V1','I_BACK','I_BACK','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'VTAssn')) :
            fname = specdir+'testVTAssn'
            onespec(fname,'CD','V2','V1_ind','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','V2','ALL','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','V2','I_RANGE','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','V2','I_STRIDE','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','V2','I_BACK','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MTSubA')) :
            fname = specdir+'testMTSubA'
            onespec(fname,'CD','V1','A_row','A_col','A','ME','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','V1','ALL','ALL','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','V1','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','V1','I_STRIDE','I_STRIDE','A','ME','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','V1','I_BACK','I_BACK','A','ME','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'VTSubA')) :
            fname = specdir+'testVTSubA'
            onespec(fname,'CD','V2','V1_ind','','V1','VE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','V2','ALL','','V1','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','V2','I_RANGE','','V1','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','V2','I_STRIDE','','V1','VE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','V2','I_BACK','','V1','VE','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MAssn')) :
            fname = specdir+'testMAssn'
            onespec(fname,'CD','ME','A_row','A_col','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','MEA','ALL','ALL','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','MER','I_RANGE','I_RANGE','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','MES','I_STRIDE','I_STRIDE','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','MEB','I_BACK','I_BACK','A','M','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'MSubA')) :
            fname = specdir+'testMSubA'
            onespec(fname,'CD','ME','A_row','A_col','A','ME','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CA','MEA','ALL','ALL','A','MEA','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CR','MER','I_RANGE','I_RANGE','A','MER','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CS','MES','I_STRIDE','I_STRIDE','A','MES','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
            onespec(fname,'CB','MEB','I_BACK','I_BACK','A','MEB','ANY_BOOL,PLUS',
                    'TYPE','ALL','4')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'CAssn')) :
            fname = specdir+'testCAssn'
            onespec(fname,'CD','CE','A_row','A_col','A','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CA','CEA','ALL','A_col','A','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CR','CER','I_RANGE','I_RANGE','A','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CS','CES','I_STRIDE','I_STRIDE','A','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CB','CEB','I_BACK','I_BACK','A','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'CSubA')) :
            fname = specdir+'testCSubA'
            onespec(fname,'CD','CE','A_row','A_col','A','CE','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CA','CEA','ALL','A_col','A','CEA','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CR','CER','I_RANGE','A_col','A','CER','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CS','CES','I_STRIDE','A_col','A','CES','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CB','CEB','I_BACK','A_col','A','CEB','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'RAssn')) :
            fname = specdir+'testRAssn'
            onespec(fname,'CD','CE','A_row','A_col','A','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CA','CEA','A_col','ALL','A','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CR','CER','I_RANGE','I_RANGE','A','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CS','CES','I_STRIDE','I_STRIDE','A','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CB','CEB','I_BACK','I_BACK','A','V1','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'RSubA')) :
            fname = specdir+'testRSubA'
            onespec(fname,'CD','CE','A_row','A_col','A','CE','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CA','CEA','A_row','ALL','A','CEA','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CR','CER','A_row','I_RANGE','A','CER','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CS','CES','A_row','I_STRIDE','A','CES','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CB','CEB','A_row','I_BACK','A','CEB','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'VAssn')) :
            fname = specdir+'testVAssn'
            onespec(fname,'CD','VE','V1_ind','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CA','VEA','ALL','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CR','VER','I_RANGE','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CS','VES','I_STRIDE','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CB','VEB','I_BACK','','V1','V2','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
        if ((len(sys.argv) == 1) or (sys.argv[1] == 'VSubA')) :
            fname = specdir+'testVSubA'
            onespec(fname,'CD','VE','V1_ind','','V1','VE','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CA','VEA','ALL','','V1','VEA','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CR','VER','I_RANGE','','V1','VER','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CS','VES','I_STRIDE','','V1','VES','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
            onespec(fname,'CB','VEB','I_BACK','','V1','VEB','ANY_BOOL,PLUS',
                    'TYPE','ALL','2')
