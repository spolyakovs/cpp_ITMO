#include <iostream>
#include <fstream>
#include <cmath>


float function(float x) {
  return -x * log(x);
}

//needed in defining zero_line
int round_up(float x) {
  if ((int)x == x) {
    return x;
  }
  else {
    return x + 1;
  }
}


int main() {
  int width, height;
  float xmin, xmax, ymin = 0, ymax = 0; //zero_line always need to be visible
  std::cin >> width >> height >> xmin >> xmax;
  ++height; //height + zero_line
  float cell_width = (xmax - xmin) / width;

  // Array of results of the function
  float *y_array = new float[width];
  for (int i = 0; i < width; ++i) {
    float current_x = xmin + cell_width * i;
    float current_y = function(current_x);

    y_array[i] = current_y;

    //define min and max Y value
    ymin = std::min(current_y, ymin);
    ymax = std::max(current_y, ymax);
  }


  float cell_height = (ymax - ymin) / (height - 1);
  //line number where Y=0 (----------------)
  int zero_line = round_up(ymax / cell_height);

  //drawing (42 - 65)
  std::ofstream output_file ("graph.txt");
  //for positive Y
  for (int i = 0; i < zero_line; ++i) {
    for (int j = 0; j < width; ++j) {
      if ((zero_line - i) * cell_height < y_array[j]) { output_file << '#'; }
      else { output_file << ' '; }
    }
    output_file << std::endl;
  }
  // zero line
  for (int j = 0; j < width; ++j) {
    output_file << '-';
  }
  output_file << std::endl;
  // for negative Y
  for (int i = zero_line + 1; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if ((i - zero_line) * cell_height < (-y_array[j])) { output_file << '#'; }
      else { output_file << ' '; }
    }
    output_file << std::endl;
  }
  delete[] y_array;
}
