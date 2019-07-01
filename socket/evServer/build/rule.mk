include build/dir.mk
SRCS_DIR=$(shell find $(SRCS_ROOT)  -maxdepth 3 -type d)
BIN_SRCS_DIR=$(shell find $(BIN_SRCS_ROOT)  -maxdepth 2 -type d)

SRCS = $(foreach d,$(SRCS_DIR),$(wildcard $(d)/*.cpp))
OBJS = $(addprefix $(OBJS_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(SRCS))))
BIN_SRCS = $(foreach d,$(BIN_SRCS_DIR),$(wildcard $(d)/*.cpp))
BIN_OBJS = $(addprefix $(OBJS_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(BIN_SRCS))))
APPNAME=$(foreach d,$(BIN_SRCS),$(notdir $(basename $(d))))
BBNAME=$(filter-out $(SRCS_ROOT),$(foreach d,$(SRCS_DIR),$(notdir $(basename $(d)))))
BBDIR=$(filter-out $(SRCS_ROOT),$(foreach d,$(SRCS_DIR),$(basename $(d))))
LIBNAME=$(foreach d,$(BBNAME),$(addsuffix .$(LIB_SUFFIX),$(addprefix $(LIB_DIR)/lib,$(d))))

define make-obj
$1:$2
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

define make-bin
$1:$2
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$$@ $$< -Wl,--start-group $(LIBNAME) -Wl,--end-group $(LIBS)
endef

define make-a
$1:$2
	$(AR) $$@ $2
endef

define make-so
$1:$2
	$(CC) -shared -o $$@ $2
endef

all: gen $(LIBNAME) $(APPNAME)

gen:
	$(MKDIR) $(OBJS_DIR)
	$(MKDIR) $(LIB_DIR)
	$(MKDIR) $(BIN_DIR)

$(foreach d,$(BBDIR),\
	$(eval $(call make-$(LIB_SUFFIX),$(addsuffix .$(LIB_SUFFIX),$(addprefix $(LIB_DIR)/lib,$(notdir $(d)))),\
	$(addprefix $(OBJS_DIR)/,\
	$(patsubst %.cpp,%.o,$(notdir $(wildcard $(d)/*.cpp)))))))
$(foreach d,$(SRCS_DIR),\
	$(eval $(call make-obj,$(OBJS_DIR)/%.o,$(d)/%.cpp)))
$(foreach d,$(BIN_SRCS_DIR),\
	$(eval $(call make-obj,$(OBJS_DIR)/%.o,$(d)/%.cpp)))
$(foreach d,$(APPNAME),\
	$(eval $(call make-bin,$(d),\
	$(addprefix $(OBJS_DIR)/,$(addsuffix .o, $(d))))))
