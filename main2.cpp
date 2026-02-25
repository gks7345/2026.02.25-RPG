#include <iostream>
#include <string>
#include <vector>
#include <map>

class Weapon {
public:
	std::string name;
	int attack;
public:
	Weapon() {}
	Weapon(std::string name, int attack):name(name), attack(attack) { }
	int getAttack() { return attack; }
	void setName(std::string name) { Weapon::name = name; }
	void setAttack(int attack) { Weapon::attack = attack; }
	std::string getName() { return name; }
};

class Unit {
protected:
	std::string name;
	int hp, attack;
public:
	Unit(std::string name, int hp, int attack) : name(name), hp(hp), attack(attack) { }
	std::string getName() { return name; }
	int getAttack() { return attack; }
	int getHp() { return hp; }
	void attacktedDamage(int damage) {
		if (damage == 0) {
			return;
		}
		hp -= damage;
		std::cout <<" -- " << name << "이(가) " << damage << " 데미지를 입였습니다. 남은 HP: " << hp << " -- " << std::endl;
		if (isDead()) {
			std::cout<<" -- " << name << "이(가) 사망하였습니다."<<" -- "<<std::endl;
		}
	}

	virtual int attackDamage(std::string enemy) {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 공격할 수 없습니다." << " -- " << std::endl;
			return 0;
		}
		std::cout << " -- " << name << "이(가)" << enemy << "를(을) 공격합니다." << " -- " << std::endl;
		return attack;
	}

	virtual void setWeapon(Weapon change_weapon) {	}

	bool isDead() {
		if (hp <= 0) {
			return true;
		}
		return false;
	}

	virtual void printStat() {
		std::cout << " [" << name << "] " << std::endl;
		std::cout << "HP : " << hp << std::endl;
		std::cout << "공격력 : " << attack << std::endl;
		if (isDead()) {
			std::cout << "-사망-" << std::endl;
		}
	}
};

class Monster : public Unit {
private:
public:
	Monster(std::string name, int hp, int attack) : Unit(name, hp, attack) {}
};

class Hero : public Unit {
private:
	Weapon current_weapon;
public:
	Hero(std::string name, int hp, int attack) : Unit(name, hp, attack) { 
		current_weapon.setName("맨손");
		current_weapon.setAttack(0);
	}
	Hero(std::string name, int hp, int attack, Weapon current_weapon) : Unit(name, hp, attack), current_weapon(current_weapon) { }
	void setWeapon(Weapon change_weapon) override {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 무기를 교체할 수 없습니다." << " -- " << std::endl;
			return;
		}
		current_weapon = change_weapon;
	}
	int attackDamage(std::string enemy) override {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 공격할 수 없습니다." << " -- " << std::endl;
			return 0;
		}
		std::cout << " -- " << name << "이(가)" << enemy << "를(을) 공격합니다." << " -- " << std::endl;
		return attack + current_weapon.getAttack();
	}

	void printStat() override {
		std::cout << " [" << name << "] " << std::endl;
		std::cout << "HP : " << hp << std::endl;
		std::cout << "공격력 : " << attack << std::endl;
		std::cout << "무기 : " << current_weapon.getName() << "    무기 공격력 : " << current_weapon.getAttack() << std::endl;
		if (isDead()) {
			std::cout << "-사망-" << std::endl;
		}
	}
};

class RPG {
private:
	std::vector<std::unique_ptr<Unit>> units;
	std::map<std::string, Weapon> weapons;
public:
	RPG() { weapons["맨손"] = Weapon("맨손",0); }
	void addWeapon(Weapon weapon) {
		weapons[weapon.getName()] = weapon;
	}
	void createHero(std::string name, int hp, int attack) {
		std::cout << " -- " << "Hero를 생성하였습니다." << " -- " << std::endl;
		units.push_back(std::make_unique<Hero>(name, hp, attack));
	}
	void createHero(std::string name, int hp,int attack,std::string weaponname) {
		if (validWeapon(weaponname)) {
			std::cout << " -- " << weaponname << "이(가) 없습니다. 추가 해주세요." << " -- " << std::endl;
			return;
		}
		std::cout << " -- " << "Hero를(을) 생성하였습니다." << " -- " << std::endl;
		units.push_back(std::make_unique<Hero>(name, hp, attack, weapons[weaponname]));
	}
	void changeWeapon(std::string unitname, std::string weaponname) {
		Unit* unit = findUnit(unitname);
		if (unit == nullptr) {
			std::cout << " -- " << unitname << "이(가) 없습니다." << " -- " << std::endl;
			return;
		}
		if (validWeapon(weaponname)) {
			std::cout << " -- " <<"무기 " << weaponname << "이(가) 없습니다. 추가 해주세요." << " -- " << std::endl;
			return;
		}
		unit->setWeapon(weapons[weaponname]);
	}
	bool validWeapon(std::string weaponname) {
		if (weapons.find(weaponname) != weapons.end()) {
			return false;
		}
		return true;
	}

	void createMonster(std::string name, int hp, int attack) {
		std::cout << " -- " << "Monster를(을) 생성하였습니다." << " -- " << std::endl;
		units.push_back(std::make_unique<Monster>(name, hp, attack));
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
		int damage = unit->attackDamage(enemyname);
		enemy->attacktedDamage(damage);
	}

	Unit* findUnit(std::string unitname) {
		for (auto& unit : units) {
			if (unit->getName() == unitname) {
				return unit.get();
			}
		}return nullptr;
	}

	
};

int main() {
	RPG game;
	game.createHero("Hero", 100, 30);
	game.findUnit("Hero")->printStat();
	game.changeWeapon("Hero","한손검");
	game.addWeapon(Weapon("한손검", 10));
	game.changeWeapon("Hero", "한손검");
	game.findUnit("Hero")->printStat();

	game.createMonster("Monster", 100, 8);
	game.findUnit("Monster")->printStat();

	game.attackUnit("Hero", "Monster");
	game.attackUnit("Hero", "Monster");
	game.attackUnit("Hero", "Monster");
	game.findUnit("Monster")->printStat();
	game.attackUnit("Monster", "Hero");
	
	game.createMonster("Monster2", 100, 120);
	game.findUnit("Monster2")->printStat();
	game.attackUnit("Monster2", "Hero");
	game.changeWeapon("Hero", "맨손");
}