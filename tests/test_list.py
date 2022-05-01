lst = [1,"hello"]

print lst
print lst[0]
print lst[1]

a = "hello"

print a[2]

if "lo" in "hello":
    print "yes"
else:
    print "no"

if "hello" in lst:
    print "yes"
else:
    print "no"  

lst.append(2)
print lst[2] #2

lst.replace(0,4)
print lst  #[4,hello,2]

lst[2] = "world" 

print lst #[4,hello,world]

#删除测试
del lst[0]
print lst #[hello,world]
lst.pop()
print lst #[hello]
lst.remove("hello")
print lst #[]
