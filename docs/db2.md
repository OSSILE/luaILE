## DB2 Module documentation

All the DB2 functions are within the `db2` namespace.

### Function list

* `allocEnv` - Allocate an envrionment first.
* `freeEnv`
* `allocConnection` - Allocate a connection to connect to a database.
* `freeConnection`
* `Connect` - Connect to a database.
* `Disconnect` - Disconnect from a database.
* `allocStatement` - Allocate a statement before executing.
* `closeStatement` - Close a statement (close cursor & free).
* `executeStatement` - Run a valid SQL statement.
* `fetch` - If SQL statement was a SELECT, using `db2.fetch` to move the cursor to the next row.
* `getColumn` - Grab the value of a specific column.
* `printError` - If the statement has crashed internally, use `db2.printError` to see more information.

***

#### `db2.allocEnv()` - Allocate an environment

##### Notes

* Allocate an environment to connect and run statements in.
* Returns environment handle as `number`.
* Always keep the handle stored so you are able to correctly free the environment at the end of the script.

```lua
  local env = db2.allocEnv()
  print(env)
  
  db2.freeEnv(env)
```

***

#### `db2.allocConnection()` - Allocate a connection

##### Parameters

1. Environment handle

##### Notes

* Allocate a connection to run statements in.
* Returns connection handle as `number`.
* Always keep the handle stored so you are able to correctly disconnect at the end of the script.

```lua
  local env = db2.allocEnv()
  print(env)
  
  local hdl = db2.allocConnection(env)
  print(hdl);
  
  db2.freeConnection(hdl)
  db2.freeEnv(env)
```

***

#### `db2.Connect(hdl, db)` - Connect to a database

##### Parameters

1. Connection handle
2. Database name (`string`)

##### Notes

* Only supports local databases currently. Support for external databases/system with username and password are coming, eventually.

```lua
  local env = db2.allocEnv()
  print(env)
  
  local hdl = db2.allocConnection(env)
  print(hdl);
  
  db2.Connect(hdl, "*LOCAL")
  
  db2.Disconnect(hdl)
  db2.freeConnection(hdl)
  db2.freeEnv(env)
```

***

#### `db2.allocateStatement(hdl)` - Allocate a statement handle to run and fetch an SQL statement

##### Parameters

1. Connection handle

##### Notes

* Returns statement handle as `number`.
* Always keep the handle stored so you are able to correctly free/close the statement at the end of the script.

```lua
  local env = db2.allocEnv()
  print(env)
  
  local hdl = db2.allocConnection(env)
  print(hdl);
  
  db2.Connect(hdl, "*LOCAL")
  
  local stmt = db2.allocStatement(hdl)
  print(stmt)
  
  db2.closeStatement(stmt)
  db2.Disconnect(hdl)
  db2.freeConnection(hdl)
  db2.freeEnv(env)
```

***

#### `db2.executeStatement(hdl, statement)` - Run a valid SQL statement

##### Parameters

1. Statement handle
2. SQL statement (`string`)

##### Notes

* Returns SQLRETURN value as `number`.
* If a SELECT statement is used, you are also able to use `db2.fetch(stmt)`.

```lua
  local env = db2.allocEnv()
  print(env)
  
  local hdl = db2.allocConnection(env)
  print(hdl);
  
  db2.Connect(hdl, "*LOCAL")
  
  local stmt = db2.allocStatement(hdl)
  print(stmt)
  
  local execres = db2.executeStatement(stmt, "INSERT INTO MYFILE VALUES('Goodbye', 1234.57)") 
  print(execres)
  
  db2.closeStatement(stmt)
  db2.Disconnect(hdl)
  db2.freeConnection(hdl)
  db2.freeEnv(env)
```

***

#### `db2.fetch(stmt)` - Fetch the first or next row from a table

##### Parameters

1. Statement handle

##### Notes

* Returns SQLRETURN value as `number`. (`0` is successful)
* To get the columns out of a fetch, use `db2.getColumn(stmt, col, type, len)`.

```lua
  local env = db2.allocEnv()
  local hdl = db2.allocConnection(env)
  db2.Connect(hdl, "*LOCAL")
  local stmt = db2.allocStatement(hdl)
  
  local execres = db2.executeStatement(stmt, "SELECT * FROM #LALLAN/MYFILE") 
  
  local retval
  while db2.fetch(stmt) == 0.0 do
    retval = db2.getColumn(stmt, 2, db2.SQLCHAR, 10)
    print(retval)
  end
  
  db2.closeStatement(stmt)
  db2.Disconnect(hdl)
  db2.freeConnection(hdl)
  db2.freeEnv(env)
```
