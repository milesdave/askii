#ifndef _CONFIG_H
#define _CONFIG_H

// sprites
#define CHAR_PLAYER_LEFT '/'
#define CHAR_PLAYER_DOWN '|'
#define CHAR_PLAYER_RIGHT '\\'
#define CHAR_PLAYER_GAMEOVER 'X'
#define CHAR_TREE 'A'

// colours
#define COLOUR_PLAYER_ID 1
#define COLOUR_PLAYER COLOR_BLUE
#define COLOUR_TREE_ID 2
#define COLOUR_TREE COLOR_GREEN
#define COLOUR_SCORE_ID 3
#define COLOUR_SCORE_FG COLOR_WHITE
#define COLOUR_SCORE_BG COLOR_RED
#define COLOUR_WINDOW_ID 4
#define COLOUR_WINDOW_FG COLOR_WHITE
#define COLOUR_WINDOW_BG COLOR_RED
#define COLOUR_SHADOW_ID 5
#define COLOUR_SHADOW COLOR_BLACK

// limits
#define SPAWN_INTERVAL 4
#define SPEED_INIT 10
#define SPEED_MAX 70
#define SPEED_INTERVAL 100
#define SPEED_INCREASE 2

// keys
#define KEY_QUIT 'q'
#define KEY_PAUSE 'p'
#define _KEY_LEFT KEY_LEFT
#define _KEY_DOWN KEY_DOWN
#define _KEY_RIGHT KEY_RIGHT

// geometry
#define WIN_GAMEOVER_W 21
#define WIN_GAMEOVER_H 7
#define WIN_GAMEOVER_X ((termw / 2) - (WIN_GAMEOVER_W / 2))
#define WIN_GAMEOVER_Y ((termh / 2) - (WIN_GAMEOVER_H / 2))
#define WIN_PAUSED_W 10
#define WIN_PAUSED_H 3
#define WIN_PAUSED_X ((termw / 2) - (WIN_PAUSED_W / 2))
#define WIN_PAUSED_Y (termh - (termh / 3))
#define WIN_TITLE_W 22
#define WIN_TITLE_H 6
#define WIN_TITLE_X ((termw / 2) - (WIN_TITLE_W / 2))
#define WIN_TITLE_Y ((termh / 2) - (WIN_TITLE_H / 2))

// text
#define TEXT_GAMEOVER_1 "OUCH!"
#define TEXT_GAMEOVER_2 "YOU MADE IT"
#define TEXT_GAMEOVER_3 "LAST RUN"
#define TEXT_PAUSED "PAUSED"
#define TEXT_TITLE_1 " askii "
#define TEXT_TITLE_2 "ANY KEY START"
#define TEXT_TITLE_3 "ARROWS MOVE"
#define TEXT_TITLE_4 "P PAUSE"
#define TEXT_TITLE_5 "Q QUIT"

// last score file
#define FILE_SCORE "/tmp/askii-score"

#endif
