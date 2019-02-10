// Medicine Class
// DOMAIN

#pragma once
#include <string>
#include <iostream>


class Med
{
public:
	Med();		//Default Constructor 
	Med(const std::string&, const double, const double, const double);		//Constructor with parameters
	~Med();
	std::string getName() const;
	void setName(std::string&);
	double getConcentration() const;
	void setConcentration(double);
	double getQuantity() const;
	void setQuantity(double);
	double getPrice() const;
	void setPrice(double);
	bool operator==(const Med&) const;
	bool operator!=(const Med&) const;
	 
private:
	std::string name;
	double concentration;
	double quantity;
	double price;
};

