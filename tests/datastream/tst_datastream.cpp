//! Qt Includes
#include <QtTest/QtTest>

//! Project Includes
#include "datastream.h"

class tst_DataStream : public QObject
{
    Q_OBJECT
    
private slots:
    void testInt8();
    void testUint8();
    void testInt16();
    void testUint16();
    void testInt32();
    void testUint32();
    void testInt64();
    void testUint64();

    void testFloat();
    void testDouble();
    void testLongDouble();

    void testCString();
    void testString();

    void testSeek();

    void testVector();
    void testList();
    void testForwardList();
    void testSet();
    void testMap();
    void testUnorderedSet();
    void testUnorderedMap();
};

void tst_DataStream::testInt8()
{
    int8 in = 1;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    int8 out = 0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "c_int8 read/write failed.");
}

void tst_DataStream::testUint8()
{
    uint8 in = 1;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    uint8 out = 0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "c_uint8 read/write failed.");
}

void tst_DataStream::testInt16()
{
    int16 in = 1;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    int16 out = 0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "c_int16 read/write failed.");
}

void tst_DataStream::testUint16()
{
    uint16 in = 1;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    uint16 out = 0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "c_uint16 read/write failed.");
}

void tst_DataStream::testInt32()
{
    int32 in = 1;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    int32 out = 0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "c_int32 read/write failed.");
}

void tst_DataStream::testUint32()
{
    uint32 in = 1;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    uint32 out = 0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "c_uint32 read/write failed.");
}

void tst_DataStream::testInt64()
{
    int64 in = 1;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    int64 out = 0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "c_int64 read/write failed.");
}

void tst_DataStream::testUint64()
{
    uint64 in = 1;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    uint64 out = 0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "c_uint64 read/write failed.");
}

void tst_DataStream::testFloat()
{
    float in = 1.001f;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    float out = 0.0f;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "float read/write failed.");
}

void tst_DataStream::testDouble()
{
    double in = 1.001;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    double out = 0.0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "double read/write failed.");
}

void tst_DataStream::testLongDouble()
{
    longdouble in = 1.001;

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    longdouble out = 0.0;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "long double read/write failed.");
}

void tst_DataStream::testCString()
{
    const char *in = "cstring data";

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    char *out = nullptr;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(out, "cstring read/write failed.");
    QVERIFY2(strcmp(in, out) == 0, "cstring read/write failed.");

    delete[] out;
}

void tst_DataStream::testString()
{
    std::string in = "string data";

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    std::string out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "std::string read/write failed.");
}

void tst_DataStream::testSeek()
{
    std::string in = "string data";

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << 0;
    writeStream << in;

    writeStream.seek(0);

    writeStream << static_cast<uint32>(in.size());

    uint32 size = 0;
    std::string out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> size;
    readStream >> out;

    QVERIFY2(static_cast<uint32>(in.size() == size), "seek failed.");
    QVERIFY2(in == out, "seek failed.");
}

void tst_DataStream::testVector()
{
    std::vector<std::string> in(10, "string data");

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    std::vector<std::string> out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "vector read/write failed.");
}

void tst_DataStream::testList()
{
    std::list<std::string> in(10, "string data");

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    std::list<std::string> out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "list read/write failed.");
}

void tst_DataStream::testForwardList()
{
    std::forward_list<std::string> in(10, "string data");

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    std::forward_list<std::string> out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "forward list read/write failed.");
}

void tst_DataStream::testSet()
{
    std::set<std::string> in;

    in.insert("string data");

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    std::set<std::string> out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "set read/write failed.");
}

void tst_DataStream::testMap()
{
    std::map<std::string, std::string> in;

    in.insert(std::make_pair("key one", "value one"));
    in.insert(std::make_pair("key two", "value two"));

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    std::map<std::string, std::string> out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "map read/write failed.");
}

void tst_DataStream::testUnorderedSet()
{
    std::unordered_set<std::string> in;

    in.insert("string data");

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    std::unordered_set<std::string> out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "unordered set read/write failed.");
}

void tst_DataStream::testUnorderedMap()
{
    std::unordered_map<std::string, std::string> in;

    in.insert(std::make_pair("key one", "value one"));
    in.insert(std::make_pair("key two", "value two"));

    std::string buffer;

    Calibri::DataStream<std::string> writeStream(buffer);
    writeStream << in;

    std::unordered_map<std::string, std::string> out;

    Calibri::DataStream<std::string> readStream(buffer);
    readStream >> out;

    QVERIFY2(in == out, "unordered map read/write failed.");
}

QTEST_MAIN(tst_DataStream)

#include "tst_datastream.moc"
