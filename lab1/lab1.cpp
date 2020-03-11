#include <iostream>
#include <math.h>


float function(float x) {
  return x * log(x);
}

//needed in defining zero_line
int round_up(float x) {
  if ((int)x == x) { return x; }
  else { return x + 1; }
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
    if (current_y < ymin) { ymin = current_y; }
    if (current_y > ymax) { ymax = current_y; }
  }


  float cell_height = (ymax - ymin) / (height - 1);
  //line number where Y=0 (----------------)
  int zero_line = round_up(ymax / cell_height);

  //drawing (42 - 65)
  //for positive Y
  for (int i = 0; i < zero_line; ++i) {
    std::cout << i + 1 << ' ';
    for (int j = 0; j < width; ++j) {
      if ((zero_line - i) * cell_height < y_array[j]) { std::cout << '#'; }
      else { std::cout << ' '; }
    }
    std::cout << std::endl;
  }
  // zero
  std::cout << zero_line + 1 << ' ';
  for (int j = 0; j < width; ++j) {
    std::cout << '-';
  }
  // for negative Y
  std::cout << std::endl;
  for (int i = zero_line + 1; i < height; ++i) {
    std::cout << i + 1 << ' ';
    for (int j = 0; j < width; ++j) {
      if ((i - zero_line) * cell_height < (-y_array[j])) { std::cout << '#'; }
      else { std::cout << ' '; }
    }
    std::cout << std::endl;
  }
}
