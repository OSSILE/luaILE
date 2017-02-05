
do
  local env = db2.allocEnv()
  print(env)
  
  local hdl = db2.allocConnection(env)
  print(hdl);
  
  db2.Connect(hdl, "*LOCAL")
  
  local stmt = db2.allocStatement(hdl)
  print(stmt)
  
  local execres = db2.executeStatement(stmt, "SELECT DEPTNO, DEPTNAME, MGRNO FROM sample/DEPARTMENT") 
  print(execres)
  
  local retval
  while db2.fetch(stmt) == 0.0 do
    retval = db2.getColumn(stmt, 1, 3)
    print(retval)
    retval = db2.getColumn(stmt, 2, 36)
    print(retval)
    retval = db2.getColumn(stmt, 3, 6)
    if retval ~= db2.NULL then
      print(retval)
    end
  end
  
  local stmt = db2.closeStatement(stmt)
  
  db2.Disconnect(hdl)
  
  local hdleres = db2.freeConnection(hdl)
  local envres = db2.freeEnv(env)
end
