local node = {
	name = "peaceful",
	track = "assets/30 Golden Win (piano).ogg",
	bpm = 112,
}

-- the update function is called periodically, normally on the beat of the music
function node.update()
	-- values set from c++ code will be saved in the world table
	if world.enemy_count <= 0 then
		-- the next_node function changes the state of the music box
		-- next_node("peaceful_to_combat")
		next_node(states["combat"])
		-- early return, we don't have to check other variables
		return
	end

	-- activate layers depending on the current state of the game
	set_layer("choir",   world.wonders > 4)
	set_layer("strings", world.wonders > 2)
	set_layer("piano",   world.wonders > 0)
end

return node