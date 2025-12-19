#ifndef VALIDATE_H
#define VALIDATE_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
#include "Conditional.h"
#include "Start.h"
#include "End.h"
#include <string>
using namespace std;

class Validate : public Action
{
public:
    Validate(ApplicationManager* pAppManager);
    virtual void ReadActionParameters();
    virtual void Execute();
};

#endif
