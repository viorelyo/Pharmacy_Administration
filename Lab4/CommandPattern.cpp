#include "stdafx.h"
#include "CommandPattern.h"


Receiver::~Receiver()
{
}


void Receiver::Add(const std::string& name, double concentration, double quantity, double price)
{
	command = new AddCommand(name, concentration, quantity, price);
	command->setCtrl(&ctrl);
	command->execute();
	DoneCommands.push_back(command);
}


int Receiver::Delete(const std::string & name, double concentration, double quantDel)
{
	command = new DeleteCommand(name, concentration, quantDel);
	command->setCtrl(&ctrl);
	int ret = command->execute();				//save the return code of the function (importand in case of warnings)
	DoneCommands.push_back(command);
	return ret;
}


int Receiver::Update(const std::string & name, double concentration, double newPrice)
{
	command = new UpdateCommand(name, concentration, newPrice);
	command->setCtrl(&ctrl);
	int ret = command->execute();				//save the return code of the function (importand in case of warnings)
	DoneCommands.push_back(command);
	return ret;
}


int Receiver::Undo()
{
	if (DoneCommands.size() == 0) {
		return -1;			//there is nothing to undo
	}
	else
	{
		command = DoneCommands.back();
		DoneCommands.pop_back();
		command->unExecute();
		Trash.push_back(command);

		return 0;
	}
}

int Receiver::Redo()
{
	if (Trash.size() == 0) {
		return -1;				//nothing to redo
	}
	else
	{
		command = Trash.back();
		Trash.pop_back();
		command->execute();
		DoneCommands.push_back(command);

		return 0;
	}
}
