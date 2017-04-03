#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/17 15:12:56 by jguyon            #+#    #+#              #
#*   Updated: 2017/03/28 18:55:11 by jguyon           ###   ########.fr       *#
#                                                                              #
#******************************************************************************#

# Configuration variables
include config.mk
# Local overrides, should be excluded from version-control
-include local.mk

override CPPFLAGS := $(strip $(CPPFLAGS) -I$(INCLUDE_PATH) -MMD -MP)
override LDFLAGS := $(strip $(LDFLAGS) -L.)
override LDLIBS := $(strip $(LDLIBS) $(NAME:lib%.a=-l%))

SOURCES := $(foreach module,$(MODULES),$(filter $(module)/%,$(SOURCES)))

SRC := $(SOURCES:%=$(SOURCE_PATH)/%.c)
OBJ := $(SRC:%.c=$(BUILD_PATH)/%.o)
DEP := $(OBJ:%.o=%.d)

TST_SRC := $(TESTS:%=$(TEST_PATH)/%.c)
TST_CMN := $(TESTS_COMMON:%=$(TEST_PATH)/%.c)
TST_EXE := $(TST_SRC:%.c=$(BUILD_PATH)/%.t)
TST_DEP := $(TST_EXE:%.t=%.d)

PATHS := $(sort $(dir $(OBJ) $(TST_EXE)))

# Default target
all: $(DEFAULT_BUILD)

# Compile library with release flags
release: CPPFLAGS := $(strip $(CPPFLAGS) $(RLSFLAGS))
release: $(NAME)

# Compile library with debug flags
debug: CPPFLAGS := $(strip $(CPPFLAGS) $(DBGFLAGS))
debug: $(NAME)

# Compile tests
# If the library needs to be updated, test flags will be used.
# Use the check target to avoid that.
test: CPPFLAGS := $(strip $(CPPFLAGS) $(TSTFLAGS))
test: $(TST_EXE)

# Compile the library and execute its tests
# If a version of the library is already compiled and does not need updating,
# it will not be recompiled.
# As a consequence, running for example make fclean && make -j release check
# will test the release version even if check is configured to default
# to the debug version.
ifeq ($(strip $(TST_EXE)),)
check:
	@echo "Could not find any tests"
else
check: $(CHECK_BUILD) test
	$(PROVE) $(TST_EXE)
endif

# Remove intermediate files
clean:
	-rm -f $(OBJ) $(DEP) $(TST_DEP)

# Remove library, tests and intermediate files
fclean: clean
	-rm -f $(NAME) $(TST_EXE)

# Recompile library
re: fclean all

.PHONY: all release debug test check clean fclean re

$(NAME): $(OBJ)
	@rm -f $@
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_PATH)/%.o: %.c $(BUILD_PATH)/%.d
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@touch $@

$(BUILD_PATH)/%.t: %.c $(BUILD_PATH)/%.d $(TST_CMN) $(NAME)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(filter %.c,$^) $(LDLIBS)
	@touch $@

$(BUILD_PATH)/%.d: ;

-include $(DEP) $(TST_DEP)

$(OBJ) $(TST_EXE): | $(PATHS)

$(PATHS):
	@mkdir -p $@
