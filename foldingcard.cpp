/*==========================================================================================
During the early days of computer programming, instructons were encoded
using designated cards. Imagine a card arranged in a grid patern with M rows
and N columns (Fig. 1). Each cell within this grid could potentally contain a
small, removable paper dot. If the dot is removed, it leaves behind a hole, thus
each cell is marked by the presence or absence of such a hole.

You are tasked with configuring a card device, but the challenge is that it's not
equipped to create new holes. Fortunately, there's already a card at your
disposal. The strategy involves folding the card vertically in such a place that it
results in the rightmost column overlaying to the left. This fold aligns certain
cells on the grid. Take, for instance, a card with 7 columns (Fig. 1). By folding it
between the 3rd and 4th columns (Fig. 2), the adjacent cells from columns 3 and
4, 2 and 5, as well as 1 and 6, will align respectively. The 7th column will then
dangle, not aligning with the inital card layout. The newly reconfigured card now
consists of 4 columns (Fig. 3), with the order from left to right being the dangling
7th column, then the pairs (1,6), (2,5), and finally (3,4). Holes will appear in this
altered configuration only where both corresponding cells had holes in the prefolded card.

If you fold a card along a specified column, how will the appearance of the card change postfolding?
==========================================================================================*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//=================================================
// Function for folding a card
//=================================================
vector<string> foldCard(int M, int N, int K, const vector<string>& card) {
    vector<string> foldedCard;
    
    for (const auto& row : card) {
        // Separates row into two strings, one before the index K and one after (if K=3, #o##oo -> #o# , #oo)
        string smaller_row = row.substr(K);
        string larger_row = row.substr(0, K);

        reverse(smaller_row.begin(), smaller_row.end()); // flips smaller_row (#oo -> oo#)

        // Makes sure that the smaller_row is smaller and the larger row is larger, if not then it switches them
        if (smaller_row.length() > larger_row.length()) {
            string temp = smaller_row;
            smaller_row = larger_row;
            larger_row = temp;
        }

        // Starts from the last value of each of the two rows and compares them (#o# , oo#):
        // # = o --> becomes #
        // o = o --> becomes o
        // # = # --> becomes #
        for (int i=smaller_row.length() - 1; i > -1; i--) {
            if (larger_row[i+1] == 'o' && smaller_row[i] == '#') { // if either row index has '#' it will update larger_row with '#'
                larger_row[i+1] = '#';
            }
            if (larger_row[i+1] == '#' && smaller_row[i] == 'o') {
                larger_row[i+1] = '#';
            }
        }
        foldedCard.push_back(larger_row);
    }
    return foldedCard;
};

//=================================================
// Main Function
//=================================================
int main() {
    int M, N, K;
    cin >> M >> N >> K; // Get rows, cols and fold index from command line

    vector<string> card;
    // Get card data from command line, row by row.
    for (int i = 0; i < M; ++i) {
        string row;
        cin >> row;
        card.push_back(row);
    }

    vector<string> foldedCard = foldCard(M, N, K, card);

    // Outputs foldedcard to command line
    for (const auto& row : foldedCard) {
        cout << row << endl;
    }

    return 0;
}
