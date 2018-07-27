#include "Employee.h"

Employee::Employee(std::string name, Money salary, Money bonusSalary, int workingDaysCount, int ID)
	: ID(ID)
	, salary(salary)
	, bonusSalary(bonusSalary)
	, balance(0)
	, workingDaysCount(workingDaysCount)
	, name(name)
{
}

Money Employee::GetSalary() const
{
	return salary;
}

void Employee::SetSalary(Money amount)
{
	salary = amount;
}

int Employee::AddBalance(Money amount)
{
	if (balance < Money{ 0 }) { return -1; }
	balance += amount;
	return 0;
}

Money Employee::GetBonusSalary() const
{
	return bonusSalary;
}

void Employee::SetBonusSalary(Money amount)
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
