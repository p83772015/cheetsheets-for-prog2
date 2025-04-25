#include <iostream>
#include <fstream>
using namespace std;

void
export_odd_even(fstream *input_file_obj)
{
  fstream even_file_obj;
  fstream odd_file_obj;
  int num;

  while (*input_file_obj >> num) {
    if (num % 2 == 0) {
      // This branch runs if `num` is even.
      if (!even_file_obj.is_open()) {
	// Open `even.txt` only if `num % 2 == 0`.
	even_file_obj.open("even.txt", ios::out);
	if (even_file_obj.fail()) {
	  cerr << "File for writing failed to open.\n";
	  exit(1);
	}
      }
      even_file_obj << num << '\n';
    } else {
      // This branch runs if `num` is odd.
      if (!odd_file_obj.is_open()) {
	// Open `odd.txt` only if `num % 2 != 0`.
	odd_file_obj.open("odd.txt", ios::out);
	if (odd_file_obj.fail()) {
	  cerr << "File for writing failed to open.\n";
	  exit(1);
	}
      }
      odd_file_obj << num << '\n';
    }
  }

  even_file_obj.close();
  odd_file_obj.close();
}

int
main ()
{
  fstream input_file_obj;
  string input_file_name;

  cout << "Welcome to Odd and Even Finder Program!\n"
       << "\n"
       << "Find in FILE all the odd and even numbers.\n"
       << "Results are put to odd.txt and even.txt.\n"
       << "\n"
       << "Enter input FILE: ";

  // Open the text file for reading.
  cin >> input_file_name;		// Prompt for text file for reading.
  input_file_obj.open(input_file_name, ios::in);
  if (input_file_obj.fail()) {
    cerr << "File for reading failed to open.\n";
    exit(1);
  }

  // Notify user if done!
  export_odd_even(&input_file_obj);
  cout << "Finding done! Please Check the files 'odd.txt' and 'even.txt'."
       << '\n';

  // Cleanup
  input_file_obj.close();
  return 0;
}
