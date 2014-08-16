//! Qt Includes
#include <QtTest/QtTest>

//! Calibri-Library Includes
#include "io/datastream.h"

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
    void testDeque();
    void testForwardList();
    void testList();
    void testSet();
    void testMultiSet();
    void testMap();
    void testMultiMap();
    void testUnorderedSet();
    void testUnorderedMultiSet();
    void testUnorderedMap();
    void testUnorderedMultiMap();
};

void tst_DataStream::testInt8()
{
    int8 in { 64 };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "int8 read/write failed.");
}

void tst_DataStream::testUint8()
{
    uint8 in { 64 };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "uint8 read/write failed.");
}

void tst_DataStream::testInt16()
{
    int16 in { 64 };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "int16 read/write failed.");
}

void tst_DataStream::testUint16()
{
    uint16 in { 64 };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "uint16 read/write failed.");
}

void tst_DataStream::testInt32()
{
    int32 in { 64 };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "int32 read/write failed.");
}

void tst_DataStream::testUint32()
{
    uint32 in { 64 };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "uint32 read/write failed.");
}

void tst_DataStream::testInt64()
{
    int64 in { 64 };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "int64 read/write failed.");
}

void tst_DataStream::testUint64()
{
    uint64 in { 64 };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "uint64 read/write failed.");
}

void tst_DataStream::testFloat()
{
    float in { 64.0064f };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "float read/write failed.");
}

void tst_DataStream::testDouble()
{
    double in { 64.0064d };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "double read/write failed.");
}

void tst_DataStream::testLongDouble()
{
    longdouble in { 64.0064l };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "longdouble read/write failed.");
}

void tst_DataStream::testCString()
{
    const char *in { "cstring data" };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    char *out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(out, "cstring read/write failed.");
    QVERIFY2(strcmp(in, out) == 0, "cstring read/write failed.");

    delete[] out;
}

void tst_DataStream::testString()
{
    std::string in { "string data" };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "std::string read/write failed.");
}

void tst_DataStream::testSeek()
{
    std::string in { "string data" };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << 0;
    writeStream << in;

    writeStream.seek(0);

    writeStream << Calibri::metaCast<uint32>(in.size());

    uint32 size {};
    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> size;
    readStream >> out;

    QVERIFY2(Calibri::metaCast<uint32>(in.size() == size), "seek failed.");
    QVERIFY2(in == out, "seek failed.");
}

void tst_DataStream::testVector()
{
    std::vector<std::string> in { 2, "string data" };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "vector read/write failed.");
}

void tst_DataStream::testDeque()
{
    std::deque<std::string> in { 2, "string data" };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "deque read/write failed.");
}

void tst_DataStream::testForwardList()
{
    std::forward_list<std::string> in { 2, "string data" };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "forward list read/write failed.");
}

void tst_DataStream::testList()
{
    std::list<std::string> in { 2, "string data" };

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "list read/write failed.");
}

void tst_DataStream::testSet()
{
    std::set<std::string> in {};
    in.insert("string data");

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "set read/write failed.");
}

void tst_DataStream::testMultiSet()
{
    std::multiset<std::string> in {};
    in.insert("string data");
    in.insert("string data");

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "multiset read/write failed.");
}

void tst_DataStream::testMap()
{
    std::map<std::string, std::string> in {};
    in.insert(std::make_pair("key one", "value one"));
    in.insert(std::make_pair("key two", "value two"));

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "map read/write failed.");
}

void tst_DataStream::testMultiMap()
{
    std::multimap<std::string, std::string> in {};
    in.insert(std::make_pair("key one", "value one"));
    in.insert(std::make_pair("key one", "value two"));

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "multimap read/write failed.");
}

void tst_DataStream::testUnorderedSet()
{
    std::unordered_set<std::string> in {};
    in.insert("string data");

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "unordered set read/write failed.");
}

void tst_DataStream::testUnorderedMultiSet()
{
    std::unordered_multiset<std::string> in {};
    in.insert("string data");
    in.insert("string data");

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "unordered multiset read/write failed.");
}

void tst_DataStream::testUnorderedMap()
{
    std::unordered_map<std::string, std::string> in {};
    in.insert(std::make_pair("key one", "value one"));
    in.insert(std::make_pair("key two", "value two"));

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "unordered map read/write failed.");
}

void tst_DataStream::testUnorderedMultiMap()
{
    std::unordered_multimap<std::string, std::string> in {};
    in.insert(std::make_pair("key one", "value one"));
    in.insert(std::make_pair("key one", "value two"));

    Calibri::Buffer data {};

    Calibri::DataStream<decltype(data)> writeStream(&data);
    writeStream << in;

    decltype(in) out {};

    decltype(writeStream) readStream(&data);
    readStream >> out;

    QVERIFY2(in == out, "unordered multimap read/write failed.");
}

QTEST_MAIN(tst_DataStream)

#include "tst_datastream.moc"
