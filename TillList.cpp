#include "TillList.h"
#include <algorithm>

Till * TillList::FindTill(int ID)
{
	auto it = tills.find(ID);
	return it != tills.end() ? &it->second : nullptr;
}

Till * TillList::FindFirstOpenTill()
{
	auto it = std::find_if(std::begin(tills),
		std::end(tills),
		[](const auto& till) { return till.second.IsOpen(); });
	
	return it != tills.end() ? &it->second : nullptr;
}

bool TillList::CheckTillIsOpen(int ID)
{
	Till* tillptr = FindTill(ID);
	return tillptr ? tillptr->IsOpen() : false;
}

int TillList::OpenTill(int ID)
{
	auto it = tills.find(ID);
	if (it != tills.end())
	{
		it->second.Open();
		return 0;
	}
	return -1;
}

int TillList::CloseTill(int ID)
{
	auto it = tills.find(ID);
	if (it != tills.end())
	{
		it->second.Close();
		return 0;
	}
	return -1;
}

int TillList::CheckoutAllTills()
{
	for (auto& till : tills)
	{
		till.second.DrawCash(till.second.GetCurrentCash());
	}
	return 0;
}

int TillList::CloseAllTills()
{
	for (auto& till : tills)
	{
		till.second.Close();
	}
	return 0;
}

Money TillList::GetTotalMoneyInTills()
{
	Money money(0);
	for (auto& till : tills)
	{
		money += till.second.GetCurrentCash();
	}
	return money;
}

int TillList::AddTill(const Till & till)
{
	return AddTill(till.GetID(), till.GetMaxCash(), till.GetCurrentCash());
}

int TillList::AddTill(int ID, Money maxCash, Money currentCash)
{
	auto it = tills.emplace(std::make_pair(ID, Till(ID, maxCash, currentCash)));
	return it.second ? 0 : -1;
}

int TillList::RemoveTill(Till * till)
{
	int statusCode = RemoveTill(till->GetID());
	return statusCode;
}

int TillList::RemoveTill(int ID)
{
	return tills.erase(ID) == 0 ? -1 : 0;
}

void TillList::RemoveAllElements() 
{
	tills.clear();
}

int TillList::GetTillCount() const
{
	return tills.size();
}
