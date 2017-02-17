#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 14:04:23 by jguyon            #+#    #+#              #
#    Updated: 2017/02/17 20:11:28 by jguyon           ###   ########.fr        #
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
	streams \
	printf \
	program \

# Executable name
NAME = minishell

# Source names to compile the program
# main does not need to be specified here, it will be added in the Makefile
SOURCES = \
	ms_error \
	\
	ms_env_start \
	ms_env_end \
	ms_env_get \
	ms_env_set \
	ms_env_unset \
	ms_env_clear \
	ms_resolve_bin \
	\
	ms_parse_cmd \
	ms_exec_cmd \
	ms_destroy_cmd \

# Wildcard for test files, it makes experimentation easier
TEST_FILES := $(basename $(notdir $(wildcard $(TEST_PATH)/*.c)))

# Source names to execute as tests
TESTS = $(filter test_%,$(TEST_FILES))

# Source names to compile with every test executable
TESTS_COMMON = $(filter-out $(TESTS),$(TEST_FILES))
