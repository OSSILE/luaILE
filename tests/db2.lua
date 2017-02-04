
do
  local env = db2.allocEnv()
  print(env)
  
  local hdl = db2.allocConnection(env)
  print(hdl);
  
  db2.Connect(hdl, "*LOCAL")
  
  local stmt = db2.allocStatement(hdl)
  print(stmt)
  
  local execres = db2.executeStatement(stmt, "INSERT INTO #LALLAN/MYFILE VALUES('Goodbye', 1234.57)") 
  print(execres)
  
  db2.printError(env, hdl, stmt)
  
  local stmt = db2.freeStatement(stmt)
  
  db2.Disconnect(hdl);
  
  local hdleres = db2.freeConnection(hdl)
  local envres = db2.freeEnv(env)
end
