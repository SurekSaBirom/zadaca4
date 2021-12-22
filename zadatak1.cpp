#include <iostream>
#include <list>

template <typename t>
t& funk( std::list<t>& L, int q){
    auto it = L.begin();
    for(int i = 0; i < q; ++i)
        ++it;
    t& p = *it;
    return p;
}

int main() {
 
    std::list<int> a;
    int k;
    auto it = back_inserter(a);

    while(std::cin >> k) *it = k;  //a.push_back(k);

    a.sort();

    auto it_begin = a.begin();
    auto it_end = a.end();
    std::cout << *it_begin << ' ' << *(--it_end) << std::endl;


    // provjeravanje da li funkcija radi ispravno :
    auto& u = funk(a, 1);
    u += 5;
    for (auto &&i : a) 
    {
        std::cout << i << '-';
    }
    std::cout << "\b \n";

    return 0;
}