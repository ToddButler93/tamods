#pragma once

#include <mutex>
#include <sstream>
#include <map>

#include <nlohmann/json.hpp>

#include "SdkHeaders.h"
#include "Logger.h"

using json = nlohmann::json;

namespace ModdedMenuData {

	class GameClass {
	private:
		std::map<int, std::vector<int> > data;
	public:
		GameClass();

		void add_item(int equip_point, int item_id);
		void clear();

		std::vector<int> get_equipment(int equip_point);
	};

	class MenuData {
	private:
		std::mutex menuDataMutex;
		std::string timestamp = "";
		std::map<int, GameClass> data;
	public:
		MenuData();

		void process_menudata_message(int class_id, std::string kind, std::string category, int item_id, std::string msg_timestamp);
		
		GameClass get_class(int class_id);
	};

}

extern ModdedMenuData::MenuData g_ModdedMenuData;