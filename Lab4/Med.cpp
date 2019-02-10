#include "stdafx.h"
#include "Med.h"


Med::Med()
{
	this->name = "";
	this->concentration = 0;
	this->quantity = 0;
	this->price = 0;
}

Med::Med(const std::string& name, const double concentration, const double quantity, const double price)
{
	this->name = name;
	this->concentration = concentration;
	this->quantity = quantity;
	this->price = price;
}

Med::~Med()
{
}

std::string Med::getName() const
{
	return this->name;
}

void Med::setName(std::string& nam) 
{
	this->name = nam;
}

double Med::getConcentration() const 
{
	return concentration;
}

void Med::setConcentration(double concentr)
{
	this->concentration = concentr;
}

double Med::getQuantity() const
{
	return quantity;
}

void Med::setQuantity(double quant)
{
	this->quantity = quant;
}

double Med::getPrice() const
{
	return price;
}

void Med::setPrice(double pr)
{
	this->price = pr;
}

bool Med::operator==(const Med& other) const
{
	/*
	*	Overload == operator 
	*	Used for find function <algorithm>
	*	Verify if two Elements of class Med are equal
	*	They are equal when they both have same name and concentration
	*/

	if ((this->name == other.name) && (this->concentration == other.concentration))
		return true;
	else
		return false;
}

bool Med::operator!=(const Med& other) const
{
	if ((this->name != other.name) && (this->concentration != other.concentration))
		return true;
	else
		return false;
}
