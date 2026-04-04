#include "Stat.h"

Stat::Stat() {
	str = 0;
	dex = 0;
	def = 0;
}
Stat::Stat(int str, int dex, int def) :str(str), dex(dex), def(def) {}

int Stat::getStr() { return str; }
int Stat::getDex() { return dex; }
int Stat::getDef() { return def; }
void Stat::setStr(int str) { Stat::str = str; }
void Stat::setDex(int dex) { Stat::dex = dex; }
void Stat::setDef(int def) { Stat::def = def; }