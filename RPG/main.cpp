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

class Unit;

class Skill {
protected:
	std::string name;
	int damage;
	int cost_mp;
	int cost_hp;
public:
	Skill() {
		damage = 0;
		cost_mp = 0;
		cost_hp = 0;
		name = "없음";
	}
	std::string getName() { return name; }
	virtual void activeSkill(Unit* caster, Unit* target) = 0;
	int getCostMp() { return cost_mp; }
	int getCostHp() { return cost_hp; }
	virtual std::unique_ptr<Skill> clone() = 0;
};

class Unit {
private:
	std::string name;
	int hp, mp;
	int max_hp, max_mp;
	Stat stats;
	std::unique_ptr<Weapon> current_weapon;
	std::random_device rd;
	std::vector<std::unique_ptr<Skill>> unitskills;

public:
	Unit(std::string& name) :name(name) {}
	Unit(std::string& name, int max_hp, int max_mp, Stat& stats) : name(name), max_hp(max_hp), max_mp(max_mp), stats(stats) {
		hp = max_hp;
		mp = max_mp;
	}
	Unit(std::string& name, int max_hp, int max_mp, Stat& stats, std::unique_ptr<Weapon> weapon) : name(name), max_hp(max_hp), max_mp(max_mp), stats(stats) {
		current_weapon = move(weapon);
		hp = max_hp;
		mp = max_mp;
	}
	std::string getName() { return name; }
	int getHp() { return hp; }
	int getMaxHp() { return max_hp; }
	void setHp(int new_hp) { hp = new_hp; }
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

	void addUnitSkill(std::unique_ptr<Skill> skill) {
		std::cout << " -- " << name << "이(가) " << skill->getName() << " 스킬을 배웁니다. --" << std::endl;
		unitskills.push_back(move(skill));
	}

	void activeSkill(std::string skill_name, Unit* target) {
		Skill* skill = findUnitSkill(skill_name);
		if (skill == nullptr) {
			std::cout << " -- " << name << "이(가) " << skill_name << "스킬을 배우지 않았습니다. -- " << std::endl;
			return;
		}
		if (isDead()) {
			std::cout << " -- " << name << "이(가) 이미 사망하여 스킬을 사용할 수 없습니다." << " -- " << std::endl;
			return;
		}

		int cost_hp = skill->getCostHp();
		int cost_mp = skill->getCostMp();

		if (hp < cost_hp && mp < cost_mp) {
			std::cout << " -- HP와 MP가 부족하여 스킬을 사용할 수 없습니다. -- " << std::endl;;
			return;
		}
		if (hp < cost_hp && cost_hp > 0) {
			std::cout << " -- HP가 부족하여 스킬을 사용할 수 없습니다. -- " << std::endl;
			return;
		}
		if (mp < cost_mp && cost_mp > 0) {
			std::cout << " -- MP가 부족하여 스킬을 사용할 수 없습니다. -- " << std::endl;
			return;
		}

		std::cout << " -- " << name << "이(가) " << target->getName() << "에게 " << skill_name << "스킬을 사용합니다. -- " << std::endl;
		mp -= cost_mp;
		hp -= cost_hp;
		skill->activeSkill(this, target);
	}

	Skill* findUnitSkill(std::string skill_name) {
		for (auto& skill : unitskills) {
			if (skill->getName() == skill_name) {
				return skill.get();
			}
		}
		return nullptr;
	}

	virtual void printStat() {
		std::cout << " [" << name << "] " << std::endl;
		std::cout << "HP : " << hp << " / " << max_hp << std::endl;
		std::cout << "MP : " << mp << " / " << max_mp << std::endl;
		std::cout << "힘 : " << stats.getStr() << std::endl;
		std::cout << "민첩 : " << stats.getDex() << std::endl;
		std::cout << "방어 : " << stats.getDef() << std::endl;
		std::cout << "무기 : " << current_weapon->getName() << "    무기 총 공격력 : " << current_weapon->getAttack() << std::endl;
		if (isDead()) {
			std::cout << "-사망-" << std::endl;
		}
	}
};



class Fireball : public Skill {
public:
	Fireball() {
		Skill::name = "Fireball";
		Skill::cost_hp = 0;
		Skill::cost_mp = 10;
		Skill::damage = 20;
	}
	void activeSkill(Unit* caster, Unit* target) override {
		if (caster->getName() == target->getName()) {
			std::cout << " -- 자신을 공격할 수 없습니다. -- " << std::endl;
			return;
		}
		if (target->isDead()) {
			std::cout << " -- " << target->getName() << "이(가) 이미 사망하였습니다." << " -- " << std::endl;
			return;
		}

		std::cout << " -- MP " << cost_mp << "가 사용됩니다. --" << std::endl;
		target->attackedDamage(damage);
	}

	std::unique_ptr<Skill> clone() override {
		return std::make_unique<Fireball>(*this);
	}

};

class PowerStrike : public Skill {
public:
	PowerStrike() {
		Skill::name = "PowerStrike";
		Skill::cost_hp = 15;
		Skill::cost_mp = 20;
		Skill::damage = 30;
	}
	void activeSkill(Unit* caster, Unit* target) override {
		if (caster->getName() == target->getName()) {
			std::cout << " -- 자신을 공격할 수 없습니다. -- " << std::endl;
			return;
		}
		if (target->isDead()) {
			std::cout << " -- " << target->getName() << "이(가) 이미 사망하였습니다." << " -- " << std::endl;
			return;
		}

		if (target->getCurrentWeapon()->get()->getCategory() == Category::shield) {
			std::cout << " -- 스킬 위력이 30에서 40으로 증가 합니다. --" << std::endl;
			target->attackedDamage(40);
			return;
		}
		std::cout << " -- HP " << cost_hp << "가 사용됩니다. --" << std::endl;
		std::cout << " -- MP " << cost_mp << "가 사용됩니다. --" << std::endl;
		target->attackedDamage(damage);
	}
	virtual std::unique_ptr<Skill> clone() {
		return std::make_unique<PowerStrike>(*this);
	}
};

class ArrowShot : public Skill {
public:
	ArrowShot() {
		Skill::name = "ArrowShot";
		Skill::cost_hp = 0;
		Skill::cost_mp = 15;
		Skill::damage = 25;
	}
	void activeSkill(Unit* caster, Unit* target) override {
		if (caster->getName() == target->getName()) {
			std::cout << " -- 자신을 공격할 수 없습니다. -- " << std::endl;
			return;
		}
		if (target->isDead()) {
			std::cout << " -- " << target->getName() << "이(가) 이미 사망하였습니다." << " -- " << std::endl;
			return;
		}

		if (target->getCurrentWeapon()->get()->getCategory() == Category::shield) {
			std::cout << " -- 스킬 위력이 25에서 10으로 감소 합니다. --" << std::endl;
			target->attackedDamage(10);
			return;
		}
		std::cout << " -- MP " << cost_mp << "가 사용됩니다. --" << std::endl;
		target->attackedDamage(damage);
	}
	std::unique_ptr<Skill> clone() override {
		return std::make_unique<ArrowShot>(*this);
	}
};

class Heal : public Skill {
private:
	int heal_hp;
public:
	Heal() {
		Skill::name = "Heal";
		Skill::cost_hp = 0;
		Skill::cost_mp = 30;
		Skill::damage = 0;
		heal_hp = 40;
	}
	void activeSkill(Unit* caster, Unit* target) override {
		if (caster->isDead()) {
			std::cout << " -- 시전 유닛 " << caster->getName() << "이(가) 이미 사망하였습니다." << " -- " << std::endl;
			return;
		}

		int max_hp = target->getMaxHp();
		int current_hp = target->getHp();
		if (target->getHp() == max_hp) {
			std::cout << " -- 대상의 HP가 가득 차 있습니다. --" << std::endl;
			return;
		}
		std::cout << " -- MP " << cost_mp << "가 사용됩니다. --" << std::endl;
		std::cout << " -- 유닛 " << target->getName() << "이(가) 체력을 40 회복합니다. -- " << std::endl;
		if (target->getHp() + heal_hp > max_hp) {
			target->setHp(max_hp);
			return;
		}
		target->setHp(current_hp + 40);
	}
	std::unique_ptr<Skill> clone() override {
		return std::make_unique<Heal>(*this);
	}
};

class RPG {
private:
	std::vector<std::unique_ptr<Unit>> units;
	//std::map<std::string, std::unique_ptr<Weapon>> weapons;
	std::map<std::string, std::shared_ptr<Weapon>> weapons;
	std::vector<std::unique_ptr<Skill>> skills;

	//category categorys;
public:
	RPG() {
		//Weapon no_weapon = Weapon();
		weapons["맨손"] = std::make_shared<Weapon>();
		skills.push_back(std::make_unique<Fireball>());
		skills.push_back(std::make_unique<PowerStrike>());
		skills.push_back(std::make_unique<ArrowShot>());
		skills.push_back(std::make_unique<Heal>());
	}

	void addWeapon(std::shared_ptr<Weapon> weapon) {
		weapons[weapon->getName()] = weapon;
	}
	void createUnit(std::string name, int hp, int mp, Stat stats) {
		std::cout << " -- " << name << "를(을) 생성하였습니다." << " -- " << std::endl;
		units.push_back(std::make_unique<Unit>(name, hp, mp, stats, weapons["맨손"]->clone()));
	}
	void createUnit(std::string name, int hp, int mp, Stat stats, std::string weaponname) {
		if (hasWeapon(weaponname)) {
			std::cout << " -- " << name << "를(을) 생성하였습니다." << " -- " << std::endl;
			units.push_back(std::make_unique<Unit>(name, hp, mp, stats, weapons[weaponname]->clone()));
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
			std::cout << " -- 유닛 " << unitname << "이(가) 없습니다." << " -- " << std::endl;
			return;
		}
		if (enemy == nullptr) {
			std::cout << " -- 유닛 " << enemyname << "이(가) 없습니다." << " -- " << std::endl;
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

	void addSkillToUnit(std::string nunitname, std::string skillname) {
		Skill* skill = findSkill(skillname);
		Unit* unit = findUnit(nunitname);
		if (skill == nullptr) {
			std::cout << " -- 스킬 " << skillname << "이(가) 존재하지 않습니다. -- " << std::endl;
			return;
		}
		if (unit == nullptr) {
			std::cout << " -- 유닛 " << nunitname << "이(가) 없습니다. -- " << std::endl;
			return;
		}
		unit->addUnitSkill(skill->clone());
	}

	Skill* findSkill(std::string skillname) {
		for (auto& skill : skills) {
			if (skill->getName() == skillname) {
				return skill.get();
			}
		}
		return nullptr;
	}

	void activeSkillOfUnit(std::string castername, std::string targetname, std::string skillname) {
		Skill* skill = findSkill(skillname);
		Unit* caster = findUnit(castername);
		Unit* target = findUnit(targetname);
		if (skill == nullptr) {
			std::cout << " -- 스킬 " << skillname << "이(가) 존재하지 않습니다. -- " << std::endl;
			return;
		}
		if (caster == nullptr) {
			std::cout << " -- 시전 유닛 " << castername << "이(가) 없습니다. -- " << std::endl;
			return;
		}
		if (target == nullptr) {
			std::cout << " -- 대상 유닛 " << targetname << "이(가) 없습니다. -- " << std::endl;
			return;
		}

		caster->activeSkill(skillname, target);
	}
};

int main() {
	RPG game = RPG();
	/*Weapon axe = Axe();
	Weapon spear = Spear();
	Weapon shield = Shield();
	Weapon arrow = Arrow();*/

	game.createUnit("Hero", 100, 200, Stat(2, 2, 2));
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

	game.createUnit("Monster1", 100, 100, Stat(2, 2, 2), "활");
	game.printUnit("Monster1");

	game.attackUnit("Hero", "Monster1");
	game.attackUnit("Hero", "Monster1");
	game.attackUnit("Hero", "Monster1");
	game.printUnit("Monster1");
	game.attackUnit("Monster1", "Hero");

	game.createUnit("Monster2", 100, 100, Stat(2, 2, 2), "방패");
	game.printUnit("Monster2");
	game.attackUnit("Hero", "Monster2");


	//game.printUnit("Hero");
	game.addSkillToUnit("Hero", "Heal");
	game.addSkillToUnit("Hero", "PowerStrike");
	game.activeSkillOfUnit("Hero", "Monster2", "PowerStrike");
	game.printUnit("Monster2");
	game.activeSkillOfUnit("Hero", "Monster2", "Heal");
	game.printUnit("Monster2");
	game.activeSkillOfUnit("Hero", "Monster2", "Heal");
	game.activeSkillOfUnit("Hero", "Monster2", "Heal");
	//game.changeWeapon("Hero", "맨손");

}