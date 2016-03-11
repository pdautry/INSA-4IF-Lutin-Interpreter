#include "ps3.h"

int PS3::Transition(ProgramStateMachine &machine, Symbol symbol)
{
    switch (symbol) {

    case S_READ:///< 'lire'
        machine.PileUp(symbol, new PS6("PS6"));
        break;
    case S_WRITE:///< 'ecrire'
        machine.PileUp(symbol, new PS5("PS5"));
        break;
    case S_ID:///< identifiant '\w[\w\d]*'
        machine.PileUp(symbol, new PS9("PS9"));
        break;
    case S_EOF:///< $
        break;
    case S_I:///< instruction
        machine.PileUp(symbol, new PS4("PS4"));
        break;
    default:
        machine.Unexpected(symbol);
        break;
    }
    return -1;
}

PS3::PS3() :
    AbstractPS("PS3")
{

}
