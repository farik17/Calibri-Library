//! Qt Includes
#include <QtTest/QtTest>

//! Std Includes
#include <iostream>

//! CalibriLibrary Includes
#include "tools/meta_cast.h"

using Calibri::meta_cast;

enum class Types : uint8
{
    Int8 = 0,
    Uint8,
    Int16,
    Uint16,
    Int32,
    Uint32,
    Int64,
    Uint64,
    Float,
    Double,
    Longdouble,
    Cstring,
    String,
    Wstring,
    Wcstring
};

static std::list<Types> mTypes = {
    Types::Int8,
    Types::Uint8,
    Types::Int16,
    Types::Uint16,
    Types::Int32,
    Types::Uint32,
    Types::Int64,
    Types::Uint64,
    Types::Float,
    Types::Double,
    Types::Cstring,
    Types::String
};

class tst_meta_cast : public QObject
{
    Q_OBJECT

private slots:
    void testFromStringToNumeric();
    void testFromNumericToString();
    void testStringToWString();
    void testWStringToString();
    void testFailCases();
};

void tst_meta_cast::testFromStringToNumeric()
{
    std::string inStringInt { "3" };
    std::string inStringFloat { "3.003" };
    std::wstring inWstringInt { L"3" };
    std::wstring inWstringFloat { L"3.003" };

    for (const auto &type : mTypes) {
        switch (type) {
        case Types::Int8: {
            int8 controlValue { 3 };

            bool ok { false };

            auto out = meta_cast<int8> (inStringInt, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to int8");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to int8");

            out = meta_cast<int8> (inWstringInt);
            QVERIFY2(out, "Failed to convert from std::wstring to int8");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to int8");

            break;
        }

        case Types::Uint8: {
            uint8 controlValue { 3 };

            bool ok { false };

            auto out = meta_cast<uint8> (inStringInt, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to uint8");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to uint8");

            out = meta_cast<uint8> (inWstringInt);
            QVERIFY2(out, "Failed to convert from std::wstring to uint8");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to uint8");

            break;
        }

        case Types::Int16: {
            int16 controlValue { 3 };

            bool ok { false };

            auto out = meta_cast<int16> (inStringInt, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to int16");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to int16");

            out = meta_cast<int16> (inWstringInt);
            QVERIFY2(out, "Failed to convert from std::wstring to int16");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to int16");

            break;
        }

        case Types::Uint16: {
            uint16 controlValue { 3 };

            bool ok { false };

            auto out = meta_cast<uint16> (inStringInt, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to uint16");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to uint16");

            out = meta_cast<uint16> (inWstringInt);
            QVERIFY2(out, "Failed to convert from std::wstring to uint16");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to uint16");

            break;
        }

        case Types::Int32: {
            int32 controlValue { 3 };

            bool ok { false };

            auto out = meta_cast<int32> (inStringInt, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to int32");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to int32");

            out = meta_cast<int32> (inWstringInt);
            QVERIFY2(out, "Failed to convert from std::wstring to int32");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to int32");

            break;
        }

        case Types::Uint32: {
            uint32 controlValue { 3 };

            bool ok { false };

            auto out = meta_cast<uint32> (inStringInt, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to uint32");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to uint32");

            out = meta_cast<uint32> (inWstringInt);
            QVERIFY2(out, "Failed to convert from std::wstring to int32");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to uint32");

            break;
        }

        case Types::Int64: {
            int64 controlValue { 3 };

            bool ok { false };

            auto out = meta_cast<int64> (inStringInt, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to int64");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to int64");

            out = meta_cast<int64> (inWstringInt);
            QVERIFY2(out, "Failed to convert from std::wstring to int64");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to int64");

            break;
        }

        case Types::Uint64: {
            uint64 controlValue { 3 };

            bool ok { false };

            auto out = meta_cast<uint64> (inStringInt, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to uint64");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to uint64");

            out = meta_cast<uint64> (inWstringInt);
            QVERIFY2(out, "Failed to convert from std::wstring to uint64");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to uint64");

            break;
        }

        case Types::Float: {
            float controlValue { 3.003 };

            bool ok { false };

            auto out = meta_cast<float> (inStringFloat, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to float");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to float");

            out = meta_cast<float> (inWstringFloat);
            QVERIFY2(out, "Failed to convert from std::wstring to float");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to float");

            break;
        }

        case Types::Double: {
            double controlValue { 3.003 };

            bool ok { false };

            auto out = meta_cast<double> (inStringFloat, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to double");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to double");

            out = meta_cast<double> (inWstringFloat);
            QVERIFY2(out, "Failed to convert from std::wstring to double");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to double");

            break;
        }

        case Types::Longdouble: {
            longdouble controlValue { 3.003 };

            bool ok { false };

            auto out = meta_cast<longdouble> (inStringFloat, &ok);
            QVERIFY2(ok, "Failed to convert from std::string to longdouble");
            QVERIFY2(out == controlValue, "Failed to convert from std::string to longdouble");

            out = meta_cast<longdouble> (inWstringFloat);
            QVERIFY2(out, "Failed to convert from std::wstring to longdouble");
            QVERIFY2(out == controlValue, "Failed to convert from std::wstring to longdouble");

            break;
        }

        default:
            break;
        }
    }
}

void tst_meta_cast::testFromNumericToString()
{
    std::string stringControlValueInt { "3" };
    std::wstring wstringControlValueInt { L"3" };

    std::string stringControlValueFloat { "3.003000" };
    std::wstring wstringControlValueFloat { L"3.003000" };


    for (auto type : mTypes) {
        switch (type) {
        case Types::Int8: {
            int8 in { 3 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueInt, "Failed to convert from std::string to int8");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueInt, "Failed to convert from std::wstring to int8");

            break;
        }

        case Types::Uint8: {
            uint8 in { 3 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueInt, "Failed to convert from std::string to uint8");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueInt, "Failed to convert from std::wstring to uint8");

            break;
        }

        case Types::Int16: {
            int16 in { 3 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueInt, "Failed to convert from std::string to int16");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueInt, "Failed to convert from std::wstring to int16");

            break;
        }

        case Types::Uint16: {
            uint16 in { 3 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueInt, "Failed to convert from std::string to uint16");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueInt, "Failed to convert from std::wstring to uint16");

            break;
        }

        case Types::Int32: {
            int32 in { 3 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueInt, "Failed to convert from std::string to int32");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueInt, "Failed to convert from std::wstring to int32");

            break;
        }

        case Types::Uint32: {
            uint32 in { 3 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueInt, "Failed to convert from std::string to uint32");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueInt, "Failed to convert from std::wstring to uint32");

            break;
        }

        case Types::Int64: {
            int64 in { 3 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueInt, "Failed to convert from std::string to int64");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueInt, "Failed to convert from std::wstring to int64");

            break;
        }

        case Types::Uint64: {
            uint64 in { 3 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueInt, "Failed to convert from std::string to uint64");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueInt, "Failed to convert from std::wstring to uint64");

            break;
        }

        case Types::Float: {
            float in { 3.003 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueFloat, "Failed to convert from std::string to float");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueFloat, "Failed to convert from std::wstring to float");

            break;
        }

        case Types::Double: {
            double in { 3.003 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueFloat, "Failed to convert from std::string to double");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueFloat, "Failed to convert from std::wstring to double");

            break;
        }

        case Types::Longdouble: {
            longdouble in { 3.003 };

            auto outString = meta_cast<std::string> (in);
            QVERIFY2(outString == stringControlValueFloat, "Failed to convert from std::string to longdouble");

            auto outWstring = meta_cast<std::wstring> (in);
            QVERIFY2(outWstring == wstringControlValueFloat, "Failed to convert from std::wstring to longdouble");

            break;
        }

        default:
            break;
        }
    }
}

void tst_meta_cast::testStringToWString()
{
    std::string inInt { "3" };
    std::string inFloat { "3.003" };

    std::wstring controlWstringInt { L"3" };
    std::wstring controlWstringFloat { L"3.003" };

    auto out = meta_cast<std::wstring> (inInt);
    QVERIFY2(out == controlWstringInt, "Fail to cast std::string to std::wstring");

    out.clear();

    out = meta_cast<std::wstring> (inFloat);
    QVERIFY2(out == controlWstringFloat, "Fail to cast std::string to std::wstring");
}

void tst_meta_cast::testWStringToString()
{
    std::wstring inwstringInt { L"3" };
    std::wstring inwstringFloat { L"3.003" };

    std::string controlStringInt { "3" };
    std::string controlStringFloat { "3.003" };

    auto out = meta_cast<std::string> (inwstringInt);
    QVERIFY2(out == controlStringInt, "Fail to cast std::wstring to std::string");

    out.clear();

    out = meta_cast<std::string> (inwstringFloat);
    QVERIFY2(out == controlStringFloat, "Fail to cast std::wstring to std::string");
}

void tst_meta_cast::testFailCases()
{
    int8 ctrlInt { 0 };
    float ctrlFloat { 0.0f };
    std::string inFailInt { "3and some trash data" };
    std::string inFailFloat { "3.003and some trash data " };

    std::string inTooBigNumber { "123456" };

    bool ok { false };

    auto outInt8 = meta_cast<int8> (inFailInt, &ok);

    QVERIFY2 (!ok, "Failed \"fail case\" cast from std::string to int8. ok == true");
    QVERIFY2 (outInt8 == ctrlInt, "Failed \"fail case\" cast from std::string to int8. out != ctrlInt");

    auto outFloat = meta_cast<float> (inFailFloat, &ok);

    QVERIFY2 (!ok, "Failed \"fail case\" cast from std::string to float. ok == true");
    QVERIFY2 (outFloat == ctrlFloat, "Failed \"fail case\" cast from std::string to float. out != ctrlInt");

    auto int8ToBig = meta_cast<int8> (inTooBigNumber, &ok);

    (void)int8ToBig;

    QVERIFY2 (!ok, "Failed \"fail case\" cast from std::string to float. ok == true");
}

QTEST_MAIN(tst_meta_cast)

#include "tst_meta_cast.moc"

