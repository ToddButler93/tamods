local tamodsmenu = ubermenu:add_submenu({ title = "TAMods Settings" })
	local sub1 = tamodsmenu:add_submenu({ title = "Damage Numbers" })
		sub1:add_variable({ title = "Display Limit",             varname = "damageNumbersLimit",                   default = 0,     min = 0, max = 4000, inc = 1, description = "Only show Damage Numbers\nwhen doing at least this\namount of damage\nDefault: 0" })
		sub1:add_variable({ title = "Horizontal Offset",         varname = "damageNumbersOffsetX",                 default = 0.0,                        inc = 1.0 })
		sub1:add_variable({ title = "Vertical Offset",           varname = "damageNumbersOffsetY",                 default = 0.0,                        inc = 1.0 })
		sub1:add_variable({ title = "Scale",                     varname = "damageNumbersScale",                   default = 1.0,   min = 0.0,           inc = 0.1 })
		sub1:add_variable({ title = "Center Position",           varname = "revertOriginalDamageNumbers",          default = false })
		sub1:add_variable({ title = "Center Position Threshold", varname = "revertOriginalDamageNumbersThreshold", default = 100,   min = 0,             inc = 1 })
		sub1:add_variable({ title = "Stream Numbers",            varname = "showDamageNumberStream",               default = false })
		sub1:add_variable({ title = "Show Hit Count",            varname = "showChainBulletHitCount",              default = false })
		sub1:add_variable({ title = "Stream Timeout",            varname = "damageNumberStreamTimeout",            default = 0.5,   min = 0.1,           inc = 0.1 })
		sub1:add_variable({ title = "Custom Text",               varname = "damageNumberCustomText",               default = "" })
		sub1:add_variable({ title = "Use Rainbow",               varname = "showRainbow",                          default = false })
		sub1:add_color({    title = "Start Color",               varname = "damageNumbersColorMin",                default = rgb(255,255,255,255) })
		sub1:add_color({    title = "End Color",                 varname = "damageNumbersColorMax",                default = rgb(248,83,83,255) })
		sub1:add_separator({})
		sub1:add_item({ title = "Apply", func = config.reloadVariables })

	local sub1 = tamodsmenu:add_submenu({ title = "Gameplay" })
		sub1:add_variable({ title = "Show Weapon",              varname = "showWeapon",         default = true })
		sub1:add_variable({ title = "Show Body",                varname = "showBodyMesh",       default = true })
		sub1:add_variable({ title = "Use FOV Scaling",          varname = "useFOVScaling",      default = true })
		sub1:add_variable({ title = "Sensitivity",              varname = "sens",               default = 10.0, min = 0.0, inc = 0.1 })
		sub1:add_variable({ title = "Zoomed Sensitivity",       varname = "sensZoom",           default = 5.0, min = 0.0,  inc = 0.1 })
		sub1:add_variable({ title = "Zoomedx2 Sensitivity",     varname = "sensZoooom",         default = 2.0, min = 0.0,  inc = 0.1 })
		sub1:add_variable({ title = "Use Custom Weapon Offset", varname = "customWeaponOffset", default = false })
		sub1:add_fvector({  title = "Weapon Offset",            varname = "weaponOffset",       default = Vector(0.0, 0.0, 0.0), inc = 0.2 })
		sub1:add_separator({})
		sub1:add_item({ title = "Apply", func = config.reloadVariables })

	local sub1 = tamodsmenu:add_submenu({ title = "HUD" })
		local sub2 = sub1:add_submenu({ title = "Crosshair" })
			sub2:add_variable({ title = "Show Stock Crosshairs", varname = "showCrosshair",  default = true })
			sub2:add_variable({ title = "Scale",                 varname = "crosshairScale", default = 1.0, min = 0.0, inc = 0.5 })
			sub2:add_color({    title = "Color",                 varname = "crosshairColor", default = rgba(255,255,255,255) })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })
		local sub2 = sub1:add_submenu({ title = "Chat" })
			sub2:add_color({ title = "Friendly Console Color",   varname = "friendlyChatColor",    default = rgb(158, 208, 212) })
			sub2:add_color({ title = "Enemy Console Color",      varname = "enemyChatColor",       default = rgb(255, 111, 111) })
			sub2:add_color({ title = "Whispers Console Color",   varname = "whisperChatColor",     default = rgb(207, 165, 101) })
			sub2:add_color({ title = "Friendly HUD Color",       varname = "friendlyHUDChatColor", default = rgb(158, 208, 211) })
			sub2:add_color({ title = "Enemy HUD Color",          varname = "enemyHUDChatColor",    default = rgb(249, 32, 32) })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })
		local sub2 = sub1:add_submenu({ title = "Markers" })
			sub2:add_color({ title = "Friend Name Color",        varname = "friendlyColor",          default = rgb(119, 186, 255) })
			sub2:add_color({ title = "Enemy Name Color",         varname = "enemyColor",             default = rgb(248, 83, 83) })
			sub2:add_color({ title = "Enemy Marker Color",       varname = "enemyMarkerColor",       default = rgb(255, 23, 23) })
			sub2:add_color({ title = "Special Enemy Marker",     varname = "enemyIsFMarkerColor",    default = rgb(239, 164, 0) })
			sub2:add_color({ title = "Friend Marker Color",      varname = "friendlyMarkerColor",    default = rgb(115, 225, 255) })
			sub2:add_color({ title = "Special Friend Marker",    varname = "friendlyIsFMarkerColor", default = rgb(81, 250, 85) })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })
		local sub2 = sub1:add_submenu({ title = "Speed counter" })
			sub2:add_variable({ title = "Minimal value",         varname = "skiBarMin", default = 30,  min = 0, inc = 1 })
			sub2:add_variable({ title = "Maximal value",         varname = "skiBarMax", default = 300, min = 0, inc = 1 })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })
		local sub2 = sub1:add_submenu({ title = "Stopwatch" })
			sub2:add_variable({ title = "Stop on cap",           varname = "stopwatchStopOnCap",     default = false })
			sub2:add_variable({ title = "Stop on death",         varname = "stopwatchStopOnDeath",   default = true })
			sub2:add_variable({ title = "Notifications",         varname = "stopwatchNotifications", default = true })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })
		local sub2 = sub1:add_submenu({ title = "Icons" })
			sub2:add_variable({ title = "Show objectives",       varname = "showObjectiveIcon",    default = true })
			sub2:add_variable({ title = "Show objective text",   varname = "showObjectiveText",    default = true })
			sub2:add_variable({ title = "Show flag base",        varname = "showFlagBaseIcon",     default = true })
			sub2:add_variable({ title = "Show flag home base",   varname = "showFlagHomeBaseIcon", default = true })
			sub2:add_variable({ title = "Show CTF base",         varname = "showCTFBaseIcon",      default = true })
			sub2:add_variable({ title = "Show nuggets",          varname = "showNuggetIcon",       default = true })
			sub2:add_variable({ title = "Show players",          varname = "showPlayerIcon",       default = true })
			sub2:add_variable({ title = "Show vehicles",         varname = "showVehicleIcon",      default = true })
			sub2:add_variable({ title = "Show mines",            varname = "showMineIcon",         default = true })
			sub2:add_variable({ title = "Show mine text",        varname = "showMineText",         default = true })
			sub2:add_variable({ title = "Show sensors",          varname = "showSensorIcon",       default = true })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })
		local sub2 = sub1:add_submenu({ title = "Misc" })
			sub2:add_variable({ title = "General scale",         varname = "IFFScale",            default = 1.0, min = 0.0, inc = 0.5 })
			sub2:add_variable({ title = "Always show ammo",      varname = "showFirstPersonAmmo", default = false })
			sub2:add_variable({ title = "Console size",          varname = "consoleSize",         default = 0.75, min = 0.0, max = 1.0, inc = 0.01 })
			sub2:add_variable({ title = "Console transparency",  varname = "consoleTransparency", default = 0.8,  min = 0.0, max = 1.0, inc = 0.01 })
			sub2:add_variable({ title = "Mute all VGS",          varname = "muteVGS",             default = false })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })

	local sub1 = tamodsmenu:add_submenu({ title = "Magic Chain" })
		sub1:add_variable({ title = "Use Magic Chain",        varname = "useMagicChain",           default = false })
		sub1:add_variable({ title = "Use small bullets",      varname = "useSmallBullets",         default = false })
		sub1:add_variable({ title = "Center bullets",         varname = "centerBulletSpawn",       default = false })
		sub1:add_variable({ title = "Ping multiplier",        varname = "bulletPingMultiplier",    default = 1.0, min = 0.0, inc = 0.1 })
		sub1:add_variable({ title = "Spawn delay",            varname = "bulletSpawnDelay",        default = 0.0, min = 0.0, inc = 0.1 })
		sub1:add_variable({ title = "Use custom spawn",       varname = "customBulletSpawnOffset", default = false })
		sub1:add_fvector({  title = "Custom spawn offset",    varname = "bulletSpawnOffset",       default = Vector(180.0, 0.0, 0.0), inc = 0.5 })
		sub1:add_separator({})
		sub1:add_item({ title = "Apply", func = config.reloadVariables })

	local sub1 = tamodsmenu:add_submenu({ title = "Roam map" })
		sub1:add_variable({ title = "Disable base turrets",   varname = "disableBaseTurrets",       default = false })
		sub1:add_variable({ title = "Disable power",          varname = "disablePower",             default = false })
		sub1:add_variable({ title = "Show saved locations",   varname = "showSavedLocations",       default = true })
		sub1:add_variable({ title = "Max speed with flag",    varname = "maxSpeedWithFlag",         default = 0, min = 0, inc = 1 })
		sub1:add_variable({ title = "Deceleration with flag", varname = "decelerationRateWithFlag", default = 10, inc = 1 })
		sub1:add_separator({})
		sub1:add_item({ title = "Apply", func = config.reloadVariables })

	local sub1 = tamodsmenu:add_submenu({ title = "Route recording" })
		sub1:add_variable({ title = "Draw interval",          varname = "routeDrawInterval",     default = 500, min = 100, inc = 10 })
		sub1:add_variable({ title = "Draw transparency",      varname = "routeDrawTransparency", default = 0.8, min = 0.0, max = 1.0, inc = 0.01 })
		sub1:add_variable({ title = "ETA draw interval",      varname = "routeDrawETAInterval",  default = 5,   min = 0, inc = 1 })
		sub1:add_variable({ title = "Replay with rotation",   varname = "routeReplayRotation",   default = true })
		sub1:add_variable({ title = "Smooth replay",          varname = "routeCinematicMode",    default = false })
		sub1:add_separator({})
		sub1:add_item({ title = "Apply", func = config.reloadVariables })

	local sub1 = tamodsmenu:add_submenu({ title = "Sounds" })
		sub1:add_variable({ title = "Sound mode",          varname = "hitSoundMode",      default = 0,   min = 1, max = 3, inc = 1 })
		sub1:add_variable({ title = "Hit sound min pitch", varname = "hitSoundPitchMin",  default = 0.4, min = 0.0, inc = 0.1 })
		sub1:add_variable({ title = "Hit sound max pitch", varname = "hitSoundPitchMax",  default = 1.6, min = 0.0, inc = 0.1 })
		sub1:add_variable({ title = "Damage reference",    varname = "hitSoundDamageRef", default = 600, min = 0,   inc = 10 })
		sub1:add_separator({})
		local sub2 = sub1:add_submenu({ title = "Files" })
			sub2:add_variable({ title = "Hit",                  varname = "soundHit",              default = "" })
			sub2:add_variable({ title = "Headshot",             varname = "soundHeadShot",         default = "" })
			sub2:add_variable({ title = "Kill",                 varname = "soundKill",             default = "" })
			sub2:add_variable({ title = "Air mail",             varname = "soundAirMail",          default = "" })
			sub2:add_variable({ title = "Blue plate",           varname = "soundBluePlate",        default = "" })
			sub2:add_variable({ title = "Killing spree",        varname = "soundStreak1",          default = "" })
			sub2:add_variable({ title = "Rampage",              varname = "soundStreak2",          default = "" })
			sub2:add_variable({ title = "Relentless",           varname = "soundStreak3",          default = "" })
			sub2:add_variable({ title = "Unstoppable",          varname = "soundStreak4",          default = "" })
			sub2:add_variable({ title = "The Slayer",           varname = "soundStreak5",          default = "" })
			sub2:add_variable({ title = "Double kill",          varname = "soundMultiKill1",       default = "" })
			sub2:add_variable({ title = "Triple kill",          varname = "soundMultiKill2",       default = "" })
			sub2:add_variable({ title = "Quatra kill",          varname = "soundMultiKill3",       default = "" })
			sub2:add_variable({ title = "Ultra kill",           varname = "soundMultiKill4",       default = "" })
			sub2:add_variable({ title = "Team kill",            varname = "soundMultiKill5",       default = "" })
			sub2:add_variable({ title = "First blood",          varname = "soundFirstBlood",       default = "" })
			sub2:add_variable({ title = "Headshot kill",        varname = "soundHeadShotKill",     default = "" })
			sub2:add_variable({ title = "Artillery shot",       varname = "soundArtilleryShot",    default = "" })
			sub2:add_variable({ title = "Melee kill",           varname = "soundMeleeKill",        default = "" })
			sub2:add_variable({ title = "Roadkill",             varname = "soundRoadKill",         default = "" })
			sub2:add_variable({ title = "Fast grab",            varname = "soundFastGrab",         default = "" })
			sub2:add_variable({ title = "Our flag grabbed",     varname = "soundFlagBlueGrab",     default = "" })
			sub2:add_variable({ title = "Enemy flag grabbed",   varname = "soundFlagRedGrab",      default = "" })
			sub2:add_variable({ title = "Our flag picked up",   varname = "soundFlagBluePickup",   default = "" })
			sub2:add_variable({ title = "Enemy flag picked up", varname = "soundFlagRedPickup",    default = "" })
			sub2:add_variable({ title = "Our flag captured",    varname = "soundFlagBlueCapture",  default = "" })
			sub2:add_variable({ title = "Enemy flag captured",  varname = "soundFlagRedCapture",   default = "" })
			sub2:add_variable({ title = "Our flag returned",    varname = "soundFlagBlueReturn",   default = "" })
			sub2:add_variable({ title = "Enemy flag returned",  varname = "soundFlagRedReturn",    default = "" })
			sub2:add_variable({ title = "Our flag dropped",	    varname = "soundFlagBlueDrop",     default = "" })
			sub2:add_variable({ title = "Enemy flag dropped",   varname = "soundFlagRedDrop",      default = "" })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })

		local sub2 = sub1:add_submenu({ title = "Volumes" })
			sub2:add_variable({ title = "Hit",                  varname = "volumeHit",             default = 0.55, min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Headshot",             varname = "volumeHeadShot",        default = 0.55, min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Kill",                 varname = "volumeKill",            default = 0.55, min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Air mail",             varname = "volumeAirMail",         default = 0.55, min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Blue plate",           varname = "volumeBluePlate",       default = 0.55, min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Killing spree",        varname = "volumeStreak1",         default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Rampage",              varname = "volumeStreak2",         default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Relentless",           varname = "volumeStreak3",         default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Unstoppable",          varname = "volumeStreak4",         default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "The Slayer",           varname = "volumeStreak5",         default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Double kill",          varname = "volumeMultiKill1",      default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Triple kill",          varname = "volumeMultiKill2",      default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Quatra kill",          varname = "volumeMultiKill3",      default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Ultra kill",           varname = "volumeMultiKill4",      default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Team kill",            varname = "volumeMultiKill5",      default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "First blood",          varname = "volumeFirstBlood",      default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Headshot kill",        varname = "volumeHeadShotKill",    default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Artillery shot",       varname = "volumeArtilleryShot",   default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Melee kill",           varname = "volumeMeleeKill",       default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Roadkill",             varname = "volumeRoadKill",        default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Fast grab",            varname = "volumeFastGrab",        default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Our flag grabbed",     varname = "volumeFlagBlueGrab",    default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Enemy flag grabbed",   varname = "volumeFlagRedGrab",     default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Our flag picked up",   varname = "volumeFlagBluePickup",  default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Enemy flag picked up", varname = "volumeFlagRedPickup",   default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Our flag captured",    varname = "volumeFlagBlueCapture", default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Enemy flag captured",  varname = "volumeFlagRedCapture",  default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Our flag returned",    varname = "volumeFlagBlueReturn",  default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Enemy flag returned",  varname = "volumeFlagRedReturn",   default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Our flag dropped",     varname = "volumeFlagBlueDrop",    default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_variable({ title = "Enemy flag dropped",   varname = "volumeFlagRedDrop",     default = 0.5,  min = 0.0, inc = 0.1 })
			sub2:add_separator({})
			sub2:add_item({ title = "Apply", func = config.reloadVariables })
		sub1:add_separator({})
		sub1:add_item({ title = "Apply", func = config.reloadVariables })

	tamodsmenu:add_variable({ title = "Record stats", varname = "recordStats", default = false })
	tamodsmenu:add_separator({})
	tamodsmenu:add_item({ title = "Apply", func = config.reloadVariables })

sub1 = nil
sub2 = nil
