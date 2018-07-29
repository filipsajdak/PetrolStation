#pragma once
#include "Depot.h"
#include "TillList.h"
#include "Employee.h"
#include <vector>
#include <map>
#include "Money.h"

struct EmployeeNotFound {};
struct DepotNotFound {};
struct NotEnoughMoney {};
class PetrolStation
{
public:
	PetrolStation(std::string name, int ID);
	PetrolStation(const PetrolStation&) = delete;
	PetrolStation& operator=(const PetrolStation&) = delete;
	PetrolStation(PetrolStation&&) = default;
	PetrolStation& operator=(PetrolStation&&) = default;

	void AddEmployee(Employee emp);
	//Removing is performed by ID only, the corresponding employee is looked up in the employeevec and then removed
	int RemoveEmployee(int ID);
	//Returns the current amount of employees assigned to this particular station
	int GetEmployeeCount() const;
	//Functions that make possible to perform operations on employee
	//int value of -1 means there is no such employee, 0 means success
	Money GetEmployeeSalary(int ID);
	int SetEmployeeSalary(int ID, Money amount);
	Money GetEmployeeBonusSalary(int ID);
	int SetEmployeeBonusSalary(int ID, Money amount);
	std::string GetEmployeeName(int ID);
	int ChangeEmployeeName(int ID, std::string name);
	int GetEmployeeWorkingDaysCount(int ID);
	int SetEmployeeWorkingDaysCount(int ID, int count);
	//Pays employee his monthly salary + bonussalary
	int PayAllEmployees();

	void PayEmployee(const Money & topay, Employee & e);

	//These functions are responsible for adding and removing Depots from the depotMap, similarly as with employees they can be constructed in two distinct ways
	void AddDepot(Depot depot);
	//Removes a depot from depotMap by its ID
	int removeDepot(int ID);
	bool isDepotWorking(int ID);
	std::string GetDepotFuelType(int ID);
	//Returns the capacitance of this particular fuel depot
	int GetDepotMaxFuelAmount(int ID);
	//Returns the current fuel amount in depot
	int GetDepotCurrentFuelAmount(int ID);


	//Returns the station's name
	std::string GetName() const;
	//Returns the station's ID
	int GetID()const;
	//Returns total balance of this instance of PetrolStation
	Money GetBalance() const;
	//Returns current amount of open tills in tillList
	int GetCurrentOpenTillsCount() const;
	//Returns total amount of tills assigned to this station (both open and closed)
	int GetMaximumTills() const;

	void AddTill(const Till& till);
	int RemoveTill(int ID);

	//These functions are called to open/close or checkout a till of particular ID
	int OpenTill(int ID);
	int CloseTill(int ID);
	int CheckoutTill(int ID);
	Money GetMoneyInTill(int ID);
	int CheckoutAllTills();
	int CloseAllTills();

	//Most prominent function - it performs purchasing of fuel by a Client and adequately calls all other functions responsible for fuel/money management
	//It searches for the first open till and performs cash operations on it, it also searches for first open depot of the required FuelType
	//It returns integer value because we may be unable to perform required fuel withdrawal operation due to lack of fuel (1 for failure and 0 for success)
	int SellFuel(int amount, FuelType type);

	//This function is the counterpart of SellFuel function, it is responsible for refuelling empty depots, it's integer return value (1 for failure and 0 for success), because
	//we may be unable to perform that operation, due to lack of particular fuel type depots or volume in our depots
	//this function substracts the special amount of money required to buy fuel from our total balance (we assume that prices are constant and perform a switch statement on fuelType)
	int AddFuel(FuelType fuelType, int amount);
	//Refuels all depots
	int RefuellAll();

	//These functions return the cost of deemed type of fuel dependent on current course of petrol type
	Money GetSellCost(const FuelType type)const;
	Money GetBuyCost(const FuelType type)const;



	struct FuelPrices
	{
		Money sellPrice;
		Money buyPrice;
	};

private:
	int ID;
	std::string name;
	std::vector<Employee> employeevec;
	std::vector<Depot> depotvec;
	TillList tillList;
	int currentOpenTillsCount;
	Money balance{10000}; //they start with some balance
	std::map<FuelType, FuelPrices> prices;
	//Returns index of given employee in the vector or returns -1 to indicate there is no such employee
	Employee& GetEmployee(int ID);
	Depot& GetDepot(int ID);

	auto FindDepotWithEnoughFuel(int amount, FuelType type);
	auto FindEmployee(int ID);

	

	//Returns employee under given index, or if there is none we change data of the arbitrary 0th employee
	//Employee& GetEmployeeUnderIndex(int index);
};