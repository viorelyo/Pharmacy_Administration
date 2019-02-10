#include "stdafx.h"
#include "Repository.h"
#include <algorithm>				//used for - find()
#include <iomanip>				//used for setprecision()


Repository::Repository()
{
	medicines = {};
}

Repository::~Repository()
{
}

void Repository::addMed(const Med& elem)
{
	/*
	*	If the elem is in vector, it's quantity is increased
	*	otherwise it is added to the vector
	*/

	int pos = this->findMed(elem);

	if (pos == -1)
		medicines.push_back(elem);
	else {
		medicines[pos].setQuantity(medicines[pos].getQuantity() + elem.getQuantity());
	}	
}

void Repository::updateMed(const Med& elem, double newPrice)
{
	int pos = this->findMed(elem);
	medicines[pos].setPrice(newPrice);
}

int Repository::deleteMed(const std::string& name, double concentration, double quant)
{
	/*
	*	Verifies if the elem exists in vector
	*	Deletes the selectet quantity - quant from the selecte elem
	*	If there is no more quantity in elem, the elem is removed from vector
	*/

	int pos = this->findByID(name, concentration);

	if (pos == -1) {
		return -1;		//no such element
	}
	else {
		double actualQuantity = this->medicines[pos].getQuantity();
		if (actualQuantity - quant <= 0)			//delete the whole quantity (object)
			this->medicines.erase(medicines.begin() + pos);
		else			//remove the selected quantity - quant
			this->medicines[pos].setQuantity(this->medicines[pos].getQuantity() - quant);
		return 0;		//successfully
	}
}

int Repository::findMed(const Med& elem)
{
	/*
	*	Search an element in vector
	*	Returns the index of object in vector
	*/

	auto it = std::find(medicines.begin(), medicines.end(), elem);		//search element in vector

	if (it == medicines.end())
		return -1;			//element not founded
	else
		return std::distance(medicines.begin(), it);		//return index of element in vector
}

int Repository::findByID(const std::string& name, double concentration) {
	/*
	*	Search an element in vector by it's uniqe identifier (name + concentration)
	*	Returns the index of object in vector
	*/

	for (unsigned i = 0; i < medicines.size(); i++)
		if (medicines[i].getName() == name && medicines[i].getConcentration() == concentration)
			return i;
	return -1;
}

std::vector<Med> Repository::getMedicines() const
{
	return medicines;
}