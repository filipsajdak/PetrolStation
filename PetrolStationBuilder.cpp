#include "PetrolStationBuilder.h"

#include <vector>
#include <algorithm>
#include <iostream>

#include "PetrolStation.h"
#include "Employee.h"
#include "Depot.h"
#include "Till.h"

class PetrolStationBuilder::PetrolStationBuilderImpl {
public:
	PetrolStationBuilderImpl(std::string name, int ID) : name(name), ID(ID) {}

	void add(Employee&& e) {
		employees.emplace_back(std::move(e));
	}

	void add(Depot&& d) {
		depots.emplace_back(std::move(d));
	}

	void add(Till&& t) {
		tills.emplace_back(std::move(t));
	}

	PetrolStation build() {
		PetrolStation p(std::move(name), std::move(ID));
		for (auto&& e : employees) p.AddEmployee(std::move(e));
		for (auto&& d : depots) p.AddDepot(std::move(d));
		for (auto&& t : tills) p.AddTill(std::move(t));
		return p;
	}

private:
	std::string name;
	int ID;
	std::vector<Employee> employees;
	std::vector<Depot> depots;
	std::vector<Till> tills;
};

PetrolStationBuilder::PetrolStationBuilder(std::string name, int ID) : pimpl{ new PetrolStationBuilderImpl(name, ID) } {}
PetrolStationBuilder::~PetrolStationBuilder() = default;

PetrolStationBuilder& PetrolStationBuilder::add(Employee&& employee) {
	pimpl->add(std::move(employee));
	return *this;
}

PetrolStationBuilder& PetrolStationBuilder::add(Depot&& depot) {
	pimpl->add(std::move(depot));
	return *this;
}

PetrolStationBuilder& PetrolStationBuilder::add(Till&& till) {
	pimpl->add(std::move(till));
	return *this;
}

PetrolStation PetrolStationBuilder::build() {
	return pimpl->build();
}
