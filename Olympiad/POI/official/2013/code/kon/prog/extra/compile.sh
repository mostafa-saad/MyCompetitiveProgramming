#!/bin/bash
#
#
# $1 - source
# $2 - output
# [ $3 - language = C | CPP | PAS ] 
#
#
SRC=$1
OUT=$2
LANG=$3

# source file should be in current directory
function compile_pas() {
    FOO=foo
    cp $SRC kon.pas
    ppc386 -O2 -XS -Xt "kongrader.pas" "-o$FOO"
    r=$?
    if [ -f "$FOO" ] ; then 
	mv "$FOO" "$OUT"
    fi
    return $r
}

function compile_ocaml() {
    FOO=foo.ml
    mv "$SRC" "$FOO"
    ocamlopt "$FOO" -o "$OUT"
    r=$?
    return $r
}

function compile_java() {
    FOO=${SRC:0:3}.java
    FOO1=${SRC:0:3}.class
    mv "$SRC" "$FOO"
    /java/bin/javac "$FOO"
    r=$?
    /java/bin/jar cf "$OUT" *.class
    rm -f "$FOO" "$FOO1"
    return $r
}


function compile_c() {
    /usr/bin/gcc -x c -O2 -static -o "$OUT" kongrader.c "$SRC" -lm
    return $?
}

function compile_cpp() {
    /usr/bin/g++ -x c++ kongrader.cpp -x c++ -O2 -static -o "$OUT" "$SRC" -lm -Wl,--start-group -lstdc++ -lsupc++ -Wl,--end-group
    return $?
}

function repack_zip() {
    zipinfo -t $SRC >info || return 1
    len=`tail -n 1 info | sed -ne 's/.* \([0-9]\+\) bytes uncompressed.*/\1/p'`
    if [ "$len" -gt 11000000 ]; then
	echo File too long 1>&2
	exit 1
    fi

    dir="repack_tmp" 
    dir2="repack_tmp2" 
    rm -rf "$dir" "$dir2"
    mkdir "$dir" "$dir2" || return 1
    unzip -d "$dir" -qqjLo $SRC || return 1

    find "$dir" -iname '*.out' -size -10000k -exec mv {} "$dir2" \;

    outputs=`find "$dir2" -iname '*.out' -size -10000k`
    IFS=$'\n'
    for f in $outputs; do
	d=`echo $f | tr A-Z a-z`
	if [ "$f" != "$d" ]; then
	    mv "$f" "$d"
	fi
    done

    echo foo >"$dir2/_bar" # zip wants a non empty archive
    rm -f tmp.zip
    zip -qqjr tmp.zip "$dir2" || return 1
    rm -rf "$dir" "$dir2"
    mv tmp.zip $OUT
}

function repack_tgz() {
    dir="repack_tmp" 
    dir2="repack_tmp2" 
    rm -rf "$dir" "$dir2"
    mkdir "$dir" "$dir2" || return 1
    tar -xzf "$SRC" -C "$dir" || return 1

    find "$dir" -iname '*.out' -size -10000k -exec mv {} "$dir2" \;

    outputs=`find "$dir2" -iname '*.out' -size -10000k`
    IFS=$'\n'
    for f in $outputs; do
	d=`echo $f | tr A-Z a-z`
	if [ "$f" != "$d" ]; then
	    mv "$f" "$d"
	fi
    done

    echo foo >"$dir2/_bar" # zip wants a non empty archive
    rm -f tmp.zip
    zip -qqjr tmp.zip "$dir2" || return 1
    rm -rf "$dir" "$dir2"
    mv tmp.zip $OUT
}

function set_pax_flags() {
   /sbin/paxctl -CEMRXS "$OUT" > /dev/null 2>&1    
}

function check_out_size() {                                                                          
if [ -f "$OUT" ] && ! find "$OUT" -size -10240k | grep -q ''; then                               
   echo "Executable file too large."                                                            
   exit 1;
fi
} 

if [ -f "$SRC" ] ; then
    if [ -z "$OUT" ] ; then
	exit 101
    fi

    if [ -z "$LANG" ] ; then
	LANG=`echo $SRC | sed -e "s/.*\.//g"`
    fi

    case "$LANG" in
    PAS|pas)
	compile_pas
    set_pax_flags
    check_out_size
	res=$?
	;;
    C|c)
	compile_c
    set_pax_flags
    check_out_size
	res=$?
	;;
    CPP|CC|cpp|cc)
	compile_cpp
    set_pax_flags
    check_out_size
	res=$?
	;;
    JAVA|java)
	compile_java
	res=$?
	;;
    ML|ml|OCAML|ocaml)
	compile_ocaml
	res=$?
	;;
    ZIP)
	repack_zip
	res=$?
	;;
    TGZ)
	repack_tgz
	res=$?
	;;
    *)
	exit 102
    esac
    exit $res
else
    # no input file
    exit 100
fi

