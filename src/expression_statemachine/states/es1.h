#ifndef ES1_H
#define ES1_H


#include "src/interfaces/abstractstate.h"

/**
 * @brief Etat définissant le comportement par defaut pour les transitions des états de
 *      la machine à état qui analyse les expressions arithmétiques.
 */
class ES1 : public AbstractState
{
public:
    ES1();
    ~ES1(){}

    /**
     * @brief Réalise la transition depuis un état vers un autre état
     * @param machine
     * @param symbol
     * @return
     */
    virtual TransitionResult Transition(AbstractStateMachine & machine, Symbol symbol);


};

#endif // ES1_H
