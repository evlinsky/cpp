// = declaration
//int my_fav_num(int a, int b);

int main(int argc, char** argv) {
  return my_fav_num(argc);
}

// = definition (implicit declaration)
int my_fav_num(int a, int b) {
  return a + b;
}
