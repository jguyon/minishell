#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/13 18:27:34 by jguyon            #+#    #+#              #
#    Updated: 2017/05/04 17:18:42 by jguyon           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Programs and their flags
SHELL = /bin/sh
CC = clang
CFLAGS = -Wall -Werror -Wextra -std=gnu11
CPPFLAGS =
LDFLAGS =
LDLIBS =
PROVE = prove -f

# Flags to add for debugging
DBGFLAGS = -g -DFT_FEATURE_DEBUG

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
	dlists \
	darrays \
	streams \
	printf \
	program \

# Executable name
NAME = 21sh

# Source names to compile the program
# main does not need to be specified here, it will be added in the Makefile
SOURCES = \
	errors/sh_strerror \
	\
	files/sh_path_join \
	files/sh_path_canonical \
	files/sh_check_dir \
	files/sh_check_bin \
	\
	builtins/sh_builtin_echo \
	builtins/sh_builtin_cd \
	builtins/sh_builtin_pwd \
	builtins/sh_builtin_env \
	builtins/sh_builtin_setenv \
	builtins/sh_builtin_unsetenv \
	builtins/sh_builtin_exit \
	\
	env/sh_env_start \
	env/sh_env_end \
	env/sh_env_vars \
	env/sh_env_getvar \
	env/sh_env_setvar \
	env/sh_env_unsetvar \
	env/sh_env_getcwd \
	env/sh_env_chdir \
	env/sh_env_binpath \
	env/sh_env_builtin \
	env/sh_env_exec_bin \
	env/sh_env_exec_builtin \
	env/sh_env_exec \
	env/sh_env_pipe \
	env/sh_env_wait \
	env/sh_env_exit \
	env/sh_env_should_exit \
	env/sh_env_status \
	\
	lexer/sh_lexer_init \
	lexer/sh_lexer_token \
	lexer/sh_lexer_word \
	lexer/sh_lexer_operator \
	lexer/sh_lexer_eoi \
	lexer/sh_lexer_translate \
	\
	parse/sh_parse_cmd \
	parse/sh_parse_pipelist \
	parse/sh_parse_seqlist \
	\
	ast/sh_word_new \
	ast/sh_word_tostr \
	ast/sh_word_del \
	ast/sh_cmd_new \
	ast/sh_cmd_push \
	ast/sh_cmd_toargv \
	ast/sh_cmd_del \
	ast/sh_pipelist_new \
	ast/sh_pipelist_push \
	ast/sh_pipelist_pop \
	ast/sh_pipelist_del \
	ast/sh_seqlist_new \
	ast/sh_seqlist_push \
	ast/sh_seqlist_pop \
	ast/sh_seqlist_del \
	\
	exec/sh_exec_cmd \
	exec/sh_exec_pipelist \
	exec/sh_exec_seqlist \
	\
	shell/sh_shell_start \
	shell/sh_shell_prompt \
	shell/sh_shell_end \

# Source names to execute as tests
TESTS = $(patsubst $(TEST_PATH)/%.c,%,$(wildcard $(TEST_PATH)/*/*.c))

# Source names to compile with every test executable
TESTS_COMMON = $(patsubst $(TEST_PATH)/%.c,%,$(wildcard $(TEST_PATH)/*.c))
