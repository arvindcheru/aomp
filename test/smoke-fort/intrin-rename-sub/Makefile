NOOPT        = 1
NOOMP        = 1
OMP_FLAGS    = -DNOOMP
include ../../Makefile.defs

TESTNAME     = rename-sub
TESTSRC_MAIN = rename-sub.f90
TESTSRC_AUX  =
TESTSRC_ALL  = $(TESTSRC_MAIN) $(TESTSRC_AUX)

FLANG        ?= flang-new
OMP_BIN      = $(AOMP)/bin/$(FLANG)
CC           = $(OMP_BIN) $(VERBOSE)
#-ccc-print-phases
#"-\#\#\#"

RUNCMD       = ./doit.sh ${TESTNAME} && ./chkit.sh

include ../Makefile.rules
