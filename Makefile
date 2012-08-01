##################################################
#      makefile for c++ random.org client        #
##################################################

########################
#   user sepecifics    #
########################
# comment-out the following line to use gcc
USE_CLANG = 1
# comment-out the following line for 32-bit archetecture
IS_64BIT  = 1

########################
# do not modify below  #
########################
# library name
LIBNAME = RdO
# header & source files to compile
FILES = RdoAbsObject RdoQuota RdoIntegers RdoSequence \
	RdoStrings RdoRandom RdoBytes \
	RdoOptions
# binary executable programs
PROGRAMS = random-dot-org example-api-fake-key example-api-powerlaw
# version number
VERSION   = 0.1
# general rules
include makefiles/Makefile.common
