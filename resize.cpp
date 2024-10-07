#include <iostream>
#include <fstream>
#include "Image.hpp"
#include "Matrix.hpp"
#include "processing.hpp"
using namespace std;

int main(int argc, char* argv[]) {

  // Base Case
  if ((argc < 4) || (argc > 5)) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  ifstream is(argv[1]);
  if(!is.is_open()) {
    // if not open
    cout << "Error opening file: " << argv[1] << endl;
    return 1;
  }

  Image* img = new Image;
  Image_init(img, is);
  int initial_width = Image_width(img);
  int new_width = atoi(argv[3]);
  int initial_height = Image_height(img);
  int new_height;
  if (argc == 5){
    new_height = atoi(argv[4]);
  } else {
    new_height = initial_height;
  }
    
  if (new_width <= 0 || new_width > initial_width || 
  new_height <= 0 || new_height > initial_height) { 
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
    << "WIDTH and HEIGHT must be less than or equal to original" << endl;

    delete img; 
    return 1;
  }
  
  seam_carve(img, new_width, new_height);
  ofstream os(argv[2]);
  Image_print(img, os);

  // END OF RESIZE.CPP
  delete img;
  return 0;
}