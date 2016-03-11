#include "ps8.h"

#include "../rules.h"

AbstractState::TransitionResult PS8::Transition(AbstractStateMachine &machine, Symbol symbol)
{
    AbstractState::TransitionResult ret = AbstractState::UNEXPECTED;
    switch (symbol.code) {
    case S_READ:///< 'lire'
        machine.Reduce(RULE_8);
        ret = AbstractState::REDUCED;
        break;
    case S_WRITE:///< 'ecrire'
        machine.Reduce(RULE_8);
        ret = AbstractState::REDUCED;
        break;
    case S_ID:///< identifiant '\w[\w\d]*'
        machine.Reduce(RULE_8);
        ret = AbstractState::REDUCED;
        break;
    case S_EOF:///< $
        machine.Reduce(RULE_8);
        ret = AbstractState::REDUCED;
        break;
    default:
        machine.Unexpected(symbol);
        break;
    }
    return ret;
}

PS8::PS8() :
    AbstractState("PS8")
{

}
