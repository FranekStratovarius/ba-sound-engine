#include "lua_helpers.hpp"

void dumpstack (lua_State *L) {
	int top=lua_gettop(L);
	for (int i=1; i <= top; i++) {
		printf("%d\t%s\t", i, luaL_typename(L,i));
		switch (lua_type(L, i)) {
			case LUA_TNUMBER:
				printf("%g\n",lua_tonumber(L,i));
				break;
			case LUA_TSTRING:
				printf("%s\n",lua_tostring(L,i));
				break;
			case LUA_TBOOLEAN:
				printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
				break;
			case LUA_TNIL:
				printf("%s\n", "nil");
				break;
			default:
				printf("%p\n",lua_topointer(L,i));
				break;
		}
	}
}

void print_value(lua_State* L, int idx) {
	if(lua_isnil(L, idx))
		printf("nil");
	else if(lua_isboolean(L, idx)) {
		printf("%s", lua_toboolean(L,idx) ? "true" : "false");
	} else if(lua_isinteger(L, idx)) {
		printf("%d", (int)lua_tointeger(L, idx));
	} else if(lua_isnumber(L, idx)) {
		printf("%f", lua_tonumber(L, idx));
	} else if(lua_isstring(L,idx)) {
		printf("%s", lua_tostring(L, idx));
	} else if(lua_istable(L, idx)) {
		printf("%p", lua_topointer(L, idx));
	}
}

void print_table(lua_State* L,int depth) {
	//den befehl hab ich nicht ganz geblickt, aber damit geht man auf dem stack in ne tabelle rein
	lua_pushnil(L);
	//solange es weitere werte in der tabelle gibt, wird sie durchlaufen
	while(lua_next(L, -2) != 0){
		//einrückung damits schön aussieht^^
		for(int i = 0; i < depth; i++) {
			printf("  ");
		}
		//wenn tabelle in aktueller tabelle in diese absteigen
		if(lua_istable(L, -1)) {
			//formatierung für schöne ausgabe
			//key ausgeben
			print_value(L, -2);
			printf(":{\n");
			//in verschachtelte tabelle absteigen (und für die einrückung eins hochzählen)
			print_table(L, depth + 1);
			for(int i = 0; i < depth; i++){
				printf("	");
			}
			printf("},\n");
		//sonst key-value paare ausgeben
		} else {
			//key ausgeben
			print_value(L, -2);
			printf("=");
			//value ausgeben
			print_value(L, -1);
			printf(",\n");
		}
		//wenn wert bearbeitet von stack nehmen
		lua_pop(L, 1);
	}
}