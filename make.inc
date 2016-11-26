############################################################################
#
#  Program:         SuperLU_DIST
#
#  Module:          make.inc
#
#  Purpose:         Top-level Definitions
#
#  Creation date:   February 4, 1999   version alpha
#
#  Modified:	    September 1, 1999  version 1.0
#                   March 15, 2003     version 2.0
#
# 		    January 18, 2006   Sam Adams
#                                      General Dynamics - Network Systems
#                       works for i386 Linux, with LAM-MPI 7.1.1 and GCC 4.
#
############################################################################
#
#  The machine (platform) identifier to append to the library names
#
PLAT		=

#
#  The name of the libraries to be created/linked to
#
DSuperLUroot 	= $(HOME)/Softwares/SuperLU_DIST_5.1.2
DSUPERLULIB   	= $(DSuperLUroot)/lib/libsuperlu_dist.a
#
BLASDEF	     	= -DUSE_VENDOR_BLAS
BLASLIB      	= $(LOAD_MKL_SERIAL) 

############################################################################
## parmetis 4.x.x, 32-bit integer
# PARMETIS_DIR	:= ${HOME}/Carver/lib/parmetis-4.0.3
## parmetis 4.x.x, 64-bit integer
# PARMETIS_DIR	:= ${HOME}/Carver/lib/parmetis-4.0.3_64

METISLIB    ?= -L${PARMETIS_DIR}/build/Linux-x86_64/libmetis -lmetis
PARMETISLIB ?= -L${PARMETIS_DIR}/build/Linux-x86_64/libparmetis -lparmetis
I_PARMETIS  ?= -I${PARMETIS_DIR}/include -I${PARMETIS_DIR}/metis/include

# use existing modules on Edison
ifeq ($(findstring edison,$(shell uname -n)),edison)
METISLIB     = -L${METIS_DIR}/lib/ -lmetis
PARMETISLIB  = -L${PARMETIS_DIR}/lib/ -lparmetis
I_PARMETIS   = -I${METIS_DIR}/include -I${PARMETIS_DIR}/include
endif
############################################################################

# Define the required Fortran libraries, if you use C compiler to link
FLIBS	 	= 

# Define all the libraries
LIBS            = $(DSUPERLULIB) $(BLASLIB) $(PARMETISLIB) $(METISLIB)

#
#  The archiver and the flag(s) to use when building archive (library)
#  If your system has no ranlib, set RANLIB = echo.
#
ARCH         	= ar
ARCHFLAGS    	= cr
RANLIB       	= ranlib

############################################################################
# C compiler setup
CC             ?= mpicc
# CFLAGS should be set to be the C flags that include optimization
CFLAGS         ?= -std=c99 -pipe -O2 ${I_PARMETIS}
#
# NOOPTS should be set to be the C flags that turn off any optimization
NOOPTS		= 
############################################################################
# FORTRAN compiler setup
FORTRAN        ?= mpif77
F90FLAGS       ?= 
############################################################################
LOADER	       ?= mpif77
LOADOPTS	= 
############################################################################
ifeq ($(findstring edison,$(shell uname -n)),edison)
CC = cc
CFLAGS = -fast -m64 -std=c99 -Wall -DDEBUGlevel=0 -DPRNTlevel=0 -DPROFlevel=0 ${I_PARMETIS}
FORTRAN = ftn
F90FLAGS = -fast
LOADER = $(CC)
endif

############################################################################
#  C preprocessor defs for compilation (-DNoChange, -DAdd_, or -DUpCase)
#
#  Need follow the convention of how C calls a Fortran routine.
#
CDEFS        = -DAdd__ 
