#pragma once
#include <iostream>
#include "Category.h"
//#include "Unit.h"
class Unit;

class Skill {
protected:
	std::string name;
	int damage;
	int cost_mp;
	int cost_hp;
public:
	Skill();
	std::string getName();
	virtual void activeSkill(Unit* caster, Unit* target) = 0;
	int getCostMp();
	int getCostHp();
	virtual std::unique_ptr<Skill> clone() = 0;
};


class Fireball : public Skill {
public:
	Fireball();
	void activeSkill(Unit* caster, Unit* target) override;

	std::unique_ptr<Skill> clone() override;
};

class PowerStrike : public Skill {
public:
	PowerStrike();
	void activeSkill(Unit* caster, Unit* target) override;
	std::unique_ptr<Skill> clone() override;
};


class ArrowShot : public Skill {
public:
	ArrowShot();
	void activeSkill(Unit* caster, Unit* target) override;
	std::unique_ptr<Skill> clone() override;
};


class Heal : public Skill {
private:
	int heal_hp;
public:
	Heal();
	void activeSkill(Unit* caster, Unit* target) override;
	std::unique_ptr<Skill> clone() override;
};