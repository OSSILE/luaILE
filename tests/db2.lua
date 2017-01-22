
do
  local env = db2.allocEnv()
  print(env)
  local res = db2.freeEnv(env)
end