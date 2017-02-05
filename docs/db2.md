### DB2 Module documentation

All the DB2 functions are within the `db2` namespace.

##### Function list

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
