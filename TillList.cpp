#include "TillList.h"
#include <algorithm>
#include <numeric>
#include "FindIf.h"

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
		till.second.Checkout();
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
	return std::accumulate(tills.begin(), tills.end(), Money(0), [](auto&& m, auto&& t) {
		return m + t.second.GetCurrentCash();
	});
}

int TillList::AddTill(Till till)
{
	auto it = tills.emplace(std::make_pair(till.GetID(), std::move(till)));
	return it.second ? 0 : -1;
}

int TillList::RemoveTill(int ID)
{
	if (tills.erase(ID) == 0)
		throw TillNotFound();
	return 0;
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

int TillList::GetCurrentOpenTillsCount() const
{
	return std::count_if(tills.begin(), tills.end(), [](auto&& t) {
		return t.second.IsOpen();
	});
}
