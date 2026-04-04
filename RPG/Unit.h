#pragma once
#include <random>
#include "Category.h"
#include "Stat.h"
#include "Weapon.h"
#include "Skill.h"

class Unit {
private:
	std::string name;
	int current_hp, current_mp;
	int max_hp, max_mp;
	Stat stats;
	std::unique_ptr<Weapon> current_weapon;
	std::random_device rd;
	std::vector<std::unique_ptr<Skill>> unitskills;

public:
	Unit(std::string& name);
	Unit(std::string& name, int max_hp, int max_mp, const Stat& stats);
	Unit(std::string& name, int max_hp, int max_mp, const Stat& stats, std::unique_ptr<Weapon> weapon);
	std::string getName();
	int getCurrentHp();
	int getMaxHp();
	void setCurrentHp(int new_hp);
	int getCurrentMp();
	void setCurrentMp(int new_mp);

	Category getCurrentWeaponCategory();

	void attackedDamage(int damage);

	bool evasionAttack();

	int attackDamage(Unit* enemy);

	void setWeapon(std::unique_ptr<Weapon>&& change_weapon);
	int getUnitAttack();
	bool isDead();

	void addUnitSkill(std::unique_ptr<Skill> skill);

	void activeSkill(std::string skill_name, Unit* target);

	bool isValidCost(Skill* skill);
	Skill* findUnitSkill(std::string skill_name);

	void printStat();
};