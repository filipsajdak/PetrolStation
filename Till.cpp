#include "Till.h"

Till::Till(int ID, Money maxCash, Money currentCash)
	: ID(ID)
	, maxCash(maxCash)
	, currentCash(currentCash)
{

}

int Till::DepositCash(Money amount)
{
	if (currentCash + amount <= maxCash)
	{
		currentCash += amount;
		return 0;
	}
	else
	{
		return -1;
	}
}

void Till::Checkout()
{
	DrawCash(GetCurrentCash());
}

int Till::DrawCash(Money amount)
{
	if (currentCash - amount >= Money(0))
	{
		currentCash -= amount;
		return 0;
	}
	else
	{
		return -1;
	}
}

Money Till::GetCurrentCash() const
{
	return currentCash;
}

Money Till::GetMaxCash() const
{
	return maxCash;
}

int Till::GetID() const
{
	return ID;
}

bool Till::IsOpen() const
{
	return isOpen;
}

void Till::Open()
{
	isOpen = true;
}

void Till::Close()
{
	isOpen = false;
}
