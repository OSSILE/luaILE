
do
  local env = db2.allocEnv()
  print(env)
  
  local hdl = db2.allocConnect(env);
  print(hdl);
  
  local hdleres = db2.freeConnect(hdl);
  local envres = db2.freeEnv(env)
end