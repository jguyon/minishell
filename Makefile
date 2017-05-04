#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/04 15:58:00 by jguyon            #+#    #+#              #
#    Updated: 2017/05/04 16:39:36 by jguyon           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

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

# Release target (default)
all: $(NAME)

# Compile program with debug flags
debug: LIBFT_MODULES := $(strip $(LIBFT_MODULES) debug tap)
debug: CPPFLAGS := $(strip $(CPPFLAGS) $(DBGFLAGS))
debug: LDLIBS := $(strip $(LDLIBS) -ldbg)
debug: $(LIBDBG) $(NAME)

# Compile tests
# If the program needs to be updated, test flags will be used.
# Use the check target to avoid that.
test: LIBFT_MODULES := $(strip $(LIBFT_MODULES) debug tap)
test: CPPFLAGS := $(strip $(CPPFLAGS) $(DBGFLAGS))
test: LDLIBS := $(strip $(LDLIBS) -ldbg -ltap)
test: $(LIBDBG) $(LIBTAP) $(TST_EXE)

# Compile the program and execute its tests
# If a version of the program is already compiled and does not need updating,
# it will not be recompiled.
# As a consequence, running for example make fclean && make -j all check
# will test the release version even if check is configured to default
# to the debug version.
ifeq ($(strip $(TST_EXE)),)
check:
	@echo "Could not find any tests"
else
check: test
	$(PROVE) $(TST_EXE)
endif

# Remove intermediate files
clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	-rm -f $(OBJ) $(DEP) $(TST_DEP) $(LIBFT) $(LIBDBG) $(LIBTAP)

# Remove executable, tests and intermediate files
fclean: clean
	-rm -f $(NAME) $(TST_EXE)

# Recompile executable
re: fclean all

.PHONY: all debug test check clean fclean re force

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(LDFLAGS) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_PATH)/%.o: %.c $(BUILD_PATH)/%.d
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<
	@touch $@

$(BUILD_PATH)/%.t: %.c $(BUILD_PATH)/%.d $(TST_CMN) $(TST_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $(filter %.c %.o,$^) $(LDLIBS)
	@touch $@

$(BUILD_PATH)/%.d: ;

-include $(DEP) $(TST_DEP)

$(OBJ) $(TST_EXE): | $(PATHS)

$(LIBFT): force
	@$(MAKE) -C $(LIBFT_PATH) \
		NAME='$(patsubst $(LIBFT_PATH)/%.a,%.a,$@)' \
		MODULES='$(LIBFT_MODULES)' \
		CPPFLAGS='$(CPPFLAGS)'

$(LIBDBG): force
	@$(MAKE) -C $(LIBFT_PATH) \
		NAME='$(patsubst $(LIBFT_PATH)/%.a,%.a,$@)' \
		MODULES='debug' \
		CPPFLAGS='$(CPPFLAGS)'

$(LIBTAP): force
	@$(MAKE) -C $(LIBFT_PATH) \
		NAME='$(patsubst $(LIBFT_PATH)/%.a,%.a,$@)' \
		MODULES='tap' \
		CPPFLAGS='$(CPPFLAGS)'

$(PATHS):
	@mkdir -p $@
