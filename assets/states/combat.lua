local node = {
	name = "combat",
	-- track = "assets/tracks/05-5-loop.ogg",
	layers = {
		french_horn_1 = "assets/tracks/05-5-loop.ogg",
		french_horn_2 = "assets/tracks/06-5-loop.ogg",
		cowbell = "assets/tracks/07-5-loop.ogg",
		sleigh_bells = "assets/tracks/08-5-loop.ogg",
		taikos = "assets/tracks/09-5-loop.ogg",
		snare_drum = "assets/tracks/10-5-loop.ogg",
		field_drum = "assets/tracks/11-5-loop.ogg",
		bongos = "assets/tracks/12-5-loop.ogg",
		bass_drum = "assets/tracks/13-5-loop.ogg",
		electric_lp_heavy = "assets/tracks/14-5-loop.ogg",
		electric_sc_heavy = "assets/tracks/15-5-loop.ogg",
		harp = "assets/tracks/16-5-loop.ogg",
		violins = "assets/tracks/17-5-loop.ogg",
		violinchellos = "assets/tracks/18-5-loop.ogg",
	},
	bpm = 120,
}

-- the update function is called periodically, normally on the beat of the music
function node.update()
	-- values set from c++ code will be saved in the world table
	if world.enemy_count <= 0 then
		-- the next_node function changes the state of the music box
		-- next_node("peaceful_to_combat")
		next_node(states["peaceful"])
		-- early return, we don't have to check other variables
		return
	end

	-- activate layers depending on the current state of the game
	set_layer("cowbell",           true)
	set_layer("sleigh_bells",      true)
	set_layer("taikos",            true)
	set_layer("snare_drum",        true)
	set_layer("field_drum",        true)
	set_layer("bongos",            true)
	set_layer("bass_drum",         true)
	set_layer("french_horn_1",     world.enemy_count > 1 and world.boss == 1)
	set_layer("harp",              world.enemy_count > 1 and world.boss ~= 1)
	set_layer("electric_lp_heavy", world.enemy_count > 2 and world.boss == 1)
	set_layer("electric_sc_heavy", world.enemy_count > 2 and world.boss == 1)
	set_layer("violins",           world.enemy_count > 2 and world.boss ~= 1)
	set_layer("violinchellos",     world.enemy_count > 2 and world.boss ~= 1)
	set_layer("french_horn_2",     world.enemy_count > 3)
end

return node