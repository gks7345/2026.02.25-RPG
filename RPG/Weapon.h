#pragma once
#include <iostream>
#include <string>
#include "Stat.h"
#include "Category.h"

class Weapon {
protected:
	std::string name;
	int attack;
	Stat add_stats;
	Category category;
public:
	Weapon();
	Weapon(std::string& name, int attack);
	Weapon(std::string& name, int attack, Stat& add_stats);
	Weapon(const Weapon& weapon);
	virtual ~Weapon() = default;
	int getAttack();
	void setName(std::string& name);
	void setAttack(int attack);
	void setAddStats(Stat& add_stats);

	std::string getName();
	Stat* getAddStats();
	virtual Category getCategory();

	virtual int getWeaponDamage(Category enemys_weapon);
	virtual std::unique_ptr<Weapon> clone() const;
};


class No_weapon : public Weapon {
public:
	No_weapon();
	No_weapon(int attack, Stat& add_stats);
	No_weapon(std::string name, int attack, Stat& add_stats);

	std::unique_ptr<Weapon> clone() const override;
};


class One_hand_sword : public Weapon {
private:
public:
	One_hand_sword();
	One_hand_sword(int attack, Stat& add_stats);
	One_hand_sword(std::string name, int attack, Stat& add_stats);

	Category getCategory() override;

	std::unique_ptr<Weapon> clone() const override;
};


class Arrow : public Weapon {
private:
public:
	Arrow();
	Arrow(int attack, Stat& add_stats);
	Arrow(std::string name, int attack, Stat& add_stats);

	Category getCategory() override;

	int getWeaponDamage(Category enemys_weapon) override;

	std::unique_ptr<Weapon> clone() const override;
};


class Axe : public Weapon {
private:
public:
	Axe();
	Axe(int attack, Stat& add_stats);
	Axe(std::string name, int attack, Stat& add_stats);

	Category getCategory() override;

	int getWeaponDamage(Category enemys_weapon) override;

	std::unique_ptr<Weapon> clone() const override;
};


class Spear : public Weapon {
private:
public:
	Spear();
	Spear(int attack, Stat& add_stats);
	Spear(std::string name, int attack, Stat& add_stats);

	Category getCategory() override;

	int getWeaponDamage(Category enemys_weapon) override;
	std::unique_ptr<Weapon> clone() const override;
};


class Shield : public Weapon {
private:
public:
	Shield();
	Shield(int attack, Stat& add_stats);
	Shield(std::string name, int attack, Stat& add_stats);

	Category getCategory() override;

	std::unique_ptr<Weapon> clone() const override;
};
