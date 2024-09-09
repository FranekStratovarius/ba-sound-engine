local node = {
	name = "combat_start",
	layers = {
		french_horn_1     = "assets/tracks/05-4-start_loop.ogg",
		french_horn_2     = "assets/tracks/06-4-start_loop.ogg",
		cowbell           = "assets/tracks/07-4-start_loop.ogg",
		sleigh_bells      = "assets/tracks/08-4-start_loop.ogg",
		taikos            = "assets/tracks/09-4-start_loop.ogg",
		snare_drum        = "assets/tracks/10-4-start_loop.ogg",
		field_drum        = "assets/tracks/11-4-start_loop.ogg",
		bongos            = "assets/tracks/12-4-start_loop.ogg",
		bass_drum         = "assets/tracks/13-4-start_loop.ogg",
		electric_lp_heavy = "assets/tracks/14-4-start_loop.ogg",
		electric_sc_heavy = "assets/tracks/15-4-start_loop.ogg",
		harp              = "assets/tracks/16-4-start_loop.ogg",
		violins           = "assets/tracks/17-4-start_loop.ogg",
		violinchellos     = "assets/tracks/18-4-start_loop.ogg",
	},
	bpm = 120,
}

local function set_dynamic_layers()
	set_layer("french_horn_1",     world.enemy_count > 1 and world.boss == 1)
	set_layer("harp",              world.enemy_count > 1 and world.boss ~= 1)
	set_layer("electric_lp_heavy", world.enemy_count > 2 and world.boss == 1)
	set_layer("electric_sc_heavy", world.enemy_count > 2 and world.boss == 1)
	set_layer("violins",           world.enemy_count > 2 and world.boss ~= 1)
	set_layer("violinchellos",     world.enemy_count > 2 and world.boss ~= 1)
	set_layer("french_horn_2",     world.enemy_count > 3)
end

function node.init()
	set_layer("cowbell",           true)
	set_layer("sleigh_bells",      true)
	set_layer("taikos",            true)
	set_layer("snare_drum",        true)
	set_layer("field_drum",        true)
	set_layer("bongos",            true)
	set_layer("bass_drum",         true)
	set_dynamic_layers()
end

-- the update function is called periodically, normally on the beat of the music
function node.update()
	-- values set from c++ code will be saved in the world table
	if world.enemy_count <= 0 then
		-- the next_node function changes the state of the music box
		-- next_node("peaceful_to_combat")
		next_node(states["combat_to_peaceful"])
		-- early return, we don't have to check other variables
		return
	end

	-- activate layers depending on the current state of the game
	set_dynamic_layers()
end

return node