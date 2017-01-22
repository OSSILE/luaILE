# luaILE
Lua 5.3.3 for IBM i.

On-going development is happening to make sure all the test cases for 5.3.3 [found here](https://www.lua.org/tests/) pass without any issues.

### Todo

* DB2 API

## Build and try

1. `RELICGET PLOC('https://github.com/WorksOfBarry/luaILE/archive/master.zip') PDIR('luaILE-master') PNAME('LUA')`
2. `CALL LUA '-V'`
