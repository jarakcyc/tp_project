#include "horde.h"
#include "aliance.h"
#include "army.h"
#include <gtest/gtest.h>

TEST(ARMY, class_Warrior_1) {
    Warrior* unit = new Warrior("Warrior", warrior_type::INFANTRY, 100, 20, 50);
    ASSERT_EQ(unit->name, "Warrior");
    ASSERT_EQ(unit->type, warrior_type::INFANTRY);
    ASSERT_EQ(unit->max_health, 100);
    ASSERT_EQ(unit->health, 100);
    ASSERT_EQ(unit->damage, 20);
    ASSERT_EQ(unit->cost, 50);
    delete unit;
}

TEST(ARMY, class_Warrior_2) {
    Warrior* unit = new Warrior("Dimas", warrior_type::DISTANCE, 200000, 100000, 100500);
    ASSERT_EQ(unit->name, "Dimas");
    ASSERT_EQ(unit->type, warrior_type::DISTANCE);
    ASSERT_EQ(unit->max_health, 200000);
    ASSERT_EQ(unit->health, 200000);
    ASSERT_EQ(unit->damage, 100000);
    ASSERT_EQ(unit->cost, 100500);
    delete unit;
}

TEST(ARMY, test_class_Infantry) {
    Warrior* unit = new Infantry("unit", 1, 2);
    ASSERT_EQ(unit->name, "unit");
    ASSERT_EQ(unit->type, warrior_type::INFANTRY);
    ASSERT_EQ(unit->max_health, 1);
    ASSERT_EQ(unit->health, 1);
    ASSERT_EQ(unit->damage, 2);
    delete unit;
}

TEST(ARMY, test_class_Distance) {
    Warrior* unit = new Distance("unit", 1, 2);
    ASSERT_EQ(unit->name, "unit");
    ASSERT_EQ(unit->type, warrior_type::DISTANCE);
    ASSERT_EQ(unit->max_health, 1);
    ASSERT_EQ(unit->health, 1);
    ASSERT_EQ(unit->damage, 2);
    delete unit;
}

TEST(ARMY, test_class_Hero) {
    Warrior* unit = new Hero("unit", 1, 2);
    ASSERT_EQ(unit->name, "unit");
    ASSERT_EQ(unit->type, warrior_type::HERO);
    ASSERT_EQ(unit->max_health, 1);
    ASSERT_EQ(unit->health, 1);
    ASSERT_EQ(unit->damage, 2);
    delete unit;
}

TEST(HORDE, test_units) {
    Warrior* unit = new Orc();
    ASSERT_EQ(unit->name, "Orc");
    delete unit;
    unit = new Tauren();
    ASSERT_EQ(unit->name, "Tauren");
    delete unit;
    unit = new Warlock();
    ASSERT_EQ(unit->name, "Warlock");
    delete unit;
    unit = new Shaman();
    ASSERT_EQ(unit->name, "Shaman");
    delete unit;
    unit = new Thrall();
    ASSERT_EQ(unit->name, "Thrall");
    delete unit;
    unit = new Zuljin();
    ASSERT_EQ(unit->name, "Zuljin");
    delete unit;
}

TEST(HORDE, class_ArmyFactory_create_infantry_test) {
    ArmyFactory* factory = new HordeArmyFactory();
    Warrior* unit = factory->create_infantry("Orc");
    ASSERT_EQ(unit->name, "Orc");
    ASSERT_EQ(unit->type, warrior_type::INFANTRY);
    delete unit;
    unit = factory->create_infantry("Tauren");
    ASSERT_EQ(unit->name, "Tauren");
    ASSERT_EQ(unit->type, warrior_type::INFANTRY);
    delete unit;
    unit = factory->create_distance("Warlock");
    ASSERT_EQ(unit->name, "Warlock");
    ASSERT_EQ(unit->type, warrior_type::DISTANCE);
    delete unit;
    unit = factory->create_distance("Shaman");
    ASSERT_EQ(unit->name, "Shaman");
    ASSERT_EQ(unit->type, warrior_type::DISTANCE);
    delete unit;
    unit = factory->create_hero("Thrall");
    ASSERT_EQ(unit->name, "Thrall");
    ASSERT_EQ(unit->type, warrior_type::HERO);
    delete unit;
    unit = factory->create_hero("Zuljin");
    ASSERT_EQ(unit->name, "Zuljin");
    ASSERT_EQ(unit->type, warrior_type::HERO);
    delete unit;
    delete factory;
}

TEST(ALIANCE, test_units) {
    Warrior* unit = new Soldier();
    ASSERT_EQ(unit->name, "Soldier");
    delete unit;
    unit = new Knight();
    ASSERT_EQ(unit->name, "Knight");
    delete unit;
    unit = new Mag();
    ASSERT_EQ(unit->name, "Mag");
    delete unit;
    unit = new Priest();
    ASSERT_EQ(unit->name, "Priest");
    delete unit;
    unit = new Varian();
    ASSERT_EQ(unit->name, "Varian");
    delete unit;
    unit = new Greymane();
    ASSERT_EQ(unit->name, "Greymane");
    delete unit;
}

TEST(ALIANCE, class_ArmyFactory_create_infantry_test) {
    ArmyFactory* factory = new AlianceArmyFactory();
    Warrior* unit = factory->create_infantry("Soldier");
    ASSERT_EQ(unit->name, "Soldier");
    ASSERT_EQ(unit->type, warrior_type::INFANTRY);
    delete unit;
    unit = factory->create_infantry("Knight");
    ASSERT_EQ(unit->name, "Knight");
    ASSERT_EQ(unit->type, warrior_type::INFANTRY);
    delete unit;
    unit = factory->create_distance("Mag");
    ASSERT_EQ(unit->name, "Mag");
    ASSERT_EQ(unit->type, warrior_type::DISTANCE);
    delete unit;
    unit = factory->create_distance("Priest");
    ASSERT_EQ(unit->name, "Priest");
    ASSERT_EQ(unit->type, warrior_type::DISTANCE);
    delete unit;
    unit = factory->create_hero("Varian");
    ASSERT_EQ(unit->name, "Varian");
    ASSERT_EQ(unit->type, warrior_type::HERO);
    delete unit;
    unit = factory->create_hero("Greymane");
    ASSERT_EQ(unit->name, "Greymane");
    ASSERT_EQ(unit->type, warrior_type::HERO);
    delete unit;
    delete factory;
}

TEST(HERO_BUILDER, test_adding_items) {
    HeroBuilder builder;
    Hero* hero = new Hero("test", 0, 0);
    builder.set_hero(hero);
    builder.add_item(1);
    ASSERT_EQ(hero->damage, 200);
    ASSERT_EQ(hero->health, 500);
    ASSERT_EQ(hero->max_health, 500);
    builder.remove_item(1);
    ASSERT_EQ(hero->damage, 0);
    ASSERT_EQ(hero->health, 0);
    ASSERT_EQ(hero->max_health, 0);
    ASSERT_EQ((int)hero->items.size(), 0);
    builder.add_item(2);
    ASSERT_EQ(hero->damage, 500);
    ASSERT_EQ(hero->health, 0);
    ASSERT_EQ(hero->max_health, 0);
    builder.add_item(3);
    ASSERT_EQ((int)hero->items.size(), 2);
    delete hero;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}