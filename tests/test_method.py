def foo():
    print "hello"

class A(object):
    def func(self):
        print self
        print "world"

a = A()
a.func()            