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
int doFloodFill(GBufferedImage& image, int x, int y, int newColor, int originalColor);
Set<string> generatePersonalCurriculum(Map<string, Vector<string>> & prereqMap, string goal, Set<string> & curriculum);
void printCurriculum(Set<string> curriculum);


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

void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal) {
    Set<string> test;
    Set<string> curriculum = generatePersonalCurriculum(prereqMap, goal, test);

    // if (!prereqMap.containsKey(goal)) {
    //     if (!curriculum.contains(goal)) {
    //         curriculum.add(goal);
    //     }
    // } else {
    //    for (string prereq : prereqMap[goal]) {
    //        personalCurriculum(prereqMap, prereq);
    //         if (!curriculum.contains(goal)) {
    //             curriculum.add(goal);
    //         }
    //    } 
    // }
    
    // for (string prereq : prereqMap[goal]) {
    //     if (!curriculum.contains(prereq)) {
    //         curriculum.add(prereq);
    //     }
    //     personalCurriculum(prereqMap, prereq);
    // }

    // if (!curriculum.contains(goal)) {
    //     curriculum.add(goal);
    // }
    printCurriculum(curriculum);

}

/**
 * Function: Print Curriculum
 * ---------------------------
 * Iterates through the set of strings and prints each string out to console on sep line.
 */
void printCurriculum(Set<string> curriculum) {
    for (string course : curriculum) {
        cout << course << endl;
    }
}

Set<string> generatePersonalCurriculum(Map<string, Vector<string>> & prereqMap, string goal, Set<string> & curriculum) {

    if (!prereqMap.containsKey(goal)) {
        if (!curriculum.contains(goal)) {
            curriculum.add(goal);
        }
        return curriculum;
    } 
    else { 
        for (string prereq : prereqMap[goal]) {
            generatePersonalCurriculum(prereqMap, prereq, curriculum);
            // if (!curriculum.contains(prereq)) {
            //     curriculum.add(prereq);
            // }
       } 
    }
    return curriculum;
}

string generate(Map<string, Vector<string> > & grammar, string symbol) {
    // your code here
    cout << "[recursion generate called]" << endl;
    return "";
}
