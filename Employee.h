#pragma once
#include <iostream>
#include "Money.h"

class Employee
{
public:
	Employee(std::string name, Money salary, Money bonusSalary, int workingDaysCount, int ID);
	Employee(const Employee&) = delete;
	Employee& operator=(const Employee&) = delete;
	Employee(Employee&&) = default;
	Employee& operator=(Employee&&) = default;
	~Employee() = default;

	//Simple getters and setters
	Money GetSalary() const;
	Money GetTotalSalary() const;
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