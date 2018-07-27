#pragma once
#include <iostream>
#include "Money.h"

class Employee
{
public:
	//Constructor and destructor
	Employee(std::string name, Money salary, Money bonusSalary, int workingDaysCount, int ID);
	Employee(const Employee& empl) = default;
	~Employee() = default;

	//Simple getters and setters
	Money GetSalary() const;
	void SetSalary(Money amount);

	int AddBalance(Money amount);

	//Simple getters and setters
	Money GetBonusSalary()const;
	void SetBonusSalary(Money amount);

	//Simple getters and setters
	std::string GetName()const;
	void ChangeName(std::string name);

	//Simple getters and setters
	int GetWorkingDaysCount() const;
	void SetWorkingDaysCount(int count);

	//Returns this employee's ID
	int GetID() const;

private:
	int ID;
	Money salary;
	Money bonusSalary;
	Money balance{ 0 };
	int workingDaysCount;
	std::string name;
};