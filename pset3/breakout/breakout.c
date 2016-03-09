//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "spl/gevents.h"
#include "spl/gobjects.h"
#include "spl/gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// height and width of the paddle in pixels
#define HEIGHT_P 10
#define WIDTH_P 70

// height and width of each brick in pixels
#define HEIGHT_B 35
#define WIDTH_B 10

// gap between the bricks in pixels
#define GAP_B 5

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    waitForClick();
    
    double hori_v = 2.0;
    double vert_v;
    do
    {        
        vert_v = 3 + drand48();
    } while (vert_v < 1.0);

    // keep playing until game over
    
    updateScoreboard(window, label, points);
    
    while (lives > 0 && bricks > 0)
    {
               
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                double x = getX(event);
                if (getX(event) + getWidth(paddle) >= getWidth(window))
                {
                    x = getWidth(window) - getWidth(paddle);
                }
                
                double y = HEIGHT - 100;
                
                setLocation(paddle, x, y);
            }            
            
        }
        
        
        
        move(ball, hori_v, vert_v);
        
        if (getX(ball) + getWidth(ball) >= getWidth(window) || getX(ball) <= 0)
        {
            hori_v = -hori_v;
        }
        
        else if (getY(ball) <= 0)
        {
            vert_v = -vert_v;
        }
        
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            --lives;
            removeGWindow(window, ball);
            
            if (lives != 0)
            {
                waitForClick();
                ball = initBall(window);
                do
                {        
                    vert_v = 3 + drand48();
                } while (vert_v < 1.0);
            
                waitForClick();
                continue;
            }
        }
        
        GObject object = detectCollision(window, ball);
        
        if (object != NULL)
        {
            if (object == paddle)
            {
                vert_v = -vert_v;                
            }
        
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                ++points;
                --bricks;
                vert_v = -vert_v;
                
                removeGWindow(window, label);
                label = initScoreboard(window);
                updateScoreboard(window, label, points);
            }        
            
        }
        
       pause(10);
    }
    
    waitForClick();
    
    removeGWindow(window, label);
    removeGWindow(window, ball);
    
    double x, y;  
        
    if (points == 50)
    {
        
        label = newGLabel("You Won !");
        setFont(label, "SansSerif-36");
        x = (getWidth(window) - getWidth(label)) / 2;
        y = (getHeight(window) - getHeight(label)) / 2;
    }
    
    else
    {
        label = newGLabel("Sorry ! You LOST !!");
        setFont(label, "SansSerif-36");
        x = (getWidth(window) - getWidth(label)) / 2;
        y = (getHeight(window) - getHeight(label)) / 2; 
    }
    
    setLocation(label, x, y);
    add(window, label);

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    char* brk_clr [ROWS] = {"RED", "PINK", "YELLOW", "GREEN", "BLUE"};
   
   int x_cord = 2;
   int y_cord = 50;
   
   for (int i = 0; i < ROWS; ++i)
   {
        for (int j = 0; j < COLS; ++j)
        {
            GRect rect = newGRect(x_cord, y_cord, HEIGHT_B, WIDTH_B);
            setColor(rect, brk_clr[i]);
            setFilled(rect, true);
            add(window, rect);
            
            x_cord += HEIGHT_B + GAP_B;
        }
        
        x_cord = 2;
        y_cord += WIDTH_B + GAP_B;
   }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval circle = newGOval(((WIDTH / 2) - RADIUS), ((HEIGHT / 2) - RADIUS), RADIUS * 2, RADIUS * 2);
    setColor(circle, "BLACK");
    setFilled(circle, true);
    add(window, circle); 
    
    return circle;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rect = newGRect((WIDTH / 2) - (WIDTH_P / 2), HEIGHT-100, WIDTH_P, HEIGHT_P);
    
    setColor(rect, "BLACK");
    setFilled(rect, true);
    add(window, rect);
    
    return rect;
    return NULL;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
