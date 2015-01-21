//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithm/simplify.h>

class tst_Simplify : public QObject
{
    Q_OBJECT

private slots:
    void testSimplifyString();
    void testSimplifyWString();
    void testSimplifyByteArray();
};

void tst_Simplify::testSimplifyString()
{
    bool ok {};

    std::string in { " \t\r\nsome data, some \r\ndata\n2\t  " };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, std::string("some data, some data 2"));

    in = { "\t \n \r\n " };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, std::string());

    in = { "Some data" };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, std::string("Some data"));

    in = { "" };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, std::string());
}

void tst_Simplify::testSimplifyWString()
{
    bool ok {};

    std::wstring in { L" \t\r\nsome data, some \r\ndata\n2\t  " };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, std::wstring(L"some data, some data 2"));

    in = { L"\t \n \r\n " };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, std::wstring());

    in = { L"Some data" };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, std::wstring(L"Some data"));

    in = { L"" };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, std::wstring());
}

void tst_Simplify::testSimplifyByteArray()
{
    bool ok {};

    Calibri::ByteArray in { " \t\r\nsome data, some \r\ndata\n2\t  " };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, Calibri::ByteArray("some data, some data 2"));

    in = { "\t \n \r\n " };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, Calibri::ByteArray());

    in = { "Some data" };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, Calibri::ByteArray("Some data"));

    in = { "" };
    ok = Calibri::simplify(in);
    QVERIFY(ok);
    QCOMPARE(in, Calibri::ByteArray());
}

QTEST_MAIN(tst_Simplify)

#include "tst_simplify.moc"
