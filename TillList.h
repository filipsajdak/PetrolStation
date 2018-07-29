#pragma once
#include "Till.h"
#include <map>

struct TillNotFound {};

class TillList
{
public:
	TillList() = default;
	TillList(const TillList&) = delete;
	TillList& operator=(const TillList&) = delete;
	TillList(TillList&&) = default;
	TillList& operator=(TillList&&) = default;

	Till& GetFirstOpenTill();

	bool CheckTillIsOpen(int ID);

	//These functions are called by the owning PetrolStation instance to operate on particular Till, i.e. close it/ open
	int OpenTill(int ID);
	int CloseTill(int ID);
	int CheckoutAllTills();
	int CloseAllTills();

	Money GetTotalMoneyInTills();
	//These functions are responsible for managing the tills in the List
	//They keep the list sorted by ID for convenience
	//If we add Till by the same ID they return int value -1
	int AddTill(Till till);

	//Removes a Till of particular ID from the list, returns an integer value which tells us whether we successfully removed the till or not (1 for an error, 0 for a success)
	int RemoveTill(int ID);

	//Returns the total amount of Tills associated with this list
	int GetTillCount()const;

	Till& GetTill(int ID);
	int GetCurrentOpenTillsCount() const;
private:
	std::map<int, Till> tills;

};