-- load the modules
local combat = require("assets.states.combat")
local peaceful = require("assets.states.peaceful")

-- create the music_states table with the loaded modules
music_states = {
	combat,
	peaceful,
}

first_state = function()
	return states.combat
end

world = {
	enemy_count = 0,
	wonders = 0
}