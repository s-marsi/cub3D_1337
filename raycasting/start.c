#include "../cub3D.h"

// Fonction pour obtenir la position X du joueur
int get_position_x(char **map) {
    int y, x;

    y = 0;
    while (map[y]) {
        x = 0;
        while (map[y][x]) {
            if (map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'N' || map[y][x] == 'W')
                return (x);
            x++;
        }
        y++;
    }
    return (-1);
}

// Fonction pour obtenir la position Y du joueur
int get_position_y(char **map) {
    int y, x;

    y = 0;
    while (map[y]) {
        x = 0;
        while (map[y][x]) {
            if (map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'N' || map[y][x] == 'W')
                return (y);
            x++;
        }
        y++;
    }
    return (-1);
}

// Initialisation des valeurs
int init_values(t_init *vars, t_data *pars) {
    vars->window_width = 1200;
    vars->window_height = 900;
    vars->mlx = mlx_init();
    if (!vars->mlx)
        return (0);
    vars->win = mlx_new_window(vars->mlx, vars->window_width, vars->window_height, "cub3D");
    if (!vars->win)
        return (0);
    vars->mlx_img = mlx_new_image(vars->mlx, vars->window_width, vars->window_height);
    if (!vars->mlx_img)
        return (0);
    vars->data_img = mlx_get_data_addr(vars->mlx_img, &vars->bits_per_pixel, &vars->size_line, &vars->endian);
    vars->tile_size = 30;
    vars->map = pars->mapStructure;
    vars->map_rows_num = 38;  // Assurez-vous que cela correspond à votre carte
    vars->map_cols_num = 63;   // Assurez-vous que cela correspond à votre carte
    vars->fov_angle = (60 * (M_PI / 180));
    vars->num_rays = vars->window_width;

    vars->rays = malloc(sizeof(t_rays) * vars->num_rays);
    if (!vars->rays)
        return (0);

    return (1);
}

// Fonction pour dessiner un rectangle
void draw_rectangle(t_init *vars, int x, int y, int width, int height, int color) {
    int i, j;

    for (i = y; i < y + height; i++) {
        for (j = x; j < x + width; j++) {
            int offset = (i * vars->size_line) + (j * (vars->bits_per_pixel / 8));
            *(unsigned int *)(vars->data_img + offset) = color; 
        }
    }
}

// Fonction pour dessiner la carte
void renderMap(t_init *vars) {
    // int i, j;
    int x, y;

    y = 0;
    while (y < vars->map_rows_num) {
        x = 0;
        while (x < vars->map_cols_num) {
            if (y < vars->map_rows_num && x < vars->map_cols_num && vars->map[y][x]) {
                if (vars->map[y][x] == '0') {
                    draw_rectangle(vars, x * vars->tile_size, y * vars->tile_size, vars->tile_size, vars->tile_size, 0x000000);  // Noir pour l'espace vide
                } else if (vars->map[y][x] == '1') {
                    draw_rectangle(vars, x * vars->tile_size, y * vars->tile_size, vars->tile_size, vars->tile_size, 0xFFFFFF);  // Blanc pour les murs
                }
            }
            x++;
        }
        y++;
    }
}

// Vérifie s'il y a un mur à la position donnée
int mapHasWall(float x, float y, t_init *vars) {
    if (x < 0 || x >= vars->window_width || y < 0 || y >= vars->window_height)
        return (1);
    int mapGridIndexX = floor(x / vars->tile_size);
    int mapGridIndexY = floor(y / vars->tile_size);
    
    if (mapGridIndexY < 0 || mapGridIndexY >= vars->map_rows_num || 
        mapGridIndexX < 0 || mapGridIndexX >= vars->map_cols_num)
        return (1);
    
    return vars->map[mapGridIndexY][mapGridIndexX] == '1' || vars->map[mapGridIndexY][mapGridIndexX] == '$';
}

// Initialisation de la carte
void initializeMap(t_init *vars) {
    vars->map = malloc(vars->map_rows_num * sizeof(char *));
    if (vars->map == NULL) {
        perror("Error allocating memory for map rows");
        exit(1);
    }

    for (int i = 0; i < vars->map_rows_num; i++) {
        vars->map[i] = malloc((vars->map_cols_num + 1) * sizeof(char));  // +1 pour le caractère nul
        if (vars->map[i] == NULL) {
            perror("Error allocating memory for map columns");
            exit(1);
        }
    }
}

// Libération de la mémoire de la carte
void free_map(t_init *vars) {
    for (int i = 0; i < vars->map_rows_num; i++) {
        free(vars->map[i]);
    }
    free(vars->map);
}

float ft_rotate_angle(int player_x, int player_y, t_init *vars) {
    if (vars->map[player_y][player_x] == 'N')
        return (M_PI / 2);
    else if (vars->map[player_y][player_x] == 'E')
        return (0);
    else if (vars->map[player_y][player_x] == 'S')
        return ((3 * M_PI) / 2);
    else if (vars->map[player_y][player_x] == 'W')
        return (M_PI);
    else
        return (-1);
}

// Autres fonctions nécessaires pour le fonctionnement du programme
void init_player(t_init *vars) {
    int player_x = get_position_x(vars->map);
    int player_y = get_position_y(vars->map);

    if (player_x == -1 || player_y == -1) {
        printf("Error: Player position not found in the map.\n");
        exit(1);
    }

    vars->player->player_x = (player_x * vars->tile_size) + (vars->tile_size / 2);
    vars->player->player_y = (player_y * vars->tile_size) + (vars->tile_size / 2);
    printf("player pos  : x = %f | y = %f\n", vars->player->player_x, vars->player->player_y);

    vars->player->width = 5;
    vars->player->height = 5;
    vars->player->turnDirection = 0;
    vars->player->walkDirection = 0;
    vars->player->rotationAngle = ft_rotate_angle(player_x, player_y, vars);
    vars->player->walkSpeed = 4;
    vars->player->turnSpeed = 4 * (M_PI / 180);
}


// Gestion des événements de touches
int handle_key_press(int keycode, t_init *vars) {
    printf("%d\n", keycode);
    if (keycode == 65307) {
        mlx_destroy_window(vars->mlx, vars->win);
        free(vars->mlx);
        exit(0);
    }
    if (keycode == 119)
        vars->player->walkDirection = 1;
    if (keycode == 115)
        vars->player->walkDirection = -1;
    if (keycode == 65363)
        vars->player->turnDirection = 1;
    if (keycode == 65361)
        vars->player->turnDirection = -1;
    return (0);
}

int handle_key_up(int keycode, t_init *vars) {
    if (keycode == 119 || keycode == 115)
        vars->player->walkDirection = 0;
    if (keycode == 65363 || keycode == 65361)
        vars->player->turnDirection = 0;
    return (0);
}

static int handle_mouse_click(t_init *vars) {
    mlx_destroy_window(vars->mlx, vars->win);
    free(vars->mlx);
    exit(0);
    return (0);
}

void handle_keys(t_init *vars) {
    mlx_hook(vars->win, 2, 1L << 0, handle_key_press, vars);
    mlx_hook(vars->win, 3, 1L << 1, handle_key_up, vars);
    mlx_hook(vars->win, 17, 0, handle_mouse_click, vars);
}


// Fonction pour rendre le joueur
void renderPlayer(t_init *vars, int i) {
    if (i == 0)
        draw_rectangle(vars, vars->player->player_x, vars->player->player_y, vars->player->width, vars->player->height, 0xFF0000);
}

// Fonction pour rendre la scène
void render(t_init *vars) {
    renderMap(vars);
    renderPlayer(vars, 0);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->mlx_img, 0, 0);
}

// Mise à jour de la position du joueur
int ft_move_player(t_init *vars) {
    static int vit;
    float moveStep;
    float newPlayeX;
    float newPlayeY;
    vit++;

    if (vit == 1000) {
        vars->player->rotationAngle += vars->player->turnDirection * vars->player->turnSpeed;
        moveStep = vars->player->walkDirection * vars->player->walkSpeed;
        newPlayeX = vars->player->player_x + cos(vars->player->rotationAngle) * moveStep;
        newPlayeY = vars->player->player_y + sin(vars->player->rotationAngle) * moveStep;
        if (!mapHasWall(newPlayeX, newPlayeY, vars)) {
            vars->player->player_x = newPlayeX;
            vars->player->player_y = newPlayeY;
            vars->mlx_img = mlx_new_image(vars->mlx, vars->window_width, vars->window_height);
            vars->data_img = mlx_get_data_addr(vars->mlx_img, &vars->bits_per_pixel, &vars->size_line, &vars->endian);
            mlx_clear_window(vars->mlx, vars->win);
            render(vars);
        }
        vit = 0;
    }
    
    return (0);
}

// Mise à jour de la logique du jeu
void update(t_init *vars) {
    mlx_loop_hook(vars->mlx, ft_move_player, vars);
}

// Fonction principale de raycasting
void raycasting(t_data *data) {
    t_init vars;
    t_player player;

    vars.player = &player;
    initializeMap(&vars);
    vars.prgrm_runing = init_values(&vars, data);
    init_player(&vars);
    handle_keys(&vars);
    render(&vars);
    update(&vars);
    mlx_loop(vars.mlx);
    mlx_destroy_window(vars.mlx, vars.win);
    free_map(&vars);  // Libérez la mémoire de la carte
}