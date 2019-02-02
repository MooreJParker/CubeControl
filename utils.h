#ifndef GC_ANALYZER_H
#define GC_ANALYZER_H

/******************************************************
All threshold values are the result of experimentation.
These values may not work on other controllers
******************************************************/

/****************
Stick thresholds
****************/
uint8_t STICK_NEUTRAL = 130;

// Stick Pressed all the way to right or left
uint8_t STICK_RIGHT_MAX = STICK_NEUTRAL + 100;
uint8_t STICK_LEFT_MAX = STICK_NEUTRAL - 100;

// Minimum values for the stick to pick up movement
uint8_t STICK_RIGHT_MIN = STICK_NEUTRAL + 30;
uint8_t STICK_LEFT_MIN = STICK_NEUTRAL - 30;

// Maximum values to still be considered a walk
uint8_t STICK_RIGHT_WALK_MAX = STICK_RIGHT_MIN + 28;
uint8_t STICK_LEFT_WALK_MAX = STICK_LEFT_MIN - 32;

/*****************
Trigger thresholds
*****************/
uint8_t TRIGGER_THRESH = 50;
uint8_t TRIGGER_NEUTRAL = 32;

typedef uint8_t StickStatus; enum
{
    NEUTRAL = 0,
    LEFT    = 1,
    RIGHT   = 2,
    UP      = 3,
    DOWN    = 4
};

uint8_t getMovementDirection( uint8_t xAxis )
{
    uint8_t rightThresh = 140;
    uint8_t leftThresh = 100;

    StickStatus movement = 0;
    if ( xAxis < leftThresh )
    {
        movement = LEFT;
    }
    else if ( xAxis > rightThresh )
    {
        movement = RIGHT;
    }

    return movement;
}

bool walking( uint8_t xAxis )
{
    StickStatus stickDir = getMovementDirection( xAxis );
    bool walking = false;

    if ( LEFT == stickDir )
    {
        if ( xAxis > STICK_LEFT_WALK_MAX &&
             xAxis < STICK_LEFT_MIN      )
        {
            walking = true;
        }
    }
    else if ( RIGHT == stickDir )
    {
        if ( xAxis < STICK_RIGHT_WALK_MAX &&
             xAxis > STICK_RIGHT_MIN      )
        {
            walking = true;
        }

    }

    return walking;
}

uint8_t flipXaxis( uint8_t xAxis )
{
    uint8_t rVal = STICK_NEUTRAL;
    if( LEFT == xAxis )
    {
        rVal = STICK_RIGHT_MAX;
    }
    else if( RIGHT == xAxis )
    {
        rVal = STICK_LEFT_MAX;
    }

    return rVal;
}

bool leftTriggerPressed( uint8_t left )
{
    uint8_t left_thresh = 50;

    if ( TRIGGER_THRESH < left )
    {
        return true;
    }
    return false;
}

#endif //GC_ANALYZER_H
