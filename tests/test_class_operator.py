#测试运算符重载，目前仅实现加法
class A(object):
    def __init__(self,v):
        self.value = v

    def __add__(self,a):
        print "executing operator +"
        return A(self.value + a.value)
    def __call__(self,a):
        if self.value > a.value:
            print "gt"
        elif self.value < a.value:
            print "lt"
        elif self.value == a.value:
            print "eq"
        else:
            print "can not compare"                
    def __getitem__(self,key):
        if key == "hello":
            return "hi"
        elif key == "how are you":
            return "fine"
    def __setitem__(self,key,value):
        print self
        print key
        print value            

a = A(1)
b = A(2)
c = a + b

print a.value
print b.value
print c.value

a(b)#lt
a(a)#eq
b(a)#gt

print a["hello"]
print a["how are you"]
a["one"] = 1