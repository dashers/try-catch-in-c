// main->f1(catchException)->f2->f3->throwException

#include <stdio.h>

void throwException(int);
void cancelCatchException(void);
int catchException(void);

void f3()
{
  fprintf(stderr, "f3 entered\n");
  throwException(1999);
  fprintf(stderr, "f3 exiting\n");
}

void f2()
{  
  fprintf(stderr, "f2 entered\n");
  f3();
  fprintf(stderr, "f2 exiting\n");
}

void f1()
{
  fprintf(stderr, "f1 entered\n");
  int caughtException;
  if ((caughtException = catchException()))
  {
    fprintf(stderr, "catch clause entered\n");
    fprintf(stderr, "caught exception %d\n", caughtException);
    fprintf(stderr, "catch clause exiting\n");
  }
  else
  {

    fprintf(stderr, "try block entered\n");
    f2();
    cancelCatchException();
    fprintf(stderr, "try block exiting\n");
  }

  fprintf(stderr, "f1 exiting\n");
}

int main(int argc, char*argv[])
{
  
  fprintf(stderr, "main entered\n");
  f1();
  fprintf(stderr, "main exiting\n");
  return 0;
}
