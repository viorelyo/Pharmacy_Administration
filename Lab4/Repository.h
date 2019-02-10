#pragma once
#include "Med.h"
#include <vector>


class Repository
{
public:
	Repository();
	~Repository();
	void addMed(const Med&);
	void updateMed(const Med&, double);
	int deleteMed(const std::string&, double, double);
	int findMed(const Med&);
	int findByID(const std::string& , double);
	std::vector<Med> getMedicines() const;
private:
	std::vector<Med> medicines;
};

