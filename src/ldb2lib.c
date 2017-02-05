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

static int db2_allocEnv(lua_State *L) {
  SQLHENV env = 0;
  int sqltrue = SQL_TRUE;

  if (SQLAllocEnv(&env) == SQL_ERROR) {
    lua_pushnumber(L, SQL_ERROR); //0 = ERROR
    return luaL_execresult(L, SQL_ERROR);
    
  } else {
    lua_pushnumber(L, env);  /* true if there is a shell */
    return 1;
  }
}

static int db2_freeEnv(lua_State *L) {
  SQLHENV env = lua_tointeger(L, 1);

  SQLRETURN res = SQLFreeEnv(env);

  lua_pushnumber(L, res);
  return res;
}

static int db2_allocConnect(lua_State *L) {
  SQLHENV env = lua_tointeger(L, 1);
  SQLHDBC hdl = 0;

  if (SQLAllocConnect(env, &hdl) != SQL_SUCCESS) {
    lua_pushnumber(L, SQL_ERROR); //0 = ERROR
    return luaL_execresult(L, SQL_ERROR);
  } else {

    lua_pushnumber(L, hdl);  /* true if there is a shell */
    return 1;
  }
}

static int db2_freeConnect(lua_State *L) {
  SQLRETURN res = SQLFreeConnect(lua_tointeger(L, 1));

  lua_pushnumber(L, res);
  return res;
}

static int db2_Connect(lua_State *L) {
  SQLHDBC hdl = lua_tointeger(L, 1);
  SQLCHAR *database = (char*) luaL_optstring(L, 2, NULL);

  SQLRETURN res = SQLConnect(hdl, database, SQL_NTS, 0, SQL_NTS, 0, SQL_NTS);

  if (res != SQL_SUCCESS) {
    lua_pushnumber(L, res);
    return luaL_execresult(L, SQL_ERROR);
  } else {
    SQLINTEGER sqltrue = SQL_TRUE;
    SQLINTEGER nocmt = SQL_TXN_NO_COMMIT;
    
    SQLSetConnectAttr(hdl, SQL_ATTR_DBC_SYS_NAMING, &sqltrue, 0);
    SQLSetConnectAttr(hdl, SQL_ATTR_COMMIT, &nocmt, 0);
    
    lua_pushnumber(L, res);
    return 1;
  }
}

static int db2_Disconnect(lua_State *L) {
  SQLRETURN res = SQLDisconnect(lua_tointeger(L, 1));

  lua_pushnumber(L, res);
  return res;
}

static int db2_allocStatement(lua_State *L) {
  SQLHDBC hdl = lua_tointeger(L, 1);
  SQLHSTMT stmt = 0; 

  if (SQLAllocStmt(hdl, &stmt) != SQL_SUCCESS) {
    lua_pushnumber(L, SQL_ERROR); //0 = ERROR
    return luaL_execresult(L, SQL_ERROR);
  } else {
    lua_pushnumber(L, stmt);
    return 1;
  }
}

static int db2_closeStatement(lua_State *L) {
  SQLHSTMT stmt = lua_tointeger(L, 1);
  
  SQLCloseCursor(stmt);
  SQLFreeStmt(stmt, SQL_CLOSE);

  lua_pushnumber(L, 1);
  return 1;
}

static int db2_executeDirect(lua_State *L) {
  SQLHSTMT stmt = lua_tointeger(L, 1);
  SQLCHAR *statement = (char*) luaL_optstring(L, 2, NULL);

  SQLRETURN res = SQLExecDirect(stmt, statement, SQL_NTS);
  lua_pushnumber(L, res);
  return 1;
}

static int db2_fetch(lua_State *L) {
  SQLHSTMT stmt = lua_tointeger(L, 1); 
  
  SQLRETURN res = SQLFetch(stmt);
  lua_pushnumber(L, res);
  return 1;
}

static int db2_getColumn(lua_State *L) {
  SQLINTEGER rlength;
  
  SQLHSTMT stmt = lua_tointeger(L, 1);
  SQLSMALLINT col = lua_tointeger(L, 2);
  SQLINTEGER len = lua_tointeger(L, 3);
  
  SQLCHAR * fieldRet;
  
  SQLGetCol(stmt, col, SQL_CHAR, (SQLPOINTER) fieldRet, len, &rlength);
  fieldRet[len] = '\0';
  lua_pushstring(L, fieldRet);
  
  return 1;
}

static int db2_printError(lua_State *L) {

  SQLHENV env = lua_tointeger(L, 1);
  SQLHDBC hdl = lua_tointeger(L, 2);
  SQLHSTMT stmt = lua_tointeger(L, 3);

  SQLCHAR     buffer[SQL_MAX_MESSAGE_LENGTH + 1];
  SQLCHAR     sqlstate[SQL_SQLSTATE_SIZE + 1];
  SQLINTEGER  sqlcode;
  SQLSMALLINT length;


  while ( SQLError(env, hdl, stmt, sqlstate, &sqlcode, buffer,
                   SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS )
  {
    printf("\n **** ERROR *****\n");
    printf("         SQLSTATE: %s\n", sqlstate);
    printf("Native Error Code: %ld\n", sqlcode);
    printf("%s \n", buffer);
  };

  return (SQL_ERROR);
}

/* }====================================================== */

static const luaL_Reg db2lib[] = {
  {"allocEnv",        db2_allocEnv},
  {"freeEnv",         db2_freeEnv},
  {"allocConnection", db2_allocConnect},
  {"freeConnection",  db2_freeConnect},
  {"Connect",         db2_Connect},
  {"Disconnect",      db2_Disconnect},
  {"allocStatement",  db2_allocStatement},
  {"closeStatement",  db2_closeStatement},

  {"executeStatement", db2_executeDirect},
  {"fetch",            db2_fetch},
  {"getColumn",        db2_getColumn},
  {"printError",       db2_printError},
  
  {"NULL", NULL},
  
  {"SQL_SUCCESS", NULL},
  {"SQL_SUCCESS_WITH_INFO", NULL},
  {"SQL_NO_DATA_FOUND", NULL},
  {"SQL_NEED_DATA", NULL},
  {"SQL_NO_DATA", NULL},
  {"SQL_ERROR", NULL},
  {"SQL_INVALID_HANDLE", NULL},
  {"SQL_STILL_EXECUTING", NULL},
  {NULL, NULL}
};

/* }====================================================== */



LUAMOD_API int luaopen_db2 (lua_State *L) {
  char null[1] = "~";
  luaL_newlib(L, db2lib);
  
  lua_pushstring(L, null);
  lua_setfield(L, -2, "NULL");
  
  lua_pushnumber(L, 0);
  lua_setfield(L, -2, "SQL_SUCCESS");
  
  lua_pushnumber(L, 1);
  lua_setfield(L, -2, "SQL_SUCCESS_WITH_INFO");
  
  lua_pushnumber(L, 100);
  lua_setfield(L, -2, "SQL_NO_DATA_FOUND");
  
  lua_pushnumber(L, 99);
  lua_setfield(L, -2, "SQL_NEED_DATA");
  
  lua_pushnumber(L, 100);
  lua_setfield(L, -2, "SQL_NO_DATA");
  
  lua_pushnumber(L, -1);
  lua_setfield(L, -2, "SQL_ERROR");
  
  lua_pushnumber(L, -2);
  lua_setfield(L, -2, "SQL_INVALID_HANDLE");
  
  lua_pushnumber(L, 2);
  lua_setfield(L, -2, "SQL_STILL_EXECUTING");
  
  return 1;
}

