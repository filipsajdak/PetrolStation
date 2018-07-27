#include "Employee.h"

Employee::Employee(std::string name, int salary, int bonusSalary, int workingDaysCount, int ID) 
	: ID(ID)
	, salary(salary)
	, bonusSalary(bonusSalary)
	, balance(0)
	, workingDaysCount(workingDaysCount)
	, name(name)
{
}

int Employee::GetSalary() const
{
	return salary;
}

void Employee::SetSalary(int amount)
{
	salary = amount;
}

int Employee::AddBalance(int amount)
{
	if (balance < 0) { return -1; }
	balance += amount;
	return 0;
}

int Employee::GetBonusSalary() const
{
	return bonusSalary;
}

void Employee::SetBonusSalary(int amount)
{
	bonusSalary = amount;
}

std::string Employee::GetName() const
{
	return name;
}

void Employee::ChangeName(std::string name)
{
	this->name = name;
}

int Employee::GetWorkingDaysCount() const
{
	return workingDaysCount;
}

void Employee::SetWorkingDaysCount(int count)
{
	workingDaysCount = count;
}

int Employee::GetID() const
{
	return ID;
}
