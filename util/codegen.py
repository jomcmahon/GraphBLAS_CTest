
#   GraphBLAS C Test Suite
#   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
#   SPDX-License-Identifier: Apache-2.0

#   DESCRIPTION: code generator for built-in objects

from GBlists import *

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
