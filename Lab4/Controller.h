#pragma once
#include "Repository.h"


class Controller
{
public:
	Controller();
	Controller(const Repository& r);  
	~Controller();
	Repository getRepo() const;
	void addMedToRepository(const std::string&, double, double, double);
	int updateMedInRepository(const std::string&, double, double);
	int DeleteFromRepository(const std::string&, double, double);
	std::vector<Med> shortSupply(double) const;
	std::vector<Med> searchName(const std::string&) const;
	std::vector<std::vector<Med>> groupPrice() const;
private:
	Repository repo;
};

