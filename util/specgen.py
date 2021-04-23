
#   GraphBLAS C Test Suite
#   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
#   SPDX-License-Identifier: Apache-2.0

#   DESCRIPTION: spec generator for test suites

import sys
from GBlists import *

# database of all default inputs and outputs
testdatadict = {}
def inoutdict() :
    testdatadict["eAddM"] = ['C','A','B','','A','M']
    testdatadict["eAddV"] = ['C','V1','V2','','V2','V1']
    testdatadict["eMultM"] = ['C','A','B','','A','M']
    testdatadict["eMultV"] = ['C','V1','V2','','V2','V1']
    testdatadict["kron"] = ['C','A','B','','','',]
    testdatadict["MRed"] = ['C','A','','', 'V2','V1']
    testdatadict["MAppl"] = ['C','A','','','A','M']
    testdatadict["VAppl"] = ['C','V1','','','V1','V2']
    testdatadict["MSel"] = ['C','A','','','A','M']
    testdatadict["VSel"] = ['C','V1','','','V1','V2']
    testdatadict["MTRed"] = ['C','A','','','S','A']
    testdatadict["VTRed"] = ['C','V1','','','S','V2']
    testdatadict["mxm"] = ['C','A','B','','A','M']
    testdatadict["mxv"] = ['C','A','V2','','V2','V1']
    testdatadict["vxm"] = ['C','V1','A','','V2','V1']
    testdatadict["tran"] = ['C','A','','','A','M']
    testdatadict["CExtrD"] = ['CD','A','A_row','A_col','CE','CE']
    testdatadict["CExtrA"] = ['CA','A','ALL','A_col','V1','V1']
    testdatadict["CExtrR"] = ['CR','A','I_RANGE','A_col','V1','V1']
    testdatadict["CExtrS"] = ['CS','A','I_STRIDE','A_col','CE','CE']
    testdatadict["CExtrB"] = ['CB','A','I_BACK','A_col','CE','CE']
    testdatadict["VExtrD"] = ['CD','V1','V1_ind','','VE','VE']
    testdatadict["VExtrA"] = ['CA','V1','ALL','','V2','V2']
    testdatadict["VExtrR"] = ['CR','V1','I_RANGE','','V2','V2']
    testdatadict["VExtrS"] = ['CS','V1','I_STRIDE','','VE','VE']
    testdatadict["VExtrB"] = ['CB','V1','I_BACK','','VE','VE']
    testdatadict["MExtrD"] = ['CD','A','A_row','A_col','ME','ME']
    testdatadict["MExtrA"] = ['CA','A','ALL','ALL','B','M']
    testdatadict["MExtrR"] = ['CR','A','I_RANGE','I_RANGE','B','M']
    testdatadict["MExtrS"] = ['CS','A','I_STRIDE','I_STRIDE','ME','ME']
    testdatadict["MExtrB"] = ['CB','A','I_BACK','I_BACK','ME','ME']
    testdatadict["MTAssnD"] = ['CD','V1','A_row','A_col','A','M']
    testdatadict["MTAssnA"] = ['CA','V1','ALL','ALL','A','M']
    testdatadict["MTAssnR"] = ['CR','V1','I_RANGE','I_RANGE','A','M']
    testdatadict["MTAssnS"] = ['CS','V1','I_STRIDE','I_STRIDE','A','M']
    testdatadict["MTAssnB"] = ['CB','V1','I_BACK','I_BACK','A','M']
    testdatadict["VTAssnD"] = ['CD','V2','V1_ind','','V1','V2']
    testdatadict["VTAssnA"] = ['CA','V2','ALL','','V1','V2']
    testdatadict["VTAssnR"] = ['CR','V2','I_RANGE','','V1','V2']
    testdatadict["VTAssnS"] = ['CS','V2','I_STRIDE','','V1','V2']
    testdatadict["VTAssnB"] = ['CB','V2','I_BACK','','V1','V2']
    testdatadict["MTSubAD"] = ['CD','V1','A_row','A_col','A','ME']
    testdatadict["MTSubAA"] = ['CA','V1','ALL','ALL','A','M']
    testdatadict["MTSubAR"] = ['CR','V1','I_RANGE','I_RANGE','A','M']
    testdatadict["MTSubAS"] = ['CS','V1','I_STRIDE','I_STRIDE','A','ME']
    testdatadict["MTSubAB"] = ['CB','V1','I_BACK','I_BACK','A','ME']
    testdatadict["VTSubAD"] = ['CD','V2','V1_ind','','V1','VE']
    testdatadict["VTSubAA"] = ['CA','V2','ALL','','V1','V1']
    testdatadict["VTSubAR"] = ['CR','V2','I_RANGE','','V1','V1']
    testdatadict["VTSubAS"] = ['CS','V2','I_STRIDE','','V1','VE']
    testdatadict["VTSubAB"] = ['CB','V2','I_BACK','','V1','VE']
    testdatadict["MAssnD"] = ['CD','ME','A_row','A_col','A','M']
    testdatadict["MAssnA"] = ['CA','MEA','ALL','ALL','A','M']
    testdatadict["MAssnR"] = ['CR','MER','I_RANGE','I_RANGE','A','M']
    testdatadict["MAssnS"] = ['CS','MES','I_STRIDE','I_STRIDE','A','M']
    testdatadict["MAssnB"] = ['CB','MEB','I_BACK','I_BACK','A','M']
    testdatadict["MSubAD"] = ['CD','ME','A_row','A_col','A','ME']
    testdatadict["MSubAA"] = ['CA','MEA','ALL','ALL','A','MEA']
    testdatadict["MSubAR"] = ['CR','MER','I_RANGE','I_RANGE','A','MER']
    testdatadict["MSubAS"] = ['CS','MES','I_STRIDE','I_STRIDE','A','MES']
    testdatadict["MSubAB"] = ['CB','MEB','I_BACK','I_BACK','A','MEB']
    testdatadict["CAssnD"] = ['CD','CE','A_row','A_col','A','V2']
    testdatadict["CAssnA"] = ['CA','CEA','ALL','A_col','A','V2']
    testdatadict["CAssnR"] = ['CR','CER','I_RANGE','I_RANGE','A','V2']
    testdatadict["CAssnS"] = ['CS','CES','I_STRIDE','I_STRIDE','A','V2']
    testdatadict["CAssnB"] = ['CB','CEB','I_BACK','I_BACK','A','V2']
    testdatadict["CSubAD"] = ['CD','CE','A_row','A_col','A','CE']
    testdatadict["CSubAA"] = ['CA','CEA','ALL','A_col','A','CEA']
    testdatadict["CSubAR"] = ['CR','CER','I_RANGE','A_col','A','CER']
    testdatadict["CSubAS"] = ['CS','CES','I_STRIDE','A_col','A','CES']
    testdatadict["CSubAB"] = ['CB','CEB','I_BACK','A_col','A','CEB']
    testdatadict["RAssnD"] = ['CD','CE','A_row','A_col','A','V1']
    testdatadict["RAssnA"] = ['CA','CEA','A_col','ALL','A','V1']
    testdatadict["RAssnR"] = ['CR','CER','I_RANGE','I_RANGE','A','V1']
    testdatadict["RAssnS"] = ['CS','CES','I_STRIDE','I_STRIDE','A','V1']
    testdatadict["RAssnB"] = ['CB','CEB','I_BACK','I_BACK','A','V1']
    testdatadict["RSubAD"] = ['CD','CE','A_row','A_col','A','CE']
    testdatadict["RSubAA"] = ['CA','CEA','A_row','ALL','A','CEA']
    testdatadict["RSubAR"] = ['CR','CER','A_row','I_RANGE','A','CER']
    testdatadict["RSubAS"] = ['CS','CES','A_row','I_STRIDE','A','CES']
    testdatadict["RSubAB"] = ['CB','CEB','A_row','I_BACK','A','CEB']
    testdatadict["VAssnD"] = ['CD','VE','V1_ind','','V1','V2']
    testdatadict["VAssnA"] = ['CA','VEA','ALL','','V1','V2']
    testdatadict["VAssnR"] = ['CR','VER','I_RANGE','','V1','V2']
    testdatadict["VAssnS"] = ['CS','VES','I_STRIDE','','V1','V2']
    testdatadict["VAssnB"] = ['CB','VEB','I_BACK','','V1','V2']
    testdatadict["VSubAD"] = ['CD','VE','V1_ind','','V1','VE']
    testdatadict["VSubAA"] = ['CA','VEA','ALL','','V1','VEA']
    testdatadict["VSubAR"] = ['CR','VER','I_RANGE','','V1','VER']
    testdatadict["VSubAS"] = ['CS','VES','I_STRIDE','','V1','VES']
    testdatadict["VSubAB"] = ['CB','VEB','I_BACK','','V1','VEB']

# lists of tests classified by types of inputs
binmonsemlist = ["eAddM","eAddV","eMultM","eMultV","kron"]
binmonlist = ["MRed"]
binunlist = ["MAppl","VAppl"]
seloplist = ["MSel","VSel"]
monoplist = ["MTRed","VTRed"]
semoplist = ["mxm","mxv","vxm"]
typeoplist = ["tran"]
indexoplist = ["CExtr","VExtr","MExtr","MTAssn","VTAssn","MTSubA","VTSubA",
               "MAssn","MSubA","CAssn","CSubA","RAssn","RSubA","VAssn","VSubA"]

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

# three cases: no mask/no accum; mask/no accum; no mask/accum
def notboth(testf, out, i0, i1, i2, iv, m, acc, obj, name, d) :
    specgen(testf, out+'D', i0, i1, i2, '', '', '',
            obj, name, d)
    if (m != '') :
        specgen(testf, out+'M', i0, i1, i2, '', m, '',
                obj, name, d)
    if ((acc != '') and (iv != '')) :
        specgen(testf, out+'A', i0, i1, i2, iv, '', acc,
                obj, name, d)

# four cases: no mask/no accum; mask/no accum; no mask/accum; mask/accum
def onespec(testf, out, i0, i1, i2, iv, m, acc, obj, name, d) :
    notboth(testf, out, i0, i1, i2, iv, m, acc, obj, name, d)
    if ((m != '') and (acc != '')) :
        specgen(testf, out+'B', i0, i1, i2, iv, m, acc,
                obj, name, d)
#    specgen(testf, out+'T', i0, i1, i2, iv, m, acc,
#            '', '', d)

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
#    onespec(testf, out+'B', i0, i1, i2, iv, m, acc, 'BINOP', bname, d)
#    onespec(testf, out+'U', i0, i1, i2, iv, m, acc, 'UNOP', uname, d)
    onespec(testf, out, i0, i1, i2, iv, m, acc, 'UNOP', uname, d)

# for index operations: default, ALL, RANGE, STRIDE, and BACK cases
def selectindop(testf, op, acc, name, d, ilist) :
    for c in ilist :
        ta = testdatadict[op+c]
        onespec(testf, ta[0], ta[1], ta[2], ta[3], ta[4], ta[5], acc,
                'TYPE', name, d)

# for index operations: default, ALL, RANGE, STRIDE, and BACK cases
def notbothindop(testf, op, acc, name, d, ilist) :
    for c in ilist :
        ta = testdatadict[op+c]
        notboth(testf, ta[0], ta[1], ta[2], ta[3], ta[4], ta[5], acc,
                'TYPE', name, d)

# spec and list that iterate over ALL objects for all tests
def fullspec(specdir) :
    acc = 'ANY_BOOL,PLUS'
    alltests = binmonsemlist+binmonlist+binunlist+seloplist+monoplist
    alltests += semoplist+typeoplist+indexoplist

    inoutdict()
    for x in alltests :
        testf = specdir+'test'+x
        if x in indexoplist :
            ilist = ['D', 'A', 'R', 'S', 'B']
            selectindop(testf, x, acc, 'ALL', 'ALL', ilist)
        else :
            ta = testdatadict[x]
            if (x in binmonsemlist) :
                binmonsem(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                          'ALL','ALL','ALL','ALL')
            elif (x in binmonlist) :
                binmon(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                       'ALL','ALL','ALL')
            elif (x in binunlist) :
                binun(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                      'ALL','ALL','ALL')
            elif (x in seloplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'SELOP','ALL','ALL')
            elif (x in monoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'MON','ALL','ALL')
            elif (x in semoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'SEMI','ALL','ALL')
            elif (x in typeoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'TYPE','ALL','ALL')

# spec and list for current tests being debugged
def defaultspec(specdir) :
    acc = 'ANY_BOOL,PLUS'
    alltests = binmonsemlist+binmonlist+binunlist+seloplist+monoplist
    alltests += semoplist+typeoplist+indexoplist

    inoutdict()
    for x in alltests :
        testf = specdir+'test'+x
        if x in indexoplist :
            ilist = ['D', 'A', 'R', 'S', 'B']
            if (x in ['CAssn','CSubA','RAssn','RSubA','VAssn','VSubA']) :
                selectindop(testf, x, acc, 'ALL', '2', ilist)
            else :
                selectindop(testf, x, acc, 'ALL', '4', ilist)
        else :
            ta = testdatadict[x]
            if (x in binmonsemlist) :
                if (x in ['eAddM','kron']) : b = 'PLUS'
                elif (x in ['eAddV']) : b = 'PAIR'
                elif (x in ['eMultM','eMultV']) : b = 'ANY'

                binmonsem(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                          b,'ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
            elif (x in binmonlist) :
                binmon(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                       'MIN_','-ANY','2')
            elif (x in binunlist) :
                binun(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                      'ALL','-MINV','4')
            elif (x in seloplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'SELOP','ALL','4')
            elif (x in monoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'MON','ALL','4')
            elif (x in semoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'SEMI','ANY_PAIR_BOOL,PLUS_TIMES','4')
            elif (x in typeoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'TYPE','ALL','2')

# spec and list files for regression tests: pass all builds
def regspec(specdir) :
    acc = 'ANY_BOOL,PLUS'
    alltests = binmonsemlist+binmonlist+binunlist+seloplist+monoplist
    alltests += semoplist+typeoplist+indexoplist

    inoutdict()
    for x in alltests :
        testf = specdir+'test'+x
        if x in indexoplist :
            if (x in ['CAssn','CSubA','RAssn','RSubA','VAssn','VSubA']) :
                dstr = '2'
            else : dstr = '4'
            if (x == 'VExtr') :
                ilist = ['D', 'A', 'R', 'S']
                selectindop(testf, x, acc, 'ALL', dstr, ilist)
                ta = testdatadict[x+'B']
                onespec(testf,ta[0],ta[1],ta[2],ta[3],'','','',
                        'TYPE','ALL',dstr)
            elif x in ['MTAssn', 'VTAssn'] :
                ilist = ['D', 'A', 'R', 'S']
                notbothindop(testf, x, acc, 'ALL', dstr, ilist)
                ta = testdatadict[x+'B']
                notboth(testf,ta[0],ta[1],ta[2],ta[3],ta[4],'',
                        'ANY_BOOL,PLUS','TYPE','ALL',dstr)
            elif x in ['MAssn'] :
                ilist = ['D', 'A', 'R', 'S', 'B']
                notbothindop(testf, x, acc, 'ALL', dstr, ilist)
            elif x in ['VAssn'] :
                ilist = ['D', 'A', 'R', 'S']
                notbothindop(testf, x, acc, 'ALL', dstr, ilist)
                ta = testdatadict[x+'B']
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],'',acc,
                        'TYPE','ALL',dstr)
            elif x in ['CAssn', 'CSubA', 'RAssn', 'RSubA'] :
                for c in ['D', 'A', 'R', 'S', 'B'] :
                    ta = testdatadict[x+c]
                    onespec(testf,ta[0],ta[1],ta[2],ta[3],'','','',
                            'TYPE','ALL',dstr)
            else :
                ilist = ['D', 'A', 'R', 'S', 'B']
                selectindop(testf, x, acc, 'ALL', dstr, ilist)
        else :
            ta = testdatadict[x]
            if (x in binmonsemlist) :
                if (x in ['eAddM','kron']) : b = 'PLUS'
                elif (x in ['eAddV']) : b = 'PAIR'
                elif (x in ['eMultM','eMultV']) : b = 'ANY'

                binmonsem(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                          b,'ALL','ANY_PAIR_BOOL,PLUS_TIMES','4')
            elif (x in binmonlist) :
                binmon(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                       'MIN_','-ANY','2')
            elif (x in binunlist) :
                binun(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                      'ALL','-MINV','4')
            elif (x in seloplist) :
                if (x in ['MSel']) :
                    onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                            'SELOP','ALL','4')
                else :
                    onespec(testf,ta[0],ta[1],ta[2],ta[3],'',ta[5],'',
                            'SELOP','ALL','4')
            elif (x in monoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],'',ta[5],'',
                        'MON','ALL','4')
            elif (x in semoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'SEMI','ANY_PAIR_BOOL,PLUS_TIMES','4')
            elif (x in typeoplist) :
                onespec(testf,ta[0],ta[1],ta[2],ta[3],ta[4],ta[5],acc,
                        'TYPE','ALL','2')

if __name__ == '__main__' :

    numargs = len(sys.argv)

    if (numargs == 1) :
        sys.stdout.write('Usage: one argument or 12 arguments:\n\n')
        sys.stdout.write('WORKING\n\tcurrent specs in data/working\n')
        sys.stdout.write('FULL\n\tfull specs in data/fullspec\n')
        sys.stdout.write('REGRESSION\n\tregression specs in data/regression\n')
        sys.stdout.write('test out i0 i1 i2 iv m acc obj name desc\n\t')
        sys.stdout.write('generate a single spec file in cwd\n')
        sys.exit(0)
    elif (numargs == 2) :
        if (sys.argv[1] == 'WORKING') : defaultspec('data/working/')
        elif (sys.argv[1] == 'FULL') : fullspec('data/fullspec/')
        elif (sys.argv[1] == 'REGRESSION') : regspec('data/regression/')
        else : sys.stdout.write('unknown test suite\n')
    elif (numargs == 12) :
        specgen(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4],
                sys.argv[5], sys.argv[6], sys.argv[7], sys.argv[8],
                sys.argv[9], sys.argv[10], sys.argv[11])
    else : sys.stdout.write('wrong # args\n')
