class A(object):
    def say(self):
        print "i am A"

class B(A):
    def say(self):
        print "i am B"

class C(A):
    pass

b = B()
c = C()
b.say()
c.say()    