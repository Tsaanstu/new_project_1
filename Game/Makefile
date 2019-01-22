TARGET = main.out
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
# XXX: Don't forget backslash at the end of any line except the last one
HDRS = \
	    project/include

SRCS = \
	project/src/main.cpp \
	project/src/main_menu.cpp \
	project/src/questions.cpp \
	project/src/questions_from_file.cpp \
	project/src/quiz_mermaid.cpp \
	project/src/quiz.cpp \
	project/src/Witch.cpp \
	project/src/Tree.cpp \
	project/src/GameFW.cpp \
	project/src/Floor.cpp \
	project/src/game_lab.cpp \
	project/src/map.cpp \
	project/src/man.cpp \
	project/src/player.cpp \
	project/src/view.cpp \
	project/src/labirint.cpp \
	project/src/enemy.cpp \
	project/src/game_paradise.cpp \
	project/src/platform.cpp \
	project/src/ball.cpp \
	project/src/game_hell.cpp \
	project/src/animation.cpp \
	project/src/button.cpp \
	project/src/command.cpp \
	project/src/db.cpp \
	project/src/definitions.cpp \
	project/src/entry.cpp \
	project/src/finish.cpp \
	project/src/game.cpp \
	project/src/player_move.cpp \
	project/src/player_moves.cpp \
	project/src/storyline.cpp


.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=gnu++17 -Wall -Wextra -w $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS) $(FLAGS)	
 
clean:
	rm -rf $(TARGET)
