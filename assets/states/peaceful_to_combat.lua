local node = {
	name = "peaceful_to_combat",
	layers = {
		glockenspiel = "assets/tracks/04-3-transition_to_battle.ogg",
		electric_lp_heavy = "assets/tracks/14-3-transition_to_battle.ogg",
		electric_sc_heavy = "assets/tracks/15-3-transition_to_battle.ogg",
		violins = "assets/tracks/17-3-transition_to_battle.ogg",
		violinchellos = "assets/tracks/18-3-transition_to_battle.ogg",
	},
	bpm = 120,
}

local beats = 0

local function set_dynamic_layers()
	set_layer("electric_lp_heavy", world.enemy_count > 2 and world.boss == 1)
	set_layer("electric_sc_heavy", world.enemy_count > 2 and world.boss == 1)
	set_layer("violins",           world.enemy_count > 2 and world.boss ~= 1)
	set_layer("violinchellos",     world.enemy_count > 2 and world.boss ~= 1)
end

function node.init()
	set_layer("glockenspiel", true)
	set_dynamic_layers()
end

function node.update()
	beats = beats + 1
	print("beat: " .. beats)
	if beats >= 8 then
		next_node(states["combat"])
		return
	end

	-- activate layers depending on the current state of the game
	set_dynamic_layers()
end

function node.exit()
	beats = 0
end

return node