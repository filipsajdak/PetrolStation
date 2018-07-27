#pragma once
class Money
{
public:
	constexpr explicit Money(int value = 0) : value(value)
	{}

	friend constexpr Money operator*(int amount, Money cost) noexcept
	{
		return  Money(amount * cost.value);
	}
	constexpr Money operator*(int amount) const noexcept
	{
		return Money(amount * value);
	}
	constexpr Money operator+(Money m) const noexcept
	{
		return Money(m.value + value);
	}
	constexpr Money operator-(Money m) const noexcept
	{
		return Money(value - m.value);
	}
	constexpr Money& operator-=(Money m) noexcept
	{
		value -= m.value;
		return *this;
	}
	constexpr Money& operator+=(Money m) noexcept
	{
		value += m.value;
		return *this;
	}
	constexpr bool operator<(Money m)  const noexcept { return value < m.value; }
	constexpr bool operator==(Money m) const noexcept { return value == m.value; }
	constexpr bool operator<=(Money m) const noexcept { return value <= m.value; }
	constexpr bool operator>=(Money m) const noexcept { return value >= m.value; }
	constexpr bool operator>(Money m)  const noexcept { return value > m.value; }

private:
	int value;
};