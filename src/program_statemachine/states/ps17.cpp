#include "ps17.h"
#include "../rules.h"

AbstractState::TransitionResult PS17::Transition(AbstractStateMachine &machine, Symbol symbol)
{
    AbstractState::TransitionResult ret = AbstractState::UNEXPECTED;
    switch (symbol.code) {
    case S_CONST:///< mot-clé 'const'
        machine.Reduce(Symbol(S_LD), RULE_4);
        ret = AbstractState::REDUCED;
        break;
    case S_VAR:///< mot-clé 'var'
        machine.Reduce(Symbol(S_LD), RULE_4);
        ret = AbstractState::REDUCED;
        break;
    case S_READ:///< 'lire'
        machine.Reduce(Symbol(S_LD), RULE_4);
        ret = AbstractState::REDUCED;
        break;
    case S_WRITE:///< 'ecrire'
        machine.Reduce(Symbol(S_LD), RULE_4);
        ret = AbstractState::REDUCED;
        break;
    case S_ID:///< identifiant '\w[\w\d]*'
        machine.Reduce(Symbol(S_LD), RULE_4);
        ret = AbstractState::REDUCED;
        break;
    default:
        machine.Unexpected(symbol);
        break;
    }
    return ret;

}

PS17::PS17() :
    AbstractState("PS17")
{

}
