
do
  local env = db2.allocEnv()
  print(env)
  
  local hdl = db2.allocConnection(env)
  print(hdl);
  
  db2.Connect(hdl, "*LOCAL")
  
  local stmt = db2.allocStatement(hdl)
  print(stmt)
  
  local execres = db2.executeStatement(stmt, "SELECT * FROM #LALLAN/MYFILE") 
  print(execres)
  
  local sqlchar = db2.SQLCHAR
  local sqlnum = db2.SQLNUMERIC
  
  print(sqlchar)
  print(sqlnum)
  
  local retval
  while db2.fetch(stmt) == 0.0 do
    retval = db2.getColumn(stmt, 2, 10)
    print(retval)
    retval = db2.getColumn(stmt, 1, 10)
    print(retval)
  end
  
  local stmt = db2.closeStatement(stmt)
  
  db2.Disconnect(hdl)
  
  local hdleres = db2.freeConnection(hdl)
  local envres = db2.freeEnv(env)
end
