#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 14:04:23 by jguyon            #+#    #+#              #
#    Updated: 2017/02/25 18:14:58 by jguyon           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Programs and their flags
SHELL = /bin/sh
CC = clang
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS =
LDFLAGS =
LDLIBS =
PROVE = prove -f

# Flags for release and debug versions, and test executables
RLSFLAGS =
DBGFLAGS = -g
TSTFLAGS = $(DBGFLAGS)

# Default targets for building or testing (debug or release)
DEFAULT_BUILD = release
CHECK_BUILD = debug

# Paths to find sources and headers in
SOURCE_PATH = srcs
TEST_PATH = tests
INCLUDE_PATH = includes

# Path to put intermediate files in
BUILD_PATH = build

# Path to libft
LIBFT_PATH = libft

# Needed libft modules
LIBFT_MODULES = \
	memory \
	strings \
	chars \
	numbers \
	unicode \
	dlists \
	darrays \
	streams \
	printf \
	program \

# Executable name
NAME = minishell

# Source names to compile the program
# main does not need to be specified here, it will be added in the Makefile
SOURCES = \
	sh_strerror \
	\
	sh_builtin_echo \
	sh_builtin_cd \
	sh_builtin_pwd \
	sh_builtin_env \
	sh_builtin_setenv \
	sh_builtin_unsetenv \
	sh_builtin_exit \
	\
	sh_env_start \
	sh_env_end \
	sh_env_vars \
	sh_env_getvar \
	sh_env_setvar \
	sh_env_unsetvar \
	sh_env_binpath \
	sh_env_builtin \
	sh_env_exec_bin \
	sh_env_exec_builtin \
	sh_env_exec \
	sh_env_exit \
	sh_env_should_exit \
	sh_env_status \
	\
	sh_init_input \
	sh_parse_word \
	sh_parse_cmd \
	\
	sh_word_new \
	sh_word_tostr \
	sh_word_del \
	sh_cmd_new \
	sh_cmd_push \
	sh_cmd_toargv \
	sh_cmd_del \
	\
	sh_exec_cmd \
	\
	sh_shell_start \
	sh_shell_prompt \
	sh_shell_end \

# Wildcard for test files, it makes experimentation easier
TEST_FILES := $(basename $(notdir $(wildcard $(TEST_PATH)/*.c)))

# Source names to execute as tests
TESTS = $(filter test_%,$(TEST_FILES))

# Source names to compile with every test executable
TESTS_COMMON = $(filter-out $(TESTS),$(TEST_FILES))
