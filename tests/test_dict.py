d = {1:"hello","world":2}

print d
print d[1]
print d["world"]

#测试默认值
d.setdefault(1,2)
d.setdefault(2,3)
print d #{1:"hello",2:3,"world":2}

#测试添加
d[3] = "xxx"
print d
#测试删除
d.remove(3)
print d
del d["world"]
print d

a = {1:"a",2:"b"}
#迭代
print a.keys()   #[1,2]
print a.values() #[a,b]

for v in a.values():  #a,b
    print v

print a.items()

for k,v in a.items():
    print k,v

for k in a.iterkeys():
    print k