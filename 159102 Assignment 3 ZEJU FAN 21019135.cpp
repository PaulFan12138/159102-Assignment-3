//ZEJU FAN 21019135
//159102 Assignment 3
//17/10/2023

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class pixel_class {
private:
  int red, green, blue;
  bool exclude;  // if true, do not check this pixel
public:
  void loaddata(int v1, int v2, int v3);
  void datatofile(fstream & ppmfile);
  int getR() { return red; }
  int getG() { return green; }
  int getB() { return blue; }
  void setexclude(bool ex) { exclude = ex; }
  bool getexclude() { return exclude; }
};

void loadButtons();

int total, xmin, xmax, ymin, ymax;  // MUST be global if used
int screenx, screeny, maxcolours;   // you must use these
pixel_class picture[600][600];      // you must use this

void CheckPixel(int x, int y);
void DrawBox(int R, int G, int B); // Added DrawBox function

int main() {

  // Step 1 : read in the image from Buttons.ppm
  loadButtons();

  // Step 2 : identify buttons and draw boxes
  //Check pixels one by one
  for (int y = 0; y < screeny; y++) {
    for (int x = 0; x < screenx; x++) {
      //This line of code gets the red (R) channel value of the pixel at the specified coordinates (x, y) and stores it in a variable called grayscale.
      int grayscale = picture[x][y].getR();
      //This line of code gets the exclude attribute value of the pixel at the specified coordinates (x, y) and stores it in a Boolean variable named exclude.
      bool exclude = picture[x][y].getexclude();
      //128 is the middle number between black and white grayscale values
      if ((grayscale > 128) && (exclude == false)) {
        total = 0;
        xmin = x;
        xmax = x;
        ymin = y;
        ymax = y;
        CheckPixel(x, y);
        //"total" is used to count the number of pixels associated with the possible pattern. If the value of total is less than 7800, then it draws a red box, otherwise, it draws a green box.
        if (total < 7800) {
          //(255,0,0) mean red
          DrawBox(255, 0, 0); // draw a red box
        } else {
          //(255,0,0) mean green
          DrawBox(0, 255, 0); // draw a green box
        }
      }
    }
  }

  // Step 3 : output the final .ppm file
  //Create a file stream object named File for operating files.
  fstream File;
  //Set the file name of the new image file to be created to "NewButtons.ppm"
  string FileName = "NewButtons.ppm";
  //Try to open the file for writing. If the file is opened successfully, it will prepare data for writing, otherwise, it will display a warning message and exit the program.
  File.open(FileName.c_str(), fstream::out);
  //If the file cannot be opened, output the warning message
  if (!File.is_open()) {
    cout << "Warning! Not able to build a new file " << FileName << endl;
    exit(2);
  }
  //Writes "P3", which is the file type identifier for PPM image files
  File << "P3" << endl;
  File << "# " << FileName << endl;
  //Write the width and height of the image
  File << screenx << " " << screeny << endl;
  File << maxcolours << endl;
  for (int y = 0; y < screeny; y++) {
    for (int x = 0; x < screenx; x++) {
      picture[x][y].datatofile(File);
    }
    File << endl;
  }
  File.close();
}

void loadButtons() {
  // load the picture from Buttons.ppm
  int x, y, R, G, B;
  fstream infile;
  string infilename, line;
  infilename = "Buttons.ppm";
  infile.open(infilename.c_str(), fstream::in);
  if (infile.is_open() == false) {
    cout << "ERROR: not able to open " << infilename << endl;
    exit(2);
  }
  getline(infile, line);  // this line is "P3"
  getline(infile, line);  // this line is "# filename"
  infile >> screenx >> screeny;  // this line is the size
  infile >> maxcolours;  // this line is 256
  for (y = 0; y < screeny; y++) {
    for (x = 0; x < screenx; x++) {
      infile >> R >> G >> B;
      picture[x][y].loaddata(R, G, B);
      picture[x][y].setexclude(false);
    }
  }
  infile.close();
}

//--------------- methods for the pixel_class ------------
void pixel_class::loaddata(int v1, int v2, int v3) {
  red = v1;
  green = v2;
  blue = v3;
}

void pixel_class::datatofile(fstream & ppmfile) {
  // write the data for one pixel to the ppm file
  ppmfile << red << " " << green;
  ppmfile << " " << blue << "  ";
}
//This function is used to recursively examine pixels associated with possible patterns, label them and find the boundaries of the pattern. During processing, it gradually expands to adjacent pixels in order to determine the complete shape of the pattern.
void CheckPixel(int x, int y) {
  int Grayscale;
  bool Exclude;
  Grayscale = picture[x][y].getR();
  if (Grayscale <= 128  || picture[x][y].getexclude() == true) 
  { 
    picture[x][y].setexclude(true);
    return;
  }
  total++;
  if (x < xmin) { xmin = x; }
  if (x > xmax) { xmax = x; }
  if (y < ymin) { ymin = y; }
  if (y > ymax) { ymax = y; }
  picture[x][y].setexclude(true);
  if (x > 0) { CheckPixel(x - 1, y); }
  if (y > 0) { CheckPixel(x, y - 1); }
  if (x < screenx - 1) { CheckPixel(x + 1, y); }
  if (y < screeny - 1) { CheckPixel(x, y + 1); }
}
//The DrawBox function is used to draw a colored rectangular box, the boundaries of which are determined by the previous recursive function CheckPixel. It marks the pixels in the box by modifying the color value of the pixel and the exclude attribute
void DrawBox(int R, int G, int B) {
  int x, y;
  for (x = xmin; x <= xmax; x++) {
    picture[x][ymin].loaddata(R, G, B);
    picture[x][ymin].setexclude(true);
    picture[x][ymax].loaddata(R, G, B);
    picture[x][ymax].setexclude(true);
  }
  for (y = ymin; y <= ymax; y++) {
    picture[xmin][y].loaddata(R, G, B);
    picture[xmin][y].setexclude(true);
    picture[xmax][y].loaddata(R, G, B);
    picture[xmax][y].setexclude(true);
  }
}