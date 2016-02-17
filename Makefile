##
## Makefile for cpp_bomberman in /home/quivy_a/Developpement/C++/Bomberman
## 
## Made by Alexandre Quivy
## Login   <quivy_a@epitech.net>
## 
## Started on  Mon May  4 13:25:41 2015 Alexandre Quivy
## Last update Sun Jun 14 22:29:35 2015 Alexandre Quivy
##

CC	=	g++

GREEN	=	\033[32m
END	=	\033[m
PRINTF	=	/usr/bin/printf

RM	=	rm -rf

CPPFLAGS +=	-W -Wall -Wextra -Werror -O
CPPFLAGS +=	-I./GDL/includes -L./GDL/libs -L./SFML/lib -I./SFML/include
CPPFLAGS +=	-lgdl_gl -lGL -lGLEW -ldl -lrt -lfbxsdk -lSDL2 -lpthread -lsfml-system -lsfml-audio

NAME	=	bomberman

SRCS	=	src/main.cpp \
		GDL/src/BasicShader.cpp \
		src/Camera.cpp \
		src/GameEngine.cpp \
		src/Map.cpp \
		src/BlockWall.cpp \
		src/BlockGround.cpp \
		src/BlockCrate.cpp \
		src/ABlock.cpp \
		src/Bomb.cpp \
		src/AItem.cpp \
		src/ItemRange.cpp \
		src/ItemCount.cpp \
		src/ItemSpeed.cpp \
		src/Explosion.cpp \
		src/Player.cpp \
		src/HumanPlayer.cpp \
		src/AIPlayer.cpp \
		src/PlayerInput.cpp \
		src/MenuEngine.cpp \
		src/SoundEngine.cpp \
                src/ButtonMenu.cpp \
                src/ButtonSelector.cpp \
                src/NumLabel.cpp \
                src/Background.cpp \
		src/GameBackground.cpp \
		src/ScoreManager.cpp

OBJS	=	$(SRCS:.cpp=.o)

OBJSM	=	$(SRCSM:.cpp=.o)

all:	$(NAME)

$(NAME):	$(OBJS)
		@$(CC) $(OBJS) $(CPPFLAGS) -ldl -o $(NAME)
		@$(PRINTF) "$(GREEN)[OK]$(END) lib successfully compiled and linked\n"

clean:
	@$(RM) $(OBJS) $(OBJS_M)
	@$(PRINTF) "$(GREEN)[OK]$(END) CLEAN $(NAME) - objects\n"

fclean:	clean
	@$(RM) $(NAME) bombermanMenu
	@$(PRINTF) "$(GREEN)[OK]$(END) FCLEAN $(NAME)\n"

re:	fclean all
