#
#  makefile - x11-keyboard demonstration code.
#
#  Copyright(C) 2021 - MT
#
#  This  program is free software: you can redistribute it and/or modify it
#  under  the terms of the GNU General Public License as published  by  the
#  Free  Software Foundation,  either version 3 of the License,  or (at  your
#  option) any later version.
#
#  This  program  is distributed in the hope that it will  be  useful,   but
#  WITHOUT   ANY   WARRANTY;   without even   the   implied   warranty   of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
#  Public License for more details.
#
#  You  should have received a copy of the GNU General Public License along
#  with this program.  If not,  see <http://www.gnu.org/licenses/>.
#
#	Note separator (tab) at the beginning of the line CANNOT be a space..!
#
#	20 Sep 21   0.1	- Initial version - MT
#							- Added '-no-pie' option so that the resulting program
#							  can be executed by double clicking on it - MT
#

PROGRAM 	= x11-keyboard
SOURCES 	= x11-keyboard.c
FILES		= *.c *.h LICENSE README.md makefile .gitignore .gitattributes
OBJECTS	= $(SOURCES:.c=.o)
OUTPUT	= $(PROGRAM).out
LIBS		= -lX11 -lm
INCLUDE	= .
FLAGS		= -Wall -pedantic -ansi -no-pie 
FLAGS		+= -Wno-comment -Wno-deprecated-declarations
#FLAGS		+= -g # For debugging
CC			= gcc

$(PROGRAM): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) -o $@ $(LIBS)

$(OBJECTS) : $(SOURCES)
	@$(CC) $(FLAGS) -c $(SOURCES) -I $(INCLUDE)

all: clean $(PROGRAM) $(OBJECTS)

clean:
	@rm -f $(OBJECTS)
#	@rm -f $(PROGRAM)

backup:
	@echo "$(PROGRAM)-`date +'%Y%m%d%H%M'`.tar.gz"; tar -czpf ..\/$(PROGRAM)-`date +'%Y%m%d%H%M'`.tar.gz $(FILES)

