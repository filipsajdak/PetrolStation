#include <gmock/gmock.h>
#include <string>
#include <sstream>
#include "PetrolStation.h"
#include "Money.h"
#include "PetrolStationBuilder.h"

inline void PrintTo(const Money& m, ::std::ostream *os)
{
	*os << m.GetValue();
}

using namespace std;

TEST(PetrolStationTests, empty_case) {
	PetrolStation p("Octan2", 2);

	EXPECT_THAT(p.GetBalance(), Money(10000));
	EXPECT_THROW(p.CloseTill(2), TillNotFound);
	EXPECT_THROW(p.CheckoutTill(23), TillNotFound);
	EXPECT_THAT(p.GetCurrentOpenTillsCount(), 0);
	EXPECT_THAT(p.GetMaximumTills(), 0);
	EXPECT_THROW(p.GetMoneyInTill(234), TillNotFound);
	EXPECT_THROW(p.RemoveTill(13), TillNotFound);
	EXPECT_THAT(p.GetEmployeeCount(), 0);
	EXPECT_THROW(p.GetEmployeeName(1), EmployeeNotFound);
	EXPECT_THROW(p.GetEmployeeBonusSalary(2), EmployeeNotFound);
	EXPECT_THROW(p.GetEmployeeSalary(100), EmployeeNotFound);
	EXPECT_THROW(p.GetDepotFuelType(2), DepotNotFound);
	EXPECT_THROW(p.GetEmployeeWorkingDaysCount(234), EmployeeNotFound);
	EXPECT_THROW(p.ChangeEmployeeName(2, "Bob"), EmployeeNotFound);
}

struct PetrolStationFixtureTests : ::testing::Test {

	PetrolStationBuilder builder;

	PetrolStationFixtureTests() 
		: builder{ "Benzin1", 1 }
	{
	}

	void SetUp() override {
		builder.add(Employee{ "John", Money(100), Money(200), 3, 1 },
			Employee{ "Barbara", Money(200), Money(300), 4, 2 },
			Employee{ "Tadeus", Money(130), Money(560), 4, 3 });
	}

};

TEST_F(PetrolStationFixtureTests, adding_and_removing_employees) {
	auto p = builder.build();

	EXPECT_THAT(p.GetEmployeeCount(), 3);
	EXPECT_THAT(p.RemoveEmployee(1), 0);
	EXPECT_THAT(p.GetEmployeeCount(), 2);
}

TEST_F(PetrolStationFixtureTests, removing_non_existing_employee) {
	auto p = builder.build();

	EXPECT_THROW(p.RemoveEmployee(4), EmployeeNotFound);
}

TEST_F(PetrolStationFixtureTests, change_employee_parameters) {
	auto p = builder.build();

	EXPECT_THAT(p.GetEmployeeName(2), "Barbara");
	EXPECT_THAT(p.ChangeEmployeeName(2, "Stepan"), 0);
	EXPECT_THAT(p.GetEmployeeName(2), "Stepan");
	EXPECT_THAT(p.SetEmployeeBonusSalary(2, Money{ 200 }), 0);
	EXPECT_THAT(p.SetEmployeeWorkingDaysCount(2, 4), 0);
	EXPECT_THAT(p.SetEmployeeSalary(2, Money{ 100 }), 0);

	EXPECT_THAT(p.GetEmployeeBonusSalary(2), Money(200));
	EXPECT_THAT(p.GetEmployeeWorkingDaysCount(2),   4);
	EXPECT_THAT(p.GetEmployeeSalary(2), Money(100));
}

struct PetrolStationWithDepotsFixtureTests : PetrolStationFixtureTests {
	void SetUp() override {
		PetrolStationFixtureTests::SetUp();

		builder.add(Depot(1, 300, FuelType::Diesel),
					Depot(2, 400, FuelType::EkoDiesel),
					Depot(4, 300, FuelType::Pb98),
					Depot(5, 500, FuelType::TurboDiesel),
					Depot(6, 100, FuelType::N02));
	}
};


TEST_F(PetrolStationWithDepotsFixtureTests, adding_and_removing_depots) {
	auto p = builder.add(Depot(3, 400, FuelType::Pb95)).build();

	EXPECT_THAT(p.removeDepot(3), 0);

	EXPECT_THROW(p.isDepotWorking(3), DepotNotFound);
}

TEST_F(PetrolStationWithDepotsFixtureTests, balance_after_adding_fuel) {
	auto p = builder.build();

	EXPECT_THAT(p.AddFuel(FuelType::Diesel, 300), 0); //DIESEL = 300
	EXPECT_THAT(p.AddFuel(FuelType::EkoDiesel, 400), 0); //EKODIESEL = 400
	
	EXPECT_THAT(p.GetBalance(), Money(7800));

	EXPECT_THAT(p.AddFuel(FuelType::Pb95, 100), -1);

	EXPECT_THAT(p.GetBalance(), Money(7800));
}

struct PetrolStationWithDepotsAndTillsFixtureTests : PetrolStationWithDepotsFixtureTests {
	void SetUp() override {
		PetrolStationWithDepotsFixtureTests::SetUp();

		builder.add(
			Till(1, Money{ 10000 }, Money{ 500 }),
			Till(2, Money{ 3000 }, Money{ 500 }),
			Till(4, Money{ 2000 }, Money{ 0 }),
			Till(3, Money{ 10000 }, Money{ 2000 })
		);
	}
};

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, adding_tills_removing_tills) {
	auto p = builder.build();

	EXPECT_THAT(p.RemoveTill(2), 0);
	EXPECT_THROW(p.RemoveTill(0), TillNotFound);
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, getting_data_from_petrolstation) {
	auto p = builder.build();

	EXPECT_THAT(p.GetBalance(), Money{ 7000 });
	EXPECT_THAT(p.GetBuyCost(FuelType::EkoDiesel), Money{ 4 });
	EXPECT_THAT(p.GetCurrentOpenTillsCount(), 4);
	EXPECT_THAT(p.GetEmployeeCount(), 3);
	EXPECT_THAT(p.GetID(), 1);
	EXPECT_THAT(p.GetMaximumTills(), 4);
	EXPECT_THAT(p.GetSellCost(FuelType::N02), Money{ 10 });
	EXPECT_THAT(p.GetName(), "Benzin1");
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, getting_data_about_depots_without_cash_operations) {
	auto p = builder.build();

	EXPECT_THAT(p.GetDepotCurrentFuelAmount(1), 0);
	EXPECT_THAT(p.GetDepotMaxFuelAmount(1), 300);
	EXPECT_THAT(p.isDepotWorking(1), true);
	EXPECT_THAT(p.GetDepotFuelType(1), "Diesel");

}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, emptying_empty_tills) {
	auto p = builder.build();

	EXPECT_THROW(p.CheckoutTill(0), TillNotFound);
	EXPECT_THROW(p.CheckoutTill(100), TillNotFound);
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, unsuccessful_cash_operations) {
	auto p = builder.build();

	PetrolStation p2("Octan2", 2);

	const Money initial_balance{ 7000 };
	const Money initial_money_in_till{ 500 };
	const int FAILED = -1;

	EXPECT_THAT(p.SellFuel(400, FuelType::EkoDiesel), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);

	//Try to buy from an empty fuel depot
	EXPECT_THAT(p.SellFuel(100, FuelType::EkoDiesel), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);
	EXPECT_THAT(p.SellFuel(200, FuelType::Diesel), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);
	EXPECT_THAT(p2.SellFuel(400, FuelType::Pb95), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);

	//Try to sell fuel station does not currently have
	EXPECT_THAT(p.SellFuel(200, FuelType::N02), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);
	
	//Try to buy fuel amout above capacitance of a fuel depot
	EXPECT_THAT(p2.AddFuel(FuelType::N02, 1000), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);

	//Checking out till 1
	EXPECT_THAT(p.CheckoutTill(1), 0);
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, refuelling_and_selling) {
	auto p = builder.build();

	EXPECT_THAT(p.AddFuel(FuelType::Diesel, 200), 0);
	EXPECT_THAT(p.SellFuel(200, FuelType::Diesel), 0);
	EXPECT_THAT(p.GetBalance(), Money{ 6600 });
	EXPECT_THAT(p.GetMoneyInTill(1), Money{ 1300 });
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, refuelling_checkout_and_closing_tills_and_salaries) {
	auto p = builder.build();

	//refuel all depots
	EXPECT_THAT(p.RefuellAll(), 0);
	EXPECT_THAT(p.GetBalance(), Money{ 2400 });
	//checkout all tills
	EXPECT_THAT(p.CheckoutAllTills(), 0);
	EXPECT_THAT(p.GetBalance(), Money{ 5400 });

	//closing all tills
	EXPECT_THAT(p.CloseAllTills(), 0);
	EXPECT_THAT(p.GetBalance(), Money{ 5400 });
	//pay employees their salary
	EXPECT_THAT(p.PayAllEmployees(), 0);
	EXPECT_THAT(p.GetBalance(), Money{ 3910 });

}
