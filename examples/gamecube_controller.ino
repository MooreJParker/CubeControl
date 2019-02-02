#include "Nintendo.h"
#include "StateMachine.h"

#define NUM_LEDS 3
#define DATA_PIN  13

// Define a Gamecube Controller
CGamecubeController GamecubeController( 3 );
CGamecubeConsole GamecubeConsole( 5 );
 
// The state machine that detects inputs
// and outputs the appropriate action
StateMachine stateMachine;

void setup()
{
}

void loop()
{
    // Try to read the controller data
    if ( GamecubeController.read() )
    {
        // Get the inputs from the controller
        Gamecube_Report_t* report = GamecubeController.getReport();

        stateMachine.processInput( report );

        // Send the input to the console
        if ( !GamecubeConsole.write( *report ) )
        {
            // Error writing to console
            delay( 1000 );
        }
    }
    else
    {
        // Error reading controller
        delay( 1000 );
    }
}

