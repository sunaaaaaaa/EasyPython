#include "integer.h"
#include "dict.h"
#include "String.h"
#include "../runtime/universe.h"
#include<iostream>
namespace easy_vm{

IntegerKlass* IntegerKlass::instance = NULL;

IntegerKlass::IntegerKlass(){
   Type* type = new Type();
   type->setOwnKlass(this);
   setSuper(ObjectKlass::getInstance());
   setKlassDict(new Dict());
   setName(new String("int"));
}

IntegerKlass* IntegerKlass::getInstance(){
   if(instance == NULL){
      instance = new IntegerKlass();
   }
   return instance;
}

void IntegerKlass::print(Object* obj){
   Integer* i = static_cast<Integer*>(obj);
    
   assert(i && (i->klass()==static_cast<Klass*>(this)));
   std::cout << std::dec << i->value() <<std::endl; 
}

Object* IntegerKlass::allocateInstance(Object* objType,std::vector<Object*>* args){
   if(!args || args->size()==0){
      return new Integer(0);
   }else{
      return NULL;
   }
} 

Object* IntegerKlass::add(Object* l,Object* r){
   if(l->klass()!=r->klass()){
      std::logic_error("integer add error,lvalue class is not sameple to rvalue class");
   }

   Integer* il = static_cast<Integer*>(l);
   Integer* ir = static_cast<Integer*>(r);
    
   assert(il && (il->klass()==static_cast<Klass*>(this)));
   assert(ir && (ir->klass()==static_cast<Klass*>(this)));
   return new Integer(il->value() + ir->value());
}

Object* IntegerKlass::sub(Object* l,Object* r){
   if(l->klass()!=r->klass()){
       std::logic_error("integer sub error,lvalue class is not sameple to rvalue class");
    }

   Integer* il = static_cast<Integer*>(l);
   Integer* ir = static_cast<Integer*>(r);
    
   assert(il && (il->klass()==static_cast<Klass*>(this)));
   assert(ir && (ir->klass()==static_cast<Klass*>(this)));
   return new Integer(il->value() - ir->value());
}

Object* IntegerKlass::mul(Object* l,Object* r){
   if(l->klass()!=r->klass()){
       std::logic_error("integer mul error,lvalue class is not sameple to rvalue class");
    }

   Integer* il = static_cast<Integer*>(l);
   Integer* ir = static_cast<Integer*>(r);
    
   assert(il && (il->klass()==static_cast<Klass*>(this)));
   assert(ir && (ir->klass()==static_cast<Klass*>(this)));

   return new Integer(il->value() * ir->value());
}

Object* IntegerKlass::div(Object* l,Object* r){
   if(l->klass()!=r->klass()){
       std::logic_error("integer div error,lvalue class is not sameple to rvalue class");
    }

   Integer* il = static_cast<Integer*>(l);
   Integer* ir = static_cast<Integer*>(r);
    
   assert(il && (il->klass()==static_cast<Klass*>(this)));
   assert(ir && (ir->klass()==static_cast<Klass*>(this)));

   return new Integer(il->value() / ir->value());
}

Object* IntegerKlass::mod(Object* l,Object* r){
    if(l->klass()!=r->klass()){
       std::logic_error("integer mod error,lvalue class is not sameple to rvalue class");
    }

    Integer* il = static_cast<Integer*>(l);
    Integer* ir = static_cast<Integer*>(r);
    
    assert(il && (il->klass()==static_cast<Klass*>(this)));
    assert(ir && (ir->klass()==static_cast<Klass*>(this)));

   return new Integer(il->value() % ir->value());
}

Object* IntegerKlass::greater(Object* l,Object* r){
   if(l->klass()!=r->klass()){
      // std::logic_error("compare op error,lvalue class is not sameple to rvalue class");
      if(Klass::compareKlass(l->klass(),r->klass()) < 0){
         return Universe::False;
      }else{
         return Universe::True;
      }
   }

   Integer* il = static_cast<Integer*>(l);
   Integer* ir = static_cast<Integer*>(r);
    
   assert(il && (il->klass()==static_cast<Klass*>(this)));
   assert(ir && (ir->klass()==static_cast<Klass*>(this)));
   if(il->value() > ir->value()){
      return Universe::True;
   }else{
      return Universe::False;
   }
}
Object* IntegerKlass::less(Object* l,Object* r){
   
   if(l->klass()!=r->klass()){
      // std::logic_error("compare op error,lvalue class is not sameple to rvalue class");
      if(Klass::compareKlass(l->klass(),r->klass()) < 0){
         return Universe::True;
      }else{
         return Universe::False;
      }
   }

   Integer* il = static_cast<Integer*>(l);
   Integer* ir = static_cast<Integer*>(r);
    
   assert(il && (il->klass()==static_cast<Klass*>(this)));
   assert(ir && (ir->klass()==static_cast<Klass*>(this)));
   if(il->value() >= ir->value()){
      return Universe::False;
   }else{
      return Universe::True;
   }
}
Object* IntegerKlass::equal(Object* l,Object* r){
    if(l->klass()!=r->klass()){
       return Universe::False;
    }

    Integer* il = static_cast<Integer*>(l);
    Integer* ir = static_cast<Integer*>(r);
    
    assert(il && (il->klass()==static_cast<Klass*>(this)));
    assert(ir && (ir->klass()==static_cast<Klass*>(this)));
    if(il->value() == ir->value()){
      return Universe::True;
   }else{
      return Universe::False;
   }
}

Object* IntegerKlass::not_equal(Object* l,Object* r){
   if(l->klass()!=r->klass()){
       return Universe::False;
    }

    Integer* il = static_cast<Integer*>(l);
    Integer* ir = static_cast<Integer*>(r);
    
    assert(il && (il->klass()==static_cast<Klass*>(this)));
    assert(ir && (ir->klass()==static_cast<Klass*>(this)));
    if(il->value() != ir->value()){
      return Universe::True;
   }else{
      return Universe::False;
   }
}
Object* IntegerKlass::ge(Object* l,Object* r){
   if(l->klass()!=r->klass()){
      // std::logic_error("compare op error,lvalue class is not sameple to rvalue class");
      if(Klass::compareKlass(l->klass(),r->klass()) <= 0){
         return Universe::False;
      }else{
         return Universe::True;
      }
   }

   Integer* il = static_cast<Integer*>(l);
   Integer* ir = static_cast<Integer*>(r);
    
   assert(il && (il->klass()==static_cast<Klass*>(this)));
   assert(ir && (ir->klass()==static_cast<Klass*>(this)));
   if(il->value() >= ir->value()){
      return Universe::True;
   }else{
      return Universe::False;
   }
}
Object* IntegerKlass::le(Object* l,Object* r){
   if(l->klass()!=r->klass()){
      // std::logic_error("compare op error,lvalue class is not sameple to rvalue class");
      if(Klass::compareKlass(l->klass(),r->klass()) < 0){
         return Universe::True;
      }else{
         return Universe::False;
      }
   }

   Integer* il = static_cast<Integer*>(l);
   Integer* ir = static_cast<Integer*>(r);
    
   assert(il && (il->klass()==static_cast<Klass*>(this)));
   assert(ir && (ir->klass()==static_cast<Klass*>(this)));
   if(il->value() <= ir->value()){
      return Universe::True;
   }else{
      return Universe::False;
   }
}

}