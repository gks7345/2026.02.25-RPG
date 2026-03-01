#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>

enum category {
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
	Stat() { }
	Stat(int str, int dex, int def) :str(str), dex(dex), def(def) { }
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
	std::string category;
public:
	Weapon() {
		name = "맨손";
		attack = 0;
		category = "없음";
	}
	Weapon(std::string& name, int attack) :name(name), attack(attack) {}
	Weapon(std::string& name, int attack, Stat& add_stats) :name(name), attack(attack), add_stats(add_stats){}
	virtual ~Weapon() = default;

	void setName(std::string& name) { Weapon::name = name; }
	void setAttack(int attack) { Weapon::attack = attack; }
	void setAddStats(Stat& add_stats) { Weapon::add_stats = add_stats; }

	std::string getName() { return name; }
	int getAttack() { return attack; }
	Stat* getAddStats() { return &add_stats; }
	virtual std::string getCategory() { return category; }

	virtual int addAttack(std::shared_ptr<Weapon> enemys_weapon) {
		return 0;
	}
};

class One_hand_sword: public Weapon {
private:
	std::string category = "한손검";
public:
	One_hand_sword() : Weapon() {
		name = "한손검";
		attack = 9;
		add_stats.setStr(3);
		add_stats.setDex(3);
	}
	One_hand_sword(int attack, Stat& add_stats) : Weapon() {
		Weapon::name = "한손검";
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
	}
	One_hand_sword(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	std::string getCategory() override { return One_hand_sword::category; }
};

class Arrow : public Weapon {
private:
	std::string category = "활";
public:
	Arrow() : Weapon() {
		name = "활";
		attack = 7;
		add_stats.setStr(2);
		add_stats.setDex(4);
	}
	Arrow(int attack, Stat& add_stats) : Weapon() {
		Weapon::name = "활";
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
	}
	Arrow(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	std::string getCategory() override { return Arrow::category; }

	int addAttack(std::shared_ptr<Weapon> enemys_weapon) override {
		if (enemys_weapon->getCategory() == "도끼" || enemys_weapon->getCategory() == "창") {
			std::cout << " -- 5의 추가 데미지를 입힙니다. -- " << std::endl;
			return 5;
		}
		if (enemys_weapon->getCategory() == "방패") {
			std::cout << " -- 활의 공격력이 5로 줄어듭니다. -- " << std::endl;
			return -2;
		}
		return 0;
	}
};

class Axe : public Weapon {
private:
	std::string category = "도끼";
public:
	Axe() : Weapon() {
		name = "도끼";
		attack = 15;
		add_stats.setStr(6);
	}
	Axe(int attack, Stat& add_stats) : Weapon() {
		Weapon::name = "도끼";
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
	}
	Axe(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	std::string getCategory() override { return Axe::category; }

	int addAttack(std::shared_ptr<Weapon> enemys_weapon) override {
		if (enemys_weapon->getCategory() == "활") {
			std::cout << " -- 7의 추가 데미지를 입힙니다. -- " << std::endl;
			return 7;
		}
		if (enemys_weapon->getCategory() == "방패") {
			std::cout << " -- 2의 추가 데미지를 입힙니다. -- " << std::endl;
			return 2;
		}
		return 0;
	}
};

class Spear : public Weapon {
private:
	std::string category = "창";
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

	std::string getCategory() override { return Spear::category; }

	int addAttack(std::shared_ptr<Weapon> enemys_weapon) override {
		if (enemys_weapon->getCategory() == "도끼") {
			std::cout << " -- 4의 추가 데미지를 입힙니다. -- " << std::endl;
			return 4;
		}
		if (enemys_weapon->getCategory() == "방패") {
			std::cout << " -- 2의 추가 데미지를 입힙니다. -- " << std::endl;
			return 2;
		}
		return 0;
	}
};

class Shield : public Weapon {
private:
	std::string category = "방패";
public:
	Shield() : Weapon() {
		name = "방패";
		attack = 3;
		add_stats.setDef(10);
		category = "방패";
	}
	Shield(int attack, Stat& add_stats) : Weapon() {
		Weapon::attack = attack;
		Weapon::add_stats = add_stats;
	}
	Shield(std::string name, int attack, Stat& add_stats) : Weapon(name, attack, add_stats) {}

	std::string getCategory() override { return category; }
};

class Unit {
protected:
	std::string name;
	int hp, total_attack;
	Stat stats;
	std::shared_ptr<Weapon> current_weapon;

public:
	Unit(std::string& name) :name(name) { }
	Unit(std::string& name, int hp, Stat& stats) : name(name), hp(hp), stats(stats) {  }
	Unit(std::string& name, int hp, Stat& stats, std::unique_ptr<Weapon> weapon) : name(name), hp(hp), stats(stats) { current_weapon = std::move(weapon); }
	std::string getName() { return name; }
	int getTotalAttack() { return total_attack; }
	int getHp() { return hp; }
	virtual std::shared_ptr<Weapon> getCurrentWeapon() {
		return current_weapon;
	}
	virtual void attackedDamage(int damage) {
		if (damage == 0) {
			return;
		}
		if (evasionAttack()) {
			std::cout << " -- " << name << "이(가) 공격을 회피하였습니다. --" << std::endl;
			return;
		}
		hp -= damage;
		std::cout << " -- " << name << "이(가) " << damage << " 데미지를 입었습니다. " << std::endl;
		hp += stats.getDef();
		std::cout << " -- " << name << "이(가) " << stats.getDef() << "만큼 방어했습니다. -- " << std::endl;
		std::cout << " -- " << name << " 남은 HP : " << hp << std::endl;
		if (isDead()) {
			std::cout<<" -- " << name << "이(가) 사망하였습니다."<<" -- "<<std::endl;
		}
	}

	virtual bool evasionAttack() {
		std::random_device rd;
		std::mt19937 gen(rd());
		if (stats.getDex() >= 5) {
			std::bernoulli_distribution dist(0.5);
			return dist(gen);
		}
		int evation_percent = stats.getDex() * 10;
		std::bernoulli_distribution dist(evation_percent / 100.0);
		return dist(gen);
	}

	virtual int attackDamage(Unit* enemy) {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 공격할 수 없습니다." << " -- " << std::endl;
			return 0;
		}
		std::cout << " -- " << name << "이(가)" << enemy->getName() << "를(을) 공격합니다." << " -- " << std::endl;
		return total_attack;
	}

	virtual void setWeapon(std::shared_ptr<Weapon> change_weapon) {	}
	virtual void updateTotalAttack() {
		total_attack = stats.getStr() * 2;
	}
	virtual void removeWeapon() {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 무기를 교체할 수 없습니다." << " -- " << std::endl;
			return;
		}
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
		if (isDead()) {
			std::cout << "-사망-" << std::endl;
		}
	}
};

class Monster : public Unit {
private:
	std::shared_ptr<Weapon> current_weapon;
public:
	Monster(std::string& name, int hp, Stat& stats) : Unit(name, hp, stats) { 
		updateTotalAttack();
	}
	Monster(std::string& name, int hp, Stat& stats, std::shared_ptr<Weapon> weapon) : Unit(name, hp, stats) {
		current_weapon = weapon;
		updateTotalAttack();
	}
	std::shared_ptr<Weapon> getCurrentWeapon() override {
		return current_weapon;
	}

	void setWeapon(std::shared_ptr<Weapon> change_weapon) override {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 무기를 교체할 수 없습니다." << " -- " << std::endl;
			return;
		}
		current_weapon = change_weapon;
		updateTotalAttack();
	}

	void removeWeapon() override{
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 무기를 교체할 수 없습니다." << " -- " << std::endl;
			return;
		}
		current_weapon = std::move(std::unique_ptr<Weapon>());
		updateTotalAttack();
	}

	void attackedDamage(int damage) override {
		if (damage == 0) {
			return;
		}
		if (evasionAttack()) {
			std::cout << " -- " << name << "이(가) 공격을 회피하였습니다. --" << std::endl;
			return;
		}

		int def = stats.getDef() + current_weapon->getAddStats()->getDef();
		std::cout << " -- " << name << "이(가) " << def << "만큼 방어했습니다. -- " << std::endl;
		damage -= def;
		std::cout << " -- " << name << "이(가) " << damage << " 데미지를 입었습니다. " << std::endl;
		hp -= damage;
		std::cout << " -- " << name << " 남은 HP : " << hp << std::endl;

		if (isDead()) {
			std::cout << " -- " << name << "이(가) 사망하였습니다." << " -- " << std::endl;
		}
	}

	bool evasionAttack() override {
		std::random_device rd;
		std::mt19937 gen(rd());
		if (stats.getDex() + current_weapon->getAddStats()->getDex() >= 5) {
			std::bernoulli_distribution dist(0.5);
			return dist(gen);
		}
		int evation_percent = (stats.getDex() + current_weapon->getAddStats()->getDex()) * 10;
		std::bernoulli_distribution dist(evation_percent / 100.0);
		return dist(gen);
	}

	int attackDamage(Unit* enemy) override {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 공격할 수 없습니다." << " -- " << std::endl;
			return 0;
		}
		std::cout << " -- " << name << "이(가)" << enemy->getName() << "를(을) 공격합니다." << " -- " << std::endl;
		std::shared_ptr<Weapon> enemys_weapon = enemy->getCurrentWeapon();
		int add_attack = current_weapon->addAttack(enemys_weapon);
		return total_attack + add_attack;
	}

	void updateTotalAttack() override {
		total_attack = (stats.getStr() + current_weapon->getAddStats()->getStr()) * 2 + current_weapon->getAttack();
	}

	void printStat() override {
		std::cout << " [" << name << "] " << std::endl;
		std::cout << "HP : " << hp << std::endl;
		std::cout << "힘 : " << stats.getStr() <<" (+" << current_weapon->getAddStats()->getStr()<<")" <<std::endl;
		std::cout << "민첩 : " << stats.getDex() <<" (+"<<current_weapon->getAddStats()->getDex()<<")"<< std::endl;
		std::cout << "방어 : " << stats.getDef() << " (+" << current_weapon->getAddStats()->getDef() << ")" << std::endl;
		std::cout << "무기 : " << current_weapon->getName() << "    무기 공격력 : " << current_weapon->getAttack() << std::endl;
		if (isDead()) {
			std::cout << "-사망-" << std::endl;
		}
	}
};

class Hero : public Unit {
private:
	std::shared_ptr<Weapon> current_weapon;
public:
	Hero(std::string& name, int hp, Stat& stats) : Unit(name, hp, stats) { 
		updateTotalAttack();
	}
	Hero(std::string& name, int hp, Stat& stats, std::shared_ptr<Weapon> weapon) : Unit(name, hp, stats) {
		current_weapon = weapon;
		updateTotalAttack();
	}
	std::shared_ptr<Weapon> getCurrentWeapon() override {
		return current_weapon;
	}
	void setWeapon(std::shared_ptr<Weapon> change_weapon) override {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 무기를 교체할 수 없습니다." << " -- " << std::endl;
			return;
		}
		current_weapon = change_weapon;
		updateTotalAttack();
	}

	void removeWeapon() override {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 무기를 해제할 수 없습니다." << " -- " << std::endl;
			return;
		}
		current_weapon = std::shared_ptr<Weapon>();
		updateTotalAttack();
	}

	void attackedDamage(int damage) override {
		if (damage == 0) {
			return;
		}
		if (evasionAttack()) {
			std::cout << " -- " << name << "이(가) 공격을 회피하였습니다. --" << std::endl;
			return;
		}
		
		int def = stats.getDef() + current_weapon->getAddStats()->getDef();
		std::cout << " -- " << name << "이(가) " << def << "만큼 방어했습니다. -- " << std::endl;
		damage -= def;
		std::cout << " -- " << name << "이(가) " << damage << " 데미지를 입었습니다. " << std::endl;
		hp -= damage;
		std::cout << " -- " << name << " 남은 HP : " << hp << std::endl;

		if (isDead()) {
			std::cout << " -- " << name << "이(가) 사망하였습니다." << " -- " << std::endl;
		}
	}

	bool evasionAttack() override {
		std::random_device rd;
		std::mt19937 gen(rd());
		if (stats.getDex() + current_weapon->getAddStats()->getDex() >= 5) {
			std::bernoulli_distribution dist(0.5);
			return dist(gen);
		}
		int evation_percent = (stats.getDex() + current_weapon->getAddStats()->getDex()) * 10;
		std::bernoulli_distribution dist(evation_percent / 100.0);
		return dist(gen);
	}

	int attackDamage(Unit* enemy) override {
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 공격할 수 없습니다." << " -- " << std::endl;
			return 0;
		}
		std::cout << " -- " << name << "이(가)" << enemy->getName() << "를(을) 공격합니다." << " -- " << std::endl;
		std::shared_ptr<Weapon> enemys_weapon = enemy->getCurrentWeapon();

		int add_attack = current_weapon->addAttack(enemys_weapon);
		return total_attack + add_attack;
	}

	void updateTotalAttack() override {
		total_attack = (stats.getStr() + current_weapon->getAddStats()->getStr()) * 2 + current_weapon->getAttack();
	}

	void printStat() override {
		std::cout << " [" << name << "] " << std::endl;
		std::cout << "HP : " << hp << std::endl;
		std::cout << "힘 : " << stats.getStr() << " (+" << current_weapon->getAddStats()->getStr() << ")" << std::endl;
		std::cout << "민첩 : " << stats.getDex() << " (+" << current_weapon->getAddStats()->getDex() << ")" << std::endl;
		std::cout << "방어 : " << stats.getDef() << " (+" << current_weapon->getAddStats()->getDef() << ")" << std::endl;
		std::cout << "무기 : " << current_weapon->getName() << "    무기 공격력 : " << current_weapon->getAttack() << std::endl;
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

	void addWeapon(std::shared_ptr<Weapon> weapon, int idx) {
		weapons[weapon->getName()] = weapon;
	}
	void createHero(std::string name, int hp, Stat stats) {
		std::cout << " -- " << "Hero를 생성하였습니다." << " -- " << std::endl;
		units.push_back(std::make_unique<Hero>(name, hp, stats, weapons["맨손"]));
	}
	void createHero(std::string name, int hp,Stat stats, std::string weaponname) {
		if (hasWeapon(weaponname)) {
			std::cout << " -- " << "Hero를(을) 생성하였습니다." << " -- " << std::endl;
			units.push_back(std::make_unique<Hero>(name, hp, stats, weapons[weaponname]));
			return;
		}
		std::cout << " -- " << weaponname << "이(가) 없습니다. 추가 해주세요." << " -- " << std::endl;
	}

	void createMonster(std::string name, int hp, Stat stats) {
		std::cout << " -- " << "Monster를(을) 생성하였습니다." << " -- " << std::endl;
		units.push_back(std::make_unique<Monster>(name, hp, stats, weapons["맨손"]));
	}
	void createMonster(std::string name, int hp, Stat stats, std::string weaponname) {
		if (hasWeapon(weaponname)) {
			std::cout << " -- " << "Monster를(을) 생성하였습니다." << " -- " << std::endl;
			units.push_back(std::make_unique<Monster>(name, hp, stats, weapons[weaponname]));
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
			unit->setWeapon(weapons[weaponname]);
			std::cout << " -- 무기 " << weaponname << " 를(을) 장착하였습니다"<< " -- " << std::endl;;
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
		unit->setWeapon(weapons["맨손"]);
		std::cout << " -- "<< unitname <<" 가 무기를 해제하였습니다" << " -- " << std::endl;;
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
		}return nullptr;
	}

	
};

int main() {
	RPG game = RPG();
	/*Weapon axe = Axe();
	Weapon spear = Spear();
	Weapon shield = Shield();
	Weapon arrow = Arrow();*/

	game.createHero("Hero", 100, Stat(2,2,2));
	game.findUnit("Hero")->printStat();
	game.changeWeapon("Hero","한손검");
	game.addWeapon(std::make_shared<One_hand_sword>(),0);
	game.addWeapon(std::make_shared<Arrow>(), 1);
	game.addWeapon(std::make_shared <Axe>(),2);
	game.addWeapon(std::make_shared <Spear>(),3);
	game.addWeapon(std::make_shared <Shield>(),4);
	game.changeWeapon("Hero", "한손검");
	game.findUnit("Hero")->printStat();
	game.changeWeapon("Hero", "도끼");
	game.findUnit("Hero")->printStat();

	game.createMonster("Monster1", 100, Stat(2, 2, 2), "활");
	game.findUnit("Monster1")->printStat();

	game.attackUnit("Hero", "Monster1");
	game.attackUnit("Hero", "Monster1");
	game.attackUnit("Hero", "Monster1");
	game.findUnit("Monster1")->printStat();
	game.attackUnit("Monster1", "Hero");
	
	game.createMonster("Monster2", 100, Stat(2, 2, 2), "방패");
	game.findUnit("Monster2")->printStat();
	game.attackUnit("Hero", "Monster2");
	//game.changeWeapon("Hero", "맨손");

}