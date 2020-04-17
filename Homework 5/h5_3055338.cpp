/*
Task: H5
Family Name: Mia
Given Name: Mohammad Lal Mahmud
Matriculation number: 3055338
Uni-Email: mohammad.mia@stud.uni-due.de
Course of Studies: ISE CE
*/
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>

#define SCREEN_WIDTH 78

using namespace std;

enum OperatingSystem { UNKNOWN, ANDROID, IOS, MACOS, LINUX, PROPRIETARY, UNIX, WINDOWS };
string operatingSystemString[] = {
    "Unknown OS","Android OS","iOS","MacOS","Linux OS"
    ,"proprietary OS","Unix OS","MS Windows OS"};

class Article {
    private:
        string model;
        double netPrice;
        double taxRate;
    public:
        Article(string name,double price, double tax = 0.19) : model(name),netPrice(price),taxRate(tax) {}

        virtual ~Article() {
            cout<<" ";
            cout<<"~Article() " << model;
            cout<<endl;
        }

        void set_model(string model) {
            this->model = model;
        }

        void set_netPrice(double netPrice) {
            this->netPrice = netPrice;
        }

        string get_model() {
            return model;
        }

        double get_netPrice(){
            return netPrice;
        }

        double get_grossPrice(){
            return netPrice + taxRate * netPrice;
        }

        virtual void print() = 0;
};

class Accessory : public Article {
    private:
        bool original;
    public:
        Accessory(string model, double netPrice, bool orig = true) : Article(model,netPrice),original(orig) { }

        virtual ~Accessory(){
            cout<<" ";
            cout<<"~Accessory()";
        }

        virtual void print(){
            cout<<get_model();
            cout<<((original)?" (original accessory)\r\n":"\r\n");
        }
};

ostream& operator<<(ostream& o, const OperatingSystem& os) {
    o<<operatingSystemString[os];
    return o;
}

class Device : public Article {
    private:
        int memory;
        OperatingSystem os;
    public:
        Device(string name, double price, int mem, OperatingSystem os = OperatingSystem::UNKNOWN) : Article(name,price),os(os),memory(mem) {}

        virtual ~Device() {
            cout<<" ";
            cout<<"~Device()";
        }

        OperatingSystem get_os() {
            return os;
        }

        virtual void print() {
            cout<<get_model();
            cout<<", RAM ";
            cout<<memory;
            cout<<"GB, ";
            cout<<os;
        }
};

class Notebook : public Device {
    private:
        string drive;
        bool convertible;
    public:
        Notebook(string name, double price, int memory, string drv, OperatingSystem os = OperatingSystem::LINUX, bool convert = false) : Device(name,price,memory,os),drive(drv),convertible(convert) { }

        virtual ~Notebook(){
            cout<<" ";
            cout<<"~Notebook()";
        }

        bool is_a_convertible() {
            return convertible;
        }

        virtual void print(){
            Device::print();
            if (is_a_convertible())
                cout<<" (convertible) ";
            cout<<", "<<drive;
            cout<<endl;
        }
};

class Phone : public Device {
    public:
        Phone(string name, double price,int memory = 4,OperatingSystem os = OperatingSystem::ANDROID) : Device(name,price,memory,os){

        }
        virtual ~Phone(){
            cout<<" ";
            cout<<"~Phone()";
        }
        virtual void print(){
            Device::print();
            cout<<" phone\r\n";
        }
};

class InCart {
    private:
        Article *article;
        int amount;
        InCart *next;
    public:
        InCart(Article *artcl, int count = 0, InCart *n = NULL) : article(artcl),amount(count),next(n) { }

        virtual ~InCart(){
            cout<<"~InCart() "<<amount;
            delete article;
        }

        InCart* get_next() {
            return next;
        }

        virtual void print() {
            cout<<" ";
            cout<<amount;
            cout<<" ";
            article->print();
            cout<<setw(50)<<right<<setprecision(2)<<fixed<<article->get_grossPrice()<<" EUR";
            cout<<right<<setw(20)<<fixed<<amount*article->get_grossPrice() << " EUR\r\n";
        }
};

class ShoppingCart {
    private:
        InCart *articles;
        double minFreeShipping;
        double sumNetPrice;
        double sumGrossPrice;
    public:
        ShoppingCart(){
            articles = NULL;
            minFreeShipping = 1000;
            sumGrossPrice = sumNetPrice = 0;
        }
        ~ShoppingCart(){
            cout<<"~ShoppingCart()\r\n";
            InCart *cart = articles;
            while (true) {
                if (!cart)
                    break;
                InCart *cart2 = cart;
                cart = cart->get_next();
                cout<<"delete article: ";
                delete cart2;
            }
        }

        void set_minFreeShipping(double minFreeShipping) {
            this->minFreeShipping = minFreeShipping;
        }

        void add_article(int amount, Article *article) {
            sumNetPrice += amount * article->get_netPrice();
            sumGrossPrice += amount * article->get_grossPrice();
            if (articles)
                articles = new InCart(article,amount,articles);
            else
                articles = new InCart(article,amount,NULL);

        }

        virtual void print(){
            for (int i=0;i<SCREEN_WIDTH;i++)
                cout<<"+";
            cout<<"\r\n+                        P R O T O - T E C - S H O P                         +"<<endl;
            cout<<"+                     Y O U R   S H O P P I N G C A R T                      +"<<endl;
            for (int i=0;i<SCREEN_WIDTH;i++)
                cout<<"+";
            cout<<endl;
            InCart *cart = articles;
            while (true) {
                if (!cart)
                    break;
                cart->print();
                cart = cart->get_next();
            }
            string singleline = "-------------";
            for (int i=0; i < SCREEN_WIDTH - singleline.length();i++)
                cout<<" ";
            cout<<singleline<<endl;
            cout<<setw(SCREEN_WIDTH - 16)<<right<<"sum net price:";
            cout<<setprecision(2)<<setw(12)<<fixed<<sumNetPrice<<" EUR\r\n";
            cout<<setw(SCREEN_WIDTH - 16)<<right<<"tax:";
            double sumTax = sumGrossPrice - sumNetPrice;
            cout<<setw(12)<<setprecision(2)<<fixed<< sumTax <<" EUR\r\n";
            cout<<setw(SCREEN_WIDTH - 16)<<right<<"sum gross price:";
            cout<<setprecision(2)<<setw(12)<<fixed<< sumGrossPrice <<" EUR\r\n";
            for (int i=0; i < SCREEN_WIDTH - singleline.length();i++)
                cout<<" ";
            cout<<singleline<<endl;
            double shipping = 0.00;
            if (sumGrossPrice<minFreeShipping)
                shipping = 5.90;
            cout<<setw(SCREEN_WIDTH - 16)<<right<<"shipping:";
            cout<<setprecision(2)<<setw(12)<< shipping <<" EUR\r\n";
            for (int i=0; i < SCREEN_WIDTH - singleline.length();i++)
                cout<<" ";
            cout<<singleline<<endl;
            cout<<setw(SCREEN_WIDTH - 16)<<right<<"total:";
            double total = 0;
            if (sumGrossPrice<minFreeShipping)
                total = sumGrossPrice + 5.90;
            else
                total = sumGrossPrice + 0.00;
            cout<<setprecision(2)<<setw(12)<<fixed<< total <<" EUR\r\n";
            string doubleline = "=============";
            for (int i=0; i < SCREEN_WIDTH - doubleline.length();i++)
                cout<<" ";
            cout<<doubleline<<endl<<endl;
        }
};

int main(int argc, char *argv[]) {
    ShoppingCart *basket = new ShoppingCart();
    basket->set_minFreeShipping(500);

    Accessory *powerbank = new Accessory("YOOLOX 10k Wireless Powerbank Qi",31.08,false);
    basket->add_article(3,powerbank);
    basket->print();

    Phone *samsung = new Phone("Samsung Galaxy S10+ SM-G975F/DS Dual SIM",661.67,8,
                                OperatingSystem::ANDROID);
    basket->add_article(1,samsung);

    Phone *apple = new Phone("Apple iPhone 11 Pro 256GB",1097.47,4,OperatingSystem::IOS);
    basket->add_article(2,apple);

    Notebook *asus = new Notebook("ASUS ROG Strix Scar III G731",1586.55,16,
                            "512GB SSD + 1TB SSHD",OperatingSystem::WINDOWS);
    basket->add_article(1,asus);

    basket->print();

    delete basket;
    return EXIT_SUCCESS;
}

