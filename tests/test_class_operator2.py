keys = []
values = []
class B(object):
    def __init__(self):
        print "init"
    def __setattr__(self,k,v):
        if k in keys:
            index = keys.find(k)
            values[index] = v
        else:
            keys.append(k)
            values.append(v)
    def __getattr__(self,k):
        if k in keys:
            index = keys.find(k)
            return values[index]
        else:
            return None

b = B()
b.foo = 1
b.bar = 2
print b.foo
print b.bar

b.foo = 3
print b.foo