#!/bin/sh
bindir=$(pwd)
cd /Users/hyunahome/Desktop/OpenGL_Tutorial/ogl-master/misc05_picking/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/hyunahome/Desktop/OpenGL_Tutorial/MinSizeRel/misc05_picking_custom 
	else
		"/Users/hyunahome/Desktop/OpenGL_Tutorial/MinSizeRel/misc05_picking_custom"  
	fi
else
	"/Users/hyunahome/Desktop/OpenGL_Tutorial/MinSizeRel/misc05_picking_custom"  
fi