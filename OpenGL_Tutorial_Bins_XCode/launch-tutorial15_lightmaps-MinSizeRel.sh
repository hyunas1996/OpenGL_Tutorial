#!/bin/sh
bindir=$(pwd)
cd /Users/hyunahome/Desktop/OpenGL_Tutorial/ogl-master/tutorial15_lightmaps/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/hyunahome/Desktop/OpenGL_Tutorial/OpenGL_Tutorial_Bins_XCode/MinSizeRel/tutorial15_lightmaps 
	else
		"/Users/hyunahome/Desktop/OpenGL_Tutorial/OpenGL_Tutorial_Bins_XCode/MinSizeRel/tutorial15_lightmaps"  
	fi
else
	"/Users/hyunahome/Desktop/OpenGL_Tutorial/OpenGL_Tutorial_Bins_XCode/MinSizeRel/tutorial15_lightmaps"  
fi
