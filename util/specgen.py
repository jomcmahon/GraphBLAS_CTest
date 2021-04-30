
#   GraphBLAS C Test Suite
#   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
#   SPDX-License-Identifier: Apache-2.0

#   DESCRIPTION: spec generator for test suites

import sys
from GBlists import *

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
                il = []
                vl = []
                if (len(v) > 0) : il, vl = map(list, zip(*v))
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
        for dsc in desclst :
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

if __name__ == '__main__' :

    numargs = len(sys.argv)

    if (numargs == 1) :
        sys.stdout.write('Usage: one argument or 11 arguments:\n\n')
        sys.stdout.write('filename\n\tread test suite spec in curr dir\n')
        sys.stdout.write('test out i0 i1 i2 iv m acc obj name desc\n\t')
        sys.stdout.write('generate a single spec file in cwd\n')
        sys.exit(0)
    elif (numargs == 2) :
        with open(sys.argv[1]) as fp :
            specdir = ''
            for line in fp :
                x = [sub.replace('NONE','') for sub in line.strip().split()]
                if (len(x) == 1) : specdir = x[0]
                elif (len(x) == 12) :
                    tf = specdir + '/test' + x[1]
                    doacc = (x[6] != '') and (x[8] != '')
                    if ('D' in x[0]) :
                        specgen(tf, x[2]+'D', x[3], x[4], x[5], '', '', '',
                                x[9], x[10], x[11])
                    if (('M' in x[0]) and (x[7] != '')) :
                        specgen(tf, x[2]+'M', x[3], x[4], x[5], '', x[7], '',
                                x[9], x[10], x[11])
                    if (('A' in x[0]) and doacc) :
                        specgen(tf, x[2]+'A', x[3], x[4], x[5], x[6], '', x[8],
                                x[9], x[10], x[11])
                    if (('B' in x[0])  and (x[7] != '') and doacc) :
                        specgen(tf, x[2]+'B', x[3], x[4], x[5], x[6], x[7],
                                x[8], x[9], x[10], x[11])
            fp.close()
    elif (numargs == 12) :
        x = [sub.replace('NONE','') for sub in sys.argv]
        specgen(x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8], x[9], x[10],
                x[11])
    else : sys.stdout.write('wrong # args\n')
