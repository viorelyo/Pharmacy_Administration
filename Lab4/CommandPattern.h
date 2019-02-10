#pragma once
#include "Controller.h"


//Each command (Add, Delete, Update) inherites from Command class
//Works on principle of command and it's reverse (each command has it's own class with 2 methods (execute -> Controller), (unExecute -> reverse from Controller)
//After an execution, the command instance is added to the stack(vector)
//At undo it is poped from the stack 


class Command
{
protected:
	Controller * ctrl;
public:
	virtual ~Command() { delete this; }
	virtual int execute() = 0;
	virtual int unExecute() = 0;

	void setCtrl(Controller *c) {
		this->ctrl = c;
	}
};


class AddCommand : public Command
{
private:
	std::string name;
	double concentration;
	double quantity;
	double price;
public:
	AddCommand(const std::string& nam, double conc, double quant, double pret) : name(nam), concentration(conc), quantity(quant), price(pret) {}

	int execute()
	{
		ctrl->addMedToRepository(name, concentration, quantity, price);
		return 0;
	}

	int unExecute()
	{
		return ctrl->DeleteFromRepository(name, concentration, quantity);				//reverse of add is delete
	}
};


class DeleteCommand : public Command
{
private:
	std::string name;
	double concentration;
	double quantDel;
	double price;
public:
	DeleteCommand(const std::string& nam, double conc, double quanDelete) : name(nam), concentration(conc), quantDel(quanDelete) {}

	int execute()
	{
		int pos = ctrl->getRepo().findByID(name, concentration);
		if (pos != -1) {
			price = ctrl->getRepo().getMedicines()[pos].getPrice();
			return ctrl->DeleteFromRepository(name, concentration, quantDel);
		}
		else
		{
			return -1;							//reproduces the effect from Controller
		}
	}

	int unExecute()
	{
		ctrl->addMedToRepository(name, concentration, quantDel, price);					//reverse of delete is add
		return 0;
	}
};


class UpdateCommand : public Command
{
private:
	std::string name;
	double concentration;
	double newPrice;
	double oldPrice;
public:
	UpdateCommand(const std::string& nam, double conc, double newPret) : name(nam), concentration(conc), newPrice(newPret) {}

	int execute()
	{
		int pos = ctrl->getRepo().findByID(name, concentration);
		if (pos != -1) {
			oldPrice = ctrl->getRepo().getMedicines()[pos].getPrice();
			return ctrl->updateMedInRepository(name, concentration, newPrice);
		}
		else
			return -1;				//reproduces the effect from Controller
	}

	int unExecute()
	{
		return ctrl->updateMedInRepository(name, concentration, oldPrice);			//should save the oldPrice and reverse the update
	}
};


class Receiver
{
private:
	std::vector<Command*> DoneCommands;				//used at undo
	std::vector<Command*> Trash;					//used at redo

	Controller ctrl;
	Command* command;
public:
	void setMyCtrl(const Controller& c) { this->ctrl = c; }
	Controller getCtrl() const { return ctrl; }
	~Receiver();

	void Add(const std::string&, double, double, double);
	int Delete(const std::string&, double, double);
	int Update(const std::string&, double, double);

	int Undo();
	int Redo();
};
