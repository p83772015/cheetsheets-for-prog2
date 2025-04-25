#include <iostream>
#include <fstream>
using namespace std;

int *
find_min_max_in_file(fstream *file_obj)
{
  int line;
  int *min_max_tuple = (int *)malloc(2 * sizeof(int));
  int highest;
  *file_obj >> highest;
  int lowest = highest;
  while (*file_obj >> line) {
    (highest < line) && (highest = line);
    (lowest > line) && (lowest = line);
  }
  min_max_tuple[0] = lowest;
  min_max_tuple[1] = highest;
  return min_max_tuple;
}

int
main ()
{
  fstream file_obj;
  string file_name;
  int *min_max;

  cout << "Welcome to Min-Max Program!\n"
       << "\n"
       << "Find the smallest and largest integer in FILE.\n"
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
  min_max = find_min_max_in_file(&file_obj);
  cout << "Smallest integer: " << min_max[0] << '\n'
       << "Largest integer: " << min_max[1] << '\n';

  // Cleanup
  file_obj.close();
  return 0;
}
