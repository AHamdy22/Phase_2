#ifndef Paste_H
#define Paste_H

#include "Actions\Action.h"
#include "Statements\Statement.h"
class Paste : public Action
{
	Point Position;
	Statement* InClipboard;

public:

	Paste(ApplicationManager* pAppManager);

	void ReadActionParameters();

	void Execute();

};

#endif