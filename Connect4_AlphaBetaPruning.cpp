#include <bits/stdc++.h>
using namespace std;


int alphabeta(int depth, bool isMaximizing,
              vector<vector<int>> &tree, int node,
              int alpha, int beta) {

    if (depth == tree.size() - 1) {
        return tree[depth][node];
    }

    if (isMaximizing) {
        int best = INT_MIN;


        best = max(best, alphabeta(depth + 1, false, tree, node * 2, alpha, beta));
        alpha = max(alpha, best);
        if (beta <= alpha) return best;


        best = max(best, alphabeta(depth + 1, false, tree, node * 2 + 1, alpha, beta));
        alpha = max(alpha, best);
        return best;
    } else {
        int best = INT_MAX;


        best = min(best, alphabeta(depth + 1, true, tree, node * 2, alpha, beta));
        beta = min(beta, best);
        if (beta <= alpha) return best;


        best = min(best, alphabeta(depth + 1, true, tree, node * 2 + 1, alpha, beta));
        beta = min(beta, best);
        return best;
    }
}

int main() {

    vector<vector<int>> tree = {
        {0},
        {0, 0, 0},
        {4, 7, 2, -4, -4, 4}
    };

    int bestScore = INT_MIN;


    for (int i = 0; i < 3; i++) {
        bestScore = max(bestScore, alphabeta(1, false, tree, i,
                                             INT_MIN, INT_MAX));
    }

    cout << "Best score for AI (Alpha–Beta): " << bestScore << endl;
    return 0;
}


