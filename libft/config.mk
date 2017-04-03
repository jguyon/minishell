#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/05 15:28:18 by jguyon            #+#    #+#              #
#    Updated: 2017/02/20 02:14:48 by jguyon           ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Programs and their flags
SHELL = /bin/sh
CC = clang
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS =
LDFLAGS =
LDLIBS =
AR = ar
ARFLAGS = rcs
PROVE = prove -f

# Flags for release and debug versions, and test executables
RLSFLAGS =
DBGFLAGS = -g -DFT_FEATURE_DEBUG
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

# Release and debug name of the library
NAME = libft.a

# Modules to include in the build
MODULES = \
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
	debug \
	tap \

# Sources names to include in the library
SOURCES = \
	memory/ft_memalloc \
	memory/ft_memdel \
	memory/ft_memchr \
	memory/ft_memcmp \
	memory/ft_memset \
	memory/ft_bzero \
	memory/ft_memcpy \
	memory/ft_memccpy \
	memory/ft_memmove \
	\
	strings/ft_strnew \
	strings/ft_strdel \
	strings/ft_strdup \
	strings/ft_strsub \
	strings/ft_strjoin \
	strings/ft_strtrim \
	strings/ft_strsplit \
	strings/ft_strlen \
	strings/ft_strnlen \
	strings/ft_strchr \
	strings/ft_strrchr \
	strings/ft_strchrnul \
	strings/ft_strstr \
	strings/ft_strnstr \
	strings/ft_strcmp \
	strings/ft_strncmp \
	strings/ft_strequ \
	strings/ft_strnequ \
	strings/ft_strclr \
	strings/ft_strcpy \
	strings/ft_strncpy \
	strings/ft_strcat \
	strings/ft_strncat \
	strings/ft_strlcat \
	\
	chars/ft_isalpha \
	chars/ft_isdigit \
	chars/ft_isalnum \
	chars/ft_isascii \
	chars/ft_isprint \
	chars/ft_toupper \
	chars/ft_tolower \
	\
	numbers/ft_atoi \
	numbers/ft_itoa \
	\
	unicode/ft_wcconv \
	unicode/ft_wclen \
	unicode/ft_wstrlen \
	\
	dlists/ft_dlst_init \
	dlists/ft_dlst_insertl \
	dlists/ft_dlst_insertr \
	dlists/ft_dlst_pushl \
	dlists/ft_dlst_pushr \
	dlists/ft_dlst_remove \
	dlists/ft_dlst_popl \
	dlists/ft_dlst_popr \
	dlists/ft_dlst_replace \
	dlists/ft_dlst_swap \
	dlists/ft_dlst_slice \
	dlists/ft_dlst_splicel \
	dlists/ft_dlst_splicer \
	dlists/ft_dlst_joinl \
	dlists/ft_dlst_joinr \
	dlists/ft_dlst_prev \
	dlists/ft_dlst_next \
	dlists/ft_dlst_first \
	dlists/ft_dlst_last \
	dlists/ft_dlst_empty \
	dlists/ft_dlst_singular \
	dlists/ft_dlst_foreachl \
	dlists/ft_dlst_foreachr \
	dlists/ft_dlst_foreachl_from \
	dlists/ft_dlst_foreachr_from \
	dlists/ft_dlst_sort \
	\
	darrays/ft_darr_init \
	darrays/ft_darr_copy \
	darrays/ft_darr_set \
	darrays/ft_darr_get \
	darrays/ft_darr_clear \
	\
	streams/ft_fopencookie \
	streams/ft_fmemopen \
	streams/ft_open_memstream \
	streams/ft_fdopen \
	streams/ft_setvbuf \
	streams/ft_fwrite \
	streams/ft_fread \
	streams/ft_fputc \
	streams/ft_fgetc \
	streams/ft_fputs \
	streams/ft_fgets \
	streams/ft_ferror \
	streams/ft_feof \
	streams/ft_clearerr \
	streams/ft_fflush \
	streams/ft_fclose \
	streams/ft_fcloseall \
	\
	printf/ft_printf \
	printf/ft_vprintf \
	printf/ft_snprintf \
	printf/ft_vsnprintf \
	printf/ft_fprintf \
	printf/ft_vfprintf \
	printf/pf_parse_info \
	printf/pf_convert \
	printf/pf_convert_char \
	printf/pf_convert_str \
	printf/pf_convert_int \
	printf/pf_convert_uint \
	printf/pf_convert_ptr \
	printf/pf_uintmax_len \
	printf/pf_write_pad \
	printf/pf_write_str \
	printf/pf_write_wstr \
	printf/pf_write_uint \
	\
	debug/ft_debug \
	debug/ft_assert \
	\
	tap/ft_tap_start \
	tap/ft_tap_end \
	tap/ft_tap_pass \
	tap/ft_tap_fail \
	tap/ft_tap_diag \
	tap/ft_tap_plan \
	tap/ft_tap_test \
	tap/ft_tap_ok \
	tap/ft_tap_notok \
	tap/ft_tap_ieq \
	tap/ft_tap_notieq \
	tap/ft_tap_ueq \
	tap/ft_tap_notueq \
	tap/ft_tap_seq \
	tap/ft_tap_notseq \
	tap/ft_tap_quote \
	\
	program/ft_onexit \
	program/ft_cleanup \
	program/ft_exit \
	program/ft_setprogname \
	program/ft_getprogname \
	program/ft_getopt \
	program/ft_error \

# Wildcard for test files, it makes experimentation easier
TEST_FILES := $(basename $(notdir $(wildcard $(TEST_PATH)/*.c)))

# Source names to execute as tests
TESTS = $(filter test_%,$(TEST_FILES))

# Source names to compile with every test executable
TESTS_COMMON = $(filter-out $(TESTS),$(TEST_FILES))
