#include "es10.h"
#include "../rules.h"

AbstractState::TransitionResult ES10::Transition(AbstractStateMachine &machine, const Symbol & symbol)
{
    AbstractState::TransitionResult ret = AbstractState::UNEXPECTED;
    switch (symbol.code) {
    case S_EOF:
        machine.Reduce(SYM_F, RULE_9);
        ret = AbstractState::REDUCED;
        break;
    case S_PF:
        machine.Reduce(SYM_F, RULE_9);
        ret = AbstractState::REDUCED;
        break;
    case S_PLUS:
        machine.Reduce(SYM_F, RULE_9);
        ret = AbstractState::REDUCED;
        break;
    case S_MINUS:
        machine.Reduce(SYM_F, RULE_9);
        ret = AbstractState::REDUCED;
        break;
    case S_MULT:
        machine.Reduce(SYM_F, RULE_9);
        ret = AbstractState::REDUCED;
        break;
    case S_DIV:
        machine.Reduce(SYM_F, RULE_9);
        ret = AbstractState::REDUCED;
        break;
    case S_PV:
        machine.Reduce(SYM_F, RULE_9);
        ret = AbstractState::REDUCED;
        break;
    default:
        SYNTAX_ERROR_HANDLER(SYM_PV)
        break;
    }
    return ret;
}

ES10::ES10() :
    AbstractState("ES10")
{

}
