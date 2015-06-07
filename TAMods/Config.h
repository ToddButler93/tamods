#pragma once

#include <fstream>
#include <string>
#include <regex>
#include <map>
#include "Loadout.h"
#include "Utils.h"
#include "Data.h"

class Config
{
public:
	Config();
	~Config();

	void reset();
	void parseFile();
	bool parseLine(const std::string &str);

private:
	int _getWeaponID(const std::string &class_name, const std::string &str);

public:
	int damageNumbersLimit;
	bool showErrorNotifications;
	bool showWeapon;
	bool showCrosshair;
	float crosshairScale;
	Loadout *loadouts[9][9];
	std::map<int, std::pair<int, int>> crosshairs;

	// Damage number customization
	float damageNumbersOffsetX;
	float damageNumbersOffsetY;
	float damageNumbersScale;

	// Damage number / chain count streaming
	bool showDamageNumberStream;
	bool showChainBulletHitCount;
	double damageNumberStreamingResetTime;
	unsigned long lastDamageNumberShowEventTime;
	int damageNumberStreamValue;
	int damageNumberStreamCount;
};
