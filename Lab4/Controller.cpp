#include "stdafx.h"
#include "Controller.h"
#include <algorithm>


Controller::Controller()
{
}


Controller::Controller(const Repository& r)
{
	this->repo = r;
}


Controller::~Controller()
{
}

Repository Controller::getRepo() const
{
	return repo;
}

void Controller::addMedToRepository(const std::string & nume, double concentr, double quant, double pret)
{
	int pos = repo.findByID(nume, concentr);				//verifies by ID if the product is in repo
	if (pos == -1) {									
		Med obj(nume, concentr, quant, pret);				//if not -> creates a new one
		this->repo.addMed(obj);
	}
	else
	{
		Med obj = repo.getMedicines()[pos];					//otherwise	updates the existing one (quantity is increased)
		obj.setQuantity(quant);
		this->repo.addMed(obj);
	}
}

int Controller::updateMedInRepository(const std::string & nume, double concentr, double newPrice)
{
	int pos = repo.findByID(nume, concentr);				
	if (pos == -1)										
		return -1;
	else {												//if the object is in repo then updates it
		Med obj = repo.getMedicines()[pos];
		this->repo.updateMed(obj, newPrice);
		return 0;
	}
}

int Controller::DeleteFromRepository(const std::string & nume, double concentr, double quantDel)
{
	return this->repo.deleteMed(nume, concentr, quantDel);
}

std::vector<Med> Controller::shortSupply(double items) const
{
	/*
	*	Returns vector of Med Objects that has quantity below than that indicated - items
	*/

	std::vector<Med> allMedicines = this->repo.getMedicines();
	std::vector<Med> runOut;			//vector with found objects

	for (unsigned i = 0; i < allMedicines.size(); i++) {
		if (allMedicines[i].getQuantity() < items)
			runOut.push_back(allMedicines[i]);
	}

	return runOut;
}

std::vector<Med> Controller::searchName(const std::string & search) const
{
	/*
	*	Search for available Medications containing given string - search
	*   If the given string - search is empty return all Medications
	*	Otherwise returns the vector with founded objects
	*	The vector is sorted alphabetically
	*/

	std::vector<Med> allMedicines = this->repo.getMedicines();
	
	std::sort(allMedicines.begin(), allMedicines.end(), [](const Med& lName, const Med& rName) { return lName.getName() < rName.getName(); });		//sort alphabetically (use specified comparator (lambda function)

	if (search == "")
		return allMedicines;
	else
	{
		std::vector<Med> found;				//vector with found objects

		for (unsigned i = 0; i < allMedicines.size(); i++) {
			if (allMedicines[i].getName().std::string::find(search) != std::string::npos)
				found.push_back(allMedicines[i]);
		}

		return found;
	}

}

std::vector<std::vector<Med>> Controller::groupPrice() const
{
	/*
	*	Group Medications by their price
	*	Returns a matrix of Med Objects
	*/

	std::vector<Med> allMedicines = this->repo.getMedicines();
	std::vector<std::vector<Med>> group;			//declaration of "Matrix"

	if (allMedicines.size() != 0) {					//the algorithm is done in case there are objects in allMedicine vector
		std::vector<Med> line;						//declaration of vector that will be inserted in "Matrix"
		unsigned j = 0;
		bool added = false;

		line.push_back(allMedicines[0]);		//init first element of "Matrix"
		group.push_back(line);						
		
		for (unsigned i = 1; i < allMedicines.size(); i++) {
			j = 0;
			added = false;
			while (j < group.size()) {								//size of group is variable (is permanently modified)
				if (allMedicines[i].getPrice() == group[j][0].getPrice()) {			//First object of each line-vector contains the group-price
					group[j].push_back(allMedicines[i]);					//Append an object to it's coresponding price-group
					added = true;
					break;
				}
				j++;
			}
			if (!added) {
				std::vector<Med> lines;								//Declare the vector-lines that will be inserted in group-"Matrix"
				lines.push_back(allMedicines[i]);
				group.push_back(lines);								//Insert each line-vector 
			}
		}
	}
	return group;
}