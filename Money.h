#pragma once
class Money
{
public:
	Money(int value = 0) : value(value)
	{}

	friend Money operator*(int amount, Money cost)
	{
		return amount * cost.value;
	}
	Money operator*(int amount)
	{
		return amount * value;
	}
	Money operator+(Money m)
	{
		return m.value + value;
	}
	Money operator-(Money m)
	{
		return value - m.value;
	}
	Money& operator-=(Money m)
	{
		value -= m.value;
		return *this;
	}
	Money& operator+=(Money m)
	{
		value += m.value;
		return *this;
	}
	bool operator<(Money m) const { return value < m.value; }
	bool operator==(Money m) const { return value == m.value; }
	bool operator<=(Money m) const { return value <= m.value; }
	bool operator>=(Money m) const { return value >= m.value; }
	bool operator>(Money m) const { return value > m.value; }


private:
	int value;
};