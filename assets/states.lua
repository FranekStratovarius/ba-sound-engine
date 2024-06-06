-- load the modules
local combat = require("assets.states.combat")
local peaceful = require("assets.states.peaceful")

-- create the music_states table with the loaded modules
music_states = {
	combat,
	peaceful,
}