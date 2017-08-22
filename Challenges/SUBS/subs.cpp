#include <iostream>
#include <vector>
using namespace std;

vector<unsigned int> find_locations(string, string);

int main()
{
    string strand, motif;
    cin >> strand >> motif;
    vector<unsigned int> locations = find_locations(strand, motif);
    for(int i=0; i < locations.size(); i++) {
        cout << locations[i] << " ";
    }
    return 0;
}

vector<unsigned int> find_locations(string strand, string motif)
{
    vector<unsigned int> result;
    size_t pos = strand.find(motif);
    while(pos != string::npos) {
        result.push_back(++pos);
        pos = strand.find(motif, pos);
    }
    return result;
}
