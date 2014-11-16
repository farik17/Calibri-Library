//! Qt includes
#include <QtTest/QtTest>

//! Std includes
#include <iostream>

//! Calibri-Library includes
#include "tools/metacast.h"

class tst_metacast : public QObject
{
    Q_OBJECT

private slots:
    void testStringToInt8();
    void testStringToUInt8();
    void testStringToInt16();
    void testStringToUInt16();
    void testStringToInt32();
    void testStringToUInt32();
    void testStringToInt64();
    void testStringToUInt64();
    void testStringToFloat();
    void testStringToDouble();
    void testStringToLongDouble();

    void testInt8ToString();
    void testUInt8ToString();
    void testInt16ToString();
    void testUInt16ToString();
    void testInt32ToString();
    void testUInt32ToString();
    void testInt64ToString();
    void testUInt64ToString();
    void testFloatToString();
    void testDoubleToString();
    void testLongDoubleToString();

    void testStringToWString();
    void testWStringToString();
    void testFailCases();
};

void tst_metacast::testStringToInt8()
{
    bool ok { false };

    int8 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::strtol("3", &end, 10)));

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::wcstol(L"3", &wend, 10)));
}

void tst_metacast::testStringToUInt8()
{
    bool ok { false };

    uint8 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::strtoul("3", &end, 10)));

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::wcstoul(L"3", &wend, 10)));
}

void tst_metacast::testStringToInt16()
{
    bool ok { false };

    int16 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::strtol("3", &end, 10)));

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::wcstol(L"3", &wend, 10)));
}

void tst_metacast::testStringToUInt16()
{
    bool ok { false };

    uint16 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::strtoul("3", &end, 10)));

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::wcstoul(L"3", &wend, 10)));
}

void tst_metacast::testStringToInt32()
{
    bool ok { false };

    int32 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::strtol("3", &end, 10)));

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::wcstol(L"3", &wend, 10)));
}

void tst_metacast::testStringToUInt32()
{
    bool ok { false };

    uint32 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::strtoul("3", &end, 10)));

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::wcstoul(L"3", &wend, 10)));
}

void tst_metacast::testStringToInt64()
{
    bool ok { false };

    int64 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::strtoll("3", &end, 10)));

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::wcstoll(L"3", &wend, 10)));
}

void tst_metacast::testStringToUInt64()
{
    bool ok { false };

    uint64 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::strtoull("3", &end, 10)));

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY(ok);
    QCOMPARE(out, Calibri::metaCast<decltype(out)>(std::wcstoull(L"3", &wend, 10)));
}

void tst_metacast::testStringToFloat()
{
    bool ok { false };

    float out {};

    char *end {};
    wchar_t *wend {};;

    out = Calibri::metaCast<decltype(out)>("3.03", &ok);
    QVERIFY(ok);
    QCOMPARE(out, std::strtof("3.03", &end));

    out = Calibri::metaCast<decltype(out)>(L"3.03", &ok);
    QVERIFY(ok);
    QCOMPARE(out, std::wcstof(L"3.03", &wend));
}

void tst_metacast::testStringToDouble()
{
    bool ok { false };

    double out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3.003", &ok);
    QVERIFY(ok);
    QCOMPARE(out, std::strtod("3.003", &end));

    out = Calibri::metaCast<decltype(out)>(L"3.003", &ok);
    QVERIFY(ok);
    QCOMPARE(out, std::wcstod(L"3.003", &wend));
}

void tst_metacast::testStringToLongDouble()
{
    bool ok { false };

    longdouble out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3.0003", &ok);
    QVERIFY(ok);
    QCOMPARE(out, std::strtold("3.0003", &end));

    out = Calibri::metaCast<decltype(out)>(L"3.0003", &ok);
    QVERIFY(ok);
    QCOMPARE(out, std::wcstold(L"3.0003", &wend));
}

void tst_metacast::testInt8ToString()
{
    int8 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testUInt8ToString()
{
    uint8 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testInt16ToString()
{
    int16 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testUInt16ToString()
{
    uint16 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testInt32ToString()
{
    int32 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testUInt32ToString()
{
    uint32 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testInt64ToString()
{
    int64 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testUInt64ToString()
{
    uint64 in { 3 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testFloatToString()
{
    float in { 3.03 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testDoubleToString()
{
    double in { 3.003 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testLongDoubleToString()
{
    longdouble in { 3.0003 };

    QCOMPARE(Calibri::metaCast<std::string>(in), std::to_string(in));
    QCOMPARE(Calibri::metaCast<std::wstring>(in), std::to_wstring(in));
}

void tst_metacast::testStringToWString()
{
    QCOMPARE(Calibri::metaCast<std::wstring>("Some data"), std::wstring(L"Some data"));
}

void tst_metacast::testWStringToString()
{
    QCOMPARE(Calibri::metaCast<std::string>(L"Some data"), std::string("Some data"));
}

void tst_metacast::testFailCases()
{
    bool ok { false };

    auto outInteger = Calibri::metaCast<int8>("3Some data", &ok);
    QVERIFY(!ok);
    QCOMPARE(outInteger, Calibri::metaCast<decltype(outInteger)>(0));

    auto outFloatingPoint = Calibri::metaCast<float>("3.003Some data", &ok);
    QVERIFY(!ok);
    QCOMPARE(outFloatingPoint, 0.0f);

    auto outOverflow = Calibri::metaCast<int8>(123456);
    QCOMPARE(outOverflow, static_cast<int8>(123456));
}

QTEST_MAIN(tst_metacast)

#include "tst_metacast.moc"

