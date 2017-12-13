CONNECTALDIR := ../../connectal

USER_CLK_PERIOD := 40

BUILD_DIR := $(CURDIR)/build
PROJECTDIR = $(BUILD_DIR)/$(BOARD)

S2H_INTERFACES = LoopReq:Loop.loop
H2S_INTERFACES = Loop:LoopInd:host

BSVFILES = LoopIF.bsv
CPPFILES = test.cpp

CONNECTALFLAGS += -D IMPORT_HOSTIF -D XILINX_SYS_CLK --nocache -v
CONNECTALFALGS += --mainclockperiod=$(USER_CLK_PERIOD)

include $(CONNECTALDIR)/Makefile.connectal
