//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <tools/bytearray.h>

class tst_bytearray : public QObject
{
    Q_OBJECT

private slots:
    void testUpper();
    void testLower();
    void testHex();
    void testBase64();
};

void tst_bytearray::testUpper()
{
    bool ok {};

    Calibri::ByteArray in { "some data" };
    auto out = in.toUpper(&ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("SOME DATA"));

    out = Calibri::ByteArray("some data").toUpper(&ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("SOME DATA"));

}

void tst_bytearray::testLower()
{
    bool ok {};

    Calibri::ByteArray in { "SOME DATA" };
    auto out = in.toLower(&ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("some data"));

    out = Calibri::ByteArray("SOME DATA").toLower(&ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::ByteArray("some data"));
}

void tst_bytearray::testHex()
{
    bool ok {};

    auto out = Calibri::ByteArray("Some date").toHex(&ok);
    QVERIFY(ok);

    out = Calibri::ByteArray::fromHex(out, &ok);
    QVERIFY(ok);

    QCOMPARE(out, Calibri::ByteArray("Some date"));
}

void tst_bytearray::testBase64()
{
    bool ok {};

    auto out = Calibri::ByteArray("Some date").toBase64(&ok);
    QVERIFY(ok);

    out = Calibri::ByteArray::fromBase64(out, &ok);
    QVERIFY(ok);

    QCOMPARE(out, Calibri::ByteArray("Some date"));
}

QTEST_MAIN(tst_bytearray)

#include "tst_bytearray.moc"
