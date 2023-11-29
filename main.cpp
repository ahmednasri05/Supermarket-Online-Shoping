#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "models.h"
#include "routes.h"
using namespace std;
int main() {
    Person person;
    person.age = 5;
    cout << person.age << endl;
    cout << Greeting() << endl;
    return 0;
}