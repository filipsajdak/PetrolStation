#include "PetrolStation.h"
#include <algorithm>
#include "FindIf.h"

namespace {

	const std::map<FuelType, PetrolStation::FuelPrices>::value_type fuel_prices[] = {
		{ FuelType::Diesel		, { Money{  4 }, Money{ 2 } }},
		{ FuelType::TurboDiesel	, { Money{  5 }, Money{ 3 } }},
		{ FuelType::EkoDiesel	, { Money{  6 }, Money{ 4 } }},
		{ FuelType::Pb95		, { Money{  3 }, Money{ 1 } }},
		{ FuelType::Pb98		, { Money{  4 }, Money{ 1 } }},
		{ FuelType::N02			, { Money{ 10 }, Money{ 6 } }},
	};
}


PetrolStation::PetrolStation(std::string name, int ID) 
	: ID(ID)
	, name(name)
	, prices(std::begin(fuel_prices), std::end(fuel_prices))
{
}

void PetrolStation::AddEmployee(Employee emp)
{
	employeevec.emplace_back(std::move(emp));
}

auto PetrolStation::FindEmployee(int ID) {
	auto&& it = find_if(employeevec, WithID(ID));

	if (it == end(employeevec))
		throw EmployeeNotFound();
	
	return it;
}

int PetrolStation::RemoveEmployee(int ID)
{
	employeevec.erase(FindEmployee(ID));
	return 0;
}

void PetrolStation::AddDepot(Depot depot)
{
	depotvec.emplace_back(std::move(depot));
}

int PetrolStation::removeDepot(int ID)
{
	auto it = find_if(depotvec, WithID(ID));
	if (it == depotvec.end()) return -1;
	depotvec.erase(it);
	return 0;
}

bool PetrolStation::isDepotWorking(int ID)
{
	return GetDepot(ID).IsWorking();
}

std::string PetrolStation::GetDepotFuelType(int ID)
{
	return GetDepot(ID).GetFuelTypeString();
}

int PetrolStation::GetDepotMaxFuelAmount(int ID) 
{
	return GetDepot(ID).GetMaxFuelAmount();
}

int PetrolStation::GetDepotCurrentFuelAmount(int ID)
{
	return GetDepot(ID).GetCurrentFuelAmount();
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
	return *FindEmployee(ID);
}

Depot& PetrolStation::GetDepot(int ID)
{
	auto it = find_if(depotvec, WithID(ID));
	if (it == depotvec.end()) throw DepotNotFound();
	return *it;
}

inline auto PetrolStation::FindDepotWithEnoughFuel(int amount, FuelType type)
{
	return find_if(depotvec,
		[=](auto const& depot)
	{
		return depot.GetFuelType() == type && depot.GetCurrentFuelAmount() >= amount;
	});
}

int PetrolStation::GetCurrentOpenTillsCount() const
{
	return tillList.GetCurrentOpenTillsCount();
}

int PetrolStation::GetMaximumTills() const
{
	return tillList.GetTillCount();
}

void PetrolStation::AddTill(Till till)
{
	auto i = tillList.AddTill(std::move(till));
	if (i == 0)
	{
		balance -= till.GetCurrentCash();
	}

}

int PetrolStation::RemoveTill(int ID)
{
	auto& till = tillList.GetTill(ID);

	auto currmoney = till.GetCurrentCash();
	tillList.RemoveTill(ID);
	balance += currmoney;
	return 0;
}

int PetrolStation::OpenTill(int ID)
{
	tillList.OpenTill(ID);
	return 0;
}

int PetrolStation::CloseTill(int ID)
{
	CheckoutTill(ID);
	tillList.CloseTill(ID);
	return 0;
}

int PetrolStation::CheckoutTill(int ID)
{
	auto& tillptr = tillList.GetTill(ID);
	auto toSubstract = tillptr.GetCurrentCash();
	if (tillptr.DrawCash(toSubstract) != 0)
	{
		return -1;
	}
	balance += toSubstract;
	return 0;
}

Money PetrolStation::GetMoneyInTill(int ID)
{
	return tillList.GetTill(ID).GetCurrentCash();
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
	auto& openTill = tillList.GetFirstOpenTill();
	//add cash to till
	if (openTill.DepositCash(amount * GetSellCost(type)) != 0)
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
		if (depot.GetFuelType() == fuelType && amount <= depot.GetAvailableVolume())
		{
			depot.ReFuel(amount);
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
		int tofuel = depot.GetAvailableVolume();
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


