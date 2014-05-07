#ifndef _GAME_H
#define _GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <sstream>
#include "Block.h"

class Game {
    private:
        //Variables
        ALLEGRO_EVENT_QUEUE* event_queue;
        ALLEGRO_DISPLAY* display;
        ALLEGRO_TIMER* timer;
        ALLEGRO_FONT* font;
        ALLEGRO_BITMAP* container;
        ALLEGRO_BITMAP* blue;
        ALLEGRO_BITMAP* green;
        ALLEGRO_BITMAP* orange;
        ALLEGRO_BITMAP* purple;
        ALLEGRO_BITMAP* red;
        ALLEGRO_BITMAP* turquois;
        ALLEGRO_BITMAP* yellow;
        int grid[21][18];
        int score;
        int level;
        float speed;
        int linesNeeded;
        int linesMult;
        bool done;

        //Functions
        void drawGameOver();
        void draw(Block*);
        void checkCollision(Block*, int);
        bool checkSet(Block*);
        void setBlock(Block*);
        void checkLines();
        void deleteLine(int);

        //Private singleton design
        static Game* _instance;
        Game() {};
    public:
        //For singleton design
        static Game* Instance();

        //Functions
        int Init();
        void MainLoop();
};

//-------------------------------------Singleton Design------------------------------------
Game* Game::_instance = NULL;

Game* Game::Instance() {
    if(_instance == NULL)
        _instance = new Game;
    return _instance;
}
//-----------------------------------End Singleton Design-----------------------------------

//---------------------------------------Game Functions-------------------------------------
int Game::Init() {
    //intialize game settings
    score = 0;
    speed = 0.5f;
    linesNeeded = 10;
    linesMult = 10;
    level = 1;
    done = false;

    //Start random number generator
    srand(time(NULL));

    //set grid (0=open space, 8=wall, 9=deathzone)
    int temp[21][18] = {{8,8,8,8,9,9,9,9,9,9,9,9,9,9,8,8,8,8},
                        {8,8,8,8,9,9,9,9,9,9,9,9,9,9,8,8,8,8},
                        {8,8,8,8,9,9,9,9,9,9,9,9,9,9,8,8,8,8},
                        {8,8,8,8,9,9,9,9,9,9,9,9,9,9,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,0,0,0,0,0,0,0,0,0,0,8,8,8,8},
                        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8}};
    std::memcpy(grid, temp, sizeof(grid));

    //Make sure allegro intializes
    if(!al_init()) {
        al_show_native_message_box(display, "Error", "Error: al_init", "Failed to initialize allegro!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    //Add the image addon for Allegro
    if(!al_init_image_addon()) {
      al_show_native_message_box(display, "Error", "Error: al_init_image_addon", "Failed to initialize al_init_image_addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    //Setup the display for allegro
    display = al_create_display(1000, 680);
    if(!display) {
       al_show_native_message_box(display, "Error", "Error: display", "Failed to initialize display!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    //Install the keyboard for allegro
    al_install_keyboard();

    //Install the font addon for allegro
    al_init_font_addon();

    //Install the ttf(True Type Font) for allegro
    al_init_ttf_addon();

    //Set font to Arial Black
    font = al_load_ttf_font("Fonts/ariblk.ttf", 24, 0);

    //Setup the event_queue
    event_queue = al_create_event_queue();
    if(!event_queue) {
        al_show_native_message_box(display, "Error", "Error: al_create_event_queue", "Failed to initialize al_create_event_queue!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    //Set up the bitmaps(images) to be used
    container = al_load_bitmap("Images/container.png");
    blue = al_load_bitmap("Images/blueblock.png");
    green = al_load_bitmap("Images/greenblock.png");
    orange = al_load_bitmap("Images/orangeblock.png");
    purple = al_load_bitmap("Images/purpleblock.png");
    red = al_load_bitmap("Images/redblock.png");
    turquois = al_load_bitmap("Images/turquoiseblock.png");
    yellow = al_load_bitmap("Images/yellowblock.png");

    timer = al_create_timer(1.0/60);

    //Register types of events the event_queue will handle
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_start_timer(timer);

    return 0;
}

void Game::MainLoop() {
    //Variables
    int num = 0;
    bool blockSet = false;
    bool slam = false;
    ALLEGRO_EVENT ev;


    //Main Loop
    while(!done) {
        //Create a new block
        num = rand() % 7;
        Block* block = Block::create(num);
        blockSet = false;

        //Loop until the block is set
        while(!blockSet) {
            bool drawgfx = false;
            slam = false;

            //Obtain event actions before updating
            do{
                al_wait_for_event(event_queue, &ev);

                //Clicking the close button
                if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    done = true;
                    blockSet = true;
                    break;
                }
                //Key presses
                else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
                    //Move block right
                    if(ev.keyboard.keycode == ALLEGRO_KEY_D) {
                        block->moveRight();
                        checkCollision(block, 1);
                    }
                    //Move block left
                    if(ev.keyboard.keycode == ALLEGRO_KEY_A) {
                        block->moveLeft();
                        checkCollision(block, 2);
                    }
                    //Rotate block counterclockwise
                    if(ev.keyboard.keycode == ALLEGRO_KEY_Q){
                        block->rotateLeft();
                        checkCollision(block, 3);
                    }
                    //Rotate block clockwise
                    if(ev.keyboard.keycode == ALLEGRO_KEY_E) {
                        block->rotateRight();
                        checkCollision(block, 4);
                    }
                    //Slam the block straight down
                    if(ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                        while(checkSet(block) == false) {
                            block->drop();
                        }
                        slam = true;
                        draw(block);
                        break;
                    }
                    //Press the ESC key
                    if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                        done = true;
                        blockSet = true;
                        break;
                    }
                }
                else if(ev.type == ALLEGRO_EVENT_TIMER) {
                    drawgfx = true;
                }
            }while(!al_is_event_queue_empty(event_queue));

            //Break if a slam occured so no more actions can be performed and a new block can start
            if(slam == true)
                break;

            //Update the game
            if(drawgfx) {
                block->drop();              //Attempt to drop the block down one space
                if(checkSet(block) == true) //Check if there is a collision below
                    blockSet = true;
                draw(block);                //Draw everything
            }

            //Rest by the current game speed
            al_rest(speed);
        }
        checkLines();
    }

    drawGameOver();

    //End of game cleanup
    al_destroy_bitmap(container);
    al_destroy_bitmap(blue);
    al_destroy_bitmap(green);
    al_destroy_bitmap(orange);
    al_destroy_bitmap(purple);
    al_destroy_bitmap(red);
    al_destroy_bitmap(turquois);
    al_destroy_bitmap(yellow);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
}

void Game::drawGameOver() {
    al_clear_to_color(al_map_rgb(0,0,0));
    font = font = al_load_ttf_font("Fonts/ariblk.ttf", 72, 0);
    al_draw_text(font, al_map_rgb(255,255,255), 500 , 280, ALLEGRO_ALIGN_CENTER, "GAME OVER");
    al_flip_display();
    al_rest(3);
}

void Game::draw(Block* block) {
    int num = 0;

    //clear the display
    al_clear_to_color(al_map_rgb(0,0,0));

    //Draw the graphical container
    al_draw_bitmap(container, 0, 0, 0);

    //Draw the current dropping block
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            num = block->getNum(j,i);
            if(num != 0) {
                if(num == 1) {
                    al_draw_bitmap(blue, block->getX()+(32*i), block->getY()+(32*j), 0);
                }
                if(num == 2) {
                    al_draw_bitmap(green, block->getX()+(32*i), block->getY()+(32*j), 0);
                }
                if(num == 3) {
                    al_draw_bitmap(orange, block->getX()+(32*i), block->getY()+(32*j), 0);
                }
                if(num == 4) {
                    al_draw_bitmap(purple, block->getX()+(32*i), block->getY()+(32*j), 0);
                }
                if(num == 5) {
                    al_draw_bitmap(red, block->getX()+(32*i), block->getY()+(32*j), 0);
                }
                if(num == 6) {
                    al_draw_bitmap(turquois, block->getX()+(32*i), block->getY()+(32*j), 0);
                }
                if(num == 7) {
                    al_draw_bitmap(yellow, block->getX()+(32*i), block->getY()+(32*j), 0);
                }
            }
        }
    }

    //Draw the blocks set on the grid
    for(int i = 0; i < 21; i++) {
        for(int j = 0; j < 18; j++) {
            num = grid[i][j];
            if(num != 0) {
                if(num == 1) {
                    al_draw_bitmap(blue, j*32, i*32, 0);
                }
                if(num == 2) {
                    al_draw_bitmap(green, j*32, i*32, 0);
                }
                if(num == 3) {
                    al_draw_bitmap(orange, j*32, i*32, 0);
                }
                if(num == 4) {
                    al_draw_bitmap(purple, j*32, i*32, 0);
                }
                if(num == 5) {
                    al_draw_bitmap(red, j*32, i*32, 0);
                }
                if(num == 6) {
                    al_draw_bitmap(turquois, j*32, i*32, 0);
                }
                if(num == 7) {
                    al_draw_bitmap(yellow, j*32, i*32, 0);
                }
            }
        }
    }

    //Draw the text
    std::stringstream ss;
    std::string str;
    const char* cstrLvl;
    const char* cstrLines;
    const char* cstrScore;

    ss << level;
    str = "Level: " + ss.str();
    cstrLvl = str.c_str();
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 0, ALLEGRO_ALIGN_LEFT, cstrLvl);

    ss.str("");
    ss << linesNeeded;
    str = "Lines Left: " + ss.str();
    cstrLines = str.c_str();
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 32, ALLEGRO_ALIGN_LEFT, cstrLines);

    ss.str("");
    ss << score;
    str = "Score: " + ss.str();
    cstrScore = str.c_str();
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 64, ALLEGRO_ALIGN_LEFT, cstrScore);

    al_draw_text(font, al_map_rgb(255,255,255), 600 , 224, ALLEGRO_ALIGN_LEFT, "KEYBOARD FUNCTIONS:");
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 256, ALLEGRO_ALIGN_LEFT, "ESC = Quit Game");
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 288, ALLEGRO_ALIGN_LEFT, "A = Move Left");
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 320, ALLEGRO_ALIGN_LEFT, "D = Move Right");
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 352, ALLEGRO_ALIGN_LEFT, "Q = Rotate Counterclockwise");
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 384, ALLEGRO_ALIGN_LEFT, "R = Rotate Clockwise");
    al_draw_text(font, al_map_rgb(255,255,255), 600 , 416, ALLEGRO_ALIGN_LEFT, "Space = Slam Block");


    al_flip_display();
}

//Checks block collision with the walls
void Game::checkCollision(Block* block, int code) {
    int x = block->getX()/32;
    int y = abs(block->getY()/32);
    int num = 0;
    for(int i = 0; i < 4; i++) {
        for(int j= 0; j < 4; j++) {
            //Check if possible collision area
            if(grid[y+j][x+i] != 0 && grid[y+j][x+i] != 9) {
                num = block->getNum(j,i);
                //collision
                if(num != 0) {
                    //If the move to the right was a collision move it back left
                    if(code == 1) {
                        block->moveLeft();
                        break;
                    }
                    //If the move the left was a collision move it back right
                    if(code == 2) {
                        block->moveRight();
                        break;
                    }
                    //If a counterclockwise (rotateLeft) was a collision rotate back clockwise
                    if(code == 3){
                        block->rotateRight();
                        break;
                    }
                    //If a clockwise (rotationRight) was a collision rotate back counterclockwise
                    if(code == 4) {
                        block->rotateLeft();
                        break;
                    }
                }
            }
        }
    }
}

//Check to see if there is a collision below the block, if there is
//then set the block using setBlock function
bool Game::checkSet(Block* block) {
    int x = block->getX()/32;
    int y = abs(block->getY()/32);
    int num = 0;
    for(int i = 0; i < 4; i++) {
        for(int j= 0; j < 4; j++) {
            //Check if possible collision area
            if(grid[y+j][x+i] != 0 && grid[y+j][x+i] != 9) {
                num = block->getNum(j,i);
                //collision
                if(num != 0) {
                    block->moveUp();
                    setBlock(block);
                    return true;
                }
            }
        }
    }
    return false;
}

//Set the block in the position it is at comparitvely to the grid
void Game::setBlock(Block* block) {
    int x = block->getX()/32;
    int y = abs(block->getY()/32);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            //Don't set the 0s from the block (don't want to overwrite an already set area)
            if(block->getNum(j,i) != 0) {
                //Check if the block is being set in the death zone
                if(grid[y+j][x+i] == 9)
                    done = true;
                grid[y+j][x+i] = block->getNum(j,i);
            }
        }
    }
}

//Checks each line in the grid (that is not a boundary) to see
//if the line is complete, if it is then the deleteLine function is called
void Game::checkLines() {
    bool complete = true;
    int count = 0;
    for(int i = 0; i < 16; i++) {
        complete = true;
        for(int j = 0; j < 10; j++) {
            if(grid[i+4][j+4] == 0){     //Any position with a 0 means the line is not complete
                complete = false;
                break;
            }
        }
        if(complete == true) {
            count++;
            deleteLine(i);
        }
    }

    //Score bonus for multiple lines
    if(count == 2)
        score += 10;
    else if(count == 3)
        score += 30;
    else if(count >= 4)
        score += 100;
}

//Deletes the line indicated from checkLines and updates the game
void Game::deleteLine(int i) {
    //Delete the Line
    for(int a= 0; a < 10; a++) {
        grid[i+4][a+4] = 0;
    }

    //Drop everything above the deleted line down 1
    for(int b = i+4; b > 4; b--) {
        for(int c = 0; c < 10; c++) {
            //Make sure not to drop down death zone
            if(grid[b-1][c+4] != 9) {
                grid[b][c+4] = grid[b-1][c+4];
            }
            else {
                grid[b][c+4] = 0;
            }
        }
    }

    //Check for game update
    linesNeeded--;
    score += 20;
    if(linesNeeded <= 0) {
        level++;
        linesNeeded = linesMult*level;  //Next level needs 10 more lines then the previous
        if(speed >= 0)
            speed -= 0.05;
    }
}
//-------------------------------------End Game Functions-----------------------------------

#endif

