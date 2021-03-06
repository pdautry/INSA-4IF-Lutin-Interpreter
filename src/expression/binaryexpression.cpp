#include "binaryexpression.h"
#include "src/config.h"
#include "src/debug.h"
#include "number.h"
#include "variable.h"
#include <sstream>

#define DEEP_COPY(original, copy) \
    if(original->IsNumber()) { copy = new Number(*dynamic_cast<Number*>(original)); } \
    else if(original->IsVariable()) { copy = new Variable(*dynamic_cast<Variable*>(original)); } \
    else if(original->IsBinaryExpression()) { copy = new BinaryExpression(*dynamic_cast<BinaryExpression*>(original)); }

BinaryExpression::~BinaryExpression()
{
    // libération mémoire
    delete _left;
    delete _right;
}

BinaryExpression::BinaryExpression(BinaryOperator op, AbstractExpression * left, AbstractExpression * right) :
    AbstractExpression(),
    _op(op),
    _left(left),
    _right(right)
{}

BinaryExpression::BinaryExpression(BinaryExpression &other) :
    _op(other._op)
{
    // copie profonde de l'opérande à gauche !
    DEEP_COPY(other._left, _left)
    // copie profonde de l'opérande à droite !
    DEEP_COPY(other._right, _right)
}

void BinaryExpression::GetUsedVariables(set<string> &list) const
{
    _left->GetUsedVariables(list);
    _right->GetUsedVariables(list);
}

double BinaryExpression::Eval(DataMap &dmap, bool & ok) const
{
    double value(0);
    double left_eval = _left->Eval(dmap, ok);
    if(ok)
    {   double right_eval = _right->Eval(dmap, ok);
        // si les deux évaluations précédentes sont valides
        if(ok)
        {   // on effectue le calcul en fonction de l'opération
            switch (_op) {
            case BOP_PLUS:
                value = left_eval + right_eval;
                break;
            case BOP_MINUS:
                value = left_eval - right_eval;
                break;
            case BOP_MULT:
                value = left_eval * right_eval;
                break;
            case BOP_DIV:
                if(right_eval != 0)
                {   value = left_eval / right_eval;
                }
                else
                {   ok = false; // on baisse le flag ok pour signaler l'erreur (division par zero)
                }
                break;
            }
        }
    }
    return value;
}

AbstractExpression *BinaryExpression::Simplify(DataMap &dmap, bool &ok)
{
    AbstractExpression * simplified = NULL;
    // on essaie d'abord de simplifier les deux opérandes
    AbstractExpression * left_simplified = _left->Simplify(dmap, ok);
    if(ok)
    {   AbstractExpression * right_simplified = _right->Simplify(dmap, ok);
        if(ok)
        {   if(left_simplified != NULL)
            {   // on libère la mémoire de l'ancien opérande de gauche
                delete _left; // (<!> il faut faire des copies profondes à cause de cette ligne <!>)
                // on associe le nouvel opérande de gauche au calcul
                _left = left_simplified;
            }
            if(right_simplified != NULL)
            {   // on libère la mémoire de l'ancien opérande de droite
                delete _right; // (<!> il faut faire des copies profondes à cause de cette ligne <!>)
                // on associe le nouvel opérande de droite au calcul
                _right = right_simplified;
            }
            // on essaie ensuite de simplifier le calcul
            // si les deux opérandes sont des nombres
            if(_left->IsNumber() && _right->IsNumber())
            {   // on simplifie le calcul en évaluant ce dernier
                double value = Eval(dmap, ok);
                // si l'évaluation s'est bien déroulée
                if(ok)
                {   simplified = new Number(value);
                }
            }
            else // sinon on cherche les éléments neutres
            {
                bool uselessOk;
                switch (_op) {
                case BOP_PLUS:
                    if(_left->IsNumber() && _left->Eval(dmap, uselessOk) == 0)
                    {   // copie profonde
                        DEEP_COPY(_right, simplified)
                    }
                    else if(_right->IsNumber() && _right->Eval(dmap, uselessOk) == 0)
                    {   // copie profonde
                        DEEP_COPY(_left, simplified)
                    }
                    break;
                case BOP_MINUS:
                    if(_right->IsNumber() && _right->Eval(dmap, uselessOk) == 0)
                    {   // copie profonde
                        DEEP_COPY(_left, simplified)
                    }
                    break;
                case BOP_MULT:
                    if(_left->IsNumber() && _left->Eval(dmap, uselessOk) == 1)
                    {   // copie profonde
                        DEEP_COPY(_right, simplified)
                    }
                    else if(_right->IsNumber() && _right->Eval(dmap, uselessOk) == 1)
                    {   // copie profonde
                        DEEP_COPY(_left, simplified)
                    }
                    break;
                case BOP_DIV:
                    if(_right->IsNumber() && _right->Eval(dmap, uselessOk) == 1)
                    {   // copie profonde
                        DEEP_COPY(_left, simplified)
                    }
                    break;
                }
            }
        }
    }
    return simplified;
}

string BinaryExpression::Stringify() const
{
    stringstream ss("");

    if (_requireParenthesis)
        ss << "(";

    ss << _left->Stringify();
    switch (_op) {
    case BOP_PLUS:  ss << '+'; break;
    case BOP_MINUS: ss << '-'; break;
    case BOP_MULT:  ss << '*'; break;
    case BOP_DIV:   ss << '/'; break;
    }
    ss << _right->Stringify();

    if (_requireParenthesis)
        ss << ")";

    return ss.str();
}
