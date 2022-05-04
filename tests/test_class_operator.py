#测试运算符重载，目前仅实现加法
class A(object):
    def __init__(self,v):
        self.value = v

    def __add__(self,a):
        print "executing operator +"
        return A(self.value + a.value)

a = A(1)
b = A(2)
c = a + b

print a.value
print b.value
print c.value