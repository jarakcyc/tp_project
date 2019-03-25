#include "horde.h"
#include "aliance.h"
#include "army.h"
#include <gtest/gtest.h>

TEST(ARMY, class_Warrior_test_1) {
	Warrior* unit = new Warrior("Warrior", warrior_type::INFANTRY, 100, 20, 50);
	ASSERT_EQ(unit->name, "Warrior");
	ASSERT_EQ(unit->type, warrior_type::INFANTRY);
	ASSERT_EQ(unit->max_health, 100);
	ASSERT_EQ(unit->health, 100);
	ASSERT_EQ(unit->damage, 20);
	ASSERT_EQ(unit->cost, 50);
	delete unit;
}

TEST(ARMY, class_Warrior_test_2) {
	Warrior* unit = new Warrior("Dimas", warrior_type::DISTANCE, 200000, 100000, 100500);
	ASSERT_EQ(unit->name, "Dimas");
	ASSERT_EQ(unit->type, warrior_type::DISTANCE);
	ASSERT_EQ(unit->max_health, 200000);
	ASSERT_EQ(unit->health, 200000);
	ASSERT_EQ(unit->damage, 100000);
	ASSERT_EQ(unit->cost, 100500);
	delete unit;
}

TEST(ARMY, test_class_Infantry_test_1) {
	Warrior* unit = new Infantry("unit", 1, 2);
	ASSERT_EQ(unit->name, "unit");
	ASSERT_EQ(unit->type, warrior_type::INFANTRY);
	ASSERT_EQ(unit->max_health, 1);
	ASSERT_EQ(unit->health, 1);
	ASSERT_EQ(unit->damage, 2);
	delete unit;
}

TEST(ARMY, test_class_Distance_test_1) {
	Warrior* unit = new Distance("unit", 1, 2);
	ASSERT_EQ(unit->name, "unit");
	ASSERT_EQ(unit->type, warrior_type::DISTANCE);
	ASSERT_EQ(unit->max_health, 1);
	ASSERT_EQ(unit->health, 1);
	ASSERT_EQ(unit->damage, 2);
	delete unit;
}

TEST(HORDE, class_Orc_test) {
	Warrior* unit = new Orc();
	ASSERT_EQ(unit->name, "Orc");
	delete unit;
}

TEST(HORDE, class_Warlock_test) {
	Warrior* unit = new Warlock();
	ASSERT_EQ(unit->name, "Warlock");
	delete unit;
}

TEST(HORDE, class_ArmyFactory_create_infantry_test) {
	ArmyFactory* factory = new HordeArmyFactory();
	Warrior* orc = factory->create_infantry("Orc");
	ASSERT_EQ(orc->name, "Orc");
	ASSERT_EQ(orc->type, warrior_type::INFANTRY);
	delete orc;
	delete factory;
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}