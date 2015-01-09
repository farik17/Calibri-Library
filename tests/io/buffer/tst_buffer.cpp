//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <io/buffer.h>
#include <tools/metacast.h>

class tst_Buffer : public QObject
{
    Q_OBJECT
    
private slots:
    void testRead();
    void testWrite();
    void testCanReadLine();
    void testReadLine();
    void testAtEnd();
    void testSeek();
    void testSkip();
};

void tst_Buffer::testRead()
{
    bool ok {};
    sizeinfo bytes {};

    Calibri::Buffer in { "Some data, some data 2, some data 3, some data 4", 48 };
    Calibri::ByteArray out { 9 };
    bytes = in.read(out.data(), out.size(), &ok);
    QVERIFY(ok);
    QCOMPARE(bytes, out.size());
    QCOMPARE(out, Calibri::ByteArray("Some data"));

    in.skip(2);
    out.resize(11);
    bytes = in.read(out, out.size(), &ok);
    QVERIFY(ok);
    QCOMPARE(bytes, out.size());
    QCOMPARE(out, Calibri::ByteArray("some data 2"));

    in.skip(2);
    out = in.read(11, &ok);
    QVERIFY(ok);
    QCOMPARE(out.size(), Calibri::metaCast<sizeinfo>(11));
    QCOMPARE(out, Calibri::ByteArray("some data 3"));

    in.skip(2);
    out = in.read(15, &ok);
    QVERIFY(ok);
    QCOMPARE(out.size(), Calibri::metaCast<sizeinfo>(11));
    QCOMPARE(out, Calibri::ByteArray("some data 4"));
}

void tst_Buffer::testWrite()
{
    bool ok {};
    sizeinfo bytes {};

    Calibri::Buffer data {};
    bytes = data.write("some data", 9, &ok);
    QVERIFY(ok);
    QCOMPARE(bytes, Calibri::metaCast<sizeinfo>(9));
    QCOMPARE(data, Calibri::Buffer("some data"));

    bytes = data.write(Calibri::ByteArray(", some data 2"), 13, &ok);
    QVERIFY(ok);
    QCOMPARE(bytes, Calibri::metaCast<sizeinfo>(13));
    QCOMPARE(data, Calibri::Buffer("some data, some data 2"));

    bytes = data.write(", some data 3", &ok);
    QVERIFY(ok);
    QCOMPARE(bytes, Calibri::metaCast<sizeinfo>(13));
    QCOMPARE(data, Calibri::Buffer("some data, some data 2, some data 3"));
}

void tst_Buffer::testCanReadLine()
{
    Calibri::Buffer data { "Some data" };
    QVERIFY(!data.canReadLine());

    data = { "Some data 2\n" };
    QVERIFY(data.canReadLine());
}

void tst_Buffer::testReadLine()
{
    bool ok {};
    sizeinfo bytes {};

    Calibri::Buffer in { "Some data, some data 2", 22 };
    Calibri::ByteArray out { 9 };
    bytes = in.readLine(out, 9, &ok);
    QVERIFY(ok);
    QCOMPARE(bytes, Calibri::metaCast<sizeinfo>(9));
    QCOMPARE(out, Calibri::ByteArray("Some data"));

    in.skip(2);
    out.resize(11);
    bytes = in.readLine(out, 15, &ok);
    QVERIFY(ok);
    QCOMPARE(bytes, Calibri::metaCast<sizeinfo>(11));
    QCOMPARE(out, Calibri::ByteArray("some data 2"));

    in = { "Some data\nsome data 2\n" };
    out.resize(15);
    bytes = in.readLine(out, 15, &ok);
    QVERIFY(ok);
    QCOMPARE(bytes, Calibri::metaCast<sizeinfo>(10));
    out.resize(bytes);
    QCOMPARE(out, Calibri::ByteArray("Some data\n"));

    out = in.readLine(15, &ok);
    QVERIFY(ok);
    QCOMPARE(out.size(), Calibri::metaCast<sizeinfo>(12));
    QCOMPARE(out, Calibri::ByteArray("some data 2\n"));
}

void tst_Buffer::testAtEnd()
{
    Calibri::Buffer data { "Some data", 9 };
    QVERIFY(!data.atEnd());

    data.seek(9);
    QVERIFY(data.atEnd());
}

void tst_Buffer::testSeek()
{
    Calibri::Buffer data { "Some data", 9 };
    QVERIFY(!data.seek(15));
    QCOMPARE(data.pos(), Calibri::metaCast<sizeinfo>(0));

    QVERIFY(data.seek(9));
    QCOMPARE(data.pos(), Calibri::metaCast<sizeinfo>(9));
}

void tst_Buffer::testSkip()
{
    Calibri::Buffer data { "Some data", 9 };
    QVERIFY(!data.skip(15));
    QCOMPARE(data.pos(), Calibri::metaCast<sizeinfo>(0));

    QVERIFY(data.skip(4));
    QVERIFY(data.skip(5));
    QCOMPARE(data.pos(), Calibri::metaCast<sizeinfo>(9));
}

QTEST_MAIN(tst_Buffer)

#include "tst_buffer.moc"
