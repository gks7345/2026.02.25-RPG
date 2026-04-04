#include "Unit.h"
#include "Skill.h"


Skill::Skill() {
	damage = 0;
	cost_mp = 0;
	cost_hp = 0;
	name = "없음";
}
std::string Skill::getName() { return name; }
int Skill::getCostMp() { return cost_mp; }
int Skill::getCostHp() { return cost_hp; }

//##################################################################################
Unit::Unit(std::string& name) :name(name) {}
Unit::Unit(std::string& name, int max_hp, int max_mp, const Stat& stats) : name(name), max_hp(max_hp), max_mp(max_mp), stats(stats) {
	current_hp = max_hp;
	current_mp = max_mp;
}
Unit::Unit(std::string& name, int max_hp, int max_mp, const Stat& stats, std::unique_ptr<Weapon> weapon) : name(name), max_hp(max_hp), max_mp(max_mp), stats(stats) {
	current_weapon = move(weapon);
	current_hp = max_hp;
	current_mp = max_mp;
}
std::string Unit::getName() { return name; }
int Unit::getCurrentHp() { return current_hp; }
int Unit::getMaxHp() { return max_hp; }
void Unit::setCurrentHp(int new_hp) {
	if (new_hp < 0) {
		current_hp = 0;
		return;
	}
	if (new_hp > max_hp) {
		current_hp = max_hp;
		return;
	}
	current_hp = new_hp;
}
int Unit::getCurrentMp() { return current_mp; }
void Unit::setCurrentMp(int new_mp) {
	if (new_mp < 0) {
		current_hp = 0;
		return;
	}
	if (new_mp > max_hp) {
		current_mp = max_mp;
		return;
	}
	current_mp = new_mp;
}

Category Unit::getCurrentWeaponCategory() {
	return current_weapon->getCategory();
}
void Unit::attackedDamage(int damage) {
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
	current_hp -= damage;
	std::cout << " -- " << name << "이(가) " << damage << " 데미지를 입었습니다. " << std::endl;
	std::cout << " -- " << name << " 남은 HP : " << current_hp << std::endl;

	if (isDead()) {
		std::cout << " -- " << name << "이(가) 사망하였습니다." << " -- " << std::endl;
	}
}

bool Unit::evasionAttack() {
	std::mt19937 gen(rd());
	if (stats.getDex() + current_weapon->getAddStats()->getDex() >= 5) {
		std::bernoulli_distribution dist(0.5);
		return dist(gen);
	}
	int evation_percent = (stats.getDex() + current_weapon->getAddStats()->getDex()) * 10;
	std::bernoulli_distribution dist(evation_percent / 100.0);
	return dist(gen);
}

int Unit::attackDamage(Unit* enemy) {
	if (isDead()) {
		std::cout << " -- " << name << "이(가) 이미 사망하여 공격할 수 없습니다." << " -- " << std::endl;
		return 0;
	}
	if (enemy->isDead()) {
		std::cout << " -- " << enemy->getName() << "이(가) 이미 사망하였습니다." << " -- " << std::endl;
		return 0;
	}
	std::cout << " -- " << name << "이(가)" << enemy->getName() << "를(을) 공격합니다." << " -- " << std::endl;
	Category enemys_weapon = enemy->getCurrentWeaponCategory();

	return getUnitAttack() + current_weapon->getWeaponDamage(enemys_weapon);
}

void Unit::setWeapon(std::unique_ptr<Weapon>&& change_weapon) {
	if (isDead()) {
		std::cout << " -- " << name << "이(가) 이미 사망하여 무기를 교체할 수 없습니다." << " -- " << std::endl;
		return;
	}
	current_weapon = move(change_weapon);
}
int Unit::getUnitAttack() {
	return stats.getStr() * 2;
}
bool Unit::isDead() {
	if (current_hp <= 0) {
		return true;
	}
	return false;
}

void Unit::addUnitSkill(std::unique_ptr<Skill> skill) {
	std::cout << " -- " << name << "이(가) " << skill->getName() << " 스킬을 배웁니다. --" << std::endl;
	unitskills.push_back(move(skill));
}

void Unit::activeSkill(std::string skill_name, Unit* target) {
	Skill* skill = findUnitSkill(skill_name);
	if (skill == nullptr) {
		std::cout << " -- " << name << "이(가) " << skill_name << "스킬을 배우지 않았습니다. -- " << std::endl;
		return;
	}
	if (isDead()) {
		std::cout << " -- " << name << "이(가) 이미 사망하여 스킬을 사용할 수 없습니다." << " -- " << std::endl;
		return;
	}
	if (target->isDead()) {
		std::cout << " -- 대상 유닛 " << target->getName() << "이(가) 이미 사망하였습니다." << " -- " << std::endl;
		return;
	}

	if (isValidCost(skill)) {
		skill->activeSkill(this, target);
		return;
	}
}

bool Unit::isValidCost(Skill* skill) {
	if (getCurrentMp() < skill->getCostMp() && skill->getCostMp() > 0) {
		std::cout << " -- MP가 부족하여 스킬을 사용할 수 없습니다. -- " << std::endl;
		return false;
	}
	if (getCurrentHp() < skill->getCostHp() && skill->getCostHp() > 0) {
		std::cout << " -- HP가 부족하여 스킬을 사용할 수 없습니다. -- " << std::endl;
		return false;
	}
	return true;
}

Skill* Unit::findUnitSkill(std::string skill_name) {
	for (auto& skill : unitskills) {
		if (skill->getName() == skill_name) {
			return skill.get();
		}
	}
	return nullptr;
}

void Unit::printStat() {
	std::cout << " [" << name << "] " << std::endl;
	std::cout << "HP : " << current_hp << " / " << max_hp << std::endl;
	std::cout << "MP : " << current_mp << " / " << max_mp << std::endl;
	std::cout << "힘 : " << stats.getStr() << std::endl;
	std::cout << "민첩 : " << stats.getDex() << std::endl;
	std::cout << "방어 : " << stats.getDef() << std::endl;
	std::cout << "무기 : " << current_weapon->getName() << "    무기 총 공격력 : " << current_weapon->getAttack() << std::endl;
	if (isDead()) {
		std::cout << "-사망-" << std::endl;
	}
}


//##################################################################################

Fireball::Fireball() {
	Skill::name = "Fireball";
	Skill::cost_hp = 0;
	Skill::cost_mp = 20;
	Skill::damage = 20;
}
void Fireball::activeSkill(Unit* caster, Unit* target) {
	if (caster->getName() == target->getName()) {
		std::cout << " -- 자신을 공격할 수 없습니다. -- " << std::endl;
		return;
	}

	std::cout << " -- " << caster->getName() << "이(가) " << target->getName() << "에게 " << name << "스킬을 사용합니다. -- " << std::endl;
	caster->setCurrentMp(caster->getCurrentMp() - cost_mp);
	std::cout << " -- MP " << cost_mp << "가 사용됩니다. --" << std::endl;
	target->attackedDamage(damage);
}
std::unique_ptr<Skill> Fireball::clone() {
	return std::make_unique<Fireball>(*this);
}



PowerStrike::PowerStrike() {
	Skill::name = "PowerStrike";
	Skill::cost_hp = 15;
	Skill::cost_mp = 20;
	Skill::damage = 30;
}
void PowerStrike::activeSkill(Unit* caster, Unit* target) {
	if (caster->getName() == target->getName()) {
		std::cout << " -- 자신을 공격할 수 없습니다. -- " << std::endl;
		return;
	}

	std::cout << " -- " << caster->getName() << "이(가) " << target->getName() << "에게 " << name << "스킬을 사용합니다. -- " << std::endl;
	caster->setCurrentHp(caster->getCurrentHp() - cost_hp);
	caster->setCurrentMp(caster->getCurrentMp() - cost_mp);
	std::cout << " -- HP " << cost_hp << " , MP " << cost_mp << "가 소모됩니다. --" << std::endl;

	if (target->getCurrentWeaponCategory() == Category::shield) {
		std::cout << " -- 스킬 위력이 30에서 40으로 증가 합니다. --" << std::endl;
		target->attackedDamage(40);
		return;
	}
	target->attackedDamage(damage);
}
std::unique_ptr<Skill> PowerStrike::clone() {
	return std::make_unique<PowerStrike>(*this);
}


ArrowShot::ArrowShot() {
	Skill::name = "ArrowShot";
	Skill::cost_hp = 0;
	Skill::cost_mp = 15;
	Skill::damage = 25;
}
void ArrowShot::activeSkill(Unit* caster, Unit* target) {
	if (caster->getName() == target->getName()) {
		std::cout << " -- 자신을 공격할 수 없습니다. -- " << std::endl;
		return;
	}

	std::cout << " -- " << caster->getName() << "이(가) " << target->getName() << "에게 " << name << "스킬을 사용합니다. -- " << std::endl;
	caster->setCurrentMp(caster->getCurrentMp() - cost_mp);
	std::cout << " -- MP " << cost_mp << "가 소모됩니다. --" << std::endl;

	if (target->getCurrentWeaponCategory() == Category::shield) {
		std::cout << " -- 스킬 위력이 25에서 10으로 감소 합니다. --" << std::endl;
		target->attackedDamage(10);
		return;
	}
	target->attackedDamage(damage);
}
std::unique_ptr<Skill> ArrowShot::clone() {
	return std::make_unique<ArrowShot>(*this);
}


Heal::Heal() {
	Skill::name = "Heal";
	Skill::cost_hp = 0;
	Skill::cost_mp = 30;
	Skill::damage = 0;
	heal_hp = 40;
}
void Heal::activeSkill(Unit* caster, Unit* target) {
	int max_hp = target->getMaxHp();
	int current_hp = target->getCurrentHp();
	if (target->getCurrentHp() == max_hp) {
		std::cout << " -- 대상의 HP가 가득 차 있습니다. --" << std::endl;
		return;
	}

	std::cout << " -- MP " << cost_mp << "가 소모됩니다. --" << std::endl;
	caster->setCurrentMp(caster->getCurrentMp() - cost_mp);

	std::cout << " -- 유닛 " << target->getName() << "이(가) 체력을 40 회복합니다. -- " << std::endl;
	target->setCurrentHp(current_hp + 40);
}
std::unique_ptr<Skill> Heal::clone() {
	return std::make_unique<Heal>(*this);
}