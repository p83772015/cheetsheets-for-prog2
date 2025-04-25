#include <iostream>
#include <fstream>
using namespace std;

double
compute_avg_from_file(fstream *file_obj)
{
  double total = 0;
  size_t count = 0;
  double num;
  while (*file_obj >> num) {
    total += num;
    ++count;
  }
  return total / count;
}

int
main ()
{
  fstream file_obj;
  string file_name;

  cout << "Welcome to Number Averager Program!\n"
       << "\n"
       << "This program computes the average of numbers in FILE.\n"
       << "Numbers in FILE may be delimited by any whitespace\n"
       << "character.\n"
       << "\n"
       << "Enter FILE: ";
  cin >> file_name;

  // Open the text file.
  file_obj.open(file_name, ios::in);
  if (file_obj.fail()) {
    cerr << "File failed to open.\n";
    exit(1);
  }

  // Compute and print result
  cout << "The average of numbers in '" << file_name
       << "' is: " << compute_avg_from_file(&file_obj)
       << '\n';

  file_obj.close();
  return 0;
}
