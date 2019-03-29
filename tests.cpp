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
    delete factory;
}

TEST(HERO_BUILDER, TankBuilder) {
    TankBuilder* builder = new TankBuilder();
    Hero* hero = new Hero("x", 0, 0);
    builder->set_hero(hero);
    builder->add_weapon();
    builder->add_accessory();
    ASSERT_EQ(hero->weapon->name, "Warmace of Menethil");
    ASSERT_EQ(hero->accessory->name, "Deathbringer's Will");
    ASSERT_EQ(hero->health, 500);
    ASSERT_EQ(hero->damage, 200);
    delete hero;
    delete builder;
}


TEST(HERO_BUILDER, DamagerBuilder) {
    DamagerBuilder* builder = new DamagerBuilder();
    Hero* hero = new Hero("x", 0, 0);
    builder->set_hero(hero);
    builder->add_weapon();
    builder->add_accessory();
    ASSERT_EQ(hero->weapon->name, "Shadowmourne");
    ASSERT_EQ(hero->accessory->name, "Deathbringer's Will");
    ASSERT_EQ(hero->health, 0);
    ASSERT_EQ(hero->damage, 500);
    delete hero;
    delete builder;
}


TEST(HERO_BUILDER, HealBuilder) {
    HealBuilder* builder = new HealBuilder();
    Hero* hero = new Hero("x", 0, 0);
    builder->set_hero(hero);
    builder->add_weapon();
    builder->add_accessory();
    ASSERT_EQ(hero->weapon->name, "Warmace of Menethil");
    ASSERT_EQ(hero->accessory->name, "Flask of Professor Putricide");
    ASSERT_EQ(hero->health, 500);
    ASSERT_EQ(hero->damage, 200);
    delete hero;
    delete builder;
}

TEST(HERO_MANAGER, tank_builder) {
    HeroManager* manager = new HeroManager();
    TankBuilder* builder = new TankBuilder();
    manager->set_HeroBuilder(builder);
    Hero* hero = manager->create_hero();
    ASSERT_EQ(hero->weapon->name, "Warmace of Menethil");
    ASSERT_EQ(hero->accessory->name, "Deathbringer's Will");
    ASSERT_EQ(hero->health, 1000 + 500);
    ASSERT_EQ(hero->damage, 100 + 200);
    delete hero;
    delete builder;
    delete manager;
}

TEST(HERO_MANAGER, damager_builder) {
    HeroManager* manager = new HeroManager();
    DamagerBuilder* builder = new DamagerBuilder();
    manager->set_HeroBuilder(builder);
    Hero* hero = manager->create_hero();
    ASSERT_EQ(hero->weapon->name, "Shadowmourne");
    ASSERT_EQ(hero->accessory->name, "Deathbringer's Will");
    ASSERT_EQ(hero->health, 1000 + 0);
    ASSERT_EQ(hero->damage, 100 + 500);
    delete hero;
    delete builder;
    delete manager;
}

TEST(HERO_MANAGER, heal_builder) {
    HeroManager* manager = new HeroManager();
    HealBuilder* builder = new HealBuilder();
    manager->set_HeroBuilder(builder);
    Hero* hero = manager->create_hero();
    ASSERT_EQ(hero->weapon->name, "Warmace of Menethil");
    ASSERT_EQ(hero->accessory->name, "Flask of Professor Putricide");
    ASSERT_EQ(hero->health, 1000 + 500);
    ASSERT_EQ(hero->damage, 100 + 200);
    delete hero;
    delete builder;
    delete manager;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}