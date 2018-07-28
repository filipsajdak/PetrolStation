#include "PetrolStation.h"
#include <algorithm>

PetrolStation::PetrolStation(std::string name, int ID) : ID(ID), name(name), currentOpenTillsCount(0)
{
	prices[FuelType::Diesel] = { Money{4}, Money{2} };
	prices[FuelType::TurboDiesel] = { Money{5}, Money{3} };
	prices[FuelType::EkoDiesel] = { Money{6}, Money{ 4 }};
	prices[FuelType::Pb95] = { Money{3}, Money{1} };
	prices[FuelType::Pb98] = { Money{4}, Money{1} };
	prices[FuelType::N02] = { Money{10}, Money{6} };
}

void PetrolStation::AddEmployee(const Employee & emp)
{
	employeevec.push_back(emp);
}


int PetrolStation::RemoveEmployee(int ID)
{
	auto&& it = std::find_if(begin(employeevec), end(employeevec), [&](auto&& e)
	{
		return e.GetID() == ID;
	});
	if (it == end(employeevec))
		throw EmployeeNotFound();
	employeevec.erase(it);
	return 0;
}

void PetrolStation::AddDepot(int ID, int maxAmount, FuelType fuelType)
{
	depotvec.emplace_back(ID, maxAmount, fuelType);
}

int PetrolStation::removeDepot(int ID)
{
	int i = GetDepotIndex(ID);
	if (i != -1)
	{
		depotvec.erase(depotvec.begin() + i);
		return 0;
	}
	return -1;
}

bool PetrolStation::isDepotWorking(int ID)
{
	int i = GetDepotIndex(ID);
	if (i != -1)
	{
		return depotvec[i].IsWorking();
	}
	return false;
}

std::string PetrolStation::GetDepotFuelType(int ID)
{
	int i = GetDepotIndex(ID);
	if (i != -1)
	{
		return depotvec[i].GetFuelTypeString();
	}
	return "NoDepot";
}

int PetrolStation::GetDepotMaxFuelAmount(int ID) 
{
	int i = GetDepotIndex(ID);
	if (i != -1)
	{
		return depotvec[i].GetMaxFuelAmount();
	}
	return -1;
}

int PetrolStation::GetDepotCurrentFuelAmount(int ID)
{
	int i = GetDepotIndex(ID);
	if (i != -1)
	{
		return depotvec[i].GetCurrentFuelAmount();
	}
	return -1;
}

std::string PetrolStation::GetName() const
{
	return name;
}

int PetrolStation::GetID() const
{
	return ID;
}

int PetrolStation::GetEmployeeCount() const
{
	return employeevec.size();
}

Money PetrolStation::GetEmployeeSalary(int ID)
{
	return GetEmployee(ID).GetSalary();
}

int PetrolStation::SetEmployeeSalary(int ID, Money amount)
{
	GetEmployee(ID).SetSalary(amount);
	return 0;
}

Money PetrolStation::GetEmployeeBonusSalary(int ID)
{
	return GetEmployee(ID).GetBonusSalary();
}

int PetrolStation::SetEmployeeBonusSalary(int ID, Money amount)
{
	GetEmployee(ID).SetBonusSalary(amount);
	return 0;
}

std::string PetrolStation::GetEmployeeName(int ID)
{
	return GetEmployee(ID).GetName();
}

int PetrolStation::ChangeEmployeeName(int ID, std::string name)
{
	GetEmployee(ID).ChangeName(name);
	return 0;;
}

int PetrolStation::GetEmployeeWorkingDaysCount(int ID)
{
	return GetEmployee(ID).GetWorkingDaysCount();
}

int PetrolStation::SetEmployeeWorkingDaysCount(int ID, int count)
{
	GetEmployee(ID).SetWorkingDaysCount(count);
	return 0;
}

int PetrolStation::PayAllEmployees()
{
	for (auto&& e: employeevec)
	{
		auto topay = e.GetTotalSalary();
		PayEmployee(topay, e);
	}
	return 0;
}

void PetrolStation::PayEmployee(const Money &topay, Employee & e)
{
	if (balance < topay)
	{
		throw NotEnoughMoney();
	}
	balance -= topay;
	e.AddBalance(topay);
}

Employee& PetrolStation::GetEmployee(int ID)
{
	auto&& it = std::find_if(begin(employeevec), end(employeevec),[&](auto&& e)
	{
		return e.GetID() == ID;
	});
	if (it == end(employeevec))
	{
		throw EmployeeNotFound();
	}
	return *it;
}

int PetrolStation::GetDepotIndex(int ID)
{
	for (size_t i = 0; i < depotvec.size(); i++)
	{
		if (depotvec[i].GetID() == ID)
		{
			return i;
		}
	}
	return -1;
}

inline auto PetrolStation::FindDepotWithEnoughFuel(int amount, FuelType type)
{
	return std::find_if(std::begin(depotvec), std::end(depotvec),
		[=](auto const& depot)
	{
		return depot.GetFuelType() == type && depot.GetCurrentFuelAmount() >= amount;
	});
}

int PetrolStation::GetCurrentOpenTillsCount() const
{
	return currentOpenTillsCount;
}

int PetrolStation::GetMaximumTills() const
{
	return tillList.GetTillCount();
}

void PetrolStation::AddTill(int ID, Money maxCash, Money currentCash)
{
	int i = tillList.AddTill(ID, maxCash, currentCash);
	balance -= currentCash;
	if (i == 0)
	{
		currentOpenTillsCount++;
	}
	
}

void PetrolStation::AddTill(const Till& till)
{
	tillList.AddTill(till);
}

int PetrolStation::RemoveTill(int ID)
{
	Till* till = tillList.FindTill(ID);
	if (!till)
	{
		return -1;
	}
	auto currmoney = till->GetCurrentCash();
	int i = tillList.RemoveTill(ID);
	if (i == 0)
	{
		balance += currmoney;
		currentOpenTillsCount--;
	}
	return i;
}

int PetrolStation::OpenTill(int ID)
{
	int i = tillList.OpenTill(ID);
	if (i == 0)
	{
		currentOpenTillsCount++;
	}
	return i;
}

int PetrolStation::CloseTill(int ID)
{
	CheckoutTill(ID);
	if (tillList.CloseTill(ID) != 0)
	{
		return -1;
	}
	else
	{
		currentOpenTillsCount--;
	}
	
	return 0;
}

int PetrolStation::CheckoutTill(int ID)
{
	Till* tillptr = tillList.FindTill(ID);
	if (!tillptr)
	{
		return -2;
	}
	auto toSubstract = tillptr->GetCurrentCash();
	if (tillptr->DrawCash(toSubstract) != 0)
	{
		return -1;
	}
	balance += toSubstract;
	return 0;
}

Money PetrolStation::GetMoneyInTill(int ID)
{
	Till* tillptr = tillList.FindTill(ID);
	if (!tillptr)
	{
		return Money(-2);
	}
	return tillptr->GetCurrentCash();
}

int PetrolStation::CheckoutAllTills()
{
	auto toadd = tillList.GetTotalMoneyInTills();
	balance += toadd;
	return tillList.CheckoutAllTills();
}

int PetrolStation::CloseAllTills()
{
	auto toadd = tillList.GetTotalMoneyInTills();
	balance += toadd;
	return tillList.CloseAllTills();
}

Money PetrolStation::GetBalance() const
{
	return balance;
}

int PetrolStation::SellFuel(int amount, FuelType type)
{
	auto result = FindDepotWithEnoughFuel(amount, type);
	if (result == std::end(depotvec))
	{
		return -1;
	}

	auto & depot = *result;
	depot.DeFuel(amount);

	//search for a free Till;
	auto openTill = tillList.FindFirstOpenTill();
	if (!openTill)
	{
		return -2;
	}
	//add cash to till
	if (openTill->DepositCash(amount * GetSellCost(type)) != 0)
	{
		return -4;
	}

	return 0;
}

int PetrolStation::AddFuel(FuelType fuelType, int amount)
{
	//check if we have enough money
	auto moneyToSubstract = GetBuyCost(fuelType) * amount;
	if (balance < moneyToSubstract)
	{
		return - 1;
	}
	for (auto& depot : depotvec)
	{
		//add fuel
		if (depot.GetFuelType() == fuelType && depot.ReFuel(amount) == 0)
		{
			balance -= moneyToSubstract;
			return 0;
		}
	}	
	return -1;
}

int PetrolStation::RefuellAll()
{
	for (auto& depot : depotvec)
	{
		int tofuel = depot.GetMaxFuelAmount() - depot.GetCurrentFuelAmount();
		auto moneyToSubstract = GetBuyCost(depot.GetFuelType()) * tofuel;
		if (depot.ReFuel(tofuel) != 0)
		{
			return -1;
		}
		balance -= moneyToSubstract;
	}
	return 0;
}

Money PetrolStation::GetSellCost(const FuelType type) const
{
	return prices.at(type).sellPrice;
}

Money PetrolStation::GetBuyCost(const FuelType type) const
{
	return prices.at(type).buyPrice;
}


