# args: 1=testbasename 2=out 3=i0 4=i1 5=i2 6=iv 7=m 8=acc 9=obj 10=name 11=dlim 12=dir
function basic () { 
    r='util/specgen.py'
    python "$r" "${12}/test$1" "$2D" "$3" "$4" "$5" "" "" "" "$9" "${10}" "${11}"
    python "$r" "${12}/test$1" "$2M" "$3" "$4" "$5" "" "$7" "" "$9" "${10}" "${11}"
    python "$r" "${12}/test$1" "$2A" "$3" "$4" "$5" "$6" "" "$8" "$9" "${10}" "${11}"
    python "$r" "${12}/test$1" "$2B" "$3" "$4" "$5" "$6" "$7" "$8" "$9" "${10}" "${11}"
}

# args: 1=testbasename 2=out 3=i0 4=i1 5=i2 6=iv 7=m 8=acc 9=bname 10=mname 11=dlim 12=dir
function binmon () {
    basic "$1" "$2B" "$3" "$4" "$5" "$6" "$7" "$8" 'BINOP' "$9" "${11}" "${12}"
    basic "$1" "$2M" "$3" "$4" "$5" "$6" "$7" "$8" 'MON' "${10}" "${11}" "${12}"
}

# args: 1=testbasename 2=out 3=i0 4=i1 5=i2 6=iv 7=m 8=acc 9=bname 10=mname 11=sname 12=dlim 13=dir
function binmonsem () {
    binmon "$1" "$2" "$3" "$4" "$5" "$6" "$7" "$8" "$9" "${10}" "${12}" "${13}"
    basic "$1" "$2S" "$3" "$4" "$5" "$6" "$7" "$8" 'SEMI' "${11}" "${12}" "${13}"
}

# args: 1=testbasename 2=out 3=i0 4=i1 5=i2 6=iv 7=m 8=acc 9=uname 10=bname 11=dlim 12=dir
function unbin () {
    basic "$1" "$2U" "$3" "$4" "$5" "$6" "$7" "$8" 'UNOP' "$9" "${11}" "${12}"
    basic "$1" "$2B" "$3" "$4" "$5" "$6" "$7" "$8" 'BINOP' "${10}" "${11}" "${12}"
}

# use new directory
d='data/newspec'

function eAddM () {
    t='eAddM'
    binmonsem "$t" 'C' 'A' 'B' "" 'A' 'M' 'GrB_PLUS' 'GrB_PLUS' 'ALL' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function eAddV () {
    t='eAddV'
    binmonsem "@t" 'C' 'V1' 'V2' "" 'V2' 'V1' 'GrB_PLUS' 'GrB_PAIR' 'ALL' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function eAddVU () {
    t='eAddVU'
    binmonsem "@t" 'C' 'V1' 'V2' "" 'V2' 'V1' 'GrB_PLUS' 'GrB_PAIR' 'ALL' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function eMultM () {
    t='eMultM'
    binmonsem "@t" 'C' 'A' 'B' "" 'A' 'M' 'GrB_PLUS' 'GrB_ANY' 'ALL' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function eMultV () {
    t='eMultV'
    binmonsem "@t" 'C' 'V1' 'V2' "" 'V2' 'V1' 'GrB_PLUS' 'GrB_ANY' 'ALL' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function kron () {
    t='kron'
    binmonsem "@t" 'C' 'A' 'B' "" "" "" "" 'GrB_ANY' 'ALL' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MRed () {
    t='MRed'
    binmon "@t" 'C' 'A' "" "" 'V2' 'V1' "" 'GrB_ANY' '_ANY' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MAppl () {
    t='MAppl'
    unbin "@t" 'C' 'A' "" "" 'A' 'M' 'GrB_PLUS' '_MINV' 'MIN' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function VAppl () {
    t='VAppl'
    unbin "@t" 'C' 'V1' "" "" 'V1' 'V2' 'GrB_PLUS' '_MINV' 'MIN' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MSel () {
    t='MSel'
    basic  "@t" 'C' 'A' "" "" 'A' 'M' 'GrB_PLUS' 'SELOP' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function VSel () {
    t='VSel'
    basic  "@t" 'C' 'V1' "" "" 'V1' 'V2' 'GrB_PLUS' 'SELOP' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MTRed () {
    t='MTRed'
    basic  "@t" 'C' 'A' "" "" 'S' 'A' 'GrB_PLUS' 'MON' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function VTRed () {
    t='VTRed'
    basic  "@t" 'C' 'V1' "" "" 'S' 'V2' 'GrB_PLUS' 'MON' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function mxm () {
    t='mxm'
    basic  "@t" 'C' 'A' 'B' "" 'A' 'M' 'GrB_PLUS' 'SEMI' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function mxv () {
    t='mxv'
    basic  "@t" 'C' 'A' 'V2' "" 'V2' 'V1' 'GrB_PLUS' 'SEMI' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function vxm () {
    t='vxm'
    basic  "@t" 'C' 'V1' 'A' "" 'V2' 'V1' 'GrB_PLUS' 'SEMI' 'GxB_PLUS_TIMES' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function tran () {
    t='tran'
    basic  "@t" 'C' 'A' "" "" 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function CExtr () {
    t='CExtr'
    basic  "@t" 'CD' 'A' 'A_row' 'A_col' 'CE' 'CE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'A' 'ALL' 'A_col' 'V1' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'A' 'I_RANGE' 'A_col' 'V1' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'A' 'I_STRIDE' 'A_col' 'CE' 'CE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'A' 'I_BACK' 'A_col' 'CE' 'CE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function VExtr () {
    t='VExtr'
    basic  "@t" 'CD' 'V1' 'V1_ind' "" 'VE' 'VE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'V1' 'ALL' "" 'V2' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'V1' 'I_RANGE' "" 'V2' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'V1' 'I_STRIDE' "" 'VE' 'VE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'V1' 'I_BACK' "" 'VE' 'VE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MExtr () {
    t='MExtr'
    basic  "@t" 'CD' 'A' 'A_row' 'A_col' 'ME' 'ME' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'A' 'ALL' 'ALL' 'B' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'A' 'I_RANGE' 'I_RANGE' 'B' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'A' 'I_STRIDE' 'I_STRIDE' 'ME' 'ME' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'A' 'I_BACK' 'I_BACK' 'ME' 'ME' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MTAssn () {
    t='MTAssn'
    basic  "@t" 'CD' 'V1' 'A_row' 'A_col' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'V1' 'ALL' 'ALL' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'V1' 'I_RANGE' 'I_RANGE' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'V1' 'I_STRIDE' 'I_STRIDE' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'V1' 'I_BACK' 'I_BACK' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function VTAssn () {
    t='VTAssn'
    basic  "@t" 'CD' 'V2' 'V1_ind' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'V2' 'ALL' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'V2' 'I_RANGE' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'V2' 'I_STRIDE' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'V2' 'I_BACK' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MTSubA () {
    t='MTSubA'
    basic  "@t" 'CD' 'V1' 'A_row' 'A_col' 'A' 'ME' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'V1' 'ALL' 'ALL' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'V1' 'I_RANGE' 'I_RANGE' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'V1' 'I_STRIDE' 'I_STRIDE' 'A' 'ME' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'V1' 'I_BACK' 'I_BACK' 'A' 'ME' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function VTSubA () {
    t='VTSubA'
    basic  "@t" 'CD' 'V2' 'V1_ind' "" 'V1' 'VE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'V2' 'ALL' "" 'V1' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'V2' 'I_RANGE' "" 'V1' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'V2' 'I_STRIDE' "" 'V1' 'VE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'V2' 'I_BACK' "" 'V1' 'VE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MAssn () {
    t='MAssn'
    basic  "@t" 'CD' 'ME' 'A_row' 'A_col' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'MEA' 'ALL' 'ALL' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'MER' 'I_RANGE' 'I_RANGE' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'MES' 'I_STRIDE' 'I_STRIDE' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'MEB' 'I_BACK' 'I_BACK' 'A' 'M' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function MSubA () {
    t='MSubA'
    basic  "@t" 'CD' 'ME' 'A_row' 'A_col' 'A' 'ME' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'MEA' 'ALL' 'ALL' 'A' 'MEA' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'MER' 'I_RANGE' 'I_RANGE' 'A' 'MER' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'MES' 'I_STRIDE' 'I_STRIDE' 'A' 'MES' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'MEB' 'I_BACK' 'I_BACK' 'A' 'MEB' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function CAssn () {
    t='CAssn'
    basic  "@t" 'CD' 'CE' 'A_row' 'A_col' 'A' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'CEA' 'ALL' 'A_col' 'A' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'CER' 'I_RANGE' 'I_RANGE' 'A' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'CES' 'I_STRIDE' 'I_STRIDE' 'A' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'CEB' 'I_BACK' 'I_BACK' 'A' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function CSubA () {
    t='CSubA'
    basic  "@t" 'CD' 'CE' 'A_row' 'A_col' 'A' 'CE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'CEA' 'ALL' 'A_col' 'A' 'CEA' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'CER' 'I_RANGE' 'A_col' 'A' 'CER' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'CES' 'I_STRIDE' 'A_col' 'A' 'CES' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'CEB' 'I_BACK' 'A_col' 'A' 'CEB' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function RAssn () {
    t='RAssn'
    basic  "@t" 'CD' 'CE' 'A_row' 'A_col' 'A' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'CEA' 'A_col' 'ALL' 'A' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'CER' 'I_RANGE' 'I_RANGE' 'A' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'CES' 'I_STRIDE' 'I_STRIDE' 'A' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'CEB' 'I_BACK' 'I_BACK' 'A' 'V1' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function RSubA () {
    t='RSubA'
    basic  "@t" 'CD' 'CE' 'A_row' 'A_col' 'A' 'CE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'CEA' 'A_row' 'ALL' 'A' 'CEA' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'CER' 'I_RANGE' 'A_col' 'A' 'CER' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'CES' 'I_STRIDE' 'A_col' 'A' 'CES' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'CEB' 'I_BACK' 'A_col' 'A' 'CEB' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function VAssn () {
    t='VAssn'
    basic  "@t" 'CD' 'VE' 'V1_ind' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'VEA' 'ALL' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'VER' 'I_RANGE' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'VES' 'I_STRIDE' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'VEB' 'I_BACK' "" 'V1' 'V2' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

function VSubA () {
    t='VSubA'
    basic  "@t" 'CD' 'VE' 'V1_ind' "" 'V1' 'VE' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CA' 'VEA' 'ALL' "" 'V1' 'VEA' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CR' 'VER' 'I_RANGE' "" 'V1' 'VER' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CS' 'VES' 'I_STRIDE' "" 'V1' 'VES' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    basic  "@t" 'CB' 'VEB' 'I_BACK' "" 'V1' 'VEB' 'GrB_PLUS' 'TYPE' 'ALL' '4' "$d"
    find "$d" -name "test$t*.spec" > "$d/test$t.list"
}

eAddM
