#pragma once

#include "Mods.h"
#include <map>

struct consoleCommand
{
	void(*function)(const std::wstring&, const std::wstring&);
	FString description;
};

namespace consoleCommands
{
	extern std::map<std::wstring, consoleCommand> map;

	void execUTConsoleCommand(const FString &command);
	void generateAutoCompleteList(TArray<FAutoCompleteCommand> &arr);

	void cmd_help(const std::wstring &cmd, const std::wstring &params);
	void cmd_lua(const std::wstring &cmd, const std::wstring &params);
	void cmd_reloadconfig(const std::wstring &cmd, const std::wstring &params);
	void cmd_reloadsounds(const std::wstring &cmd, const std::wstring &params);
	void cmd_playerlist(const std::wstring &cmd, const std::wstring &params);
	void cmd_kickvoteid(const std::wstring &cmd, const std::wstring &params);
	void cmd_say(const std::wstring &cmd, const std::wstring &params);
	void cmd_stopwatch(const std::wstring &cmd, const std::wstring &params);
	void cmd_stopwatchstart(const std::wstring &cmd, const std::wstring &params);
	void cmd_stopwatchstop(const std::wstring &cmd, const std::wstring &params);
	void cmd_statesave(const std::wstring &cmd, const std::wstring &params);
	void cmd_statetp(const std::wstring &cmd, const std::wstring &params);
	void cmd_staterecall(const std::wstring &cmd, const std::wstring &params);
	void cmd_statespawns(const std::wstring &cmd, const std::wstring &params);
	void cmd_statereset(const std::wstring &cmd, const std::wstring &params);
	void cmd_routerec(const std::wstring &cmd, const std::wstring &params);
	void cmd_routerecstart(const std::wstring &cmd, const std::wstring &params);
	void cmd_routerecstop(const std::wstring &cmd, const std::wstring &params);
	void cmd_routereplay(const std::wstring &cmd, const std::wstring &params);
	void cmd_routereplaystart(const std::wstring &cmd, const std::wstring &params);
	void cmd_routereplaystop(const std::wstring &cmd, const std::wstring &params);
	void cmd_routebot(const std::wstring &cmd, const std::wstring &params);
	void cmd_routereset(const std::wstring &cmd, const std::wstring &params);
	void cmd_routesave(const std::wstring &cmd, const std::wstring &params);
	void cmd_routeload(const std::wstring &cmd, const std::wstring &params);
	void cmd_routefind(const std::wstring &cmd, const std::wstring &params);
	void cmd_routelist(const std::wstring &cmd, const std::wstring &params);
	void cmd_toggleturrets(const std::wstring &cmd, const std::wstring &params);
	void cmd_togglepower(const std::wstring &cmd, const std::wstring &params);
	void cmd_returnflags(const std::wstring &cmd, const std::wstring &params);
	void cmd_utcommandwrapper(const std::wstring &cmd, const std::wstring &params);

	void cmd_findobjects(const std::wstring &cmd, const std::wstring &params);
	void cmd_develcommands(const std::wstring &cmd, const std::wstring &params);
}