include ../../Makefile.defs

TESTNAME     = gep_ptr2
TESTSRC_MAIN = gep_ptr2.f90
TESTSRC_AUX  =
TESTSRC_ALL  = $(TESTSRC_MAIN) $(TESTSRC_AUX)

FLANG        ?= flang-new
CFLAGS       = -c
OMP_BIN      = $(AOMP)/bin/$(FLANG)
CC           = $(OMP_BIN) $(VERBOSE)
#-ccc-print-phases
#"-\#\#\#"

RUNCMD       = ./doit.sh > ${TESTNAME}.out 2>&1 && ./chkit.sh ${TESTNAME}.out

include ../Makefile.rules
