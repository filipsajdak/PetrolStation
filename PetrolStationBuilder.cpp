#include "PetrolStationBuilder.h"

#include <vector>
#include <algorithm>
#include <iostream>

#include "PetrolStation.h"
#include "Employee.h"
#include "Depot.h"
#include "Till.h"

template <typename ProductType, typename T>
class Gatherer {
public:
	template <typename Fun>
	Gatherer(Fun&& fun) : fun(std::forward<Fun>(fun)){}

	void emplace_back(T&& i) { items.emplace_back(std::forward<T>(i)); }

	void move_to_product(ProductType& p) {
		auto from(std::move(items));
		for (auto&& e : from) fun(p, std::move(e));
	}

private:
	void(*fun)(ProductType&, T&&);
	std::vector<T> items;
};

class PetrolStationBuilder::PetrolStationBuilderImpl {
public:
	PetrolStationBuilderImpl(std::string name, int ID) 
		: name(name)
		, ID(ID)
		, employees([](auto& p, auto&& e) { p.AddEmployee(std::move(e)); })
		, depots([](auto& p, auto&& e) { p.AddDepot(std::move(e)); })
		, tills([](auto& p, auto&& e) { p.AddTill(std::move(e)); })
	{}

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
	
		employees.move_to_product(p);
		depots.move_to_product(p);
		tills.move_to_product(p);
		
		return p;
	}

	void setNameAndID(std::string n, int i) {
		name = n;
		ID = i;
	}

private:
	std::string name;
	int ID;
	Gatherer<PetrolStation, Employee> employees;
	Gatherer<PetrolStation, Depot> depots;
	Gatherer<PetrolStation, Till> tills;
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
