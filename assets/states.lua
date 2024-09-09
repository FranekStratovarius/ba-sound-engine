-- load the modules
local combat = require("assets.states.combat")
local combat_start = require("assets.states.combat_start")
local combat_to_peaceful = require("assets.states.combat_to_peaceful")
local peaceful = require("assets.states.peaceful")
local peaceful_start = require("assets.states.peaceful_start")
local peaceful_to_combat = require("assets.states.peaceful_to_combat")

-- create the music_states table with the loaded modules
music_states = {
	combat,
	combat_start,
	combat_to_peaceful,
	peaceful,
	peaceful_start,
	peaceful_to_combat,
}

-- define first state
first_state = "peaceful_start"

-- define world variables needed for this music box
-- and their initial values
world = {
	boss = 0,
	enemy_count = 0,
	wonders = 0,
}