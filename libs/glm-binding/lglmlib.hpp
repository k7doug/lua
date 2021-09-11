/*
** $Id: lglmlib.h $
** GLM binding library
** See Copyright Notice in lua.h
*/

#ifndef lglmlib_hpp
#define lglmlib_hpp

#define LUA_GLM_NAME "lua-glm"
#define LUA_GLM_VERSION "lua-glm 0.1.2"
#define LUA_GLM_COPYRIGHT "Copyright (C) 2020, Gottfried Leibniz"
#define LUA_GLM_DESCRIPTION "glm bindings for Lua"
#define LUA_GLMLIBNAME "glm"

#include <lua.hpp>
#if defined(__cplusplus)
extern "C" {
#endif

LUAMOD_API int (luaopen_glm) (lua_State *L);

#if defined(__cplusplus)
}
#endif
#endif
