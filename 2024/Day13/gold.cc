#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
typedef long long ll;

int main() {
    ll result = 0;
    while (true) {
        string str;
        ll xa, ya, xb, yb, xp, yp;
        // button a
        if (getline(cin, str)) {
            istringstream lineStream(str);
            lineStream >> str >> str >> str; // get rid of "Button A:"
            // str should contain "X+[amount],"
            str = str.substr(2);
            istringstream numStream(str);
            numStream >> xa;
            // str should contain "Y+[amount]"
            lineStream >> str;
            str = str.substr(2);
            numStream = istringstream(str);
            numStream >> ya;
        } else {
            break;
        }
        // Button B
        getline(cin, str);
        istringstream lineStream(str);
        lineStream >> str >> str >> str; // get rid of "Button B:"
        // str should contain "X+[amount],"
        str = str.substr(2);
        istringstream numStream(str);
        numStream >> xb;
        // str should contain "Y+[amount]"
        lineStream >> str;
        str = str.substr(2);
        numStream = istringstream(str);
        numStream >> yb;

        // Prize
        getline(cin, str);
        lineStream = istringstream(str);
        lineStream >> str >> str; // get rid of Prize:
        // str shoudl contain X=[amount]
        str = str.substr(2);
        numStream = istringstream(str);
        numStream >> xp;
        // str should contain Y=[amount]
        lineStream >> str;
        str = str.substr(2);
        numStream = istringstream(str);
        numStream >> yp;

        getline(cin, str); // for blank line
        /*cout<<xa<<", "<<ya<<endl;
        cout<<xb<<", "<<yb<<endl;
        cout<<xp<<", "<<yp<<endl;*/

        if (xa * yb == xb * ya) {
            continue;
        }
        // solving the system of equations
        /*
            (xa) * a + (xb) * b = xp
            (ya) * a + (yb) * b = yp 

            In general solution is,
            a = ((xp)(yb) - (yp)(xb))/((xa)(yb) - (xb)(ya))
            b = ((xa)(yp) - (ya)(xp))/((xa)(yb) - (xb)(ya))

            check divisibility in this case
        */
        xp += 10000000000000;
        yp += 10000000000000;
        ll denom = xa * yb - xb * ya;
        ll a = xp *yb - yp * xb;
        ll b = xa * yp - ya * xp;
        if (a % denom != 0 || b % denom != 0) {
            continue;
        }
        a /= denom;
        b /= denom;
        if (a < 0 || b < 0) {
            continue;
        }
        result += 3*a + b; 
    }
    cout<<result<<endl;
}