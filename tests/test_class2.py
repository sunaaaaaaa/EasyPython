class A(object):
    value = 1
    def say(self):
        print self
        print "world"
a = A()
print A
print a
print a.value
#添加额外的属性，但只在对象a中存在，使用STORE_ATTR
a.field = "hello"

print a.field
a.say()