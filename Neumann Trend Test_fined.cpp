#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <vector>

using namespace std;

int main()
{
    int n;
    vector<int> area, time;                              // Define integer variable and arrays.
    vector<float> PG;                                    // Define float.
    vector<string> result;                               // Define string arrays.
    float PG_judge[] = {0.7805, 0.8204, 0.8902, 0.9359}; // Assign PG_judge as Neumann Trend Standard W(P).

    cout << "Number of data sets: ";
    cin >> n;

    area.resize(n);
    time.resize(n);
    PG.resize(n, 0.0f);     // Initialize PG with its size and value;
    result.resize(n, "--"); // Initialize result with its size and value;

    cout << "Time(h): ";
    for (int a = 0; a < n; ++a)
    {
        cin >> time[a]; // Enter the time of measurement for each.
    }

    cout << "Area: ";
    for (int a = 0; a < n; ++a)
    {
        cin >> area[a]; // Enter the encapsulation area for each.
    }

    // Settings for output tabulation.
    cout << "Neumann Trend Test:" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << setiosflags(ios::left) << setw(14) << "Area"
         << resetiosflags(ios::left) << setiosflags(ios::right)
         << setw(9) << "Time(h)" << setw(14) << "PG" << setw(18) << "Trend(Y/N)"
         << resetiosflags(ios::right) << endl;
    cout << "--------------------------------------------------------" << endl;

    // There are (n-3) testing groups in total and for each group algorithm processes (i+1) data points for caculation.
    for (int i = 3; i < n; ++i)
    {
        int sum_area = 0, sum_numer = 0;
        double sum_denomin = 0, avg = 0; // Initialize variables before each prior loop conducted.
        for (int j = 0; j <= i; ++j)
        {
            sum_area += area[j]; // Return sum_area for every (i+1) encapsulation areas in a group.
        }
        avg = static_cast<double>(sum_area) / (i + 1); // Return avg for an average of sum0 and break the secondary loop.
        for (int k = 0; k <= i; ++k)
        {
            if (k < i)
            {
                sum_numer += pow(area[k] - area[k + 1], 2);
            }
            sum_denomin += pow(area[k] - avg, 2); // Return sum_numer for numerator and sum_denomin for denominator in accordance with the Neumann Formula.
        }
        PG[i] = static_cast<double>(sum_numer) / sum_denomin; // Return PG for Neumann Trend for every (i+1) data points.
    }

    for (int a = 0; a < n; ++a)
    {
        if (a >= 3)
        {
            // Accoring to Table value of Standard W(P) for Neumann Trend Test, we take W(P)_(a+3) for basis of judgment under 95% fiducial probability.If PG>PG_judge, there is no trend.Otherwise, there is a potential trend for degradation.
            if (PG[a] <= PG_judge[a - 3])
            {
                result[a] = "yes";
            }
            else
            {
                result[a] = "no";
            }
        }

        cout << setiosflags(ios::left) << setw(14) << area[a]
             << resetiosflags(ios::left) << setiosflags(ios::right)
             << setw(9) << time[a] << setw(14) << fixed << setprecision(4) << PG[a] << setw(18) << result[a]
             << resetiosflags(ios::right) << endl;
    }

    cout << "--------------------------------------------------------" << endl;
    return 0;
}
/* Input example:
 6147338 6147785 6154157 6141375 6127575 6118354 6090916 ; 0 1 2 5 10 18 24
 6126811 6120857 6112046 6100250 6089047 6070963 6057447
 7582457 7586934 7570156 7553261 7549265 ; 0 2 5 10 24
 7342482 7311815 7308719 7282647 7283729
*/