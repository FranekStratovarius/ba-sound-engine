-- load the modules
local combat = require("assets.states.combat")
local peaceful = require("assets.states.peaceful")

-- create the music_states table with the loaded modules
music_states = {
	combat,
	peaceful,
}

-- define first state
first_state = "peaceful"

-- define world variables needed for this music box
-- and their initial values
world = {
	boss = 0,
	enemy_count = 0,
	wonders = 0,
}