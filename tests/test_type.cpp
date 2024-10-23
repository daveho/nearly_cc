#include "tctest.h"
#include "type.h"

struct TestObjs {
  std::shared_ptr<Type> basic_int;
  std::shared_ptr<Type> basic_const_int;
  std::shared_ptr<Type> basic_volatile_int;
  std::shared_ptr<Type> basic_const_volatile_int;
  std::shared_ptr<Type> basic_volatile_const_int;
};

TestObjs *setup();
void cleanup(TestObjs *objs);

void test_basic(TestObjs *objs);
void test_qualified(TestObjs *objs);

int main(int argc, char **argv) {
  if (argc > 1)
    tctest_testname_to_execute = argv[1];

  TEST_INIT();

  TEST(test_basic);
  TEST(test_qualified);

  TEST_FINI();
}

TestObjs *setup() {
  TestObjs *objs = new TestObjs();

  objs->basic_int = std::make_shared<BasicType>(BasicTypeKind::INT, true);
  objs->basic_const_int = std::make_shared<QualifiedType>(objs->basic_int, TypeQualifier::CONST);
  objs->basic_volatile_int = std::make_shared<QualifiedType>(objs->basic_int, TypeQualifier::VOLATILE);
  objs->basic_const_volatile_int = std::make_shared<QualifiedType>(objs->basic_volatile_int, TypeQualifier::CONST);
  objs->basic_volatile_const_int = std::make_shared<QualifiedType>(objs->basic_const_int, TypeQualifier::VOLATILE);

  return objs;
}

void cleanup(TestObjs *objs) {
  delete objs;
}

void test_basic(TestObjs *objs) {
  ASSERT(objs->basic_int->get_basic_type_kind() == BasicTypeKind::INT);
  ASSERT(objs->basic_int->is_signed());
}

void test_qualified(TestObjs *objs) {
  ASSERT(objs->basic_const_int->is_const());
  ASSERT(!objs->basic_const_int->is_volatile());
  ASSERT(objs->basic_const_int->get_unqualified_type()->is_same(objs->basic_int.get()));

  ASSERT(!objs->basic_volatile_int->is_const());
  ASSERT(objs->basic_volatile_int->is_volatile());
  ASSERT(objs->basic_volatile_int->get_unqualified_type()->is_same(objs->basic_int.get()));

  ASSERT(objs->basic_const_volatile_int->is_const());
  ASSERT(objs->basic_const_volatile_int->is_volatile());
  ASSERT(objs->basic_const_volatile_int->get_unqualified_type()->is_same(objs->basic_int.get()));

  ASSERT(objs->basic_volatile_const_int->is_const());
  ASSERT(objs->basic_volatile_const_int->is_volatile());
  ASSERT(objs->basic_volatile_const_int->get_unqualified_type()->is_same(objs->basic_int.get()));

  // order of qualifiers shouldn't matter
  ASSERT(objs->basic_const_volatile_int->is_same(objs->basic_volatile_const_int.get()));
}
