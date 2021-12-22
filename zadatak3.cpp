#include <vector>
#include <map>
#include <list>
#include <iostream>

template <typename t>
void ispisi(t a){
    auto it = a.begin();
    while( it != a.end() ){
        std::cout << *it << ", ";
        ++it;
    }
    std::cout << "\b\b.\n";
}

int main(int argc, const char** argv) 
{
    
    std::vector<int> niz1{1,2,3};
    std::list<float> niz2{1.1,2.2,3.3};
    ispisi(niz1);
    ispisi(niz2);

    return 0;
}