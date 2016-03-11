#include "es5.h"
#include "es9.h"
#include "es10.h"
#include "es11.h"
#include "es7.h"

AbstractState::TransitionResult ES5::Transition(AbstractStateMachine &machine, Symbol symbol)
{
    AbstractState::TransitionResult ret = AbstractState::UNEXPECTED;
    switch (symbol.code) {
    case S_ID:
        machine.PileUp(symbol, new ES9);
        ret = AbstractState::PILED_UP;
        break;
    case S_NUM:
        machine.PileUp(symbol, new ES10);
        ret = AbstractState::PILED_UP;
        break;
    case S_PF:
        machine.PileUp(symbol, new ES11);
        ret = AbstractState::PILED_UP;
        break;
    case S_F:
        machine.PileUp(symbol, new ES7);
        ret = AbstractState::PILED_UP;
        break;
    default:
        machine.Unexpected(symbol);ret = AbstractState::UNEXPECTED;
        ret = AbstractState::UNEXPECTED;
        break;
    }
    return ret;
}

ES5::ES5() :
    AbstractState("ES5")
{

}
