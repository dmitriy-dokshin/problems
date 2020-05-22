#include <lib/matrix/matrix.h>

#include <algorithm>

using namespace std;

const char FREE_SQUARE = 'o';
const char OCCUPIED_SQUARE = 'x';
const char QUEEN_SQUARE = 'Q';

void set_queen(TMatrix<char>& board, const size_t i, const size_t j, const char q) {
    for (size_t x = 0; x < board.width(); x++) {
        board.at(i, x) = OCCUPIED_SQUARE;
    }
    for (size_t y = 0; y < board.height(); y++) {
        board.at(y, j) = OCCUPIED_SQUARE;
    }
    for (size_t x = j - min(i, j), y = i - min(i, j); x < board.width() && y < board.height(); x++, y++) {
        board.at(y, x) = OCCUPIED_SQUARE;
    }
    for (size_t x = j - min(board.height() - i - 1, j), y = i + min(board.height() - i, j + 1); x < board.width() && y > 0; x++, y--) {
        board.at(y - 1, x) = OCCUPIED_SQUARE;
    }
    board.at(i, j) = q;
}

void queens(TMatrix<char> board, size_t i, size_t n, ostream& out, size_t& total_ways) {
    if (n > 0) {
        for (size_t j = 0; j < board.width(); j++) {
            if (board.at(i, j) == FREE_SQUARE) {
                auto new_board = board;
                set_queen(new_board, i, j, QUEEN_SQUARE);
                queens(move(new_board), i + 1, n - 1, out, total_ways);
            }
        }
    } else {
        out << board << endl;
        total_ways++;
    }
}

void eight_queens() {
    const size_t n = 8;
    TMatrix<char> board(n, n, FREE_SQUARE);
    size_t total_ways = 0;
    queens(move(board), 0, n, cout, total_ways);
    cerr << "total_ways: " << total_ways << endl;
}

int main() {
    eight_queens();
}
