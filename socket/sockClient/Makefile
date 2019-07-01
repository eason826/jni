# Created with gm.pl v0.1 on Thu Apr 13 22:57:21 2017
include build/linux_host.mk
#include build/imx.mk

INCLUDES= -I./include/
LIBS:=

DEFINES= $(INCLUDES) $(DEFS) -D_GNU_SOURCE -DLINUX
CFLAGS= -fPIC $(DEFINES)

SRCS_ROOT=sw
BIN_SRCS_ROOT=process

include build/rule.mk

clean:
	@echo $(APPNAME)
	$(rm) $(OBJS) $(BIN_OBJS) $(LIBNAME) core *~
	@for i in $(APPNAME);do $(rm) $(BIN_DIR)/$$i;done
