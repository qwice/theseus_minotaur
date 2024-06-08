///////////////////////
// 과목명 : 알고리즘     //
// 이름 : 정상기	    //
// 학번 : 2019707048  //
///////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 10000
#define MAX_MAZE_WIDTH 31
#define MAX_MAZE_HEIGHT 21

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position theseus;
    Position minotaur;
} State;

typedef struct {
    State state;
    int prevIndex;
    char move;
} QueueElement;

const char *mazes[10][MAX_MAZE_HEIGHT] = {
    {
        "##########",
        "##########",
        "##  M  ###",
        "##  ## ###",
        "##   #  E#",
        "##  ## ###",
        "##  T  ###",
        "##########",
        "##########"
    },
    {
        "##########",
        "##########",
        "##  M  ###",
        "##  #  ###",
        "##  T   E#",
        "##     ###",
        "## #   ###",
        "####   ###",
        "##     ###",
        "##########",
        "##########"
    },
    {
        "#################",
        "#################",
        "##             ##",
        "##             ##",
        "##M# #T        ##",
        "## ###         ##",
        "##         # # ##",
        "##         ### ##",
        "##             ##",
        "#### ############",
        "####E############",
        "#################"
    },
    {
        "###############",
        "##########E####",
        "########## ####",
        "##T        # ##",
        "####       # ##",
        "##   #   # # ##",
        "## ### # ### ##",
        "## # # #  M  ##",
        "## # ### ##  ##",
        "## #     #   ##",
        "## # ###     ##",
        "## # #       ##",
        "## # #       ##",
        "##           ##",
        "###############",
        "###############"
    },
    {
        "###############",
        "####E##########",
        "#### ##########",
        "##         # ##",
        "##  #  #  ## ##",
        "##     #     ##",
        "##     #  ## ##",
        "##     #   # ##",
        "##     # # # ##",
        "## #     # # ##",
        "####     ### ##",
        "##M       T# ##",
        "##    #      ##",
        "##           ##",
        "###############",
        "###############"
    },
    {
        "#####################",
        "#####################",
        "##T      #   #     ##",
        "###### # # # # ### ##",
        "##   # # # # #   # ##",
        "## # ### # # # ### ##",
        "## #  M#   #   #   ##",
        "## ### # #######   ##",
        "##   # #   #       ##",
        "#### # ##  #  #######",
        "## # #     #       ##",
        "## # ### ######### ##",
        "##   #   #         ##",
        "## ###  ## # ########",
        "## # #   # #       ##",
        "## # #  ## ####### ##",
        "## #         #     ##",
        "#### ################",
        "####E################",
        "#####################"
    },
    {
        "#####################",
        "########E############",
        "######## ############",
        "##M               T##",
        "######      #      ##",
        "##                 ##",
        "##                 ##",
        "##                 ##",
        "##     ###       # ##",
        "## #   # #       # ##",
        "## ###           # ##",
        "## #             # ##",
        "## #            ## ##",
        "## #             # ##",
        "## #             # ##",
        "##               # ##",
        "##      #        # ##",
        "##                 ##",
        "#####################",
        "#####################"
    },
    {
        "###################",
        "###################",
        "E M#             ##",
        "## #        #  ####",
        "##  T          # ##",
        "##               ##",
        "##         #     ##",
        "##               ##",
        "##       #       ##",
        "##  #       #    ##",
        "##     #         ##",
        "## # #           ##",
        "## # #       #   ##",
        "#### #       ##  ##",
        "##   #   #       ##",
        "####     ###     ##",
        "##         #     ##",
        "###################",
        "###################"
    },
    {
        "###############################",
        "###############################",
        "##         #       #         ##",
        "###### # # # ##   #### ##### ##",
        "## # # # # # #         #      E",
        "## # # ### # ##   ########## ##",
        "##                           ##",
        "## # ##  # # ##  # # #####   ##",
        "## # #   # #     # #       # ##",
        "## # ##  # #     # ####### # ##",
        "##T# #   # # # # #       # #M##",
        "## # # # # # # # # ##### # # ##",
        "## # # #   # #           # # ##",
        "## # # # # # #     ##### # # ##",
        "## # # # # # # # #       # # ##",
        "## # # # # # # # # ##### # # ##",
        "## # # # # # # # #       # # ##",
        "## # # # # # # # # ##### # # ##",
        "##                           ##",
        "###############################",
        "###############################"
    },
    {
        "###############################",
        "###############################",
        "##   #               #       ##",
        "## # #  ## ####     ## ##### ##",
        "## #     # #     #   # # # # ##",
        "## #####      #     ## # # # ##",
        "##   #               # #     ##",
        "##   #  #### ###  ##   #     ##",
        "## #       # #M    #   # # # ##",
        "## #       # ###   #   #     ##",
        "## # # # # #   # # # # #     ##",
        "##         #     # # # # ######",
        "##         # #   # # # # #T#  E",
        "## #######       #   #     # ##",
        "##       #     #     #     # ##",
        "###### # ####  #  #  ### ### ##",
        "## # # # #     #           # ##",
        "## # # # ####  #    #####  # ##",
        "##               #           ##",
        "###############################",
        "###############################"
    }
};

int maze_widths[10] = {10, 10, 17, 15, 15, 21, 21, 19, 31, 31};
int maze_heights[10] = {9, 11, 12, 16, 16, 20, 20, 19, 21, 21};

int theseus_x, theseus_y, escape_x, escape_y, minotaur_x, minotaur_y;
QueueElement queue[MAX_QUEUE_SIZE];
int queueFront = 0, queueRear = 0;
int discovered[MAX_QUEUE_SIZE];

int is_position_valid(Position pos, int maze_index) {
    return pos.x >= 0 && pos.x < maze_widths[maze_index] && pos.y >= 0 && pos.y < maze_heights[maze_index] && mazes[maze_index][pos.y][pos.x] != '#';
}

int move_towards(int m, int t) {
    return (m < t) ? 2 : (m > t) ? -2 : 0;
}

Position next_minotaur_position(Position theseus, Position minotaur, int maze_index) {
    int tx = theseus.x, ty = theseus.y;
    int mx = minotaur.x, my = minotaur.y;

    for (int i = 0; i < 2; i++) {
        int dx = move_towards(mx, tx);
        if (dx != 0 && is_position_valid((Position){mx + dx, my}, maze_index) && is_position_valid((Position){mx + dx / 2, my}, maze_index)) {
            mx += dx;
            continue;
        }
        int dy = move_towards(my, ty);
        if (dy != 0 && is_position_valid((Position){mx, my + dy}, maze_index) && is_position_valid((Position){mx, my + dy / 2}, maze_index)) {
            my += dy;
            continue;
        }
    }
    return (Position){mx, my};
}

int next_theseus_states(Position pos, Position next_states[5], char moves[5], int maze_index) {
    int count = 0;
    int directions[5][2] = {{2, 0}, {0, 2}, {-2, 0}, {0, -2}, {0, 0}};
    int half[5][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {0, 0}};
    char move_chars[5] = {'R', 'D', 'L', 'U', 'S'};

    for (int i = 0; i < 5; i++) {
        int nx = pos.x + directions[i][0];
        int ny = pos.y + directions[i][1];
        int hx = pos.x + half[i][0];
        int hy = pos.y + half[i][1];
        Position new_pos = {nx, ny};
        Position half_pos = {hx, hy};

        if (is_position_valid(new_pos, maze_index) && is_position_valid(half_pos, maze_index)) {
            next_states[count] = new_pos;
            moves[count] = move_chars[i];
            count++;
        }
    }

    return count;
}

void bfs(State start, int (*stop_condition)(Position), int maze_index) {
    queueFront = queueRear = 0;  // 큐 초기화
    queue[queueRear++] = (QueueElement){start, -1, ' '};
    discovered[0] = 1;

    while (queueFront < queueRear) {
        QueueElement current = queue[queueFront++];

        Position next_states[5];
        char moves[5];
        int count = next_theseus_states(current.state.theseus, next_states, moves, maze_index);

        for (int i = 0; i < count; i++) {
            Position new_t = next_states[i];

            if (stop_condition(new_t)) {
                queue[queueRear] = (QueueElement){{new_t, current.state.minotaur}, queueFront - 1, moves[i]};
                queueRear++;
                printf("\nsolution found\n");
                int path[MAX_QUEUE_SIZE];
                int path_length = 0;
                int index = queueRear - 1;

                while (index != -1) {
                    path[path_length++] = index;
                    index = queue[index].prevIndex;
                }

                for (int i = path_length - 2; i >= 0; i--) {
                    printf("%c ", queue[path[i]].move);}
                return;
            }

            Position new_m = next_minotaur_position(new_t, current.state.minotaur, maze_index);

            if (new_t.x == new_m.x && new_t.y == new_m.y) {
                continue;
            }

            State next_state = {new_t, new_m};
            int found = 0;

            for (int j = 0; j < queueRear; j++) {
                if (queue[j].state.theseus.x == next_state.theseus.x &&
                    queue[j].state.theseus.y == next_state.theseus.y &&
                    queue[j].state.minotaur.x == next_state.minotaur.x &&
                    queue[j].state.minotaur.y == next_state.minotaur.y) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                queue[queueRear] = (QueueElement){next_state, queueFront - 1, moves[i]};
                discovered[queueRear] = 1;
                queueRear++;
            }
        }
    }

    printf("\nNo solution\n");
}

int stop_condition(Position theseus) {
    return theseus.x == escape_x && theseus.y == escape_y;
}

void solve_maze(int maze_index) {
    for (int y = 0; y < maze_heights[maze_index]; y++) {
        for (int x = 0; x < maze_widths[maze_index]; x++) {
            if (mazes[maze_index][y][x] == 'T') {
                theseus_x = x;
                theseus_y = y;
            } else if (mazes[maze_index][y][x] == 'E') {
                escape_x = x;
                escape_y = y;
            } else if (mazes[maze_index][y][x] == 'M') {
                minotaur_x = x;
                minotaur_y = y;
            }
        }
    }

    if(maze_index < 3){
        printf("\n\ntest %d:", maze_index + 1);
    }

    if(maze_index >= 3){
        printf("\n\nMaze %d:", maze_index - 2);
    }

    State start = {{theseus_x, theseus_y}, {minotaur_x, minotaur_y}};
    bfs(start, stop_condition, maze_index);
}

int main() {
    for (int i = 0; i < 10; i++) {
        solve_maze(i);
    }

    return 0;
}
