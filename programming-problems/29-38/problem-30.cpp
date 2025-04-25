#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void
flip_text_file(fstream *file_obj, fstream *flipped_file_obj)
{
  string line;
  while (getline(*file_obj, line)) {
    reverse(line.begin(), line.end());
    *flipped_file_obj << line << '\n';
  }
}  

int
main ()
{
  fstream file_obj;
  fstream flipped_file_obj;
  string file_name;
  string flipped_file_name;

  cout << "Welcome to Text Flipper Program!\n"
       << "\n"
       << "Horizontally flip a text file.\n"
       << "\n"
       << "Enter input FILE: ";

  // Open the text file for reading.
  cin >> file_name;		// Prompt for text file for reading.
  file_obj.open(file_name, ios::in);
  if (file_obj.fail()) {
    cerr << "File for reading failed to open.\n";
    exit(1);
  }

  // Open the text file for writing.
  cout << "Enter output FILE: ";
  cin >> flipped_file_name;		// Prompt for text file for writing.
  flipped_file_obj.open(flipped_file_name, ios::out);
  if (flipped_file_obj.fail()) {
    cerr << "File for writing failed to open.\n";
    exit(1);
  }

  // Notify user if done!
  flip_text_file(&file_obj, &flipped_file_obj);
  cout << "Flipping done! Please Check the file '"
       << flipped_file_name << "'.\n";

  // Cleanup
  file_obj.close();
  flipped_file_obj.close();
  return 0;
}
