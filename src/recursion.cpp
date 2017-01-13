/* 
 * This file contains the recursive functions that are called in meta.cpp.
 * The functions teach concepts of recursion.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
#include "random.h"
using namespace std;

// Declare functions

int gcd(int a, int b);
void serpinskii(GWindow &w, int leftX, int leftY, int size, int order);
void doSerpinskii(GWindow &w, double leftX, double leftY, double size, int order);
double getHeight(double a, double b);
void drawTriangle(GWindow &w, double leftX, double leftY, double size);
int floodFill(GBufferedImage& image, int x, int y, int newColor);
int doFloodFill(GBufferedImage& image, int x, int y, int newColor, int originalColor);
void generatePersonalCurriculum(Map<string, Vector<string>> & prereqMap, string goal, Set<string> &curriculum);
string pickRandomString(Vector<string> &v);


/**
 * Function: GCD
 * -------------
 * Returns the greatest common denominator of a and c, displaying the recursive steps to get to the gcd
 */
int gcd(int a, int b) {
    if (a % b == 0) {
        cout << "gcd(" << a << ", " << b << ") = " << b << endl;
        return b;
    } else {
        cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << a % b << ")" << endl;
        return gcd(b, a % b);
    }
}

/**
 * Function: Serpinskii
 * --------------------
 * Helper function that switches ints to doubles and calls doSerpinskii.
 */
void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {
    double dLeftX = leftX;
    double dLeftY = leftY;
    double dSize = size;
    doSerpinskii(w, dLeftX, dLeftY, dSize, order);
}

/**
 * Function: Do Serpinskii
 * -----------------------
 * Draws order-k Serpinskii triangles
 */
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
        
/**
 * Function: Get Height
 * --------------------
 * Returns the height of a triangle, given the hypotenuse and an adjacent side.
 */
double getHeight(double c, double a) {
    return sqrt(c * c - a * a);
}

/**
 * Function: Draw Triangle
 * -----------------------
 * Draws a triangle on GWindow w
 */
void drawTriangle(GWindow &w, double leftX, double leftY, double size) {
    double height = getHeight(size, size / 2);
    double rightX = leftX + size;
    double bottomY = leftY + height; 
    double bottomX = leftX + size/2;
    w.drawLine(leftX, leftY, rightX, leftY); // draw top side
    w.drawLine(leftX, leftY, bottomX, bottomY); // draw left side
    w.drawLine(rightX, leftY, bottomX, bottomY); // draw right side

}

/**
 * Function: Flood Fill
 * --------------------
 * Calls the function Do Flood Fill to fill the selected region with a specified color.
 * If the region selected is the same color as the specified color, the function returns 0.
 * And does not call Do Flood Fill.
 * Returns an integer equal to the number of pixels colored. 
 */
int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    int originalColor = image.getRGB(x,y);
    if (originalColor == newColor) {
        return 0;
    }
    return doFloodFill(image, x, y, newColor, originalColor);
}

/**
 * Function: Do Flood Fill
 * ------------------------
 * Uses recursion to color the pixel and adjacent pixels within bounds and of the original color.
 * Returns the number of pixels colored.
 */
int doFloodFill(GBufferedImage& image, int x, int y, int newColor, int originalColor) {
    int numPixels;
    if (image.inBounds(x, y) && image.getRGB(x, y) == originalColor) {
        image.setRGB(x, y, newColor);
        numPixels++;
        doFloodFill(image, x+1, y, newColor, originalColor); // check right pixel
        doFloodFill(image, x-1, y, newColor, originalColor); // check left pixel
        doFloodFill(image, x, y+1, newColor, originalColor); // check pixel above
        doFloodFill(image, x, y-1, newColor, originalColor); // check pixel below
    }
    return numPixels;
}

/**
 * Function: Personal Curriculum
 * -----------------------------
 * Helper function to declare a set of strings and call the recursive function:
 * Generate Personal Curriculum
 */
void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal) {
    Set<string> curriculum; // Declare set to keep avoid printing out duplicate prereqs
    generatePersonalCurriculum(prereqMap, goal, curriculum);
}

/**
 * Function: Generate Personal Curriculum
 * --------------------------------------
 * Uses recursion to print out all prerequisites
 */
void generatePersonalCurriculum(Map<string, Vector<string>> & prereqMap, string goal, Set<string> &curriculum) {
    
     for (string prereq : prereqMap[goal]) {
        generatePersonalCurriculum(prereqMap, prereq, curriculum);
        if (!curriculum.contains(prereq)) {
             cout << prereq << endl; 
             curriculum.add(prereq);
        }
     }
     if (!curriculum.contains(goal)) {
         cout << goal << endl; // Print out the original goal course
         curriculum.add(goal);
     }
}

/**
 * Function: Generate
 * ------------------
 * Generates a random expansion of grammar using recursion.
 * In Backus-Naur Form.
 */
string generate(Map<string, Vector<string> > & grammar, string symbol) {
    
    string result;

    if (!grammar.containsKey(symbol)) { // If terminal, add symbol to result.
        result += symbol;
    } else { // If not terminal...
        Vector<string> vec = grammar[symbol];
        string random = pickRandomString(vec); // Select random element from vector
        
        TokenScanner ts(random); // Parse string for multiple tokens
        while (ts.hasMoreTokens()) {
            string token = ts.nextToken();
            result += generate(grammar, token);
        }
    }
    return result;
}

/**
 * Function: Pick Random String
 * ----------------------------
 * Selects a random string element from a vector of strings.
 * If there is only one element in the vector, parses that 
 */
string pickRandomString(Vector<string> &v) {
    return v[randomInteger(0, v.size() - 1)];
}
