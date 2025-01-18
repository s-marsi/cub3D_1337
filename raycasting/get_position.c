#include "../cub3D.h"

int get_position_x(char **map) {
    int y = 0, x;
    while (map[y]) {
        x = 0;
        while (map[y][x]) {
            if (map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'N' || map[y][x] == 'W')
                return x;
            x++;
        }
        y++;
    }
    printf("Error: Player not found on map (x).\n");
    return -1;
}

int get_position_y(char **map) {
    int y = 0, x;
    while (map[y]) {
        x = 0;
        while (map[y][x]) {
            if (map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'N' || map[y][x] == 'W')
                return y;
            x++;
        }
        y++;
    }
    printf("Error: Player not found on map (y).\n");
    return -1;
}
