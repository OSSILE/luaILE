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

/* }====================================================== */

static const luaL_Reg db2lib[] = {
  {"allocEnv",   db2_allocEnv},
  {NULL, NULL}
};

/* }====================================================== */



LUAMOD_API int luaopen_db2 (lua_State *L) {
  luaL_newlib(L, db2lib);
  return 1;
}

