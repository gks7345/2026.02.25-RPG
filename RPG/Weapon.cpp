#include "Weapon.h"


Weapon::Weapon() {
	name = "없음";
	attack = 0;
}
Weapon::Weapon(std::string& name, int attack) :name(name), attack(attack) {}
Weapon::Weapon(std::string& name, int attack, Stat& add_stats):name(name), attack(attack), add_stats(add_stats) {}
Weapon::Weapon(const Weapon& weapon):name(weapon.name), attack(weapon.attack), add_stats(weapon.add_stats) {}
int Weapon::getAttack() { return attack + add_stats.getStr() * 2; }
void Weapon::setName(std::string& name) { Weapon::name = name; }
void Weapon::setAttack(int attack) { Weapon::attack = attack; }
void Weapon::setAddStats(Stat& add_stats) { Weapon::add_stats = add_stats; }
std::string Weapon::getName() { return name; }
Stat* Weapon::getAddStats() { return &add_stats; }
Category Weapon::getCategory() { return category; }
int Weapon::getWeaponDamage(Category enemys_weapon) {
	int weapon_damage = attack + add_stats.getStr() * 2;
	return weapon_damage;
}
std::unique_ptr<Weapon> Weapon::clone() const { return std::make_unique<Weapon>(*this); }


No_weapon::No_weapon() : Weapon() {
	name = "맨손";
	attack = 0;
	add_stats.setStr(0);
	add_stats.setDex(0);
	add_stats.setDef(0);
	Weapon::category = Category::no_weapon;
}
No_weapon::No_weapon(int attack, Stat& add_stats) :Weapon() {
	Weapon::name = "맨손";
	Weapon::attack = attack;
	Weapon::add_stats = add_stats;
	Weapon::category = Category::no_weapon;
}
No_weapon::No_weapon(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {
	Weapon::category = Category::no_weapon;
}
std::unique_ptr<Weapon> No_weapon::clone() const {
	return std::make_unique<No_weapon>(*this);
}


One_hand_sword::One_hand_sword() : Weapon() {
	name = "한손검";
	attack = 9;
	add_stats.setStr(3);
	add_stats.setDex(3);
	Weapon::category = Category::one_handed_sword;
}
One_hand_sword::One_hand_sword(int attack, Stat& add_stats) : Weapon() {
	Weapon::name = "한손검";
	Weapon::attack = attack;
	Weapon::add_stats = add_stats;
	Weapon::category = Category::one_handed_sword;
}
One_hand_sword::One_hand_sword(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {
	Weapon::category = Category::one_handed_sword;
}
Category One_hand_sword::getCategory() { return One_hand_sword::category; }
std::unique_ptr<Weapon> One_hand_sword::clone() const {
	return std::make_unique<One_hand_sword>(*this);
}


Arrow::Arrow() : Weapon() {
	name = "활";
	attack = 7;
	add_stats.setStr(2);
	add_stats.setDex(4);
	Weapon::category = Category::arrow;
}
Arrow::Arrow(int attack, Stat& add_stats) : Weapon() {
	Weapon::name = "활";
	Weapon::attack = attack;
	Weapon::add_stats = add_stats;
	Weapon::category = Category::arrow;
}
Arrow::Arrow(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {
	Weapon::category = Category::arrow;
}
Category Arrow::getCategory() { return Arrow::category; }
int Arrow::getWeaponDamage(Category enemys_weapon) {
	int weapon_damage = attack + add_stats.getStr() * 2;
	if (enemys_weapon == Category::axe || enemys_weapon == Category::spear) {
		std::cout << " -- 5의 추가 데미지를 입힙니다. -- " << std::endl;
		return weapon_damage + 5;
	}
	if (enemys_weapon == Category::shield) {
		std::cout << " -- 활의 공격력이 5로 줄어듭니다. -- " << std::endl;
		return 5;
	}
	return weapon_damage;
}
std::unique_ptr<Weapon> Arrow::clone() const {
	return std::make_unique<Arrow>(*this);
}

Axe::Axe() : Weapon() {
	name = "도끼";
	attack = 15;
	add_stats.setStr(6);
	Weapon::category = Category::axe;
}
Axe::Axe(int attack, Stat& add_stats) : Weapon() {
	Weapon::name = "도끼";
	Weapon::attack = attack;
	Weapon::add_stats = add_stats;
	Weapon::category = Category::axe;
}
Axe::Axe(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {
	Weapon::category = Category::axe;
}
Category Axe::getCategory() { return Axe::category; }
int Axe::getWeaponDamage(Category enemys_weapon) {
	int weapon_damage = attack + add_stats.getStr() * 2;
	if (enemys_weapon == Category::arrow) {
		std::cout << " -- 7의 추가 데미지를 입힙니다. -- " << std::endl;
		return weapon_damage + 7;
	}
	if (enemys_weapon == Category::shield) {
		std::cout << " -- 2의 추가 데미지를 입힙니다. -- " << std::endl;
		return weapon_damage + 2;
	}
	return weapon_damage;
}
std::unique_ptr<Weapon> Axe::clone() const {
	return std::make_unique<Axe>(*this);
}


Spear::Spear() : Weapon() {
	name = "창";
	attack = 12;
	add_stats.setStr(2);
	add_stats.setDex(2);
	add_stats.setDef(2);
	Weapon::category = Category::spear;
}
Spear::Spear(int attack, Stat& add_stats) : Weapon() {
	Weapon::name = "창";
	Weapon::attack = attack;
	Weapon::add_stats = add_stats;
	Weapon::category = Category::spear;
}
Spear::Spear(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {
	Weapon::category = Category::spear;
}
Category Spear::getCategory() { return Spear::category; }
int Spear::getWeaponDamage(Category enemys_weapon) {
	int weapon_damage = attack + add_stats.getStr() * 2;
	if (enemys_weapon == Category::axe) {
		std::cout << " -- 4의 추가 데미지를 입힙니다. -- " << std::endl;
		return weapon_damage + 4;
	}
	if (enemys_weapon == Category::shield) {
		std::cout << " -- 2의 추가 데미지를 입힙니다. -- " << std::endl;
		return weapon_damage + 2;
	}
	return weapon_damage;
}
std::unique_ptr<Weapon> Spear::clone() const {
	return std::make_unique<Spear>(*this);
}


Shield::Shield() : Weapon() {
	name = "방패";
	attack = 3;
	add_stats.setDef(10);
	Weapon::category = Category::shield;
}
Shield::Shield(int attack, Stat& add_stats) : Weapon() {
	Weapon::attack = attack;
	Weapon::add_stats = add_stats;
	Weapon::category = Category::shield;
}
Shield::Shield(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {
	Weapon::category = Category::shield;
}
Category Shield::getCategory() { return category; }
std::unique_ptr<Weapon> Shield::clone() const {
	return std::make_unique<Shield>(*this);
}
