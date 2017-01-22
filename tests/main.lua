
print("my first Lua script!")

local myNum = 5

do
  while myNum > 0 do
    print(string.format("myNum: %d", myNum))
    myNum = myNum - 1
  end
end

do
  for k, v in pairs(os.date("*t")) do print(k, v) end
end

do
  os.execute("echo hello")
end

do
  print(os.getenv("LANG"))
end

do
  local t = os.date('*t')
  print(string.format("Time: %d", os.time(t)))
end