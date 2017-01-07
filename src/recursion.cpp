/* 
 * TODO: Finish this comment.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
using namespace std;

// Declare functions

int gcd(int a, int b);
void serpinskii(GWindow &w, int leftX, int leftY, int size, int order);
void doSerpinskii(GWindow &w, double leftX, double leftY, double size, int order);
double getHeight(double a, double b);
void drawTriangle(GWindow &w, double leftX, double leftY, double size);
int floodFill(GBufferedImage& image, int x, int y, int newColor);


// Returns the greatest common denominator of a and c, displaying the recursive steps to get to the gcd
int gcd(int a, int b) {
    if (a % b == 0) {
        cout << "gcd(" << a << ", " << b << ") = " << b << endl;
        return b;
    } else {
        cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << a % b << ")" << endl;
        return gcd(b, a % b);
    }
}

// Helper function that switches ints to doubles and calls doSerpinskii
void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
    double dLeftX = leftX;
    double dLeftY = leftY;
    double dSize = size;
    doSerpinskii(w, dLeftX, dLeftY, dSize, order);
}

// Draws order-k Serpinskii triangles
void doSerpinskii(GWindow &w, double leftX, double leftY, double size, int order) {
        if (order == 0) {
            drawTriangle(w, leftX, leftY, size);
        } else {
            order--;
            double halfS = size / 2;
            double height = getHeight(halfS, halfS / 2);
            doSerpinskii(w, leftX, leftY, halfS, order); // Draw left triangle
            doSerpinskii(w, leftX + halfS, leftY, halfS, order); // Draw right triangle
            doSerpinskii(w, leftX + halfS / 2, leftY + height, halfS, order); // Draw bottom triangle
        }
}
        
// Uses the Pythagorean theorum to return the height given two sides of the triangle
double getHeight(double c, double a) {
    return sqrt(c * c - a * a);
}


void drawTriangle(GWindow &w, double leftX, double leftY, double size) {
    double height = getHeight(size, size / 2);
    double rightX = leftX + size;
    double bottomY = leftY + height; 
    double bottomX = leftX + size/2;
    w.drawLine(leftX, leftY, rightX, leftY); // draw top side
    w.drawLine(leftX, leftY, bottomX, bottomY); // draw left side
    w.drawLine(rightX, leftY, bottomX, bottomY); // draw right side

}

int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    // your code here
    cout << "[recursion flood fill called]" << endl;
    return 0;
}

void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal) {
    // your code here
    cout << "[recursion personal curriculum called]" << endl;
}

string generate(Map<string, Vector<string> > & grammar, string symbol) {
    // your code here
    cout << "[recursion generate called]" << endl;
    return "";
}
