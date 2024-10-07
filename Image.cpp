#include <cassert>
#include "Image.hpp"

// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {
  img->width = width;
  img->height = height;
  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
  int width, height, intensity;
  int r, g, b;
  std::string file; 
  is >> file >> width >> height >> intensity;
  Image_init(img, width, height);
  
  for(int row = 0; row < img->height; ++row) {
    for(int col = 0; col < img->width; ++col) {
      is >> r >> g >> b;

      // Dereferencing Pointer(s) w/ Respective Color Channels
      *Matrix_at(&img->red_channel, row, col) = r;
      *Matrix_at(&img->green_channel, row, col) = g;
      *Matrix_at(&img->blue_channel, row, col) = b;
    }
  }

}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3\n";
  os << img->width << " " << img->height << "\n";
  os << "255" << "\n";

  // Next, printing out each row(s) of the image
  for(int r = 0; r < Image_height(img); ++r) {
    for(int c = 0; c < Image_width(img); ++c) {

      Pixel curr = Image_get_pixel(img, r, c);
      os << curr.r << " " << curr.g << " " << curr.b << " ";
    }
    os << "\n";
  }
}

int Image_width(const Image* img) {
  return(img->width);
}

int Image_height(const Image* img) {
  return(img->height);
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));


  int r, g, b;
  r = *Matrix_at(&img->red_channel, row, column);
  g = *Matrix_at(&img->green_channel, row, column);
  b = *Matrix_at(&img->blue_channel, row, column);
  
  Pixel output = {r, g, b};
  return output;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  *Matrix_at(&img->red_channel, row, column) = color.r;
  *Matrix_at(&img->green_channel, row, column) = color.g;
  *Matrix_at(&img->blue_channel, row, column) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  Matrix_fill(&img->red_channel, color.r);
  Matrix_fill(&img->green_channel, color.g);
  Matrix_fill(&img->blue_channel, color.b);
}
