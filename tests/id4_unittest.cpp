#include <gtest/gtest.h>
#include "id.h"

class ID4Fixture : public ::testing::Test {
public:
    ID4Fixture()
        : pid(new ID4()),
          abcd("abcd"),
          abcd2('abcd')
    {
    }

    ~ID4Fixture( )
    {
        delete pid;
    }

    ID4 id;
    ID4* pid;
    ID4 abcd;
    ID4 abcd2;
};

TEST_F(ID4Fixture, initializedToZero)
{
    ASSERT_EQ(0, id.getValue());
    ASSERT_EQ(0, pid->getValue());
}

TEST_F(ID4Fixture, equalsAndNotEqual)
{
    ASSERT_EQ(id, *pid);
    ASSERT_NE(id, abcd);
}

// ���������̕����萔�̓��g���E�G���f�B�A���̊��ŕ����̏��Ԃ����]��
// �邱�Ƃ����҂����B
TEST_F(ID4Fixture, getValue)
{
    uint16_t n = 0xabcd;
    uint8_t *p = (uint8_t*) &n;

    if (*p == 0xab) {
        // �r�b�O
        ASSERT_EQ(ID4('abcd'), ID4("abcd"));
    } else if (*p == 0xcd) {
        // ���g��
        ASSERT_NE(ID4('abcd'), ID4("abcd"));
    } else {
        // �����M�����Ȃ��B
        ASSERT_TRUE(false);
    }
}
