#include "TillList.h"
#include <algorithm>
#include "FindIf.h"

Till * TillList::FindTill(int ID)
{
	auto it = tills.find(ID);
	return it != tills.end() ? &it->second : nullptr;
}

Till& TillList::GetFirstOpenTill()
{
	auto it = find_if(tills, [](const auto& till) {
		return till.second.IsOpen();
	});

	if (it == tills.end()) throw TillNotFound();

	return it->second;
}

bool TillList::CheckTillIsOpen(int ID)
{
	return GetTill(ID).IsOpen();
}

int TillList::OpenTill(int ID)
{
	GetTill(ID).Open();
	return 0;
}

int TillList::CloseTill(int ID)
{
	GetTill(ID).Close();
	return 0;
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

int TillList::AddTill(Till till)
{
	auto it = tills.emplace(std::make_pair(till.GetID(), std::move(till)));
	return it.second ? 0 : -1;
}

int TillList::AddTill(int ID, Money maxCash, Money currentCash)
{
	return AddTill({ID, maxCash, currentCash});
}

int TillList::RemoveTill(Till * till)
{
	int statusCode = RemoveTill(till->GetID());
	return statusCode;
}

int TillList::RemoveTill(int ID)
{
	if (tills.erase(ID) == 0)
		throw TillNotFound();
	return 0;
}

void TillList::RemoveAllElements() 
{
	tills.clear();
}

int TillList::GetTillCount() const
{
	return tills.size();
}

Till & TillList::GetTill(int ID)
{
	auto it = tills.find(ID);
	if (it == tills.end()) throw TillNotFound();
	return it->second;
}
