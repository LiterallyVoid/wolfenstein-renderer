#include <SDL.h>
#include <SDL_rotozoom.h>
#include <stdbool.h>
#include <math.h>

int map[24][24] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,1,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,1,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double ceilHeight[24][24] = {
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
};

double floorHeight[24][24] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1.1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

Uint8 textures[8][64][64];

#define WIDTH 320
#define HEIGHT 240
#define EPSILON 1e-5

int screen_width = WIDTH, screen_height = HEIGHT;

float sky[WIDTH][HEIGHT];

double scale = 1;

double playerX = 1;
double playerY = 1;
double playerZ = 0;
double playerAngle = 0;

Uint32 *pixels;
SDL_Surface *screen;
SDL_Surface *pixbuf;

SDL_Color palette[256];
Uint8 colormap[256][34];

Uint32 paletteInd(Uint8 p) {
    return SDL_MapRGB(pixbuf->format, palette[p].r, palette[p].g, palette[p].b);
};

void setpixel(int x, int y, Uint8 p, Uint8 l) {
    pixels[y * WIDTH + x] = paletteInd(colormap[p][l]);
};

double castRay(double x, double y, double dirX, double dirY, int *hitSide, int *hitBlock, double *texP, double *floorPtr, double *ceilPtr, bool forMovingStuff) { // XXX: move to map.c
    int mapX = (int) x;
    int mapY = (int) y;
    
    double sideDistX;
    double sideDistY;

    double deltaDistX = sqrt(1 + (dirY * dirY) / (dirX * dirX));
    double deltaDistY = sqrt(1 + (dirX * dirX) / (dirY * dirY));

    int stepX = 0;
    int stepY = 0;

    if(dirX < 0) {
        stepX = -1;
        sideDistX = (x - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + (1 - x)) * deltaDistX;
    }
    if(dirY < 0) {
        stepY = -1;
        sideDistY = (y - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + (1 - y)) * deltaDistY;
    }

    bool hit = false;
    int side = 0;
    
    while(!hit) {
        if(sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if(map[mapX][mapY] > 0) {
            if(forMovingStuff || map[mapX][mapY] != 100) {
                hit = true;
            }
        }
    }

    if(forMovingStuff && map[mapX][mapY] != 100) {
        return -1000;
    }

    if(hitBlock) *hitBlock = map[mapX][mapY];
    if(hitSide) *hitSide = side;

    double dist;

    if(side == 0) {
        dist = ((mapX - x) + ((1 - stepX) * 0.5)) / dirX;
    } else {
        dist = ((mapY - y) + ((1 - stepY) * 0.5)) / dirY;
    }

    if(texP) {
        if (side == 0) {
            *texP = y + dist * dirY;
        } else {
            *texP = x + dist * dirX;
        }

        *texP -= floor(*texP);

        if(side == 0 && dirX > 0) *texP = 1 - *texP;
        if(side == 1 && dirY < 0) *texP = 1 - *texP;
    }

    if(floorPtr && ceilPtr) {
        *floorPtr = floorHeight[mapX - (side ? 0 : stepX)][mapY - (side ? stepY : 0)];
        *ceilPtr = ceilHeight[mapX - (side ? 0 : stepX)][mapY - (side ? stepY : 0)];
    }

    return dist;
};

Uint8 getTex(int block, double x, double y) {
    unsigned int tx = x * 64;
    unsigned int ty = y * 64;
    tx &= 63;
    ty &= 63;

    return textures[block][ty][tx];
};

bool collide(double x, double y, double s) {
    if(map[(int)(x - s)][(int)(y - s)] > 0) return true;
    if(map[(int)(x + s)][(int)(y - s)] > 0) return true;
    if(map[(int)(x + s)][(int)(y + s)] > 0) return true;
    if(map[(int)(x - s)][(int)(y + s)] > 0) return true;
    return false;
};

int main(int argc, char **argv) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }
    
    screen = SDL_SetVideoMode(WIDTH * scale, HEIGHT * scale, 32, SDL_HWSURFACE | SDL_RESIZABLE);
    if(!screen) {
        SDL_Quit();
        return 1;
    }

    {
        FILE *f = fopen("data/textures.lst", "r");
        int i = -1, x, y;

        char fname[128];

        while(fgets(fname, 128, f) != NULL) {
            i++;
            for(x = 0; x < strlen(fname); x++) {
                if(fname[x] == '#' || fname[x] == '\n') {
                    fname[x] = '\0';
                }
            }
            if(strlen(fname) < 1) continue;
            FILE *j = fopen(fname, "rb");
            for(x = 0; x < 64; x++) {
                for(y = 0; y < 64; y++) {
                    unsigned char tx[1];
                    fread(tx, 1, 1, j);
                    textures[i][x][y] = tx[0];
                }
            }
            fclose(j);
        }

        fclose(f);
    }

    {
        FILE *f = fopen("data/palette.pal", "rb");
        int i;
        for(i = 0; i < 256; i++) {
            unsigned char x[3];
            fread(x, 3, 1, f);
            palette[i].r = x[0];
            palette[i].g = x[1];
            palette[i].b = x[2];
        }
        fclose(f);
    }

    {
        FILE *f = fopen("data/colormap.lmp", "rb");
        int i, j;
        for(i = 0; i < 34; i++) {
            for(j = 0; j < 256; j++) {
                unsigned char x[1];
                fread(x, 1, 1, f);
                colormap[j][i] = x[0];
            }
        }
        fclose(f);
    }

    bool quit = false;

    SDL_Event event;

    bool keys[322];
    {
        int i;
        for(i = 0; i < 322; i++) {
            keys[i] = false;
        }
    }

    int time = SDL_GetTicks();
    
    pixbuf = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH, HEIGHT, 32, 0, 0, 0, 0);

    SDL_ShowCursor(SDL_DISABLE);
    
    while(!quit) {
        int newTime = SDL_GetTicks();
        int delta = newTime - time;
        time = newTime;
        
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                keys[event.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                keys[event.key.keysym.sym] = false;
                break;
            case SDL_VIDEORESIZE: {
                double s1 = ((double) event.resize.w) / WIDTH;
                double s2 = ((double) event.resize.h) / HEIGHT;
                scale = (s1 < s2 ? s1 : s2);
                screen_width = event.resize.w;
                screen_height = event.resize.h;
                screen = SDL_SetVideoMode(event.resize.w, event.resize.h, 32, SDL_HWSURFACE | SDL_RESIZABLE);
                break;
            }
            case SDL_MOUSEMOTION: {
                int hw = screen_width * 0.5;
                int hh = screen_height * 0.5;
                playerAngle += (event.motion.x - hw) * 0.002;
                SDL_WarpMouse(hw, hh);
                break;
            }
            }
        }

        if(keys[SDLK_LEFT]) {
            playerAngle -= 0.001 * delta;
        }

        if(keys[SDLK_RIGHT]) {
            playerAngle += 0.001 * delta;
        }

        double moveX = 0, moveY = 0;

        double spd = 0.003;

        if(keys[SDLK_w]) {
            moveX += cos(playerAngle) * spd * delta;
            moveY += sin(playerAngle) * spd * delta;
        }

        if(keys[SDLK_s]) {
            moveX -= cos(playerAngle) * spd * delta;
            moveY -= sin(playerAngle) * spd * delta;
        }

        if(keys[SDLK_a]) {
            moveX += sin(playerAngle) * spd * delta;
            moveY -= cos(playerAngle) * spd * delta;
        }

        if(keys[SDLK_d]) {
            moveX -= sin(playerAngle) * spd * delta;
            moveY += cos(playerAngle) * spd * delta;
        }

        playerX += moveX;
        if(collide(playerX, playerY, 0.2 - EPSILON)) {
            playerX = ((int)(playerX)) + (moveX < 0 ? 0.2 + EPSILON : 0.8 - EPSILON);
        }

        playerY += moveY;
        if(collide(playerX, playerY, 0.2 - EPSILON)) {
            playerY = ((int)(playerY)) + (moveY < 0 ? 0.2 + EPSILON : 0.8 - EPSILON);
        }

        playerZ = floorHeight[(int)playerX][(int)playerY] - 1;

        SDL_Rect half = {0, HEIGHT * 0.5, WIDTH, HEIGHT * 0.5};
        SDL_FillRect(pixbuf, &half, paletteInd(76));
        
        if(SDL_MUSTLOCK(pixbuf)) SDL_LockSurface(pixbuf);
        
        pixels = (Uint32*) pixbuf->pixels;

        int x, y;

        double sa = sin(playerAngle);
        double ca = cos(playerAngle);

        double l;
        
        for(x = 0; x < WIDTH; x++) {
            l = (x / (float)WIDTH) * 2 - 1;
            l *= 0.8;

            int side, block;
            double texP;
            double floorH, ceilH;

            double d = castRay(playerX, playerY, ca - (sa * l), sa + (ca * l), &side, &block, &texP, &floorH, &ceilH, false);

            int size = (WIDTH / 3) / d;
            int ofs1 = (ceilH - playerZ) * size;
            int ofs2 = (floorH - playerZ) * size;

            int startY = (HEIGHT * 0.5) + ofs1;
            int endY = (HEIGHT * 0.5) + ofs2;

            int startY2 = (HEIGHT * 0.5) - size;
            int endY2 = (HEIGHT * 0.5) + size;

            double ys = 1.0 / ((endY2 - startY2) + 1);

            double yl;
            if(startY < 0) {
                yl = ys * -startY;
            } else {
                yl = 0;
            }

            int cmap = d * 2;
            if(cmap > 31) cmap = 31;

            for(y = 0; y < HEIGHT; y++) {
                bool d = false;
                if(y >= startY && y < endY) {
                    Uint8 t = getTex(block, texP, yl);
                    setpixel(x, y, t, cmap);
                    yl += ys;
                    d = true;
                }
                if(y < ((HEIGHT * 0.5))) {
                    if(y > 0) {
                        int nx = x + rand() % 3 - 1;
                        if(nx < 0) {
                            nx = WIDTH - 1;
                        }
                        if(nx >= WIDTH) {
                            nx = 0;
                        }
                        double s = (rand() % 100) / 100.0;
                        s = 1 - pow(s, HEIGHT / 10);
                        sky[nx][y - 1] = sky[x][y] * s;
                    }
                    if(!d) {
                        int xo = x + (playerAngle / M_PI * WIDTH * 2);
                        while(xo >= WIDTH) xo -= WIDTH;
                        while(xo < 0) xo += WIDTH;
                        if(sky[xo][y] > 0.5) {
                            double a = sky[xo][y];
                            if(a > 7) a = 7;
                            setpixel(x, y, 168 - a, 0);
                        } else {
                            setpixel(x, y, 8, 0);
                        }
                    }
                }
            }
            
            sky[x][(HEIGHT / 2) - 1] = rand() % 12 + 1;
        }
        
        for(x = 0; x < WIDTH; x++) {
            l = (x / (float)WIDTH) * 2 - 1;
            l *= 0.8;

            int side, block;
            double texP;
            double floorH, ceilH;

            double d = castRay(playerX, playerY, ca - (sa * l), sa + (ca * l), &side, &block, &texP, &floorH, &ceilH, true);

            if(d < 0) {
                continue;
            }

            double texOfs = 0;

            if(block == 100) {
                block = 0;
                double h = ((time % 10000) / 5000.0);
                if(h > 1) {
                    h = 2 - h;
                }
                floorH += (ceilH - floorH) * h;
                texOfs -= h;
            }


            int size = (WIDTH / 3) / d;
            int ofs1 = (ceilH - playerZ) * size;
            int ofs2 = (floorH - playerZ) * size;

            int startY = (HEIGHT * 0.5) + ofs1;
            int endY = (HEIGHT * 0.5) + ofs2;

            int startY2 = (HEIGHT * 0.5) - size;
            int endY2 = (HEIGHT * 0.5) + size;

            double ys = 1.0 / ((endY2 - startY2) + 1);

            double yl;
            if(startY < 0) {
                yl = ys * -startY;
            } else {
                yl = 0;
            }

            yl -= texOfs;

            int cmap = d * 2;
            if(cmap > 31) cmap = 31;

            for(y = 0; y < HEIGHT; y++) {
                bool d = false;
                if(y >= startY && y < endY) {
                    Uint8 t = getTex(block, texP, yl);
                    setpixel(x, y, t, cmap);
                    yl += ys;
                    d = true;
                }
            }
            
            sky[x][(HEIGHT / 2) - 1] = rand() % 12 + 1;
        }
        
        if(SDL_MUSTLOCK(pixbuf)) SDL_UnlockSurface(pixbuf);

        SDL_Rect scr = {(screen_width * 0.5) - (WIDTH * scale * 0.5),
                        (screen_height * 0.5) - (HEIGHT * scale * 0.5),
                        WIDTH * scale, HEIGHT * scale};

        SDL_Surface *scaled = zoomSurface(pixbuf, scale, scale, 0);

        SDL_BlitSurface(scaled, NULL, screen, &scr);

        SDL_FreeSurface(scaled);

        SDL_Flip(screen);
    }

    SDL_FreeSurface(pixbuf);
    SDL_Quit();
};
