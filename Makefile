##
## EPITECH PROJECT, 2022
## Rtype [WSL: Ubuntu]
## File description:
## Makefile
##

NAME = menu
CXX = g++
LDFLAGS = -lstdc++fs -std=c++2a -pthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS = \
	$(wildcard src/client/*.cpp) \
   	$(wildcard src/client/menu/*.cpp) \
   	$(wildcard src/client/utils/*.cpp)         \

OBJS = $(SRCS:.cpp=.o)

CXXFLAGS = -Wall -Wextra

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) -rf $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test