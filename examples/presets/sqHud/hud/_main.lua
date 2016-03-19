require(preset .. "hud/variables")
require(preset .. "hud/colors")
require(preset .. "hud/widgets/ammo")
require(preset .. "hud/widgets/arena_player_spawns")
require(preset .. "hud/widgets/arena_round_scores")
require(preset .. "hud/widgets/cah_capture_points")
require(preset .. "hud/widgets/crosshairs")
require(preset .. "hud/widgets/chat_vgs")
require(preset .. "hud/widgets/flag_status")
require(preset .. "hud/widgets/game_scores")
require(preset .. "hud/widgets/game_timer")
require(preset .. "hud/widgets/game_messages")
require(preset .. "hud/widgets/generator_status")
require(preset .. "hud/widgets/health_energy")
require(preset .. "hud/widgets/healthbars")
require(preset .. "hud/widgets/kill_feed")
require(preset .. "hud/widgets/rabbit_leaderboard")
require(preset .. "hud/widgets/spectators")
require(preset .. "hud/widgets/stats")
require(preset .. "hud/widgets/vehicle_health_energy")

-- Toggle HUD bound to Ctrl-O
bindKey("O", Input.PRESSED,
	function(key, event, ctrl, shift, alt)
	   if ctrl and not viewPort.isMainMenuOpen() then
	      show_hud = not show_hud
	   end
	end
)

function onDrawCustomHud(res_x, res_y)
	-- Toggle HUD
	if not show_hud or viewPort.isMainMenuOpen() then
		return
	end

	set_variables()
	local center_x = res_x / 2
	local center_y = res_y / 2

	-- Stopwatch
	if stopwatch.isRunning() then
		drawSmallText(stopwatch.timeStr(), text_color1, res_x - 140, 140, 0, 1, 1)
	end

	stats(res_x - 20, 20)
	game_messages(center_x, 150)
	chat_vgs(15, res_y - 191)
	kill_feed(15, center_y - 200)

	game_timer(center_x, 0)

	-- Draw 70x40 team colored rectangles containing team score, not in rabbit though
	if game_type ~= "TrGame_TRRabbit" then
		game_scores(center_x + 40, 0)
	end

	if viewPort.isScoreboardOpen() then
		spectators(center_x, res_y * 0.85)
		generator_status(center_x, 220)
	end

	if game_type == "TrGame_TRCTF" or game_type == "TrGame_TrCTFBlitz" or game_type == "TrGame_TRTeamRabbit" then

		flag_status(center_x + 80, 0)

	elseif game_type == "TrGame_TRRabbit" then

		rabbit_leaderboard(36, 36)
		-- Draw the current rabbit next to the game timer, but only if it's not us
		if not player.hasFlag() then
			drawText(rabbit.rabbitName(), team_colors_text[0], center_x + 80, 22, 0, 1)
		end

	elseif game_type == "TrGame_TrCaH" then

		cah_capture_points(center_x + 90, 8)

	elseif game_type == "TrGame_TrArena" then

		-- Round scores
		arena_round_scores(center_x - 65, 0)
		-- Player spawns
		arena_player_spawns(center_x, 10)
		-- Draw a warning message if we have no respawns left
		if my_team ~= 255 and not game.isWarmUp() and player.isAlive() and player.arenaSpawnsLeft() < 1 then
			drawRect(center_x - 35, 40, center_x + 35, 60, bg_color2)
			drawSmallText("Last live!", text_color3, center_x, 50, 1, 1, 1)
		end

	end

	-----------------
	-- Player info --
	-----------------
	if player.isAlive() then
		-- Store the relevant data
		local in_vehicle = player.isVehicle()

		-- Draw the current amount of charged damage for the phase rifle
		if currentWeapon.name() == "Phase Rifle" then
			drawSmallText(math.ceil(player.energy() * 5.333), text_color1, center_x - 16, res_y * 0.6, 2, 1, 1)
		end

		crosshairs(center_x, center_y)
		health_energy(center_x - 500, center_y + 300)
		ammo(center_x + 200, center_y + 300)

		-- Draw a message if we have the flag
		if player.hasFlag() then
			drawRect(res_x - 165, center_y - 90, res_x - 108, center_y - 70, bg_color1)
			drawSmallText("F L A G", rgb(168,234,168), res_x - 160, center_y - 80, 0, 1, 1)
		end
		-- Draw a message if we have rage active
		if player.isRaged() then
			drawRect(res_x - 165, center_y - 68, res_x - 108, center_y - 48, bg_color1)
			drawSmallText("R A G E", text_color3, res_x - 160, center_y - 58, 0, 1, 1)
		end

		-- Vehicle display
		if in_vehicle then

			vehicle_health_energy(res_x * 0.65, res_y - 200)

			-- Ammo, not as gravcycle passenger (-1 ammo) or for the beowulf cannon (1 ammo)
			if vehicle.ammoMax() > 1 then
				drawSmallText(vehicle.ammo() .. "/" .. vehicle.ammoMax(), currentWeapon.isLowAmmo() and text_color3 or text_color1, center_x + 16, res_y * 0.6, 0, 1, 1)
			end

		end
	else
		local respawn_time = player.respawnTime()

		if respawn_time > 0 then
			drawText(respawn_time, text_color1, center_x, res_y * 0.9, 1, 1.5)
		end
	end
end