/*
** $Id: loslib.c,v 1.64 2016/04/18 13:06:55 roberto Exp $
** Standard Operating System library
** See Copyright Notice in lua.h
*/

#define ldb2_c
#define LUA_LIB

#include "lprefix.h"

#include <errno.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "lauxlib.h"
#include "lualib.h"
#include <sqlcli.h>

static int db2_allocEnv (lua_State *L) {
  SQLHENV ptr = 0;

  if (SQLAllocEnv(&ptr) == SQL_ERROR)
    return luaL_execresult(L, SQL_ERROR);
  else {
    lua_pushnumber(L, ptr);  /* true if there is a shell */
    return 1;
  }
}

static int db2_freeEnv (lua_State *L) {
  SQLRETURN res = SQLFreeEnv(lua_tointeger(L, 1));

  if (res != SQL_SUCCESS) {
    return luaL_execresult(L, SQL_ERROR);
  } else {
    return 1;
  }
}

static int db2_allocConnect (lua_State *L) {
  SQLHENV env = lua_tointeger(L, 1);
  SQLHDBC hdl = 0;

  if (SQLAllocConnect(env, &hdl) != SQL_SUCCESS)
    return luaL_execresult(L, SQL_ERROR);
  else {
    lua_pushnumber(L, hdl);  /* true if there is a shell */
    return 1;
  }
}

static int db2_freeConnect (lua_State *L) {
  SQLRETURN res = SQLFreeConnect(lua_tointeger(L, 1));

  if (res != SQL_SUCCESS) {
    return luaL_execresult(L, SQL_ERROR);
  } else {
    return 1;
  }
}

/* }====================================================== */

static const luaL_Reg db2lib[] = {
  {"allocEnv",     db2_allocEnv},
  {"freeEnv",      db2_freeEnv},
  {"allocConnect", db2_allocConnect},
  {"freeConnect",  db2_freeConnect},
  {NULL, NULL}
};

/* }====================================================== */



LUAMOD_API int luaopen_db2 (lua_State *L) {
  luaL_newlib(L, db2lib);
  return 1;
}

