class A(object):
    value = 1
    def say(self):
        print self
        print "world"
a = A()
print A  #<type:__main__.A>
print a  #自建类型，使用默认print方法，打印地址
print a.value #1
#添加额外的属性，但只在对象a中存在，使用STORE_ATTR
a.field = "hello"

print a.field #"hello"
a.say() #打印地址 + "world"