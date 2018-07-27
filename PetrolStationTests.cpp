#include <gmock/gmock.h>
#include <string>
#include <sstream>
#include "PetrolStation.h"

using namespace std;

int run()
{
	//TESTING

	//Create a couple of stations - they should
	PetrolStation* petrol1 = new PetrolStation("Benzin1", 1);
	PetrolStation* petrol2 = new PetrolStation("Octan2", 2);

	//Testing empty cases
	cout << "Empty cases" << endl;
	cout << petrol2->GetBalance() << endl;
	cout <<petrol2->CloseTill(2) << endl;
	cout <<petrol2->CheckoutTill(23) << endl;
	cout <<petrol2->GetCurrentOpenTillsCount() << endl;
	cout <<petrol2->GetMaximumTills() << endl;
	cout <<petrol2->GetMoneyInTill(234) << endl;
	cout <<petrol2->RemoveTill(13) << endl;
	cout << petrol2->GetEmployeeCount() << endl;
	cout << petrol2->GetEmployeeName(1) << endl;
	cout << petrol2->GetEmployeeBonusSalary(2) << endl;
	cout << petrol2->GetEmployeeSalary(100) << endl;
	cout << petrol2->GetDepotFuelType(2) << endl;
	cout << petrol2->GetEmployeeWorkingDaysCount(234) << endl;
	cout << petrol2->ChangeEmployeeName(2, "Bob") << endl;



	//PETROL1 BLOCK
	//Adding Employees
	cout << endl << endl << endl << "Adding Employees" << endl;
	petrol1->AddEmployee("John", 100, 200, 3, 1);
	petrol1->AddEmployee("Barbara", 200, 300, 4, 2); //test selling buying logic!~!!!!!!!!!!!!!! add cout everywhere and make it coherent plox jacob ju ken du it
	petrol1->AddEmployee("Tadeus", 130, 560, 4, 3);
	cout << petrol1->RemoveEmployee(1) << endl;
	cout << "Removing nonexistent Employee: " << petrol1->RemoveEmployee(4) << endl;
	//Removing nonexistent Employee
	//Change Employee's parameters
	cout << "Change name from " << petrol1->GetEmployeeName(2) << " to: ";
	petrol1->ChangeEmployeeName(2, "Stepan");
	cout << petrol1->GetEmployeeName(2) << endl;
	petrol1->SetEmployeeBonusSalary(2, 200);
	petrol1->SetEmployeeWorkingDaysCount(2, 4);
	petrol1->SetEmployeeSalary(2, 100);

	//Get the data
	cout << endl << "Get all the data for employee ID: 2" << endl;
	cout << "Name: " << petrol1->GetEmployeeName(2) << endl;
	cout << "Salary: "<<petrol1->GetEmployeeSalary(2) << endl;
	cout << "BonusSalary: "<<petrol1->GetEmployeeBonusSalary(2) << endl;
	cout << "Working Days count: " << petrol1->GetEmployeeWorkingDaysCount(2) << endl;

	cout << endl<<endl<<"Adding and removing depots " << endl;
	//Adding different depots to the station
	petrol1->AddDepot(1, 300, FuelType::Diesel);
	petrol1->AddDepot(2, 400, FuelType::EkoDiesel);
	petrol1->AddDepot(3, 400, FuelType::Pb95);
	petrol1->AddDepot(4, 300, FuelType::Pb98);
	petrol1->AddDepot(5, 500, FuelType::TurboDiesel);
	petrol1->AddDepot(6, 100, FuelType::N02);
	//Removing one depot to make some restrictions
	cout << "Removing existing depot: "<<petrol1->removeDepot(3) << endl;
	cout << "Checking if nonexistent depot is open: " << petrol1->isDepotWorking(3) << endl; // -------------------------------------------
	cout << "Balance after Adding fuel: " << endl;
	petrol1->AddFuel(FuelType::Diesel, 300); //DIESEL = 300
	petrol1->AddFuel(FuelType::EkoDiesel, 400); //EKODIESEL = 400
	cout << petrol1->GetBalance() << endl;
	//Adding nonexistent fuel type
	cout << "Balance after Adding nonexistent fuel type: " << endl;
	petrol1->AddFuel(FuelType::Pb95, 100);
	cout << petrol1->GetBalance() << endl;  // -------------------------------------------------------------
	
	cout << endl << endl << "Adding tills" << endl;
	petrol1->AddTill(1, 10000, 500);
	petrol1->AddTill(2, 3000, 300); 
	petrol1->AddTill(4, 2000, 0);
	petrol1->AddTill(3, 10000, 2000);

	cout << "Removing an existing till: " << petrol1->RemoveTill(2) << endl;
	//removing nonexistent
	cout << "Removing nonexistent till: " << petrol1->RemoveTill(0) << endl;

	petrol1->AddTill(2, 3000, 500);



	//Get all the data
	cout << endl << endl << "Getting data from petrolstation 1: " << endl;
	cout << "Balance: "<<petrol1->GetBalance() << endl;
	cout << "EkoDiesel buy cost: " << petrol1->GetBuyCost(FuelType::EkoDiesel) << endl;
	cout <<"Current open tills count: " << petrol1->GetCurrentOpenTillsCount() << endl;
	cout << "Employee count: " <<petrol1->GetEmployeeCount() << endl;
	cout << "Station's ID: " <<petrol1->GetID() << endl;
	cout << "Maximum tills count :" <<petrol1->GetMaximumTills() << endl;
	cout << "NO2 sell cost: " <<petrol1->GetSellCost(FuelType::N02) << endl;
	cout << "Name :" << petrol1->GetName() << endl; // --------------------------------------------

	//Creating Clients
	cout << endl<<endl<< "Creating and testing clients data: " << endl;
	Client* client1 = new Client(1, 0);
	Client* client2 = new Client(2, 0);
	Client* client3 = new Client(*client2);
	cout << "Client1 ID: " << client1->GetID() << endl;
	cout << "Client2 totalClientcount: " << client2->GetTotalCount() << endl;
	cout << "Client3 fueledamount: " << client3->GetFueledAmount() << endl; // ------------------------------

	//Getting data about Depots
	cout << endl << endl << "Getting data about Depots" << endl;
	cout << "Current fuel amount Depot1 : " << petrol1->GetDepotCurrentFuelAmount(1) << endl;
	cout << "Max fuel amount Depot1 : " << petrol1->GetDepotMaxFuelAmount(1) << endl;
	cout << "Is it working Depot1 : " << petrol1->isDepotWorking(1) << endl;
	cout << "FuelType Depot1 : " << petrol1->GetDepotFuelType(1) << endl; // ---------------------------

	//Emptying empty tills
	cout << endl<<endl<<"Emptying empty Tills" << endl;
	cout << petrol1->CheckoutTill(0) << endl; 
	cout << petrol1->CheckoutTill(100) << endl;

	//Performing cash operations
	cout << endl << endl << "Performing cash operations" << endl;
	cout << "Selling fuel to client1: " << petrol1->SellFuel(*client1, 400, FuelType::EkoDiesel) << endl;
	cout << "Balance after operation: " << petrol1->GetBalance() << endl;
	cout << "Cash in till after operation :" << petrol1->GetMoneyInTill(1) << endl;
	//Try to buy from an empty fuel depot
	cout << "Trying to sell fuel from empty depot to client1: " << petrol1->SellFuel(*client1, 100, FuelType::EkoDiesel) << endl;
	cout << "Balance after operation: " << petrol1->GetBalance() << endl;
	cout << "Cash in till after operation :" << petrol1->GetMoneyInTill(1) << endl;
	cout << "Trying to sell Diesel to client3: " << petrol1->SellFuel(*client3, 200, FuelType::Diesel)<< endl;
	cout << "Balance after operation: " << petrol1->GetBalance() << endl;
	cout << "Cash in till after operation :" << petrol1->GetMoneyInTill(1) << endl;
	cout << "Trying to sell fuel from empty depot to client1: " << petrol2->SellFuel(*client1, 400, FuelType::Pb95) << endl;
	cout << "Balance after operation: " << petrol1->GetBalance() << endl;
	cout << "Cash in till after operation :" << petrol1->GetMoneyInTill(1) << endl;
	//Try to sell fuel station does not currently have
	cout << "Try to sell fuel station does not currently have: " << petrol1->SellFuel(*client2, 200, FuelType::N02) << endl;
	cout << "Balance after operation: " << petrol1->GetBalance() << endl;
	cout << "Cash in till after operation :" << petrol1->GetMoneyInTill(1) << endl;	
	//Try to buy fuel amout above capacitance of a fuel depot
	cout << "Try to buy fuel amout above capacitance of a fuel depot: " << petrol2->AddFuel(FuelType::N02, 1000) << endl;
	cout << "Balance after operation: " << petrol1->GetBalance() << endl;
	cout << "Cash in till after operation :" << petrol1->GetMoneyInTill(1) << endl;

	cout << endl << "Checking out till 1" << endl;
	cout << petrol1->CheckoutTill(1) << endl << endl; // -------------------------

	cout << "Refuelling Diesel depot " << endl;
	cout << petrol1->AddFuel(FuelType::Diesel, 200) << endl << endl;
	cout << "Selling fuel from diesel depot to client1: " << petrol1->SellFuel(*client2, 200, FuelType::Diesel) << endl;
	cout << "Balance after operation: " << petrol1->GetBalance() << endl;
	cout << "Cash in till after operation :" << petrol1->GetMoneyInTill(1) << endl; // ---------------------
	
	//Removing an existing till
	cout << endl<<endl<<"Removing an existing till: " << petrol1->RemoveTill(1) << endl;
	cout << "Balance after closing a till: " << petrol1->GetBalance() << endl;

	//refuel all depots
	cout << endl << endl << "Refuelling all depots: " << petrol1->RefuellAll() << endl;
	cout << "Balance after refuelling all depots: " << petrol1->GetBalance() << endl;
	//checkout all tills
	cout << endl << endl << "Checking out all tills: " << petrol1->CheckoutAllTills()<< endl;
	cout << "Balance after checking out all tills: " << petrol1->GetBalance() << endl;

	//closing all tills
	cout << endl << endl << "Closing all tills:  " << petrol1->CloseAllTills() << endl;
	cout << "Balance after closing all tills:  " << petrol1->GetBalance() << endl;
	//pay employees their salary
	cout << endl << endl << "Paying all employees: " << petrol1->PayAllEmployees() << endl;
	cout << "Balance after paying all employees: " << petrol1->GetBalance() << endl;


	delete petrol1; 
	delete petrol2;
	delete client1;
	delete client2;
	delete client3;
	return 0;
}

TEST(PetrolStation_HighLevelTests, global_test) {
	std::string expected = "Empty cases\n10000\n-1\n-2\n0\n0\n-2\n-1\n0\ninvalidID\n-1\n-1\nNoDepot\n-1\n-1\n\n\n\nAdding Employees\n0\nRemoving nonexistent Employee: -1\nChange name from Barbara to: Stepan\n\nGet all the data for employee ID: 2\nName: Stepan\nSalary: 100\nBonusSalary: 200\nWorking Days count: 4\n\n\nAdding and removing depots \nRemoving existing depot: 0\nChecking if nonexistent depot is open: 0\nBalance after Adding fuel: \n7800\nBalance after Adding nonexistent fuel type: \n7800\n\n\nAdding tills\nRemoving an existing till: 0\nRemoving nonexistent till: -1\n\n\nGetting data from petrolstation 1: \nBalance: 4800\nEkoDiesel buy cost: 4\nCurrent open tills count: 4\nEmployee count: 2\nStation's ID: 1\nMaximum tills count :4\nNO2 sell cost: 10\nName :Benzin1\n\n\nCreating and testing clients data: \nClient1 ID: 1\nClient2 totalClientcount: 0\nClient3 fueledamount: 0\n\n\nGetting data about Depots\nCurrent fuel amount Depot1 : 300\nMax fuel amount Depot1 : 300\nIs it working Depot1 : 1\nFuelType Depot1 : Diesel\n\n\nEmptying empty Tills\n-2\n-2\n\n\nPerforming cash operations\nSelling fuel to client1: 0\nBalance after operation: 4800\nCash in till after operation :2900\nTrying to sell fuel from empty depot to client1: -1\nBalance after operation: 4800\nCash in till after operation :2900\nTrying to sell Diesel to client3: 0\nBalance after operation: 4800\nCash in till after operation :3700\nTrying to sell fuel from empty depot to client1: -1\nBalance after operation: 4800\nCash in till after operation :3700\nTry to sell fuel station does not currently have: -1\nBalance after operation: 4800\nCash in till after operation :3700\nTry to buy fuel amout above capacitance of a fuel depot: -1\nBalance after operation: 4800\nCash in till after operation :3700\n\nChecking out till 1\n0\n\nRefuelling Diesel depot \n0\n\nSelling fuel from diesel depot to client1: 0\nBalance after operation: 8100\nCash in till after operation :800\n\n\nRemoving an existing till: 0\nBalance after closing a till: 8900\n\n\nRefuelling all depots: 0\nBalance after refuelling all depots: 4500\n\n\nChecking out all tills: 0\nBalance after checking out all tills: 7000\n\n\nClosing all tills:  0\nBalance after closing all tills:  7000\n\n\nPaying all employees: 0\nBalance after paying all employees: 6010\n";
	std::stringstream actual;

	auto* rdbuf = std::cout.rdbuf(actual.rdbuf());

	run();

	std::cout.rdbuf(rdbuf);

	EXPECT_THAT(actual.str(), expected);
}

TEST(PetrolStationTests, empty_case) {
	PetrolStation p("Octan2", 2);

	EXPECT_THAT(p.GetBalance(), 10000);
	EXPECT_THAT(p.CloseTill(2), -1);
	EXPECT_THAT(p.CheckoutTill(23), -2);
	EXPECT_THAT(p.GetCurrentOpenTillsCount(), 0);
	EXPECT_THAT(p.GetMaximumTills(), 0);
	EXPECT_THAT(p.GetMoneyInTill(234), -2);
	EXPECT_THAT(p.RemoveTill(13), -1);
	EXPECT_THAT(p.GetEmployeeCount(), 0);
	EXPECT_THAT(p.GetEmployeeName(1), "invalidID");
	EXPECT_THAT(p.GetEmployeeBonusSalary(2), -1);
	EXPECT_THAT(p.GetEmployeeSalary(100), -1);
	EXPECT_THAT(p.GetDepotFuelType(2), "NoDepot");
	EXPECT_THAT(p.GetEmployeeWorkingDaysCount(234), -1);
	EXPECT_THAT(p.ChangeEmployeeName(2, "Bob"), -1);
}

struct PetrolStationFixtureTests : ::testing::Test {

	PetrolStation p{ "Benzin1", 1 };

	void SetUp() override {
		p.AddEmployee("John", 100, 200, 3, 1);
		p.AddEmployee("Barbara", 200, 300, 4, 2);
		p.AddEmployee("Tadeus", 130, 560, 4, 3);
	}

};

TEST_F(PetrolStationFixtureTests, adding_and_removing_employees) {
	EXPECT_THAT(p.GetEmployeeCount(), 3);
	EXPECT_THAT(p.RemoveEmployee(1), 0);
	EXPECT_THAT(p.GetEmployeeCount(), 2);
}

TEST_F(PetrolStationFixtureTests, removing_non_existing_employee) {
	EXPECT_THAT(p.RemoveEmployee(4), -1);
}

TEST_F(PetrolStationFixtureTests, change_employee_parameters) {
	EXPECT_THAT(p.GetEmployeeName(2), "Barbara");
	EXPECT_THAT(p.ChangeEmployeeName(2, "Stepan"), 0);
	EXPECT_THAT(p.GetEmployeeName(2), "Stepan");
	EXPECT_THAT(p.SetEmployeeBonusSalary(2, 200), 0);
	EXPECT_THAT(p.SetEmployeeWorkingDaysCount(2, 4), 0);
	EXPECT_THAT(p.SetEmployeeSalary(2, 100), 0);

	EXPECT_THAT(p.GetEmployeeBonusSalary(2), 200);
	EXPECT_THAT(p.GetEmployeeWorkingDaysCount(2),   4);
	EXPECT_THAT(p.GetEmployeeSalary(2), 100);
}

struct PetrolStationWithDepotsFixtureTests : PetrolStationFixtureTests {
	void SetUp() override {
		PetrolStationFixtureTests::SetUp();
		p.AddDepot(1, 300, FuelType::Diesel);
		p.AddDepot(2, 400, FuelType::EkoDiesel);
		//		p.AddDepot(3, 400, FuelType::Pb95);
		p.AddDepot(4, 300, FuelType::Pb98);
		p.AddDepot(5, 500, FuelType::TurboDiesel);
		p.AddDepot(6, 100, FuelType::N02);
	}
};


TEST_F(PetrolStationWithDepotsFixtureTests, adding_and_removing_depots) {
	p.AddDepot(3, 400, FuelType::Pb95);

	EXPECT_THAT(p.removeDepot(3), 0);

	EXPECT_THAT(p.isDepotWorking(3), false);
}

TEST_F(PetrolStationWithDepotsFixtureTests, balance_after_adding_fuel) {
	EXPECT_THAT(p.AddFuel(FuelType::Diesel, 300), 0); //DIESEL = 300
	EXPECT_THAT(p.AddFuel(FuelType::EkoDiesel, 400), 0); //EKODIESEL = 400
	
	EXPECT_THAT(p.GetBalance(), 7800);

	EXPECT_THAT(p.AddFuel(FuelType::Pb95, 100), -1);

	EXPECT_THAT(p.GetBalance(), 7800);
}

struct PetrolStationWithDepotsAndTillsFixtureTests : PetrolStationWithDepotsFixtureTests {
	void SetUp() override {
		PetrolStationWithDepotsFixtureTests::SetUp();

		p.AddTill(1, 10000, 500);
		p.AddTill(2, 3000, 500);
		p.AddTill(4, 2000, 0);
		p.AddTill(3, 10000, 2000);
	}

	Client client1{ 1, 0    };
	Client client2{ 2, 0    };
	Client client3{ client2 };
};

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, adding_tills_removing_tills) {
	EXPECT_THAT(p.RemoveTill(2), 0);
	EXPECT_THAT(p.RemoveTill(0), -1);

	p.AddTill(2, 3000, 500);
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, getting_data_from_petrolstation) {
	EXPECT_THAT(p.GetBalance(), 7000);
	EXPECT_THAT(p.GetBuyCost(FuelType::EkoDiesel), 4);
	EXPECT_THAT(p.GetCurrentOpenTillsCount(), 4);
	EXPECT_THAT(p.GetEmployeeCount(), 3);
	EXPECT_THAT(p.GetID(), 1);
	EXPECT_THAT(p.GetMaximumTills(), 4);
	EXPECT_THAT(p.GetSellCost(FuelType::N02), 10);
	EXPECT_THAT(p.GetName(), "Benzin1");
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, getting_data_about_depots_without_cash_operations) {
	EXPECT_THAT(p.GetDepotCurrentFuelAmount(1), 0);
	EXPECT_THAT(p.GetDepotMaxFuelAmount(1), 300);
	EXPECT_THAT(p.isDepotWorking(1), true);
	EXPECT_THAT(p.GetDepotFuelType(1), "Diesel");

}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, emptying_empty_tills) {
	EXPECT_THAT(p.CheckoutTill(0),-2);
	EXPECT_THAT(p.CheckoutTill(100), -2);
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, unsuccessful_cash_operations) {
	PetrolStation p2("Octan2", 2);

	const int initial_balance = 7000;
	const int initial_money_in_till = 500;
	const int FAILED = -1;

	EXPECT_THAT(p.SellFuel(client1, 400, FuelType::EkoDiesel), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);

	//Try to buy from an empty fuel depot
	EXPECT_THAT(p.SellFuel(client1, 100, FuelType::EkoDiesel), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);
	EXPECT_THAT(p.SellFuel(client3, 200, FuelType::Diesel), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);
	EXPECT_THAT(p2.SellFuel(client1, 400, FuelType::Pb95), FAILED);
	EXPECT_THAT(p.GetBalance(), initial_balance);
	EXPECT_THAT(p.GetMoneyInTill(1), initial_money_in_till);

	//Try to sell fuel station does not currently have
	EXPECT_THAT(p.SellFuel(client2, 200, FuelType::N02), FAILED);
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
	EXPECT_THAT(p.AddFuel(FuelType::Diesel, 200), 0);
	EXPECT_THAT(p.SellFuel(client2, 200, FuelType::Diesel), 0);
	EXPECT_THAT(p.GetBalance(), 6600);
	EXPECT_THAT(p.GetMoneyInTill(1), 1300);
}

TEST_F(PetrolStationWithDepotsAndTillsFixtureTests, refuelling_checkout_and_closing_tills_and_salaries) {
	//refuel all depots
	EXPECT_THAT(p.RefuellAll(), 0);
	EXPECT_THAT(p.GetBalance(), 2400);
	//checkout all tills
	EXPECT_THAT(p.CheckoutAllTills(), 0);
	EXPECT_THAT(p.GetBalance(), 5400);

	//closing all tills
	EXPECT_THAT(p.CloseAllTills(), 0);
	EXPECT_THAT(p.GetBalance(), 5400);
	//pay employees their salary
	EXPECT_THAT(p.PayAllEmployees(), 0);
	EXPECT_THAT(p.GetBalance(), 3910);

}
