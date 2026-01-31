int main(void) {
  int a = 20;
  {
    int a = 40;
  }
  return a;
}