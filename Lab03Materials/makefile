# Makefile for ELEC278/Lectures/Code/Trees/BST Directory
# Meant to be used with MSVC nmake command, but can be modified for any
# version of a make-like utility

all:	LAB3_BST.exe \
	MAKEIDNT.exe \
	bst_strings.exe \
	bst_traversal.exe

clean:
	del *.obj
	del *.exe
	del *.bak
	del *.map

stamp:
	annotate *.c

#------------------------------------------------------------------------------
# Dependencies for Lab3 code
#------------------------------------------------------------------------------
LAB3OBJ	=	LAB3_MAIN.obj LAB3_BST.obj

LAB3_BST.exe:	$(LAB3OBJ)
		cl /nologo /Fe$* /Fm$* $(LAB3OBJ)

LAB3_MAIN.obj:		$*.c LAB3_BST.h

LAB3_BST.obj:	$*.c LAB3_BST.h

#-----------------------------------------------------------------------------
# Dependencies for general example programs, etc.
#-----------------------------------------------------------------------------

bst_strings.exe:	$*.c

bst_traversal.exe:	$*.c


