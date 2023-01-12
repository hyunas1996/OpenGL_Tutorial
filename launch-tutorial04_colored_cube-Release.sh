#!/bin/sh
bindir=$(pwd)
cd /Users/hyunahome/Desktop/OpenGL_Tutorial/ogl-master/tutorial04_colored_cube/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/hyunahome/Desktop/OpenGL_Tutorial/Release/tutorial04_colored_cube 
	else
		"/Users/hyunahome/Desktop/OpenGL_Tutorial/Release/tutorial04_colored_cube"  
	fi
else
	"/Users/hyunahome/Desktop/OpenGL_Tutorial/Release/tutorial04_colored_cube"  
fi
