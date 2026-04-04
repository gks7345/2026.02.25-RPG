#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include "Weapon.h"
#include "Skill.h"
#include "Unit.h"


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
	void createUnit(std::string name, int hp,int mp, const Stat& stats) {
		std::cout << " -- " << name <<"를(을) 생성하였습니다." << " -- " << std::endl;
		units.push_back(std::make_unique<Unit>(name, hp,mp, stats, weapons["맨손"]-> clone()));
	}
	void createUnit(std::string name, int hp, int mp, const Stat& stats, std::string weaponname) {
		if (hasWeapon(weaponname)) {
			std::cout << " -- " << name <<"를(을) 생성하였습니다." << " -- " << std::endl;
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
		unit->setWeapon(weapons["맨손"]->clone());
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
		Unit* unit = findUnit(name);
		if (unit == nullptr) {
			return;
		}
		unit->printStat();
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

	void activeSkillOfUnit(std::string castername,std::string targetname, std::string skillname) {
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

	game.createUnit("Hero", 100, 200, Stat(2,2,2));
	game.printUnit("Hero");
	game.changeWeapon("Hero","한손검");
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