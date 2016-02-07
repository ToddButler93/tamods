#include "Mods.h"

bool toggleBaseTurret_cb(UObject *Object)
{
	if (Object->IsA(ATrBaseTurret_BloodEagle::StaticClass()))
	{
		ATrBaseTurret_BloodEagle *turret = (ATrBaseTurret_BloodEagle*)Object;
		turret->m_bEnabled = turret->m_bEnabled == 0 ? 1 : 0;
	}
	else if (Object->IsA(ATrBaseTurret_DiamondSword::StaticClass()))
	{
		ATrBaseTurret_DiamondSword *turret = (ATrBaseTurret_DiamondSword*)Object;
		turret->m_bEnabled = turret->m_bEnabled == 0 ? 1 : 0;
	}
	return false;
}

bool togglePower_cb(UObject *Object)
{
	if (Object && Object->IsA(ATrPowerGenerator::StaticClass()))
	{
		ATrPowerGenerator *gen = (ATrPowerGenerator *)Object;

		bool isPowered = gen->r_bIsPowered != 0;
		gen->UpdateGeneratorPower(isPowered ? 0 : 1);

		// Restore power for all stations and turrets
		if (isPowered)
		{
			for (int i = 0; i < gen->m_PoweredObjectives.Count; i++)
			{
				if (gen->m_PoweredObjectives.Data[i]->IsA(ATrStation::StaticClass()))
					((ATrStation *)gen->m_PoweredObjectives.Data[i])->SetPowered(1);
				else if (gen->m_PoweredObjectives.Data[i]->IsA(ATrDeployable_BaseTurret::StaticClass()))
					((ATrDeployable_BaseTurret *)gen->m_PoweredObjectives.Data[i])->SetPowered(1);
			}
		}
	}
	return false;
}

void toggleTurrets()
{
	Utils::FindObjects("^TrBaseTurret_(BloodEagle|DiamondSword)", &toggleBaseTurret_cb);
}

void togglePower()
{
	Utils::FindObjects("^TrPowerGenerator_(BloodEagle|DiamondSword) TheWorld.PersistentLevel.TrPowerGenerator_", &togglePower_cb);
}

void returnFlags()
{
	if (!Utils::tr_pc || !Utils::tr_pc->WorldInfo)
		return;

	AGameInfo *gi = Utils::tr_pc->WorldInfo->Game;

	// is there a better way get the current gametype?
	if (gi && gi->IsA(ATrGame_TRCTF::StaticClass()))
	{
		for (int i = 0; i < 2; i++)
		{
			FName state = ((ATrGame_TRCTF *)gi)->m_Flags[i]->GetStateName();

			if (state == FName("Held"))
			{
				((ATrGame_TRCTF *)gi)->m_Flags[i]->eventDrop(NULL, false);
				((ATrGame_TRCTF *)gi)->m_Flags[i]->SendHome(NULL);
			}
			else if (state == FName("Dropped"))
				((ATrGame_TRCTF *)gi)->m_Flags[i]->SendHome(NULL);
		}
	}
}

int matched;

bool printObjectName(UObject *Object)
{
	Utils::printConsole(Object->GetFullName());
	matched++;

	return false;
}

namespace consoleHelpText
{
	std::string general = "\n"
		"General commands:\n"
		" /lua <command>\n"
		"   Executes a lua function\n"
		" /reload config\n"
		"   Reloads your TAMods configs (Alias: /rc)\n"
		" /reload sounds\n"
		"   Reloads all your custom sounds (Alias: /rs)\n"
		" /players\n"
		"   Print all players with their corresponding PlayerID (Alias: /list /playerlist)\n"
		" /kickvoteid <PlayerID>\n"
		"   Initiate a kick vote by PlayerID\n"
		" /stopwatch\n"
		"   Toggles the stopwatch on and off (Alias: /sw)\n"
		" /stopwatch start\n"
		"   Starts/restarts the stopwatch\n"
		" /stopwatch stop\n"
		"   Stops the stopwatch\n";
	std::string roammap = "\n"
		"Roaming map commands:\n"
		" /toggle turrets\n"
		"   Toggles base turrets on and off (Alias: /turrets)\n"
		" /toggle power\n"
		"   Toggles generator power on and off (Alias: /power)\n"
		" /returnflags\n"
		"   Returns all loose flags back to base (Alias: /flags)\n";
	std::string state = "\n"
		"State and location saving commands:\n"
		" /state save [slot number]\n"
		"   Saves your current location to the specified slot number. Without a slot number, #1 will be used (Alias: /save)\n"
		" /state tp [slot number]\n"
		"   Teleports you to a saved point and restores health and ammo. Without a slot number, #1 will be used (Alias: /tp)\n"
		" /state recall [slot number]\n"
		"   Recalls a saved point which includes velocity, health etc. Without a slot number, #1 will be used (Alias: /recall)\n"
		" /state spawns\n"
		"   Sets the saved state locations to your teams spawn points (Alias: /spawns)\n"
		" /state reset\n"
		"   Resets all saved state points\n";
	std::string route = "\n"
		"Route commands:\n"
		" /route rec\n"
		"   Toggles route recording on and off (Alias: /rec)\n"
		" /route rec start\n"
		"   Starts route recording\n"
		" /route rec stop\n"
		"   Stops route recording\n"
		" /route replay\n"
		"   Toggles route replaying on and off (Alias: /replay)\n"
		" /route replay start [start time]\n"
		"   Starts route replay at the beginning or at 'start time'\n"
		" /route replay stop\n"
		"   Stops the route replay\n"
		" /route bot [on|off]\n"
		"   Sets or toggles if a bot should be used for the route replay\n"
		" /route reset\n"
		"   Stops recording and resets the currently recorded route\n"
		" /route save <description>\n"
		"   Saves the currently recorded route to a file\n"
		" /route load <number>\n"
		"   Loads a route file by number. To list all routes with their numbers, use '/route list'\n"
		" /route find <search string>\n"
		"   Searches through the filenames of all recorded routes and lists the matches\n"
		" /route list\n"
		"   Lists all routes (Alias: /routes)\n"
		" /route all\n"
		"   Same as '/route list'\n";
}

static bool execConsoleCommand(const std::wstring &line)
{
	std::wstring linelower = line;
	std::transform(line.begin(), line.end(), linelower.begin(), ::tolower);

	/****** Redirect to TrChatConsole ******/

	// This is necessary because I run all non-custom console commands through TrPC->ConsoleCommand
	//  and TrPC doesn't have all the console commands of TrChatConsoleCommands
	if (Utils::tr_pc && Utils::tr_pc->m_PlayerCommands)
	{
		if ((linelower.substr(0, 5) == L"/mute") ||
			(linelower.substr(0, 7) == L"/unmute") ||
			(linelower.substr(0, 9) == L"/votekick") ||
			(linelower.substr(0, 7) == L"/report") ||
			(linelower.substr(0, 5) == L"/tell") ||
			(linelower.substr(0, 3) == L"/sc"))
		{
			std::wstring command = std::wstring(line.begin() + 1, line.end());
			wchar_t* wch = (wchar_t *)command.c_str();
			Utils::tr_pc->m_PlayerCommands->ChatConsoleCommand(wch);
			return true;
		}
	}
	/****** General commands ******/
	if (linelower.substr(0, 5) == L"/help")
	{
		Utils::printConsole(consoleHelpText::general);
		Utils::printConsole(consoleHelpText::roammap);
		Utils::printConsole(consoleHelpText::state);
		Utils::printConsole(consoleHelpText::route);
		return true;
	}
	else if (line.size() > 5 && linelower.substr(0, 5) == L"/lua ")
	{
		std::string luastr = std::string(line.begin() + 5, line.end());
		Utils::printConsole("lua> " + luastr);
		if (luastr[0] == '=')
			luastr.replace(0, 1, "return ");
		g_config.lua.doString(luastr);
		return true;
	}
	else if (linelower == L"/reload config" || linelower == L"/rc")
	{
		g_config.parseFile();
		return true;
	}
	else if (linelower == L"/reload sounds" || linelower == L"/rs")
	{
		g_config.reloadSounds();
		return true;
	}
	else if (linelower == L"/players" || linelower == L"/list" || linelower == L"/playerlist")
	{
		if (Utils::tr_pc && Utils::tr_pc->WorldInfo && Utils::tr_pc->WorldInfo->GRI)
		{
			ATrGameReplicationInfo *gri = (ATrGameReplicationInfo *)Utils::tr_pc->WorldInfo->GRI;

			for (int i = 0; i < gri->PRIArray.Count; i++)
				Utils::printConsole(std::to_string(gri->PRIArray.GetStd(i)->PlayerID) + ": " + Utils::f2std(gri->PRIArray.GetStd(i)->PlayerName));
		}
		return true;
	}
	else if (linelower.substr(0, 12) == L"/kickvoteid ")
	{
		std::stringstream s(std::string(line.begin() + 12, line.end()));
		int playerId;
		s >> playerId;

		if (s && playerId)
		{
			if (Utils::tr_pc && Utils::tr_pc->WorldInfo && Utils::tr_pc->WorldInfo->GRI)
			{
				ATrGameReplicationInfo *gri = (ATrGameReplicationInfo *)Utils::tr_pc->WorldInfo->GRI;

				for (int i = 0; i < gri->PRIArray.Count; i++)
				{
					if (gri->PRIArray.GetStd(i)->PlayerID == playerId)
					{
						Utils::printConsole("Trying to kick vote " + Utils::f2std(gri->PRIArray.GetStd(i)->PlayerName));

						Utils::tr_pc->RequestKickVote(gri->PRIArray.GetStd(i)->PlayerName);

						return true;
					}
				}
				Utils::printConsole("No player found with that ID");
			}
		}
		else
			Utils::printConsole("Error: Enter a valid number");

		return true;
	}
	else if (line.size() > 13 && linelower.substr(0, 13) == L"/findobjects ")
	{
		matched = 0;
		std::string needle = std::string(line.begin() + 13, line.end());
		Utils::FindObjects(needle, &printObjectName);
		Utils::console("%d objects matched", matched);
		return true;
	}
	/****** State saving ******/
	else if (linelower == L"/stopwatch" || linelower == L"/sw")
	{
		stopwatch();
		return true;
	}
	else if (linelower == L"/stopwatch start")
	{
		stopwatchStart();
		return true;
	}
	else if (linelower == L"/stopwatch stop")
	{
		stopwatchStop();
		return true;
	}
	// Command to save the current player state (location, velocity etc.)
	else if (linelower.substr(0, 11) == L"/state save" || linelower.substr(0, 5) == L"/save")
	{
		unsigned char n = linelower.substr(0, 11) == L"/state save" ? 12 : 6;
		// Without a slot number we just use slot 1
		savesSaveTo(line.size() > n ? line[n] - '0' : 1);

		return true;
	}
	// Command to teleport to a saved location
	else if (linelower.substr(0, 9) == L"/state tp" || linelower.substr(0, 3) == L"/tp")
	{
		unsigned char n = linelower.substr(0, 9) == L"/state tp" ? 10 : 4;
		// Without a slot number we just use slot 1
		savesTpTo(line.size() > n ? line[n] - '0' : 1);
		return true;
	}
	// Command to recall a full player state
	else if (linelower.substr(0, 13) == L"/state recall" || linelower.substr(0, 7) == L"/recall")
	{
		unsigned char n = linelower.substr(0, 13) == L"/state recall" ? 14 : 8;
		// Without a slot number we just use slot 1
		savesRecallTo(line.size() > n ? line[n] - '0' : 1);
		return true;
	}
	else if (linelower == L"/state spawns" || linelower == L"/spawns")
	{
		savesToSpawns();
		return true;
	}
	else if (linelower == L"/state reset")
	{
		savesReset();
		return true;
	}
	else if (linelower.substr(0, 6) == L"/state")
	{
		Utils::printConsole(consoleHelpText::state);
		return true;
	}
	/****** Route recording ******/
	else if (linelower == L"/route rec" || linelower == L"/rec")
	{
		routeRec();
		return true;
	}
	else if (linelower == L"/route rec start")
	{
		routeStartRec();
		return true;
	}
	else if (linelower == L"/route rec stop")
	{
		routeStopRec();
		return true;
	}
	else if (linelower == L"/route replay" || linelower == L"/replay")
	{
		routeReplay();
		return true;
	}
	else if (linelower == L"/route replay start")
	{
		routeStartReplay(0);
		return true;
	}
	else if (linelower.substr(0, 20) == L"/route replay start ")
	{
		std::stringstream s(std::string(line.begin() + 20, line.end()));
		float start;
		s >> start;

		if (s && start >= 0.0f)
			routeStartReplay(start);
		else
			Utils::console("Error: You have to enter a number");
		return true;
	}
	else if (linelower == L"/route replay stop")
	{
		routeStopReplay();
		return true;
	}
	else if (linelower.substr(0, 10) == L"/route bot")
	{
		if (linelower.substr(10, 13) == L" on")
			routeEnableBot(true);
		else if (linelower.substr(10, 14) == L" off")
			routeEnableBot(false);
		else if (line.length() == 10)
		{
			routeEnableBot(!g_config.routeBotReplay);
			if (g_config.routeBotReplay)
				Utils::printConsole("Bot replay is now on");
			else
				Utils::printConsole("Bot replay is now off");
		}
		else
			Utils::printConsole(consoleHelpText::route);
		return true;
	}
	else if (linelower == L"/route reset")
	{
		routeReset();
		return true;
	}
	else if (linelower.substr(0, 12) == L"/route save ")
	{
		if (line.size() > 12)
		{
			std::string desc = std::string(line.begin() + 12, line.end());
			routeSaveFile(desc);
		}
		else
			Utils::console("Error: You have to enter a description");
		return true;
	}
	else if (linelower.substr(0, 12) == L"/route load ")
	{
		if (line.size() > 12)
		{
			std::stringstream s(std::string(line.begin() + 12, line.end()));
			unsigned int n;
			s >> n;

			if (s && n >= 0)
				routeLoadFile(n);
			else
				Utils::console("Error: You have to enter a number");
		}
		else
			Utils::console("Error: You have to enter a number");
		return true;
	}
	else if (linelower.substr(0, 12) == L"/route find ")
	{
		if (line.size() > 12)
		{
			std::string needle = std::string(line.begin() + 12, line.end());
			routeFind(needle);
		}
		else
			Utils::console("Error: You have to enter a search string");
		return true;
	}
	else if (linelower == L"/route list" || linelower == L"/route all" || linelower == L"/routes")
	{
		routeListAll();
		return true;
	}
	else if (linelower.substr(0, 6) == L"/route")
	{
		Utils::printConsole(consoleHelpText::route);
		return true;
	}
	/****** Roam map only commands ******/
	else if (Utils::tr_pc && Utils::tr_pc->WorldInfo->NetMode == 0)
	{
		if (linelower == L"/toggle turrets" || linelower == L"/turrets")
		{
			toggleTurrets();
			return true;
		}
		else if (linelower == L"/toggle power" || linelower == L"/power")
		{
			togglePower();
			return true;
		}
		else if (linelower == L"/returnflags" || linelower == L"/flags")
		{
			returnFlags();
			return true;
		}
	}
	return false;
}

// Custom console commands for the big console
bool TrChatConsole_Open_InputKey(int id, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	UTrChatConsole *that = (UTrChatConsole *)dwCallingObject;
	UTrChatConsole_execInputKey_Parms *params = (UTrChatConsole_execInputKey_Parms *)pParams;

	ATrPlayerController *TrPC = that->m_TrPC;

	if (that->m_TrPC)
		Utils::tr_pc = that->m_TrPC;

	params->AmountDepressed = 1.0f;
	params->bGamepad = false;
	if (params->Key == FName("Enter") && params->Event == 1)
	{
		if (TrPC && TrPC->WorldInfo->TimeSeconds - that->m_fTypingTime < 0.150f)
			return false;
		if (that->TypedStr.Count)
		{
			if (that->IsSlashCommand())
			{
				if (!execConsoleCommand(that->TypedStr.Data))
				{
					if (that->m_TrPC)
					{
						that->TypedStr.Remove(0);
						std::string result = Utils::f2std(that->m_TrPC->ConsoleCommand(that->TypedStr, false));
						if (!result.empty())
							Utils::printConsole(result);
					}
				}
				that->SetInputText(FString(L""));
				that->SetCursorPos(0);
				that->UpdateCompleteIndices();
				pResult = (void *)true;
				return true;
			}
		}
	}
	return false;
}

// Custom console commands for the one-line console
bool TrChatConsole_Typing_InputKey(int id, UObject *dwCallingObject, UFunction* pFunction, void* pParams, void* pResult)
{
	UTrChatConsole *that = (UTrChatConsole *)dwCallingObject;
	UTrChatConsole_execInputKey_Parms *params = (UTrChatConsole_execInputKey_Parms *)pParams;

	ATrPlayerController *TrPC = that->m_TrPC;

	if (that->m_TrPC)
		Utils::tr_pc = that->m_TrPC;

	params->AmountDepressed = 1.0f;
	params->bGamepad = false;
	if (params->Key == FName("Enter") && params->Event == 1)
	{
		if (TrPC && TrPC->WorldInfo->TimeSeconds - that->m_fTypingTime < 0.150f)
			return false;
		if (that->TypedStr.Count)
		{
			if (that->IsSlashCommand())
			{
				if (!execConsoleCommand(that->TypedStr.Data))
				{
					if (that->m_TrPC)
					{
						that->TypedStr.Remove(0);
						std::string result = Utils::f2std(that->m_TrPC->ConsoleCommand(that->TypedStr, false));
						if (!result.empty())
							Utils::printConsole(result);
					}
				}
				that->TypedStr = L"";
				that->SetInputText(FString(L""));
				that->SetCursorPos(0);
				that->ChannelStr = L"";
				that->UpdateCompleteIndices();

				return false;
			}
		}
	}
	return false;
}
