#include <gtest/gtest.h>

#include "sys.h"

TEST(GlobalFunctionsTest, trimstr_nullCase)
{
    char str[100] = "";
    ASSERT_STREQ("", trimstr(str));
}

TEST(GlobalFunctionsTest, trimstr_noSpace)
{
    char str[100] = "word";
    ASSERT_STREQ("word", trimstr(str));
}

TEST(GlobalFunctionsTest, trimstr_space)
{
    char str[100] = " word ";
    ASSERT_STREQ("word", trimstr(str));
}

TEST(GlobalFunctionsTest, trimstr_tab)
{
    char str[100] = "\tword\t";
    ASSERT_STREQ("word", trimstr(str));
}

// �󔒂�������Ȃ镶�����n���ƁA������̐擪���ȑO�̃������ɃA�N
// �Z�X����o�O���������B
TEST(GlobalFunctionsTest, trimstr_letsTryToSmashStack)
{
    char changeMe[2] = { 'A','\t' };
    char str[100] = " ";

    ASSERT_STREQ("", trimstr(str));
    ASSERT_EQ('A', changeMe[0]);
    ASSERT_EQ('\t', changeMe[1]);
}

TEST(GlobalFunctionsTest, stristr)
{
    const char *str = "abABcdCD";

    ASSERT_EQ(str, stristr(str, "ab"));
    ASSERT_STREQ("ABcdCD", stristr(str + 2, "ab"));
    ASSERT_EQ(NULL, stristr(str + 4, "ab"));
}
