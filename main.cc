
import board;
import square;
import textobserver;
import subject;
import observer;
int main() {
    Board b;
    TextObserver t(&b);
    b.notifyObservers();  // Should display the board
    return 0;
}