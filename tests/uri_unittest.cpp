// URI �N���X�̃e�X�g�B

#include <gtest/gtest.h>
#include "uri.h"

class URIFixture : public ::testing::Test {
public:
};

#include "LUrlParser.h"
TEST_F(URIFixture, httpScheme)
{
    URI u("http://www.example.com");

    ASSERT_TRUE(u.isValid());
    ASSERT_STREQ("http", u.scheme().c_str());
    ASSERT_STREQ("www.example.com", u.host().c_str());
    ASSERT_EQ(80, u.port()); // �|�[�g�w�肪�Ȃ��ꍇ�̓X�L�[���̃f�t�H���g�|�[�g�B
    ASSERT_STREQ("/", u.path().c_str()); // �p�X���ȗ�����Ă���ꍇ�� "/" �ɂȂ�B
}

TEST_F(URIFixture, httpSchemeWithPortQueryAndFragment)
{
    URI u("http://localhost:7144/html/en/index.html?name=%E4%BA%88%E5%AE%9A%E5%9C%B0#top");

    ASSERT_TRUE(u.isValid());
    ASSERT_STREQ("http", u.scheme().c_str());
    ASSERT_STREQ("localhost", u.host().c_str());
    ASSERT_EQ(7144, u.port());
    ASSERT_STREQ("/html/en/index.html", u.path().c_str());
    ASSERT_STREQ("name=%E4%BA%88%E5%AE%9A%E5%9C%B0", u.query().c_str()); // �����I�� unescape �͂���Ȃ��B
    ASSERT_STREQ("top", u.fragment().c_str());
}

TEST_F(URIFixture, ftpScheme)
{
    URI u("ftp://user:pass@localhost/pub/file.bin");
    ASSERT_TRUE(u.isValid());
    ASSERT_STREQ("ftp", u.scheme().c_str());
    ASSERT_STREQ("user:pass", u.user_info().c_str());
    ASSERT_STREQ("localhost", u.host().c_str());
    ASSERT_STREQ("/pub/file.bin", u.path().c_str());
}

TEST_F(URIFixture, invalidURI)
{
    URI u("hoge");

    ASSERT_FALSE(u.isValid());
    EXPECT_STREQ("", u.scheme().c_str());
}

TEST_F(URIFixture, emptyURI)
{
    ASSERT_NO_THROW(URI(""));

    URI u("");
    ASSERT_FALSE(u.isValid());
}

// TEST_F(URIFixture, mailtoScheme)
// {
//     URI u("mailto:webmaster@example.com");
//     ASSERT_TRUE(u.isValid());
//     ASSERT_STREQ("mailto", u.scheme().c_str());
//     ASSERT_STREQ("webmaster@example.com", u.path().c_str());
//     ASSERT_STREQ("", u.host().c_str());
// }

// mailto�X�L�[���ɂ͑Ή����Ȃ��B
TEST_F(URIFixture, mailtoScheme)
{
    URI u("mailto:webmaster@example.com");
    ASSERT_FALSE(u.isValid());
}

// ����URL�͎g���Ȃ��B
TEST_F(URIFixture, relativeURI)
{
    ASSERT_NO_THROW(URI("/index.html"));

    URI u("/index.html");
    ASSERT_FALSE(u.isValid());
}
