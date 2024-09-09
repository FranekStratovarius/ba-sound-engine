local node = {
	name = "combat_to_peaceful",
	layers = {
		glockenspiel = "assets/tracks/04-6-transition_to_peaceful.ogg",
		french_horn_1 = "assets/tracks/05-6-transition_to_peaceful.ogg",
		french_horn_2 = "assets/tracks/06-6-transition_to_peaceful.ogg",
		field_drum = "assets/tracks/11-6-transition_to_peaceful.ogg",
		bongos = "assets/tracks/12-6-transition_to_peaceful.ogg",
		bass_drum = "assets/tracks/13-6-transition_to_peaceful.ogg",
		electric_lp_heavy = "assets/tracks/14-6-transition_to_peaceful.ogg",
		electric_sc_heavy = "assets/tracks/15-6-transition_to_peaceful.ogg",
		violins = "assets/tracks/17-6-transition_to_peaceful.ogg",
		violinchellos = "assets/tracks/18-6-transition_to_peaceful.ogg",
	},
	bpm = 120,
}

local beats = 0

function node.init()
	set_layer("glockenspiel",      true)
	set_layer("field_drum",        true)
	set_layer("bongos",            true)
	set_layer("bass_drum",         true)
	set_layer("french_horn_1",     true)
	set_layer("french_horn_2",     true)
	set_layer("electric_lp_heavy", world.boss == 1)
	set_layer("electric_sc_heavy", world.boss == 1)
	set_layer("violins",           world.boss ~= 1)
	set_layer("violinchellos",     world.boss ~= 1)
end

function node.update()
	beats = beats + 1
	print("beat: " .. beats)
	if beats >= 16 then
		next_node(states["peaceful"])
		return
	end
end

function node.exit()
	beats = 0
end

return node