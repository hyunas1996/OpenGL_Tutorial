#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/hyunahome/Desktop/OpenGL_Tutorial
  make -f /Users/hyunahome/Desktop/OpenGL_Tutorial/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/hyunahome/Desktop/OpenGL_Tutorial
  make -f /Users/hyunahome/Desktop/OpenGL_Tutorial/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/hyunahome/Desktop/OpenGL_Tutorial
  make -f /Users/hyunahome/Desktop/OpenGL_Tutorial/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/hyunahome/Desktop/OpenGL_Tutorial
  make -f /Users/hyunahome/Desktop/OpenGL_Tutorial/CMakeScripts/ReRunCMake.make
fi

