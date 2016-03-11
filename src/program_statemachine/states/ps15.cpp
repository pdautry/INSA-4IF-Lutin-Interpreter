#include "ps15.h"
#include "../rules.h"

AbstractState::TransitionResult PS15::Transition(AbstractStateMachine &machine, Symbol symbol)
{
    AbstractState::TransitionResult ret = AbstractState::UNEXPECTED;
    switch (symbol.code) {
    case S_V:///< ','
        machine.Reduce(Symbol(S_LV), RULE_2);
        ret = AbstractState::REDUCED;
        break;
    case S_PV:///< ';'
        machine.Reduce(Symbol(S_LV), RULE_2);
        ret = AbstractState::REDUCED;
        break;
    default:
        machine.Unexpected(symbol);
        break;
    }
    return ret;
}

PS15::PS15() :
    AbstractState("PS15")
{

}
