#include <iostream>
#include <fstream>
using namespace std;

// Implement linked lists (for fun!)
struct int_linked_list
{
  int num;
  struct int_linked_list *next;
};

struct int_linked_list *
initialize_int_linked_list(int num)
{
  struct int_linked_list *p;
  p = (struct int_linked_list *)malloc(sizeof(struct int_linked_list));

  if (p == NULL)
    throw new runtime_error("Ran out of storage.");

  p->num = num;
  p->next = NULL;

  return p;
}

struct int_linked_list *
add_to_int_linked_list(struct int_linked_list *list_item_ptr, int num)
{
  struct int_linked_list *new_item = initialize_int_linked_list(num);
  if (list_item_ptr) new_item->next = list_item_ptr;
  return new_item;
}

void
print_int_linked_list(struct int_linked_list *list_item_ptr)
{
  while (list_item_ptr) {
    cout << list_item_ptr->num << " ";
    list_item_ptr = list_item_ptr->next;
  }
}

size_t
sizeof_int_linked_list(struct int_linked_list *list_item_ptr)
{
  size_t count = 0;
  while (list_item_ptr) {
    ++count;
    list_item_ptr = list_item_ptr->next;
  }
  return count;
}

void
free_int_linked_list(struct int_linked_list *list_item_ptr)
{
  while (list_item_ptr) {
    struct int_linked_list *next_item = list_item_ptr;
    list_item_ptr = list_item_ptr->next;
    free(next_item);
  }
}

int *
int_linked_list_to_array(struct int_linked_list *list_item_ptr, size_t *arrsize)
{
  size_t i = 0;
  *arrsize = sizeof_int_linked_list(list_item_ptr);
  int *arr = (int *)malloc(*arrsize * sizeof(int));
  while (list_item_ptr) {
    arr[i] = list_item_ptr->num;
    ++i;
    list_item_ptr = list_item_ptr->next;
  }
  return arr;
}

struct int_linked_list *
append_int_linked_list(struct int_linked_list *list_item_ptr1,
		       struct int_linked_list *list_item_ptr2)
{
  if (!list_item_ptr1 || !list_item_ptr2) {
    throw runtime_error("Passed null pointer.");
  }
  struct int_linked_list *first_elt_ptr = list_item_ptr1;
  while (list_item_ptr1->next) {
    list_item_ptr1 = list_item_ptr1->next;
  }
  list_item_ptr1->next = list_item_ptr2;
  return first_elt_ptr;
}

void
swap(int *a, int*b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void
bubble_sort(int *arr, size_t n)
{
  for (size_t i = 0; i < n - 1; ++i) {
    for (size_t j = 0; j < n - i - 1; ++j) {
      if (arr[j] > arr[j+1]) {
	swap(arr+j, arr+j+1);
      }
    }
  }
}

void
merge_sort_and_dump_files_of_ints(fstream *file1_obj,
				  fstream *file2_obj,
				  fstream *file3_obj)
{
  struct int_linked_list *file1_values = NULL;
  struct int_linked_list *file2_values = NULL;
  struct int_linked_list *file3_values = NULL;
  size_t file3_arrsize;
  int num;

  while (*file1_obj >> num)
    file1_values = add_to_int_linked_list(file1_values, num);
  while (*file2_obj >> num)
    file2_values = add_to_int_linked_list(file2_values, num);

  file3_values = append_int_linked_list(file1_values, file2_values);
  int *file3_array = int_linked_list_to_array(file3_values, &file3_arrsize);
  bubble_sort(file3_array, file3_arrsize);

  for (size_t i = 0; i < file3_arrsize; ++i) {
    *file3_obj << file3_array[i] << '\n';
  }

  free_int_linked_list(file3_values);
}

int
main ()
{
  fstream file_obj_1;
  fstream file_obj_2;
  fstream file_obj_3;
  string file_name_1;
  string file_name_2;
  string file_name_3;

  cout << "Welcome to Files of Integers Merger Program!\n"
       << "\n"
       << "Merge sorted numbers from FILE1 and FILE2.\n"
       << "Output is dumped on FILE3 in ascending order."
       << "\n\n";

  // Open the text file 1 for reading.
  cout << "Enter file name of FILE1: ";
  cin >> file_name_1;		// Prompt for text file for reading.
  file_obj_1.open(file_name_1, ios::in);
  if (file_obj_1.fail()) {
    cerr << "'" << file_name_1 << "' for reading failed to open.\n";
    exit(1);
  }

  // Open the text file 2 for reading.
  cout << "Enter file name of FILE2: ";
  cin >> file_name_2;		// Prompt for text file for reading.
  file_obj_2.open(file_name_2, ios::in);
  if (file_obj_2.fail()) {
    cerr << "'" << file_name_2 << "' for reading failed to open.\n";
    exit(2);
  }

  // Open the text file 3 for writing.
  cout << "Enter file name of FILE3: ";
  cin >> file_name_3;		// Prompt for text file for reading.
  file_obj_3.open(file_name_3, ios::out);
  if (file_obj_3.fail()) {
    cerr << "'" << file_name_3 << "' for writing failed to open.\n";
    exit(3);
  }

  // Notify user if done!
  merge_sort_and_dump_files_of_ints(&file_obj_1, &file_obj_2, &file_obj_3);
  cout << "\nDone! Please Check the file '"
       << file_name_3 << "'.\n";

  // Cleanup
  file_obj_1.close();
  file_obj_2.close();
  file_obj_3.close();
  
  return 0;
}
