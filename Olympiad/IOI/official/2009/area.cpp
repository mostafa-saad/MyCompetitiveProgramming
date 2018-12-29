/**
 * Solution to IOI 2009 problem "area"
 *
 * Carl Hultquist, chultquist@gmail.com
 */
#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;

    // Be sure to use a 64-bit data-type here, as the answer could get
    // very big!
    long long area = 0;
    for (int i = 0; i < n; i++)
    {
        // For safety, read in the sides of the property as 64-bit types
        // too. This way, we know that the compiler won't try to do any
        // operations in 32-bit.
        long long a, b;
        cin >> a >> b;

        // Add on the area of this property to the total area
        area += (a * b);
    }

    cout << area << endl;
    return 0;
}
