/*
Task: H4
Family Name: Mia
Given Name: Mohammad Lal Mahmud
Matriculation number: 3055338
Uni-Email: mohammad.mia@stud.uni-due.de
Course of Studies: ISE CE
*/
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

enum TimeZone { ACT, CET, CST, EST, GMT, MSK, PST, UTC };

enum AoD { Arrival, Diparture };

class LocalTime {

    private:
        int minutes;
        TimeZone timezone;

    public:
        LocalTime() {
            minutes = -1;
            timezone = TimeZone::CET;
        }

        LocalTime(int hour, int minute, TimeZone tz = TimeZone::CET) {
            set_time(hour,minute);
            timezone = tz;
        }

        void set_time(int hour,int minute) {
            bool flag = true;
            if (hour >= 0 && hour <= 23) {
                flag = false;
            }
            if (minute >= 0 && minute <= 59) {
                flag = false;
            }
            if (flag) {
                minutes = -1;
                cout << "error" <<endl;
            }
            else {
                minutes = hour * 60 + minute;
            }
        }

        int get_hour() const{
            return minutes / 60;
        }

        int get_minute() const{
            return minutes % 60;
        }

        bool is_valid() {
            if (minutes == -1 )
                return false;
            else
                return true;
        }
        friend ostream& operator<<(ostream& os, const LocalTime& localtime);
};

ostream& operator<<(ostream& os, const LocalTime& localtime) {
    if (localtime.get_hour() >= 10)
        os << localtime.get_hour();
    else
        os << "0" << localtime.get_hour();
    os<< ":";
    if (localtime.get_minute() >= 10)
        os << localtime.get_minute();
    else
        os << "0" << localtime.get_minute();
    return os;
}

class Flight {
    private:
        AoD aod;
        string code;
        string destination;
        string gate;
        string checkIn;
        string comment;
        LocalTime expected;

    public:
        Flight(AoD aod, string c, string d, string g, string cIn = "");
        ~Flight();
        string get_code();
        string get_destination();
        string get_gate();
        string get_checkIn();
        string get_comment();
        LocalTime get_scheduled();
        void set_expected(LocalTime localtime);
        void set_comment(string c);
        bool is_Arrival();
        bool is_Diparture();
        void print(LocalTime localtime);


};

Flight::Flight(AoD aod, string c, string d, string g, string cIn) {
    this->aod = aod;
    code = c;
    destination = d;
    gate = g;
    checkIn = cIn;
    comment = "";
}

Flight::~Flight() {
    cout<<"flight "<<code<<" deleted"<<endl;
}

string Flight::get_code() {
    return code;
}
string Flight::get_destination() {
    return destination;
}
string Flight::get_gate() {
    return gate;
}
string Flight::get_checkIn() {
    return checkIn;
}
string Flight::get_comment() {
    return comment;
}
LocalTime Flight::get_scheduled() {
    return expected;
}
void Flight::set_expected(LocalTime localtime) {
    expected = localtime;
}
void Flight::set_comment(string c) {
    comment = c;
}
void Flight::print(LocalTime localtime) {
    cout<<left<<setw(9)<< code <<setw(24)<< destination;
    cout<<"    "<<localtime;
    if (expected.is_valid())
        cout<<" "<<expected<<"    ";
    else
        cout<<"          ";
    cout<<left<<setw(5)<< gate <<setw(9)<< checkIn << comment << endl;
}
bool Flight::is_Arrival() {
    if (aod == AoD::Arrival)
        return true;
    else
        return false;
}
bool Flight::is_Diparture() {
    if (aod == AoD::Diparture)
        return true;
    else
        return false;
}

class Airport {
    private:
        string name;
        Flight *slot[24][60];

    public:
        Airport(string n) {
            name = n;
            for (int i=0;i<24;i++) {
                for (int j=0;j<60;j++) {
                    slot[i][j] = nullptr;
                }
            }
        }
        ~Airport() {
            for (int i=0;i<24;i++) {
                for (int j=0;j<59;j++)
                    delete slot[i][j];
            }
        }

        void schedule(LocalTime l, Flight *flight) {
            if (l.is_valid())
                slot[l.get_hour()][l.get_minute()] = flight;
        }

        void delay(LocalTime l1, LocalTime l2) {
            if (l1.is_valid() && l2.is_valid()){
                slot[l2.get_hour()][l2.get_minute()] = slot[l1.get_hour()][l1.get_minute()];
                slot[l1.get_hour()][l1.get_minute()] = nullptr;
            }
        }

        void print(AoD ad) {
            if (ad == AoD::Arrival) {
                cout << name << " ARRIVALS" << endl;
                for (int i=0; i< name.length();i++)
                    cout << "=";
                cout << "=========";
                cout<<endl;
                cout<<"Flight   From                    Scheduled Expected Gate Check-in Comments"<<endl;
                for (int i=0; i< 24; i++) {
                    for (int j=0;j<59;j++) {
                        if (slot[i][j] && slot[i][j]->is_Arrival())
                                slot[i][j]->print(LocalTime(i,j));
                    }
                }
            }
            else {
                cout << name << " DEPARTURES" << endl;
                for (int i=0; i< name.length();i++)
                    cout << "=";
                cout<<"===========";
                cout<<endl;
                cout<<"Flight   To                      Scheduled Expected Gate Check-in Comments"<<endl;
                for (int i=0; i< 24; i++) {
                    for (int j=0;j<59;j++) {
                        if (slot[i][j] && slot[i][j]->is_Diparture())
                                slot[i][j]->print(LocalTime(i,j));
                    }
                }
            }
            cout<<endl;
        }
};

int main() {
    Airport *a = new Airport("DUSSELDORF AIRPORT");

    Flight *munich = new Flight(AoD::Arrival, "LH 2010", "Munich", "A04");
    a->schedule(LocalTime(12,40),munich);
    munich->set_expected(LocalTime(13,5));
    Flight *manchester = new Flight(AoD::Arrival, "EW 9347", "Manchester", "B04");
    a->schedule(LocalTime(14,50),manchester);
    Flight *paris = new Flight(AoD::Diparture, "AF 1307", "Paris", "B51","192-194");
    paris->set_comment("departed");
    a->schedule(LocalTime(9,10),paris);
    Flight *moscow = new Flight(AoD::Diparture, "SU 2537", "Moscow", "C31","252-255");
    moscow->set_comment("boarding");
    a->schedule(LocalTime(10,40),moscow);
    Flight *london = new Flight(AoD::Diparture, "EW 9466", "London-Heathrow", "B35","151-170");
    a->schedule(LocalTime(11,15),london);
    Flight *munich2 = new Flight(AoD::Diparture, "LH 2011", "Munich", "A40","115-120");
    munich2->set_comment("Code Sharing");
    a->schedule(LocalTime(13,25),munich2);
    Flight *izmir = new Flight(AoD::Diparture, "XQ 959", "Izmir", "C45","240-242");
    izmir->set_expected(LocalTime(15,20));
    a->schedule(LocalTime(14,55),izmir);

    a->print(AoD::Arrival);
    a->print(AoD::Diparture);
    delete a;
    return 0;
}
