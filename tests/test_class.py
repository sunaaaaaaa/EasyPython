print list
print dict
print str
print int

t = type(1)
print t
print type(t)

i = 0

while i < 5:
    t = type(t)
    print t
    i = i + 1

#通过类型创建对象
a = int()
print a

b = str()
print b

c = list()
print c

d = dict()
print d