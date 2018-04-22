#include "gtest/gtest.h"
#include "Foo.h"

TEST(FooTest, DefaultValue) {
    Foo f;
    EXPECT_EQ(0, f.get());
}

TEST (FooTest, GetSet) {
    Foo f;
    f.set(123);
    EXPECT_EQ(123,f.get());
}