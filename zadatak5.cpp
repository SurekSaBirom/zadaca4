#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <thread>
#include <chrono>
#include <unistd.h>

struct racun{
    private:
        std::string brojKartice;
        std::string pin;
        double stanje;
    public:

        racun() = default;

        racun(std::string a, double c, std::string b = "0000") 
        : brojKartice{a}, pin{b}, stanje{c}
        {}

        void ispisBrojKart(){ 
            std::string sakr;
            auto p = back_inserter(sakr);
            std::copy( brojKartice.begin(), brojKartice.begin() + 4, p );
            std::cout  << sakr << " **** **** ****" << std::endl; 
        }
        
        void provjStanje(){ std::cout << stanje << std::endl; }
        
        std::string pin_() const { return pin; }
        std::string racun_() const {return brojKartice;}
        double stanje_() const {return stanje;}

        void promjStanje(double a){ stanje = a;}
};


struct bankomat{
    private:
        std::string sifra{"ledzeppelin"};
        std::vector<std::string> historija;
    public:

        bool autorizacija(racun& a){
            std::cout << "\nUnesite vas pin: ";
            std::string p;
            for(int i = 1;; ++i){
                std::cin >> p;
                if(p != a.pin_()){
                    if(i==3){
                    std::cout << "\nPogresan unos pina 3 puta, program pauziran" << std::endl;
                    }
                    if(i==3){
                        i = 1;
                        std::this_thread::sleep_for(std::chrono::seconds(5));
                    }
                    std::cout << "\nPin code nije tacan, pokusajte ponovo: ";
                    continue;
                }
                break;
            }
            return true;
        }

        void dizanjeNovca (racun& kor){
            double a = kor.stanje_();
            int diz = 0;
            std::cout << "Unesite kolicinu za podici (mora biti djeljivo sa 10): ";
            while(std::cin >> diz){
                if(diz%10!=0){ 
                    std::cout << "\nMora biti djeljiv sa 10: ";
                    continue;
                }
                if( diz > a+1 ){
                    std::cout << "\nNemoguce je podici vise sredstava nego sto je na racunu.\n";
                    continue;
                }
                std::string his = "Korisnik sa brojem racuna " + kor.racun_() + " je podigao " + std::to_string(diz) + "KM.\n";
                historija.push_back(his);
                kor.promjStanje(a-diz-1);
                break;
            }
        }

        void uplacivanje(racun& kor){
            double a = kor.stanje_();
            int diz = 0;
            std::cout << "Unesite kolicinu za uplatiti (mora biti djeljivo sa 10): ";
            while(std::cin >> diz){
                if(diz%10!=0){ 
                    std::cout << "\nMora biti djeljiv sa 10: ";
                    continue;
                }
                if( diz <= 0 ){
                    std::cout << "\nUneseni broj mora biti pozitivan: \n";
                    continue;
                }
                std::string his = "Korisnik sa brojem racuna " + kor.racun_() + " je uplatio " + std::to_string(diz) + "KM.\n";
                historija.push_back(his);
                kor.promjStanje(a+diz);
                break;
            }
        }

        void provjera(racun& kor){
            double a = kor.stanje_();
            if(a < 0.5)
                std::cout << "Nemate dovoljno sredstava za ovu operaciju." << std::endl;
            else{
                std::cout << a-0.5;
                kor.promjStanje(a-0.5);
                std::string his = "Korisnik sa brojem racuna " + kor.racun_() + " je provjerio stanje racuna.\n";
            }
        }

        void ispisHistorije(){
            std::cout << "Sifra bankomata: ";
            std::string a;
            std::cin >> a;
            for (auto &&i : historija)
            {
                std::cout << i;
            }
            
        }

};

int main(int argc, const char** argv) 
{
    std::map< std::string, racun> m;
    bankomat bank;

    while(std::cin){
        std::string a1; std::string a2; double a3;
        std::cout << "Unos novog korisnickog racuna u sistem:\nUnesite broj kartice: ";
        std::cin >> a1;
        while(a2.size() != 4){
        std::cout << "Unesite pin (4 znaka): ";
        std::cin >> a2;
        if(!(std::cin)) break;
        }
        std::cout << "Pocetno stanje: ";
        std::cin >> a3;
        if(!(std::cin)) {
            std::cout << "\nKorisnik nije sacuvan u bazu" << std::endl;
            break;}
        racun b{a1, a3, a2};
        m[a1] = b;
    }
    std::cin.clear();
    clearerr(stdin);

    auto it = m.begin();
    std::string operacija;
    
    while(std::cin){
        std::cout<< "Broj racuna: ";
        std::cin >> operacija;
        auto pron = m.find(operacija);
        if(pron == m.end()){
            std::cout << "Korisnicki racun nije pronadjen." << std::endl;
            continue;
        }
        racun temp = pron -> second;
        while(!(bank.autorizacija(temp))){
            std::cout << "PIN: ";
        }
        while(std::cin){
        std::cout << "Unesite ime operacije (uplata, isplata, provjera): ";
        std::cin >> operacija;
        if(operacija=="uplata") bank.uplacivanje(temp);
        else if (operacija=="isplata") bank.dizanjeNovca(temp);
        else if (operacija=="provjera") bank.provjera(temp);
        }
        std::cin.clear();
        clearerr(stdin);
    }
    std::cin.clear();
    clearerr(stdin);
    std::cout << std::endl;
    bank.ispisHistorije();

    return 0;
}