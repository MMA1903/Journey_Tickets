#include <iostream>
#include <vector>
using namespace std;

struct Flight
{
    int flight_num;
    Flight* breakup;
    Flight* without_breakup;

    Flight(int flight_num)
    {
        this->flight_num = flight_num;
        this->breakup = nullptr;
        this->without_breakup = nullptr;
    }
};

bool IsLastFlight(Flight* Flight)
{
    return (Flight->breakup == nullptr && Flight->without_breakup == nullptr);
}

int counter = 1;

void PrintJourneyTickets(Flight* Flight, vector<int>& route)
{

    if (Flight == nullptr)
    {
        return;
    }

    route.push_back(Flight->flight_num);

    if (IsLastFlight(Flight))
    {
        cout << "Breakup" << " " << counter << endl << ".";
        for (int flight_num : route)
        {
            if (flight_num < 0)
            {
                cout << endl << "." << -(flight_num) << " ";
            }
            else
            {
                cout << flight_num << " ";
            }
        }
        cout << endl << endl;
        counter++;
    }

    PrintJourneyTickets(Flight->without_breakup, route);
    PrintJourneyTickets(Flight->breakup, route);

    route.pop_back();
}

void MakeJourneyRoute(Flight* Flight)
{
    vector<int> route;

    PrintJourneyTickets(Flight, route);
}

Flight* InsertJourney(int n, Flight* First_Flight, int i)
{
    if (i == 0) {}
    else
    {
        if (n < 0)
        {
            Flight* temp = new Flight(n + i);
            First_Flight = temp;

            First_Flight->breakup = InsertJourney(n, First_Flight->breakup, i - 1);
            First_Flight->without_breakup = InsertJourney(-n, First_Flight->without_breakup, i - 1);
        }

        else
        {
            Flight* temp = new Flight(n - i);
            First_Flight = temp;

            First_Flight->breakup = InsertJourney(-n, First_Flight->breakup, i - 1);
            First_Flight->without_breakup = InsertJourney(n, First_Flight->without_breakup, i - 1);
        }
    }
    return First_Flight;
}

int main()
{
    int N;
    cin >> N;
    int unsigned i = N;
    Flight* First_Flight = new Flight(0);

    MakeJourneyRoute(InsertJourney(N, First_Flight, i));
    counter = 1;
    main();
}
