lst = [1,"hello",2,"world"]
#排序
lst.reverse()
print lst

lst.sort()
print lst

#删除测试
del lst[0]
print lst #[hello,2,world]
lst.pop()
print lst #[hello,2]
lst.remove("hello")
print lst #[2]

#比较
t = ["a",2,"c",1,"b",3]

a = ["a",1,"c",1]

if t < a:
    print "t"
else:
    print "a"    