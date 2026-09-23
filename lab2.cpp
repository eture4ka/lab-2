#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Transistor {
private:
    string type;        
    double gain;        
    double maxCurrent;  

public:
    Transistor() {
        type = "Nevidomyy";
        gain = 1.0;
        maxCurrent = 0.1;
        cout << "[Konstruktor za zamovchuvannyam] stvoreno obyekt \"" << type << "\"" << endl;
    }

    Transistor(string t) {
        type = t;
        gain = 1.0;
        maxCurrent = 0.1;
        cout << "[Konstruktor z 1 parametrom] stvoreno obyekt \"" << type << "\"" << endl;
    }

    Transistor(string t, double g, double i) {
        type = t;
        gain = (g > 0) ? g : 1.0;
        maxCurrent = (i > 0) ? i : 0.1;
        cout << "[Konstruktor z 3 parametramy] stvoreno obyekt \"" << type << "\"" << endl;
    }

    Transistor(const Transistor& other) {
        type = other.type;
        gain = other.gain;
        maxCurrent = other.maxCurrent;
        cout << "[Konstruktor kopiyuvannya] skopiyovano obyekt \"" << type << "\"" << endl;
    }

    ~Transistor() {
        cout << "[Destruktor] znyshcheno obyekt \"" << type << "\"" << endl;
    }

    void setType(string t) {
        if (t.empty()) {
            cout << "  ! Pomylka: typ tranzystora ne mozhe buty porozhnim. Znachennya ne zmineno." << endl;
            return;
        }
        type = t;
    }

    void setGain(double g) {
        if (g <= 0) {
            cout << "  ! Pomylka: koefitsiyent pidsylennya maye buty bilshym za 0 (zadano "
                 << g << "). Znachennya ne zmineno." << endl;
            return;
        }
        if (g > 10000) {
            cout << "  ! Pomylka: koefitsiyent pidsylennya " << g
                 << " zanadto velykyy (max 10000). Znachennya ne zmineno." << endl;
            return;
        }
        gain = g;
    }

    void setMaxCurrent(const double& i) {
        if (i <= 0) {
            cout << "  ! Pomylka: strum maye buty bilshym za 0 (zadano "
                 << i << " A). Znachennya ne zmineno." << endl;
            return;
        }
        if (i > 100) {
            cout << "  ! Pomylka: strum " << i
                 << " A perevyshchuye dopustymu mezhu 100 A. Znachennya ne zmineno." << endl;
            return;
        }
        maxCurrent = i;
    }

    string getType() const { return type; }
    double getGain() const { return gain; }
    double getMaxCurrent() const { return maxCurrent; }

    void input() {
        string t;
        double g, i;
        cout << "Vvedit typ tranzystora: ";
        cin.ignore();
        getline(cin, t);
        cout << "Vvedit koefitsiyent pidsylennya: ";
        cin >> g;
        cout << "Vvedit maksymalnyy strum (A): ";
        cin >> i;
        setType(t);
        setGain(g);
        setMaxCurrent(i);
    }

    void print() const {
        cout << "  Typ: " << left << setw(12) << type
             << " | Koef. pidsylennya: " << right << setw(7) << fixed << setprecision(1) << gain
             << " | Max strum: " << setw(6) << setprecision(2) << maxCurrent << " A" << endl;
    }

    void copyFrom(const Transistor& other) {
        type = other.type;
        gain = other.gain;
        maxCurrent = other.maxCurrent;
        cout << "  > dani skopiyovano z obyekta \"" << other.type << "\"" << endl;
    }

    double power(double voltage) const {
        return voltage * maxCurrent;
    }
};

void upgradeGain(Transistor& t, double newGain) {
    cout << "Zmina koefitsiyenta pidsylennya obyekta \"" << t.getType() << "\":" << endl;
    t.setGain(newGain);
}

int main() {
    system("chcp 65017 > nul");

    cout << "===== STVORENNYA OBYEKTIV =====" << endl;

    Transistor unknownDevice;                               
    Transistor powerSwitch("IRF540N");                     
    Transistor amplifierKT315("KT315B", 200.0, 0.1);     
    Transistor amplifierCopy(amplifierKT315);            

    cout << endl << "===== INTERAKTYVNE VVEDENNYA DANYKH =====" << endl;
    cout << "Vvedit dani dlya pershoho tranzystora (unknownDevice):" << endl;
    unknownDevice.input();

    cout << endl << "===== POCHATKOVI DANI =====" << endl;
    unknownDevice.print();
    powerSwitch.print();
    amplifierKT315.print();
    amplifierCopy.print();

    cout << endl << "===== ZMINA POLIV ZA ZNACHENNYAM =====" << endl;
    powerSwitch.setType("MOSFET");
    powerSwitch.setGain(1500.0);
    powerSwitch.print();

    cout << endl << "===== ZMINA POLIV ZA POSYLANNYAM =====" << endl;
    double current = 33.0;
    powerSwitch.setMaxCurrent(current);   
    upgradeGain(amplifierKT315, 350.0);   
    powerSwitch.print();
    amplifierKT315.print();

    cout << endl << "===== PEREVIRKA VALIDNOSTI =====" << endl;
    unknownDevice.setGain(-50.0);      
    unknownDevice.setMaxCurrent(250.0);  
    unknownDevice.setType("");           
    cout << "Obyekt pislya nevdalykh sprob zminy:" << endl;
    unknownDevice.print();

    cout << endl << "===== KOPIYUVANNYA DANYKH METODOM =====" << endl;
    unknownDevice.copyFrom(amplifierKT315);
    unknownDevice.print();

    cout << endl << "===== REZULTAT OBCHYSLENNYA =====" << endl;
    double voltage = 12.0;
    cout << "Pry napruzi " << fixed << setprecision(1) << voltage << " V:" << endl;
    cout << "  \"" << powerSwitch.getType() << "\" vytrymuye potuzhnist "
         << setprecision(2) << powerSwitch.power(voltage) << " Vt" << endl;
    cout << "  \"" << amplifierKT315.getType() << "\" vytrymuye potuzhnist "
         << amplifierKT315.power(voltage) << " Vt" << endl;

    cout << endl << "===== ZAVERSHENNYA PROHRAMY =====" << endl;
    return 0;
}