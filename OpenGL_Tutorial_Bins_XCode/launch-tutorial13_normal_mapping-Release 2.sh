#!/bin/sh
bindir=$(pwd)
cd /Users/hyunahome/Desktop/OpenGL_Tutorial/OpenGL/ogl-master/tutorial13_normal_mapping/
export 

if test "x$1" = "x--debugger"; then
	shift
	if test "x" = "xYES"; then
		echo "r  " > $bindir/gdbscript
		echo "bt" >> $bindir/gdbscript
		GDB_COMMAND-NOTFOUND -batch -command=$bindir/gdbscript  /Users/hyunahome/Desktop/OpenGL_Tutorial/OpenGL_Tutorial_Bins_XCode/Release/tutorial13_normal_mapping 
	else
		"/Users/hyunahome/Desktop/OpenGL_Tutorial/OpenGL_Tutorial_Bins_XCode/Release/tutorial13_normal_mapping"  
	fi
else
	"/Users/hyunahome/Desktop/OpenGL_Tutorial/OpenGL_Tutorial_Bins_XCode/Release/tutorial13_normal_mapping"  
fi