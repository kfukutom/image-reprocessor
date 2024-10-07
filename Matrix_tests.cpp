#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.

TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);
  
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}


// 1x1 Matrix Test
TEST(test_one_by_one) {
  Matrix mat;
  const int width = 1;
  const int height = 1;
  const int value = 20;
  Matrix_init(&mat, 1, 1);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// 1x8 Matrix Test
TEST(test_horizontal_matrix) {
  Matrix mat;
  const int width = 1;
  const int height = 8;
  const int value = 20;
  Matrix_init(&mat, 1, 8);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// Test Case for __init__()
TEST(test_init) {
  Matrix mat;
  Matrix_init(&mat, 10, 10);
  ASSERT_EQUAL(Matrix_width(&mat), 10);
  ASSERT_EQUAL(Matrix_height(&mat), 10);
}

TEST(test_fukutomi) {

    Matrix mat;
    const int width = 100;
    const int height = 100;
    Matrix_init(&mat, width, height);
    Matrix_fill(&mat, 0);
    Matrix_fill_border(&mat, 1);

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            if (r == 0 || r == height - 1) {
                ASSERT_EQUAL(*Matrix_at(&mat, r, c), 1);
            }
            else if (c == 0 || c == width - 1) {
                ASSERT_EQUAL(*Matrix_at(&mat, r, c), 1);
            }
            else {
                ASSERT_EQUAL(*Matrix_at(&mat, r, c), 0);
            }
        }
    }

    ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 1); 
    ASSERT_EQUAL(*Matrix_at(&mat, 0, width - 1), 1); 
}

TEST(test_hachi) {
  // Hachi --> 8 in Japonesa
  Matrix mat;
  const int width = 10;
  const int height = 10;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, 8);
  Matrix_fill_border(&mat, 9);

  // Set a new minimum at (8, 8)
  *Matrix_at(&mat, 8, 8) = 0;
  int col = Matrix_column_of_min_value_in_row(&mat, 8, 0, 10);
  int correct = 8; 
  ASSERT_EQUAL(col, correct);
}

TEST(test_yaeko) {
  // Test Suite for the minimum value in a row
  Matrix mat;
  const int width = 8;
  const int height = 8;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, 8);
  int min = Matrix_min_value_in_row(&mat, 2, 0, 6);
  ASSERT_EQUAL(min, 8);
}

TEST(test_uz_fukutomi) {
  // Hachi --> 8 in Japonesa
  Matrix mat;
  const int width = 10;
  const int height = 10;
  Matrix_init(&mat, width, height);
  Matrix_fill(&mat, 10);
  int col = Matrix_column_of_min_value_in_row(&mat, 8, 0, 9);
  int correct = 0; 
  ASSERT_EQUAL(col, correct);
}

TEST(test_brandon_barco) {
  // Brandon's Favorite Color
  Matrix mat;
  Matrix_init(&mat, 12, 12);
  Matrix_fill(&mat, 0);
  int max = Matrix_max(&mat);
  ASSERT_EQUAL(max, 0);
}

TEST(aj_kon_test) {
  // AJ's Favorite Color
  Matrix mat;
  Matrix_init(&mat, 20, 20);
  Matrix_fill(&mat, 1);
  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 14, 15) = 1;
  int max = Matrix_max(&mat);
  ASSERT_EQUAL(max, 1);
}

TEST(test_edge_case_1) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  Matrix_fill_border(&mat, 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), *Matrix_at(&mat, 1,1));
}


TEST(test_edge_case_2) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill_border(&mat, 5);
  ASSERT_EQUAL(Matrix_max(&mat), 5);
  // Matrix_min_value_in_row(&mat, row, col_start, col_end)
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 2), 0);
}

TEST(test_edge_case_3) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill_border(&mat, 10);
  *Matrix_at(&mat, 1, 1) = 11;
  ASSERT_EQUAL(Matrix_max(&mat), 11);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 2), 10);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 2), 0);
}

TEST(test_edge_case_4) {
  Matrix mat;
  Matrix_init(&mat, 10, 10);
  int max = 100;

  for (int i = 0; i < Matrix_height(&mat); ++i) {
    for (int j = 0; j < Matrix_width(&mat); ++j) {
      *Matrix_at(&mat, i, j) = max;
      max--;
    }
  }
  int correct = 8;
  int test_output = Matrix_column_of_min_value_in_row(&mat, 8, 0, 9);
  ASSERT_EQUAL(test_output, correct);
}

TEST(test_edge_case_5) {
  Matrix mat;
  Matrix_init(&mat, 5, 5);
  Matrix_fill_border(&mat, 10);
  const int height = Matrix_height(&mat);
  const int width = Matrix_width(&mat);

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      if ( (r == 0 || r == height-1) 
        || (c == 0 || c == width-1)) {
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), 10);
      }
      // Inside Matrix
      else {
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), 0);
      }
    }
  }
}

TEST(test_edge_case_6) {
  Matrix mat;
  Matrix_init(&mat, 10, 10);
  Matrix_fill(&mat, 10);
  *Matrix_at(&mat, 4, 4) = 9; // Center
  int min = Matrix_min_value_in_row(&mat, 4, 0, 9);
  ASSERT_EQUAL(9, min);
}

TEST(test_edge_case_7) {
  Matrix mat;
  Matrix_init(&mat, 100, 100);
  Matrix_fill(&mat, 4);
  for (int i = 0; i < Matrix_height(&mat); ++i) {
    for (int j = 0; j < Matrix_width(&mat); ++j) {
      if (i % 2 == 0) {
        *Matrix_at(&mat, i, j) = 0;
      }
    }
  }

  // Find Minimum COL
  int min = Matrix_column_of_min_value_in_row(&mat, 0, 0, 99);
  ASSERT_EQUAL(min, 0);
}

TEST(test_edge_case_8) {
  Matrix mat;
  Matrix_init(&mat, 100, 100);
  Matrix_fill(&mat, 4);
  for (int i = 0; i < Matrix_height(&mat); ++i) {
    for (int j = 0; j < Matrix_width(&mat); ++j) {
      if (j == 99) {
        *Matrix_at(&mat, i, j) = 0;
      }
    }
  }

  // Find Minimum COL
  int min = Matrix_column_of_min_value_in_row(&mat, 0, 0, Matrix_width(&mat));
  ASSERT_EQUAL(min, 99);
}

TEST(test_edge_case_9) {
  Matrix mat;
  Matrix_init(&mat, 15, 30);
  Matrix_fill(&mat, 1);
  Matrix_fill_border(&mat, 10);

  const int height = Matrix_height(&mat);
  const int width = Matrix_width(&mat);

  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      if ( (r == 0 || r == height-1) 
        || (c == 0 || c == width-1)) {
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), 10);
      }
      // Inside Matrix
      else {
        ASSERT_EQUAL(*Matrix_at(&mat, r, c), 1);
      }
    }
  }
  ASSERT_NOT_EQUAL(*Matrix_at(&mat, 1, 3), *Matrix_at(&mat, 0, 1));
}

TEST(test_edge_case10) {
  Matrix mat;
  Matrix_init(&mat, 10, 10);
  Matrix_fill(&mat, 10);
  *Matrix_at(&mat, 4, 5) = 11;
  ASSERT_EQUAL(Matrix_max(&mat), 11);
}

TEST(test_edge_case11) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  ASSERT_EQUAL(0, *Matrix_at(&mat, 0, 0));
  Matrix_fill_border(&mat, 1);
  ASSERT_EQUAL(1, *Matrix_at(&mat, 0, 0));
  ASSERT_EQUAL(Matrix_max(&mat), 1);
  ostringstream s;
  Matrix_print(&mat, s);
  ostringstream correct;
  correct << "1 1\n";
  correct << "1 \n";
  ASSERT_EQUAL(correct.str(), s.str());
}

TEST(test_edge_case12) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);

  ASSERT_EQUAL(Matrix_width(&mat), 1);
  ASSERT_EQUAL(Matrix_height(&mat), 1);
}

TEST(test_edge_case_13) {
  Matrix mat;
  Matrix_init(&mat, 12, 12);
  for (int i = 0; i < Matrix_height(&mat); ++i) {
    for (int j = 0; j < Matrix_width(&mat); ++j) {
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 0);
    }
  }
  ASSERT_EQUAL(Matrix_max(&mat), 0);
  int col = Matrix_column_of_min_value_in_row(&mat, 0, 0, 12);
  ASSERT_EQUAL(col, 0);
}

TEST(test_matrix_print) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);

  *Matrix_at(&mat, 0, 0) = 42;
  *Matrix_at(&mat, 0, 1) = 42;
  *Matrix_at(&mat, 1, 0) = 43;
  *Matrix_at(&mat, 1, 1) = 43;
  ostringstream expected;
  expected << "2 2\n"
           << "42 42 \n"
           << "43 43 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

TEST_MAIN() // Do NOT put a semicolon here
