#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2017/04/03 17:32:04 by jguyon            #+#    #+#             *#
#*   Updated: 2017/04/03 17:32:08 by jguyon           ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

# Configuration variables
include config.mk
# Local overrides, should be excluded from version-control
-include local.mk

LIBFT = $(LIBFT_PATH)/libft.a
LIBDBG = $(LIBFT_PATH)/libdbg.a
LIBTAP = $(LIBFT_PATH)/libtap.a

override CPPFLAGS := $(strip $(CPPFLAGS) \
	-I$(INCLUDE_PATH) -I$(LIBFT_PATH)/includes \
	-MMD -MP)
override LDFLAGS := $(strip $(LDFLAGS) -L$(LIBFT_PATH))
override LDLIBS := -lft

SRC := $(SOURCES:%=$(SOURCE_PATH)/%.c) $(SOURCE_PATH)/main.c
OBJ := $(SRC:%.c=$(BUILD_PATH)/%.o)
DEP := $(OBJ:%.o=%.d)

TST_SRC := $(TESTS:%=$(TEST_PATH)/%.c)
TST_CMN := $(TESTS_COMMON:%=$(TEST_PATH)/%.c)
TST_OBJ := $(filter-out $(BUILD_PATH)/$(SOURCE_PATH)/main.o,$(OBJ))
TST_EXE := $(TST_SRC:%.c=$(BUILD_PATH)/%.t)
TST_DEP := $(TST_EXE:%.t=%.d)

PATHS := $(sort $(dir $(OBJ) $(TST_EXE)))

# Default target
all: $(DEFAULT_BUILD)

# Compile program with release flags
release: CPPFLAGS := $(strip $(CPPFLAGS) $(RLSFLAGS))
release: LDFLAGS := $(strip $(LDFLAGS) $(RLSFLAGS))
release: LIBFT_BUILD := release
release: $(NAME)

# Compile program with debug flags
debug: CPPFLAGS := $(strip $(CPPFLAGS) $(DBGFLAGS) -DFT_FEATURE_DEBUG)
debug: LDFLAGS := $(strip $(LDFLAGS) $(DBGFLAGS))
debug: LDLIBS := $(strip $(LDLIBS) -ldbg)
debug: LIBFT_BUILD := debug
debug: $(LIBDBG) $(NAME)

# Compile tests
# If the program needs to be updated, test flags will be used.
# Use the check target to avoid that.
test: CPPFLAGS := $(strip $(CPPFLAGS) $(TSTFLAGS) -DFT_FEATURE_DEBUG)
test: LDFLAGS := $(strip $(LDFLAGS) $(TSTFLAGS))
test: LDLIBS := $(strip $(LDLIBS) -ldbg -ltap)
test: LIBFT_BUILD := debug
test: $(LIBDBG) $(TST_EXE)

# Compile the program and execute its tests
# If a version of the program is already compiled and does not need updating,
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
	@$(MAKE) -C $(LIBFT_PATH) -s -w clean
	-rm -f $(OBJ) $(DEP) $(TST_DEP) $(LIBFT) $(LIBTAP)

# Remove executable, tests and intermediate files
fclean: clean
	-rm -f $(NAME) $(TST_EXE)

# Recompile executable
re: fclean all

.PHONY: all release debug test check clean fclean re force

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_PATH)/%.o: %.c $(BUILD_PATH)/%.d
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@touch $@

$(BUILD_PATH)/%.t: %.c $(BUILD_PATH)/%.d $(TST_CMN) $(TST_OBJ) $(LIBFT) $(LIBTAP)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(filter %.c %.o,$^) $(LDLIBS)
	@touch $@

$(BUILD_PATH)/%.d: ;

-include $(DEP) $(TST_DEP)

$(OBJ) $(TST_EXE): | $(PATHS)

$(LIBFT): force
	@$(MAKE) -C $(LIBFT_PATH) -j -s -w \
		NAME='$(patsubst $(LIBFT_PATH)/%.a,%.a,$@)' \
		MODULES='$(LIBFT_MODULES)' \
		$(LIBFT_BUILD)

$(LIBDBG): force
	@$(MAKE) -C $(LIBFT_PATH) -j -s -w \
		NAME='$(patsubst $(LIBFT_PATH)/%.a,%.a,$@)' \
		MODULES=debug \
		CPPFLAGS='-DFT_DEBUG_FILE="\"$(NAME).log\""' \
		$(LIBFT_BUILD)

$(LIBTAP): force
	@$(MAKE) -C $(LIBFT_PATH) -j -s -w \
		NAME='$(patsubst $(LIBFT_PATH)/%.a,%.a,$@)' \
		MODULES=tap \
		$(LIBFT_BUILD)

$(PATHS):
	@mkdir -p $@
