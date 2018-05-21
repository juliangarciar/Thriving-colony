#include "Condition.h"

Condition::Condition(Action* relatedAction) : Behaviour() {
    action = relatedAction;
}

Condition::~Condition() {
    delete action;
}