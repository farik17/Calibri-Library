//! Qt Includes
#include <QtTest/QtTest>

//! Std Includes
#include <iostream>

//! Calibri-Library Includes
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
    QVERIFY2(ok, "Failed to convert from std::string to int8");
    QVERIFY2(out == Calibri::metaCast<decltype(out)>(std::strtol("3", &end, 10)), "Failed to convert from std::string to int8");

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to int8");
    QVERIFY2(out == Calibri::metaCast<decltype(out)>(std::wcstol(L"3", &wend, 10)), "Failed to convert from std::wstring to int8");
}

void tst_metacast::testStringToUInt8()
{
    bool ok { false };

    uint8 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to uint8");
    QVERIFY2(out == Calibri::metaCast<decltype(out)>(std::strtoul("3", &end, 10)), "Failed to convert from std::string to uint8");

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to uint8");
    QVERIFY2(out == Calibri::metaCast<decltype(out)>(std::wcstoul(L"3", &wend, 10)), "Failed to convert from std::wstring to uint8");
}

void tst_metacast::testStringToInt16()
{
    bool ok { false };

    int16 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to int16");
    QVERIFY2(out == Calibri::metaCast<decltype(out)>(std::strtol("3", &end, 10)), "Failed to convert from std::string to int16");

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to int16");
    QVERIFY2(out == Calibri::metaCast<decltype(out)>(std::wcstol(L"3", &wend, 10)), "Failed to convert from std::wstring to int16");
}

void tst_metacast::testStringToUInt16()
{
    bool ok { false };

    uint16 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to uint16");
    QVERIFY2(out == Calibri::metaCast<decltype(out)>(std::strtoul("3", &end, 10)), "Failed to convert from std::string to uint16");

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to uint16");
    QVERIFY2(out == Calibri::metaCast<decltype(out)>(std::wcstoul(L"3", &wend, 10)), "Failed to convert from std::wstring to uint16");
}

void tst_metacast::testStringToInt32()
{
    bool ok { false };

    int32 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to int32");
    QVERIFY2(out == std::strtol("3", &end, 10), "Failed to convert from std::string to int32");

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to int32");
    QVERIFY2(out == std::wcstol(L"3", &wend, 10), "Failed to convert from std::wstring to int32");
}

void tst_metacast::testStringToUInt32()
{
    bool ok { false };

    uint32 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to uint32");
    QVERIFY2(out == std::strtoul("3", &end, 10), "Failed to convert from std::string to uint32");

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to uint32");
    QVERIFY2(out == std::wcstoul(L"3", &wend, 10), "Failed to convert from std::wstring to uint32");
}

void tst_metacast::testStringToInt64()
{
    bool ok { false };

    int64 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to int64");
    QVERIFY2(out == std::strtoll("3", &end, 10), "Failed to convert from std::string to int64");

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to int64");
    QVERIFY2(out == std::wcstoll(L"3", &wend, 10), "Failed to convert from std::wstring to int64");
}

void tst_metacast::testStringToUInt64()
{
    bool ok { false };

    uint64 out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to uint64");
    QVERIFY2(out == std::strtoull("3", &end, 10), "Failed to convert from std::string to uint64");

    out = Calibri::metaCast<decltype(out)>(L"3", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to uint64");
    QVERIFY2(out == std::wcstoull(L"3", &wend, 10), "Failed to convert from std::wstring to uint64");
}

void tst_metacast::testStringToFloat()
{
    bool ok { false };

    float out {};

    char *end {};
    wchar_t *wend {};;

    out = Calibri::metaCast<decltype(out)>("3.03", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to float");
    QVERIFY2(out == std::strtof("3.03", &end), "Failed to convert from std::string to float");

    out = Calibri::metaCast<decltype(out)>(L"3.03", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to float");
    QVERIFY2(out == std::wcstof(L"3.03", &wend), "Failed to convert from std::wstring to float");
}

void tst_metacast::testStringToDouble()
{
    bool ok { false };

    double out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3.003", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to double");
    QVERIFY2(out == std::strtod("3.003", &end), "Failed to convert from std::string to double");

    out = Calibri::metaCast<decltype(out)>(L"3.003", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to double");
    QVERIFY2(out == std::wcstod(L"3.003", &wend), "Failed to convert from std::wstring to double");
}

void tst_metacast::testStringToLongDouble()
{
    bool ok { false };

    longdouble out {};

    char *end {};
    wchar_t *wend {};

    out = Calibri::metaCast<decltype(out)>("3.0003", &ok);
    QVERIFY2(ok, "Failed to convert from std::string to longdouble");
    QVERIFY2(out == std::strtold("3.0003", &end), "Failed to convert from std::string to longdouble");

    out = Calibri::metaCast<decltype(out)>(L"3.0003", &ok);
    QVERIFY2(ok, "Failed to convert from std::wstring to longdouble");
    QVERIFY2(out == std::wcstold(L"3.0003", &wend), "Failed to convert from std::wstring to longdouble");
}

void tst_metacast::testInt8ToString()
{
    int8 in { 3 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from int8 to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from int8 to std::wstring");
}

void tst_metacast::testUInt8ToString()
{
    uint8 in { 3 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from uint8 to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from uint8 to std::wstring");
}

void tst_metacast::testInt16ToString()
{
    int16 in { 3 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from int16 to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from int16 to std::wstring");
}

void tst_metacast::testUInt16ToString()
{
    uint16 in { 3 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from uint16 to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from uint16 to std::wstring");
}

void tst_metacast::testInt32ToString()
{
    int32 in { 3 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from int32 to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from int32 to std::wstring");
}

void tst_metacast::testUInt32ToString()
{
    uint32 in { 3 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from uint32 to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from uint32 to std::wstring");
}

void tst_metacast::testInt64ToString()
{
    int64 in { 3 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from int64 to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from int64 to std::wstring");
}

void tst_metacast::testUInt64ToString()
{
    uint64 in { 3 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from uint64 to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from uint64 to std::wstring");
}

void tst_metacast::testFloatToString()
{
    float in { 3.03 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from float to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from float to std::wstring");
}

void tst_metacast::testDoubleToString()
{
    double in { 3.003 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from double to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from double to std::wstring");
}

void tst_metacast::testLongDoubleToString()
{
    longdouble in { 3.0003 };

    QVERIFY2(Calibri::metaCast<std::string>(in) == std::to_string(in), "Failed to convert from longdouble to std::string");
    QVERIFY2(Calibri::metaCast<std::wstring>(in) == std::to_wstring(in), "Failed to convert from longdouble to std::wstring");
}

void tst_metacast::testStringToWString()
{
    QVERIFY2(Calibri::metaCast<std::wstring>("Some data") == L"Some data", "Failed to convert from std::string to std::wstring");
}

void tst_metacast::testWStringToString()
{
    QVERIFY2(Calibri::metaCast<std::string>(L"Some data") == "Some data", "Failed to convert from std::wstring to std::string");
}

void tst_metacast::testFailCases()
{
    bool ok { false };

    auto outInteger = Calibri::metaCast<int8>("3Some data", &ok);
    QVERIFY2 (!ok, "Failed to \"bad\" convert from std::string to int8");
    QVERIFY2 (outInteger == 0, "Failed to \"bad\" convert from std::string to int8");

    auto outFloatingPoint = Calibri::metaCast<float>("3.003Some data", &ok);
    QVERIFY2 (!ok, "Failed to \"bad\" convert from std::string to float");
    QVERIFY2 (outFloatingPoint == 0.0f, "Failed to \"bad\" convert from std::string to float");

    auto outOverflow = Calibri::metaCast<int8>(123456);
    QVERIFY2 (outOverflow == static_cast<int8>(123456), "Failed to \"bad\" convert from int to int8");
}

QTEST_MAIN(tst_metacast)

#include "tst_metacast.moc"

