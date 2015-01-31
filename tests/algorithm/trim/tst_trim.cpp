//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithm/trim.hpp>

class tst_Trim : public QObject
{
    Q_OBJECT
    
private slots:
    void testTrimString();
    void testTrimWString();
    void testTrimByteArray();
};

void tst_Trim::testTrimString()
{
    bool ok {};

    std::string in { " \t\r\nsome data   " };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, std::string("some data"));

    in = { "\t \n \r\n " };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, std::string());

    in = { "Some data" };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, std::string("Some data"));

    in = { "" };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, std::string());
}

void tst_Trim::testTrimWString()
{
    bool ok {};

    std::wstring in { L" \t\r\nsome data   " };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, std::wstring(L"some data"));

    in = { L"\t \n \r\n " };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, std::wstring());

    in = { L"Some data" };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, std::wstring(L"Some data"));

    in = { L"" };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, std::wstring());
}

void tst_Trim::testTrimByteArray()
{
    bool ok {};

    Calibri::ByteArray in { " \t\r\nsome data   " };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, Calibri::ByteArray("some data"));

    in = { "\t \n \r\n " };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, Calibri::ByteArray());

    in = { "Some data" };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, Calibri::ByteArray("Some data"));

    in = { "" };
    ok = Calibri::trim(in);
    QVERIFY(ok);
    QCOMPARE(in, Calibri::ByteArray());
}

QTEST_MAIN(tst_Trim)

#include "tst_trim.moc"
