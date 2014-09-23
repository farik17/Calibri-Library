//! Qt Includes
#include <QtTest/QtTest>

//! Std Includes
#include <iostream>

//! Calibri-Library Includes
#include "tools/buffer.h"

class tst_buffer : public QObject
{
    Q_OBJECT

private slots:
    void testUpper();
    void testLower();
    void testHex();
    void testBase64();
};

void tst_buffer::testUpper()
{
    QCOMPARE(Calibri::Buffer("some data").toUpper(), Calibri::Buffer("SOME DATA"));
}

void tst_buffer::testLower()
{
    QCOMPARE(Calibri::Buffer("SOME DATA").toLower(), Calibri::Buffer("some data"));
}

void tst_buffer::testHex()
{
    bool ok { false };

    auto out = Calibri::Buffer("Some date").toHex(&ok);
    QVERIFY(ok);

    out = Calibri::Buffer::fromHex(out, &ok);
    QVERIFY(ok);

    QCOMPARE(out, Calibri::Buffer("Some date"));
}

void tst_buffer::testBase64()
{
    bool ok { false };

    auto out = Calibri::Buffer("Some date").toBase64(&ok);
    QVERIFY(ok);

    out = Calibri::Buffer::fromBase64(out, &ok);
    QVERIFY(ok);

    QCOMPARE(out, Calibri::Buffer("Some date"));
}

QTEST_MAIN(tst_buffer)

#include "tst_buffer.moc"
