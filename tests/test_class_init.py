class A(object):
    def __init__(self,v):
        self.value = v

a = A(1)
print a.value
b = A(2)

a.field = 3

A.field = 4

print a.field
print b.field
print A.field