#include <gmock/gmock.h>
#include "PetrolStationBuilder.h"
#include "PetrolStation.h"

TEST(PetrolStationBuilderTests, create_empty_petrol_station)
{
	std::string name = "name";
	int id = 1;
	auto p = PetrolStationBuilder(name, id).build();

	EXPECT_THAT(p.GetName(), name);
	EXPECT_THAT(p.GetID(), id);
}

TEST(PetrolStationBuilderTests, running_build_on_the_same_builder_without_setting_values_again_throws_exception)
{
	std::string name = "name";
	int id = 1;
	PetrolStationBuilder b(name, id);
	b.build();

	EXPECT_THROW(b.build(), RequirementsNotFulfilled);
}

TEST(PetrolStationBuilderTests, adding_one_employee)
{
	std::string name = "name";
	int id = 1;
	auto p = PetrolStationBuilder(name, id).add(Employee("one", Money(1), Money(2), 5, 1)).build();

	EXPECT_THAT(p.GetName(), name);
	EXPECT_THAT(p.GetID(), id);
}
