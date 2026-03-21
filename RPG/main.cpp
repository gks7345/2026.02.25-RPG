#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

enum class Category {
	no_weapon,
	one_handed_sword,
	arrow,
	axe,
	spear,
	shield
};

class Stat {
private:
	int str = 0;
	int dex = 0;
	int def = 0;
public:
	Stat() {}
	Stat(int str, int dex, int def) :str(str), dex(dex), def(def) {}
	int getStr() { return str; }
	int getDex() { return dex; }
	int getDef() { return def; }
	void setStr(int str) { Stat::str = str; }
	void setDex(int dex) { Stat::dex = dex; }
	void setDef(int def) { Stat::def = def; }
};

class Weapon {
protected:
	std::string name;
	int attack;
	Stat add_stats;
	Category category = Category::no_weapon;
public:
	Weapon() {
		name = "없음";
		attack = 0;
	}
	Weapon(std::string& name, int attack) :name(name), attack(attack) {}
	Weapon(std::string& name, int attack, Stat& add_stats) :name(name), attack(attack), add_stats(add_stats) {}
	Weapon(const Weapon& weapon) :name(weapon.name), attack(weapon.attack), add_stats(weapon.add_stats) {}
	virtual ~Weapon() = default;
	int getAttack() { return attack + add_stats.getStr() * 2; }
	void setName(std::string& name) { Weapon::name = name; }
	void setAttack(int attack) { Weapon::attack = attack; }
	void setAddStats(Stat& add_stats) { Weapon::add_stats = add_stats; }

	std::string getName() { return name; }
	Stat* getAddStats() { return &add_stats; }
	virtual Category getCategory() { return category; }

	virtual int getWeaponDamage(std::unique_ptr<Weapon>* enemys_weapon) {
		int weapon_damage = attack + add_stats.getStr() * 2;
		return weapon_damage;
	}

	virtual std::unique_ptr<Weapon> clone() const { return std::make_unique<Weapon>(*this); }
};

class No_weapon : public Weapon {
public:
	No_weapon() : Weapon() {
		name = "맨손";
		attack = 0;
		add_stats.setStr(0);
		add_stats.setDex(0);
		add_stats.setDef(0);
		Weapon::category = Category::no_weapon;
	}
	No_weapon(int attack, Stat& add_stats) : Weapon() {
		Weapon::name = "맨손";
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
		Weapon::category = Category::no_weapon;
	}
	No_weapon(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	std::unique_ptr<Weapon> clone() const override {
		return std::make_unique<No_weapon>(*this);
	}
};

class One_hand_sword : public Weapon {
private:
public:
	One_hand_sword() : Weapon() {
		name = "한손검";
		attack = 9;
		add_stats.setStr(3);
		add_stats.setDex(3);
		Weapon::category = Category::one_handed_sword;
	}
	One_hand_sword(int attack, Stat& add_stats) : Weapon() {
		Weapon::name = "한손검";
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
		Weapon::category = Category::one_handed_sword;
	}
	One_hand_sword(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	Category getCategory() override { return One_hand_sword::category; }

	std::unique_ptr<Weapon> clone() const override {
		return std::make_unique<One_hand_sword>(*this);
	}

};

class Arrow : public Weapon {
private:
public:
	Arrow() : Weapon() {
		name = "활";
		attack = 7;
		add_stats.setStr(2);
		add_stats.setDex(4);
		Weapon::category = Category::arrow;
	}
	Arrow(int attack, Stat& add_stats) : Weapon() {
		Weapon::name = "활";
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
		Weapon::category = Category::arrow;
	}
	Arrow(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	Category getCategory() override { return Arrow::category; }

	int getWeaponDamage(std::unique_ptr<Weapon>* enemys_weapon) override {
		int weapon_damage = attack + add_stats.getStr() * 2;
		if (enemys_weapon->get()->getCategory() == Category::axe || enemys_weapon->get()->getCategory() == Category::spear) {
			std::cout << " -- 5의 추가 데미지를 입힙니다. -- " << std::endl;
			return weapon_damage + 5;
		}
		if (enemys_weapon->get()->getCategory() == Category::shield) {
			std::cout << " -- 활의 공격력이 5로 줄어듭니다. -- " << std::endl;
			return 5;
		}
		return weapon_damage;
	}

	std::unique_ptr<Weapon> clone() const override {
		return std::make_unique<Arrow>(*this);
	}
};

class Axe : public Weapon {
private:
public:
	Axe() : Weapon() {
		name = "도끼";
		attack = 15;
		add_stats.setStr(6);
		Weapon::category = Category::axe;
	}
	Axe(int attack, Stat& add_stats) : Weapon() {
		Weapon::name = "도끼";
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
	}
	Axe(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	Category getCategory() override { return Axe::category; }

	int getWeaponDamage(std::unique_ptr<Weapon>* enemys_weapon) override {
		int weapon_damage = attack + add_stats.getStr() * 2;
		if (enemys_weapon->get()->getCategory() == Category::arrow) {
			std::cout << " -- 7의 추가 데미지를 입힙니다. -- " << std::endl;
			return weapon_damage + 7;
		}
		if (enemys_weapon->get()->getCategory() == Category::shield) {
			std::cout << " -- 2의 추가 데미지를 입힙니다. -- " << std::endl;
			return weapon_damage + 2;
		}
		return weapon_damage;
	}

	std::unique_ptr<Weapon> clone() const override {
		return std::make_unique<Axe>(*this);
	}
};

class Spear : public Weapon {
private:
	Category category = Category::spear;
public:
	Spear() : Weapon() {
		name = "창";
		attack = 12;
		add_stats.setStr(2);
		add_stats.setDex(2);
		add_stats.setDef(2);
	}
	Spear(int attack, Stat& add_stats) : Weapon() {
		Weapon::name = "창";
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
	}
	Spear(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	Category getCategory() override { return Spear::category; }

	int getWeaponDamage(std::unique_ptr<Weapon>* enemys_weapon) override {
		int weapon_damage = attack + add_stats.getStr() * 2;
		if (enemys_weapon->get()->getCategory() == Category::axe) {
			std::cout << " -- 4의 추가 데미지를 입힙니다. -- " << std::endl;
			return weapon_damage + 4;
		}
		if (enemys_weapon->get()->getCategory() == Category::shield) {
			std::cout << " -- 2의 추가 데미지를 입힙니다. -- " << std::endl;
			return weapon_damage + 2;
		}
		return weapon_damage;
	}

	std::unique_ptr<Weapon> clone() const override {
		return std::make_unique<Spear>(*this);
	}
};

class Shield : public Weapon {
private:
	Category category = Category::shield;
public:
	Shield() : Weapon() {
		name = "방패";
		attack = 3;
		add_stats.setDef(10);
	}
	Shield(int attack, Stat& add_stats) : Weapon() {
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
	}
	Shield(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	Category getCategory() override { return category; }

	std::unique_ptr<Weapon> clone() const override {
		return std::make_unique<Shield>(*this);
	}
};

class Unit {
private:
	std::string name;
	int hp;
	Stat stats;
	std::unique_ptr<Weapon> current_weapon;
	std::random_device rd;


public:
	Unit(std::string& name) :name(name) {}
	Unit(std::string& name, int hp, Stat& stats) : name(name), hp(hp), stats(stats) {}
	Unit(std::string& name, int hp, Stat& stats, std::unique_ptr<Weapon> weapon) : name(name), hp(hp), stats(stats) { current_weapon = move(weapon); }
	std::string getName() { return name; }
	int getHp() { return hp; }
	virtual std::unique_ptr<Weapon>* getCurrentWeapon() {
		return &current_weapon;
	}
	virtual void attackedDamage(int damage) {
		if (damage == 0) {
			return;
		}
		if (evasionAttack()) {
			std::cout << " -- " << name << "이(가) 공격을 회피하였습니다. --" << std::endl;
			return;
		}


		std::cout << " -- " << name << "이(가) " << stats.getDef() << "만큼 방어했습니다. -- " << std::endl;
		if (stats.getDef() >= damage) { damage = 1; }
		else { damage -= stats.getDef(); }
		hp -= damage;
		std::cout << " -- " << name << "이(가) " << damage << " 데미지를 입었습니다. " << std::endl;
		std::cout << " -- " << name << " 남은 HP : " << hp << std::endl;

		if (isDead()) {
			std::cout << " -- " << name << "이(가) 사망하였습니다." << " -- " << std::endl;
		}
	}

	virtual bool evasionAttack() {
		std::mt19937 gen(rd());
		if (stats.getDex() + current_weapon->getAddStats()->getDex() >= 5) {
			std::bernoulli_distribution dist(0.5);
			return dist(gen);
		}
		int evation_percent = (stats.getDex() + current_weapon->getAddStats()->getDex()) * 10;
		std::bernoulli_distribution dist(evation_percent / 100.0);
		return dist(gen);
	}

	virtual int attackDamage(Unit* enemy) {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 공격할 수 없습니다." << " -- " << std::endl;
			return 0;
		}
		if (enemy->isDead()) {
			std::cout << " -- " << enemy->getName() << "이(가) 이미 사망하였습니다." << " -- " << std::endl;
			return 0;
		}
		std::cout << " -- " << name << "이(가)" << enemy->getName() << "를(을) 공격합니다." << " -- " << std::endl;
		std::unique_ptr<Weapon>* enemys_weapon = enemy->getCurrentWeapon();

		return getUnitAttack() + current_weapon->getWeaponDamage(enemys_weapon);
	}

	virtual void setWeapon(std::unique_ptr<Weapon>&& change_weapon) {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 무기를 교체할 수 없습니다." << " -- " << std::endl;
			return;
		}
		current_weapon = move(change_weapon);
	}
	virtual int getUnitAttack() {
		return stats.getStr() * 2;
	}
	bool isDead() {
		if (hp <= 0) {
			return true;
		}
		return false;
	}

	virtual void printStat() {
		std::cout << " [" << name << "] " << std::endl;
		std::cout << "HP : " << hp << std::endl;
		std::cout << "힘 : " << stats.getStr() << std::endl;
		std::cout << "민첩 : " << stats.getDex() << std::endl;
		std::cout << "방어 : " << stats.getDef() << std::endl;
		std::cout << "무기 : " << current_weapon->getName() << "    무기 총 공격력 : " << current_weapon->getAttack() << std::endl;
		if (isDead()) {
			std::cout << "-사망-" << std::endl;
		}
	}
};

class RPG {
private:
	std::vector<std::unique_ptr<Unit>> units;
	//std::map<std::string, std::unique_ptr<Weapon>> weapons;
	std::map<std::string, std::shared_ptr<Weapon>> weapons;

	//category categorys;
public:
	RPG() {
		//Weapon no_weapon = Weapon();
		weapons["맨손"] = std::make_shared<Weapon>();
	}

	void addWeapon(std::shared_ptr<Weapon> weapon) {
		weapons[weapon->getName()] = weapon;
	}
	void createUnit(std::string name, int hp, Stat stats) {
		std::cout << " -- " << name << "를(을) 생성하였습니다." << " -- " << std::endl;
		units.push_back(std::make_unique<Unit>(name, hp, stats, weapons["맨손"]->clone()));
	}
	void createUnit(std::string name, int hp, Stat stats, std::string weaponname) {
		if (hasWeapon(weaponname)) {
			std::cout << " -- " << name << "를(을) 생성하였습니다." << " -- " << std::endl;
			units.push_back(std::make_unique<Unit>(name, hp, stats, weapons[weaponname]->clone()));
			return;
		}
		std::cout << " -- " << weaponname << "이(가) 없습니다. 추가 해주세요." << " -- " << std::endl;
	}

	void changeWeapon(std::string unitname, std::string weaponname) {
		Unit* unit = findUnit(unitname);
		if (unit == nullptr) {
			std::cout << " -- " << unitname << "이(가) 없습니다." << " -- " << std::endl;
			return;
		}
		if (hasWeapon(weaponname)) {
			unit->setWeapon(weapons[weaponname]->clone());
			std::cout << " -- 무기 " << weaponname << " 를(을) 장착하였습니다" << " -- " << std::endl;;
			return;
		}
		std::cout << " -- " << "무기 " << weaponname << "이(가) 없습니다. 추가 해주세요." << " -- " << std::endl;
	}

	void removeWeapon(std::string unitname) {
		Unit* unit = findUnit(unitname);
		if (unit == nullptr) {
			std::cout << " -- " << unitname << "이(가) 없습니다." << " -- " << std::endl;
			return;
		}
		unit->setWeapon(weapons["맨손"]->clone());
		std::cout << " -- " << unitname << " 가 무기를 해제하였습니다" << " -- " << std::endl;;
	}

	bool hasWeapon(std::string weaponname) {
		if (weapons.find(weaponname) != weapons.end()) {
			return true;
		}
		return false;
	}

	void attackUnit(std::string unitname, std::string enemyname) {
		Unit* unit = findUnit(unitname);
		Unit* enemy = findUnit(enemyname);
		if (unit == nullptr) {
			std::cout << " -- " << unitname << "이(가) 없습니다." << " -- " << std::endl;
			return;
		}
		if (enemy == nullptr) {
			std::cout << " -- " << enemyname << "이(가) 없습니다." << " -- " << std::endl;
			return;
		}
		int damage = unit->attackDamage(enemy);
		enemy->attackedDamage(damage);
	}

	Unit* findUnit(std::string unitname) {
		for (auto& unit : units) {
			if (unit->getName() == unitname) {
				return unit.get();
			}
		}
		return nullptr;
	}

	void printUnit(std::string name) {
		findUnit(name)->printStat();
	}
};

int main() {
	RPG game = RPG();
	/*Weapon axe = Axe();
	Weapon spear = Spear();
	Weapon shield = Shield();
	Weapon arrow = Arrow();*/

	game.createUnit("Hero", 100, Stat(2, 2, 2));
	game.printUnit("Hero");
	game.changeWeapon("Hero", "한손검");
	game.addWeapon(std::make_shared<One_hand_sword>());
	game.addWeapon(std::make_shared<Arrow>());
	game.addWeapon(std::make_shared <Axe>());
	game.addWeapon(std::make_shared <Spear>());
	game.addWeapon(std::make_shared <Shield>());
	game.changeWeapon("Hero", "한손검");
	game.printUnit("Hero");
	game.changeWeapon("Hero", "도끼");
	game.printUnit("Hero");

	game.createUnit("Monster1", 100, Stat(2, 2, 2), "활");
	game.printUnit("Monster1");

	game.attackUnit("Hero", "Monster1");
	game.attackUnit("Hero", "Monster1");
	game.attackUnit("Hero", "Monster1");
	game.printUnit("Monster1");
	game.attackUnit("Monster1", "Hero");

	game.createUnit("Monster2", 100, Stat(2, 2, 2), "방패");
	game.printUnit("Monster2");
	game.attackUnit("Hero", "Monster2");
	//game.changeWeapon("Hero", "맨손");

}