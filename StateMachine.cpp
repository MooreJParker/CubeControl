#include "StateMachine.h"
#include "utils.h"

StateMachine::StateMachine()
{
    currState = &StateMachine::stateNoInput;
    prevState = &StateMachine::stateNoInput;
}

Gamecube_Report_t* StateMachine::processInput(Gamecube_Report_t* report)
{
    currState = stateLookup(report);
    if ( currState != prevState )
    {
        ( this->*prevState )( EXIT, report );
        ( this->*currState )( ENTRY, report );
    }
    else
    {
        ( this->*currState )( CONTINUE, report );
    }
    prevState = currState;
    return report;
}

// Look up the state that corresponds to the input
StateMachine::State_ptr StateMachine::stateLookup( Gamecube_Report_t* report )
{
    if ( (*report).a )
    {
        return &StateMachine::stateA;
    }
    else if( (*report).b )
    {
        return &StateMachine::stateB;
    }
    else if ( (*report).y )
    {
        return &StateMachine::stateY;
    }
    else if ( leftTriggerPressed( (*report).left ) || 
              (*report).l                           )
    {
        return &StateMachine::stateL;
    }
    else
    {
        return &StateMachine::stateNoInput;
    }
}

// States
void StateMachine::stateNoInput( Reason reason, Gamecube_Report_t* report )
{
}

void StateMachine::stateA( Reason reason, Gamecube_Report_t* report )
{
    switch ( reason )
    {
        case ENTRY:
            break;
        case CONTINUE:
            break;
        case EXIT:
            break;
    }
}

void StateMachine::stateB( Reason reason, Gamecube_Report_t* report )
{
    switch ( reason )
    {
        case ENTRY:
            break;
        case CONTINUE:
            break;
        case EXIT:
            break;
    }
}

void StateMachine::stateY( Reason reason, Gamecube_Report_t* report )
{
    static uint8_t frameCount = 0;
    frameCount++;
    switch ( reason )
    {
        case ENTRY:
            frameCount = 0;
            break;
        case CONTINUE:
        case EXIT:
            if ( frameCount > 3 )
            {
                (*report).y = 0;
            }
            break;
    }
}

void StateMachine::stateL( Reason reason, Gamecube_Report_t* report )
{
    static uint8_t frameCount = 0;

    frameCount++;

    // Get the direction we're going
    StickStatus stickStatus = getMovementDirection( (*report).xAxis );

    switch ( reason )
    {
        case ENTRY:
            frameCount = 0;

            // First thing we do for a RAR is reverse
            // the stick direction
            (*report).xAxis = flipXaxis( stickStatus );
            break;
        case CONTINUE:
        case EXIT:
            if ( frameCount == 1 )
            {
                (*report).xAxis = flipXaxis( stickStatus );
            }
            else if ( frameCount >= 2 && frameCount <= 5 )
            {
                (*report).xAxis = flipXaxis( stickStatus );
                (*report).y = 1;
            }
            else if ( frameCount == 6 )
            {
                (*report).y = 1;
            }
            else if ( frameCount < 11 )
            {
                (*report).a = 1;
            }
            break;
    }

    // Remove the trigger input
    (*report).left = TRIGGER_NEUTRAL;
}

