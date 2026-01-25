int main(void) {
  int a = 10;
  {
    int a = 20;
    {
      int a = 30;
    }
  }
  return a;
}