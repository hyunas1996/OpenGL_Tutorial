#!/bin/sh
bindir=$(pwd)
cd /Users/hyunahome/Desktop/OpenGL_Tutorial/ogl-master/tutorial03_matrices/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/hyunahome/Desktop/OpenGL_Tutorial/MinSizeRel/tutorial03_matrices 
	else
		"/Users/hyunahome/Desktop/OpenGL_Tutorial/MinSizeRel/tutorial03_matrices"  
	fi
else
	"/Users/hyunahome/Desktop/OpenGL_Tutorial/MinSizeRel/tutorial03_matrices"  
fi
