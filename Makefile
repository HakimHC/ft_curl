#***************************************************************#
#                                                               #
#                                                               #
#                           ft_curl                            	#
#                                                               #
#                                                               #
#***************************************************************#

NAME 				= ft_curl

#***************************************************************#
#                                                               #
#                                                               #
#                           Compiler                           	#
#                                                               #
#                                                               #
#***************************************************************#

CXX					= g++

CXXFLAGS 		= -Wall -Werror -Wextra
CXXFLAGS 		+= -Wconversion -Wshadow -pedantic
CXXFLAGS 		+= -g3

CXXFLAGS 		+= -I ./include
CXXFLAGS 		+= -I ./cxxopts/include
CXXFLAGS 		+= -I ./src/arguments
CXXFLAGS 		+= -I ./src/client

#***************************************************************#
#                                                               #
#                                                               #
#                           Source                             	#
#                                                               #
#                                                               #
#***************************************************************#

SRCDIR			= src

ARG					= $(addprefix $(ARGDIR)/,$(ARGSRC))
ARGDIR			= arguments
ARGSRC			= Arguments.cpp \

CLIENT					= $(addprefix $(CLIENTDIR)/,$(CLIENTSRC))
CLIENTDIR			= client
CLIENTSRC			= Client.cpp \

MAIN					= $(addprefix $(MAINDIR)/,$(MAINSRC))
MAINDIR			= main
MAINSRC			= main.cpp \

SRC 				= $(addprefix $(SRCDIR)/,$(ARG))
SRC 				+= $(addprefix $(SRCDIR)/,$(CLIENT))
SRC 				+= $(addprefix $(SRCDIR)/,$(MAIN))

#***************************************************************#
#                                                               #
#                                                               #
#                           OBJECTS                             #
#                                                               #
#                                                               #
#***************************************************************#

OBJ = $(SRC:.cpp=.o)

#***************************************************************#
#                                                               #
#                                                               #
#                           RULES                             	#
#                                                               #
#                                                               #
#***************************************************************#

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:: fclean
re:: all

.PHONY: all clean fclean re
