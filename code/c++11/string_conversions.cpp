#include <string>
#include <sstream>
#include <iostream>
using namespace std;
int main() {
  int a_number = 1337;
  string a_string = to_string(a_number);
  int a_number_again = stoi(a_string);
  string my_hex_string = "0xffff";
  stringstream ss;
  ss << hex << my_hex_number;
  int my_hex_number;
  ss >> my_hex_number;
}
