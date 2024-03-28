add_requires("openal-soft", "libsndfile", "raylib")
if(is_plat("linux")) then
	add_requires("libsndio")
end

add_rules("mode.debug", "mode.release")

target("soundengine-usage-example") do
	set_license("LGPL-2.0")
	set_kind("binary")
	set_warnings("all", "error")

	add_files("example/src/*.cpp")
	add_includedirs("example/include")

	add_deps("soundengine")

	add_packages("openal-soft", "libsndfile", "raylib")
	if(is_plat("linux")) then
		add_packages("libsndio")
	end
	add_defines("PLATFORM_DESKTOP")

	-- copy assets after build
	after_build(function (target)
		os.cp(path.join("assets"), path.join("$(buildir)", "$(os)", "$(arch)", "$(mode)"))
	end)
end

target("soundengine") do
	set_license("LPGL-2.0")
	set_kind("shared")
	set_warnings("all", "error")

	add_files("lib/src/**.cpp")
	add_includedirs("lib/include", {public = true})

	add_packages("openal-soft", "libsndfile")
	if(is_plat("linux")) then
		add_packages("libsndio")
	end
end