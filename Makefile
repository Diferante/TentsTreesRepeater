 #*****************************************************************************
 #  Copyright (C) 2019 - Haohua Dong e Diogo Antunes
 #
 #  This file is a part of TentsTreesRepeater.
 #
 #  TentsTreesRepeater is free software: you can redistribute it and/or
 #  modify it under the terms of the GNU General Public License as published by
 #  the Free Software Foundation, either version 3 of the License, or
 #  (at your option) any later version.
 #
 #  TentsTreesRepeater is distributed in the hope that it will be useful,
 #  but WITHOUT ANY WARRANTY; without even the implied warranty of
 #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #  GNU General Public License for more details.
 #
 #  You should have received a copy of the GNU General Public License
 #  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 #
 #*****************************************************************************

# compiler
CC = gcc
CFLAGS = -Wall -std=c99 -O3 
TARGET = testgenerator

# objects (make automatically makes x.o from x.c)
OBJECTS = mapgenerator.o 


testgenerator: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

debug: CFLAGS = -Wall -std=c99 -g 
debug: testgenerator



clean:
	rm -f *.o
