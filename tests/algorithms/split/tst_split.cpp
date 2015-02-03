//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithms/split.hpp>

class tst_Split : public QObject
{
    Q_OBJECT
    
private slots:
    void testSplitToStringVector();
    void testSplitToWStringVector();
    void testSplitToByteArrayVector();
    void testSplitToStringDeque();
    void testSplitToWStringDeque();
    void testSplitToByteArrayDeque();
    void testSplitToStringForwardList();
    void testSplitToWStringForwardList();
    void testSplitToByteArrayForwardList();
    void testSplitToStringList();
    void testSplitToWStringList();
    void testSplitToByteArrayList();
};

void tst_Split::testSplitToStringVector()
{
    bool ok {};

    std::vector<std::string> out;
    ok = Calibri::split(out, std::string(";Some;;data;"), [](char symbol) noexcept { return symbol == ';'; });
    decltype(out) check { "Some", "data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::string(";Some;;data;"), ';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::string(";;Some;;;;data;;"), std::string(";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { "Some data" };
    ok = Calibri::split(out, std::string("Some data"), std::string(";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToWStringVector()
{
    bool ok {};

    std::vector<std::wstring> out;
    ok = Calibri::split(out, std::wstring(L";Some;;data;"), [](wchar symbol) noexcept { return symbol == L';'; });
    decltype(out) check { L"Some", L"data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::wstring(L";Some;;data;"), L';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::wstring(L";;Some;;;;data;;"), std::wstring(L";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { L"Some data" };
    ok = Calibri::split(out, std::wstring(L"Some data"), std::wstring(L";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToByteArrayVector()
{
    bool ok {};

    std::vector<Calibri::ByteArray> out;
    ok = Calibri::split(out, Calibri::ByteArray(";Some;;data;"), [](char symbol) noexcept { return symbol == ';'; });
    decltype(out) check { "Some", "data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, Calibri::ByteArray(";Some;;data;"), ';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, Calibri::ByteArray(";;Some;;;;data;;"), Calibri::ByteArray(";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { "Some data" };
    ok = Calibri::split(out, Calibri::ByteArray("Some data"), Calibri::ByteArray(";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToStringDeque()
{
    bool ok {};

    std::deque<std::string> out;
    ok = Calibri::split(out, std::string(";Some;;data;"), [](char symbol) noexcept { return symbol == ';'; });
    decltype(out) check { "Some", "data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::string(";Some;;data;"), ';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::string(";;Some;;;;data;;"), std::string(";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { "Some data" };
    ok = Calibri::split(out, std::string("Some data"), std::string(";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToWStringDeque()
{
    bool ok {};

    std::deque<std::wstring> out;
    ok = Calibri::split(out, std::wstring(L";Some;;data;"), [](wchar symbol) noexcept { return symbol == L';'; });
    decltype(out) check { L"Some", L"data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::wstring(L";Some;;data;"), L';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::wstring(L";;Some;;;;data;;"), std::wstring(L";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { L"Some data" };
    ok = Calibri::split(out, std::wstring(L"Some data"), std::wstring(L";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToByteArrayDeque()
{
    bool ok {};

    std::deque<Calibri::ByteArray> out;
    ok = Calibri::split(out, Calibri::ByteArray(";Some;;data;"), [](char symbol) noexcept { return symbol == ';'; });
    decltype(out) check { "Some", "data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, Calibri::ByteArray(";Some;;data;"), ';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, Calibri::ByteArray(";;Some;;;;data;;"), Calibri::ByteArray(";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { "Some data" };
    ok = Calibri::split(out, Calibri::ByteArray("Some data"), Calibri::ByteArray(";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToStringForwardList()
{
    bool ok {};

    std::forward_list<std::string> out;
    ok = Calibri::split(out, std::string(";Some;;data;"), [](char symbol) noexcept { return symbol == ';'; });
    decltype(out) check { "Some", "data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::string(";Some;;data;"), ';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::string(";;Some;;;;data;;"), std::string(";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { "Some data" };
    ok = Calibri::split(out, std::string("Some data"), std::string(";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToWStringForwardList()
{
    bool ok {};

    std::forward_list<std::wstring> out;
    ok = Calibri::split(out, std::wstring(L";Some;;data;"), [](wchar symbol) noexcept { return symbol == L';'; });
    decltype(out) check { L"Some", L"data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::wstring(L";Some;;data;"), L';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::wstring(L";;Some;;;;data;;"), std::wstring(L";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { L"Some data" };
    ok = Calibri::split(out, std::wstring(L"Some data"), std::wstring(L";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToByteArrayForwardList()
{
    bool ok {};

    std::forward_list<Calibri::ByteArray> out;
    ok = Calibri::split(out, Calibri::ByteArray(";Some;;data;"), [](char symbol) noexcept { return symbol == ';'; });
    decltype(out) check { "Some", "data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, Calibri::ByteArray(";Some;;data;"), ';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, Calibri::ByteArray(";;Some;;;;data;;"), Calibri::ByteArray(";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { "Some data" };
    ok = Calibri::split(out, Calibri::ByteArray("Some data"), Calibri::ByteArray(";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToStringList()
{
    bool ok {};

    std::list<std::string> out;
    ok = Calibri::split(out, std::string(";Some;;data;"), [](char symbol) noexcept { return symbol == ';'; });
    decltype(out) check { "Some", "data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::string(";Some;;data;"), ';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::string(";;Some;;;;data;;"), std::string(";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { "Some data" };
    ok = Calibri::split(out, std::string("Some data"), std::string(";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToWStringList()
{
    bool ok {};

    std::list<std::wstring> out;
    ok = Calibri::split(out, std::wstring(L";Some;;data;"), [](wchar symbol) noexcept { return symbol == L';'; });
    decltype(out) check { L"Some", L"data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::wstring(L";Some;;data;"), L';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, std::wstring(L";;Some;;;;data;;"), std::wstring(L";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { L"Some data" };
    ok = Calibri::split(out, std::wstring(L"Some data"), std::wstring(L";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Split::testSplitToByteArrayList()
{
    bool ok {};

    std::list<Calibri::ByteArray> out;
    ok = Calibri::split(out, Calibri::ByteArray(";Some;;data;"), [](char symbol) noexcept { return symbol == ';'; });
    decltype(out) check { "Some", "data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, Calibri::ByteArray(";Some;;data;"), ';');
    QVERIFY(ok);
    QCOMPARE(out, check);

    ok = Calibri::split(out, Calibri::ByteArray(";;Some;;;;data;;"), Calibri::ByteArray(";;"));
    QVERIFY(ok);
    QCOMPARE(out, check);

    check = { "Some data" };
    ok = Calibri::split(out, Calibri::ByteArray("Some data"), Calibri::ByteArray(";"));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

QTEST_MAIN(tst_Split)

#include "tst_split.moc"
