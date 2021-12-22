#include <iostream>
#include <string>
#include <map>

std::string upCase(std::string a){
    auto it = a.begin();
    while (it != a.end()){
        *it = ::tolower(*it);
        ++it;
    }
    return a;
}

int main() 
{
    std::map<std::string,int> a;
    int broj = 0;
    std::string unos;

    while(std::cin >> unos){
        auto find = a.find(unos);
        auto findup = a.find( upCase(unos) );
        if(find != a.end())
            ++(find -> second);
        else if( findup != a.end() )
            --(findup -> second);
        else
            a[unos] = 1;
    }

    auto it = a.begin();

    while(it != a.end())
    ( (it -> second) < 1 ) ? it = a.erase(it) : ++it;

    for (auto &&i : a)
    {
        std::cout << i.first << ": " << i.second << std::endl;
    }

    return 0;
}