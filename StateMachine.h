#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "Nintendo.h"

class StateMachine
{
public:
    StateMachine();

    Gamecube_Report_t* processInput( Gamecube_Report_t* report );

private:
    // Used to indentify the reason for being in the current state
    typedef enum
    {
        ENTRY,
        EXIT,
        CONTINUE
    } Reason;

    // The function pointer that every state must adhere to
    typedef void ( StateMachine::*State_ptr ) ( Reason reason, Gamecube_Report_t* report );

    // Used to determine how we are traveling through the state machine
    State_ptr currState;
    State_ptr prevState;

    State_ptr stateLookup( Gamecube_Report_t* report );

    // States
    void stateNoInput( Reason reason, Gamecube_Report_t* report );
    void stateA( Reason reason, Gamecube_Report_t* report );
    void stateB( Reason reason, Gamecube_Report_t* report );
    void stateY( Reason reason, Gamecube_Report_t* report );
    void stateL( Reason reason, Gamecube_Report_t* report );
};

#endif //STATE_MACHINE_H
