#include <string>
#include <iostream>

struct Foo {
    Foo(std::string v) 
        : value{v} {}
    std::string value;
};

struct Bar : virtual Foo {
    Bar(std::string v, int x) 
        : Foo{v} , mx{x} {}
    int mx; 
};

struct Baz : virtual Foo {
    Baz(std::string v, double y) 
        : Foo{v} , my{y} {}
    double my; 
};

struct Oof : Bar, Baz {
    Oof(std::string v, int x, double y, bool z) 
        : Foo{v}, Bar{v,x}, Baz{v,y}, mz{z} {}
    bool mz;
};


struct BarNV : Foo {
    BarNV(std::string v, int x) 
        : Foo{v} , mx{x} {}
    int mx; 
};

struct BazNV : Foo {
    BazNV(std::string v, double y) 
        : Foo{v} , my{y} {}
    double my; 
};

struct OofNV : BarNV, BazNV {
    OofNV(std::string v, int x, double y, bool z) 
        : BarNV{v,x}, BazNV{v,y}, mz{z} {}
    bool mz;
};

void fn(Foo*) {}
void fn(Foo&) {}

int staticcast() {
    Foo foo{"MyFoo"};
    Bar bar{"MyBar", 42};
    Baz baz{"MyBaz", 3.14};
    Oof oof{"MyOof", 13, 2.6, false};
    BarNV barnv{"MyBarNV", 42};
    BazNV baznv{"MyBazNV", 3.14};
    OofNV oofnv{"MyOofNV", 13, 2.6, false};

    fn(&foo);
    fn(&bar);
    fn(&baz);
    fn(&oof);
    fn(&barnv);
    fn(&baznv);
    //fn(&oofnv); // Ambiguous: we have two instances of Foo

    fn(foo);
    fn(bar);
    fn(baz);
    fn(oof);
    fn(barnv);
    fn(baznv);
    //fn(oofnv); // Ambiguous: we have two instances of Foo

    // static_cast<target>(source) 

    // Upcasting
    Bar bar_from_oof = static_cast<Bar>(oof); // Casting from Oof to Bar (value)
    Bar bar_from_oof_2 = oof;

    Bar& bar_ref_from_oof = static_cast<Bar&>(oof); // Casting from Oof& to Bar& (reference)
    Bar& bar_ref_from_oof_2 = oof;

    Bar* bar_ptr_from_oof = static_cast<Bar*>(&oof); // Casting from Oof* to Bar* (pointer)
    Bar* bar_ptr_from_oof_2 = &oof;

    // Downcasting

    std::cout << "&oof:" << &oof << '\n';
    //Oof oof_from_bar = static_cast<Oof>(bar_from_oof); // Error: cannot reconstruct information
    Oof& oof_ref_from_bar = static_cast<Oof&>(bar_ref_from_oof);
    //Oof& oof_ref_from_bar_2 = bar_ref_from_oof; // Implicit cast does not work

    Oof* oof_ptr_from_bar = static_cast<Oof*>(bar_ptr_from_oof);
    //Oof* oof_ptr_from_bar_2 = bar_ptr_from_oof; // Implicit cast does not work

    //BazNV baznv_from_barnv = static_cast<BazNV>(barnv);
    //BazNV* baznv_ptr_from_barnv = static_cast<BazNV*>(&barnv);
    OofNV* oofnv_ptr_from_a_bar = static_cast<OofNV*>(&barnv);
    std::cout << "my:" << oofnv_ptr_from_a_bar->my << '\n'; // Garbage
    std::cout << "mz:" << oofnv_ptr_from_a_bar->mz << '\n'; // Garbage

    Foo* foo_ptr_from_oof  = static_cast<Foo*>(&oof); // Upcasting works
    // Oof* oof_ptr_from_foo = static_cast<Oof*>(foo_ptr_from_oof); // Downcasting through a virtual doesn't

    std::cout << "&oof_ref_from_bar:" << &oof_ref_from_bar << '\n';
    std::cout << "oof_ptr_from_bar:" << oof_ptr_from_bar << '\n';

}


int dynamiccast() {
    Foo foo{"MyFoo"};
    Bar bar{"MyBar", 42};
    Baz baz{"MyBaz", 3.14};
    Oof oof{"MyOof", 13, 2.6, false};
    BarNV barnv{"MyBarNV", 42};
    BazNV baznv{"MyBazNV", 3.14};
    OofNV oofnv{"MyOofNV", 13, 2.6, false};


}

int main() {
    staticcast();
    dynamiccast();

}