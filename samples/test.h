#ifndef SAMPLE_TEST_H
#define SAMPLE_TEST_H

class Test {
 public:
  Test() = default;
  Test(int i) : i_(i) {}
  int i();

 private:
  int i_;
};

#endif
