#include "PetrolStation.h"

PetrolStation::PetrolStation(std::string name, int ID) : ID(ID), name(name), currentOpenTillsCount(0)
{

	prices[FuelType::Diesel] = { 4, 2 };
	prices[FuelType::TurboDiesel] = { 5, 3 };
	prices[FuelType::EkoDiesel] = { 6, 4 };
	prices[FuelType::Pb95] = { 3, 1 };
	prices[FuelType::Pb98] = { 4, 1 };
	prices[FuelType::N02] = { 10, 6 };
}

void PetrolStation::AddEmployee(std::string name, int salary, int bonusSalary, int workingDaysCount, int ID)
{
	Employee emp = Employee(name, salary, bonusSalary, workingDaysCount, ID);
	employeevec.push_back(emp);
}

void PetrolStation::AddEmployee(const Employee & emp)
{
	employeevec.push_back(emp);
}


int PetrolStation::RemoveEmployee(int ID)
{
	int i = GetEmployeeIndex(ID);
	if (i == -1)
	{
		return -1;
	}
	employeevec.erase(employeevec.begin() + i);
	return 0;
}

void PetrolStation::AddDepot(const Depot& depot)
{
	depotvec.push_back(depot);
}

void PetrolStation::AddDepot(int ID, int maxAmount, FuelType fuelType)
{
	auto depotToAdd = Depot(ID, maxAmount, fuelType);
	depotvec.push_back( depotToAdd);
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
	std::string fuel;
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

int PetrolStation::GetEmployeeSalary(int ID)
{
	int i = GetEmployeeIndex(ID);
	if (i != -1)
	{
		return employeevec[i].GetSalary();
	}
	return -1;
}

int PetrolStation::SetEmployeeSalary(int ID, int amount)
{
	int i = GetEmployeeIndex(ID);
	if (i != -1)
	{
		employeevec[i].SetSalary(amount);
		return 0;
	}
	return -1;
}

int PetrolStation::GetEmployeeBonusSalary(int ID)
{
	int i = GetEmployeeIndex(ID);
	if (i != -1)
	{
		return employeevec[i].GetBonusSalary();
	}
	return -1;
}

int PetrolStation::SetEmployeeBonusSalary(int ID, int amount)
{
	int i = GetEmployeeIndex(ID);
	if (i != -1)
	{
		employeevec[i].SetBonusSalary(amount);
		return 0;
	}
	return -1;
}

std::string PetrolStation::GetEmployeeName(int ID)
{
	int i = GetEmployeeIndex(ID);
	std::string name = "invalidID";
	if (i != -1)
	{
		name = employeevec[i].GetName();
		return name;
	}
	return name;
}

int PetrolStation::ChangeEmployeeName(int ID, std::string name)
{
	int i = GetEmployeeIndex(ID);
	if (i != -1)
	{
		employeevec[i].ChangeName(name);
		return 0;
	}
	return -1;
}

int PetrolStation::GetEmployeeWorkingDaysCount(int ID)
{
	int i = GetEmployeeIndex(ID);
	if (i != -1)
	{
		return employeevec[i].GetWorkingDaysCount();
	}
	return -1;
}

int PetrolStation::SetEmployeeWorkingDaysCount(int ID, int count)
{
	int i = GetEmployeeIndex(ID);
	if (i != -1)
	{
		employeevec[i].SetWorkingDaysCount(count);
		return 0;
	}
	return -1;
}

int PetrolStation::PayEmployee(int ID)
{
	int i = GetEmployeeIndex(ID);
	if (i != -1)
	{
		int topay = employeevec[i].GetSalary() + employeevec[i].GetBonusSalary();
		if ((balance - topay) >= 0)
		{
			balance -= topay;
			employeevec[i].AddBalance(topay);
			return 0;
		}
		return -2;
	}
	return -1;
}

int PetrolStation::PayAllEmployees()
{
	for (size_t i = 0; i < employeevec.size(); i++)
	{
		int topay = employeevec[i].GetSalary() + employeevec[i].GetBonusSalary();
		if ((balance - topay) < 0)
		{
			return -1;
		}
		balance -= topay;
		employeevec[i].AddBalance(topay);
	}
	return 0;
}

int PetrolStation::GetEmployeeIndex(int ID)
{
	for(size_t i = 0; i < employeevec.size(); i++)
	{
		if (employeevec[i].GetID() == ID)
		{
			return i;
		}
	}
	return -1;
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

int PetrolStation::GetCurrentOpenTillsCount() const
{
	return currentOpenTillsCount;
}

int PetrolStation::GetMaximumTills() const
{
	return tillList.GetTillCount();
}

void PetrolStation::AddTill(int ID, int maxCash, int currentCash)
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
	int currmoney = till->GetCurrentCash();
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
	int toSubstract = tillptr->GetCurrentCash();
	if (tillptr->DrawCash(toSubstract) != 0)
	{
		return -1;
	}
	balance += toSubstract;
	return 0;
}

int PetrolStation::GetMoneyInTill(int ID)
{
	Till* tillptr = tillList.FindTill(ID);
	if (!tillptr)
	{
		return -2;
	}
	return tillptr->GetCurrentCash();
}

int PetrolStation::CheckoutAllTills()
{
	int toadd = tillList.GetTotalMoneyInTills();
	balance += toadd;
	return tillList.CheckoutAllTills();
}

int PetrolStation::CloseAllTills()
{
	int toadd = tillList.GetTotalMoneyInTills();
	balance += toadd;
	return tillList.CloseAllTills();
}

long unsigned int PetrolStation::GetBalance() const
{
	return balance;
}

int PetrolStation::SellFuel(int amount, FuelType type)
{
	int count = 0;
	for (auto &i : depotvec)
	{
		//remove fuel
		if (depotvec[count].GetFuelType() == type)
		{
			if (depotvec[count].DeFuel(amount) == 0)
			{
				//add client to the list by his ID
				//we store copies of clients only

				//search for a free Till;
				auto openTill = tillList.FindFirstOpenTill();
				if (!openTill)
				{
					return -2;
				}
				//add cash to till
				if (openTill->DepositCash(amount*GetSellCost(type)) != 0)
				{
					return -4;
				}

				totalFuel -= amount; 
				return 0;
			}
		}
		
		count++;
	}

	return-1;
}

int PetrolStation::AddFuel(FuelType fuelType, int amount)
{
	int count = 0;
	//check if we have enough money
	int moneyToSubstract = GetBuyCost(fuelType) * amount;
	if (balance - moneyToSubstract < 0)
	{
		return - 1;
	}
	for (auto &i : depotvec)
	{
		//add fuel
		if (depotvec[count].GetFuelType() == fuelType)
		{
			if (depotvec[count].ReFuel(amount) == 0)
			{
				totalFuel += amount; 
				balance -= moneyToSubstract;
				return 0;
			}
		}
		
		count++;
	}	
	return -1;
}

int PetrolStation::RefuellAll()
{
	int count = 0;
	for (auto &i : depotvec)
	{
		int tofuel = depotvec[count].GetMaxFuelAmount() - depotvec[count].GetCurrentFuelAmount();
		int moneyToSubstract = GetBuyCost(depotvec[count].GetFuelType()) * tofuel;
		if (depotvec[count].ReFuel(tofuel) != 0)
		{
			return -1;
		}
		balance -= moneyToSubstract;
		count++;
	}
	return 0;
}

int PetrolStation::GetSellCost(const FuelType type) const
{
	return prices.at(type).sellPrice;
}

int PetrolStation::GetBuyCost(const FuelType type) const
{
	return prices.at(type).buyPrice;
}


