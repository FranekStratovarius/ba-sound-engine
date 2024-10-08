local node = {
	name = "peaceful",
	layers = {
		choir        = "assets/tracks/01-2-loop.ogg",
		violins      = "assets/tracks/02-2-loop.ogg",
		dream_piano  = "assets/tracks/03-2-loop.ogg",
		glockenspiel = "assets/tracks/04-2-loop.ogg",
	},
	bpm = 120,
}

local function set_dynamic_layers()
	set_layer("dream_piano",  world.wonders > 0)
	set_layer("violins",      world.wonders > 1)
	set_layer("choir",        world.wonders > 2)
end

-- this function will be called once when the state is started
function node.init()
	for k,v in pairs(states) do
		print("state: "..k.." "..v)
	end
	-- the music box needs always at least one layer active
	set_layer("glockenspiel", true)
	set_dynamic_layers()
end

-- the update function is called periodically, normally on the beat of the music
function node.update()
	-- values set from c++ code will be saved in the world table
	if world.enemy_count > 0 then
		-- the next_node function changes the state of the music box
		next_node(states["peaceful_to_combat"])
		-- early return, we don't have to check other variables
		return
	end

	-- activate layers depending on the current state of the game
	set_dynamic_layers()
end

return node