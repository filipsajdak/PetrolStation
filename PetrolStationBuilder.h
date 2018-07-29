#pragma once

#include <memory>
#include <string>

class Employee;
class PetrolStation;
class Depot;
class Till;

struct RequirementsNotFulfilled {};

class PetrolStationBuilder
{
public:
	PetrolStationBuilder(std::string name, int ID);
	~PetrolStationBuilder();

	template <typename T, typename... Args>
	PetrolStationBuilder & add(T&& a, Args... args) { 
		return add(std::forward<T>(a)).add(std::forward<Args>(args)...);
	}

	PetrolStationBuilder & add(Employee&& employee);
	PetrolStationBuilder & add(Depot&& depot);
	PetrolStationBuilder & add(Till&& till);
	PetrolStationBuilder& setNameAndID(std::string name, int ID);

	PetrolStation build();

private:
	class PetrolStationBuilderImpl;
	std::unique_ptr<PetrolStationBuilderImpl> pimpl;
};

