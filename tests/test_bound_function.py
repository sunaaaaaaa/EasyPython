class A(object):
    def __init__(self,v):
        self.value = v

a = A(1)
lst = []
lst.append(2)
print lst
#此处生成一个Method对象，其中own字段为lst对象，Method对象在Klass获取属性的时候获取
a.foo = lst.append
a.foo(3)
print lst
print A

b = A(2)

def func(self,s):
    print self.value
    print s

a.bar = func #此时绑定的是一个函数，因为a是对象，不是类型
A.bar = func #此时为类型A添加一个方法

a.bar(a,"hello")#此时需要传入a，否则缺少参数
b.bar("yayaya") #此时不需要传入b，因为bar是个方法