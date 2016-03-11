#include "ps6.h"

int PS6::Transition(ProgramStateMachine &machine, Symbol symbol)
{
    switch (symbol) {
    case S_ID:///< identifiant '\w[\w\d]*'
        machine.PileUp(symbol, new PS7("PS7"));
        break;
    default:
        machine.Unexpected(symbol);
        break;
    }
    return -1;
}

PS6::PS6() :
    AbstractPS("PS6")
{

}
