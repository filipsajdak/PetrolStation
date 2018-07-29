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
		if (name.empty()) 
			throw RequirementsNotFulfilled();
		
		PetrolStation p(std::move(name), std::move(ID));
		
		move_to_product(p, employees, [](auto&& p, auto&& e) {p.AddEmployee(std::move(e)); });
		move_to_product(p, depots, [](auto&& p, auto&& e) {p.AddDepot(std::move(e)); });
		move_to_product(p, tills, [](auto&& p, auto&& e) {p.AddTill(std::move(e)); });
		
		return p;
	}

	void setNameAndID(std::string n, int i) {
		name = n;
		ID = i;
	}

private:
	std::string name;
	int ID;
	std::vector<Employee> employees;
	std::vector<Depot> depots;
	std::vector<Till> tills;

	template <typename T, typename F>
	void move_to_product(PetrolStation& p, T&& c, F&& fun) {
		T from(std::move(c));
		for (auto&& e : from) fun(p, std::move(e));
	}
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

PetrolStationBuilder & PetrolStationBuilder::setNameAndID(std::string name, int ID)
{
	pimpl->setNameAndID(std::move(name), std::move(ID));
	return *this;
}

PetrolStation PetrolStationBuilder::build() {
	return pimpl->build();
}
