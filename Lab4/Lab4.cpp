#include "stdafx.h"
#include "UI.h"
#include <cassert>


void Tests()
{
	Repository repo;
	Controller ctrl(repo);

	ctrl.addMedToRepository("Nurofen", 500, 3, 50);
	ctrl.addMedToRepository("Nurofen", 100, 2, 45);
	ctrl.addMedToRepository("Mezym", 100, 2, 45);
	ctrl.addMedToRepository("Nurofen", 600, 3, 50);

	Receiver res;
	res.setMyCtrl(ctrl);


	assert(res.getCtrl().getRepo().getMedicines().size() == 4);

	res.Add("Septolete", 300, 1, 40);
	assert(res.getCtrl().getRepo().getMedicines().size() == 5);

	res.Undo();
	assert(res.getCtrl().getRepo().getMedicines().size() == 4);

	res.Redo();
	assert(res.getCtrl().getRepo().getMedicines().size() == 5);
	
	res.Add("Septolete", 300, 1, 40);
	assert(res.getCtrl().getRepo().getMedicines()[4].getQuantity() == 2);
	
	res.Delete("Septolete", 300, 1);
	assert(res.getCtrl().getRepo().getMedicines().size() == 5);
	
	assert(res.getCtrl().getRepo().getMedicines()[4].getQuantity() == 1);

	res.Update("Septolete", 300, 30);
	assert(res.getCtrl().getRepo().getMedicines()[4].getPrice() == 30);
	
	assert(res.getCtrl().searchName("Septolete")[0].getConcentration() == 300);

	assert(res.getCtrl().shortSupply(2)[0].getName() == "Septolete");
}



int main() 
{
	Tests();

	Repository repo;
	Controller ctrl(repo);

	ctrl.addMedToRepository("Nurofen", 500, 1, 50);
	ctrl.addMedToRepository("Nurofen", 100, 1, 45);
	ctrl.addMedToRepository("Mezym", 100, 1, 45);
	ctrl.addMedToRepository("Nurofen", 600, 1, 50);
	
	Receiver res;
	res.setMyCtrl(ctrl);
	UI ui(res);
	
	ui.run();
	
	return 0;
}