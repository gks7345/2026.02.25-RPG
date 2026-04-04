#pragma once

class Stat {
private:
	int str;
	int dex;
	int def;
public:
	Stat();
	Stat(int str, int dex, int def);
	int getStr();
	int getDex();
	int getDef();
	void setStr(int str);
	void setDex(int dex);
	void setDef(int def);
};
