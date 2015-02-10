//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <algorithms/join.hpp>

class tst_Join : public QObject
{
    Q_OBJECT

private slots:
    void testJoinVectorToString();
    void testJoinVectorToWString();
    void testJoinVectorToByteArray();
    void testJoinDequeToString();
    void testJoinDequeToWString();
    void testJoinDequeToByteArray();
    void testJoinForwardListToString();
    void testJoinForwardListToWString();
    void testJoinForwardListToByteArray();
    void testJoinListToString();
    void testJoinListToWString();
    void testJoinListToByteArray();
};

void tst_Join::testJoinVectorToString()
{
    bool ok {};

    std::vector<std::string> in { std::string("Some"), std::string("dummy"), std::string("data") };
    std::string out {};
    ok = Calibri::join(out, in, std::string(" "), [](const std::string &data) noexcept { return data != std::string("dummy"); });
    decltype(out) check { "Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { std::string("Some"), std::string("data") };
    ok = Calibri::join(out, in, std::string(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, std::string(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinVectorToWString()
{
    bool ok {};

    std::vector<std::wstring> in { std::wstring(L"Some"), std::wstring(L"dummy"), std::wstring(L"data") };
    std::wstring out {};
    ok = Calibri::join(out, in, std::wstring(L" "), [](const std::wstring &data) noexcept { return data != std::wstring(L"dummy"); });
    decltype(out) check { L"Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { std::wstring(L"Some"), std::wstring(L"data") };
    ok = Calibri::join(out, in, std::wstring(L" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, std::wstring(L" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinVectorToByteArray()
{
    bool ok {};

    std::vector<Calibri::ByteArray> in { Calibri::ByteArray("Some"), Calibri::ByteArray("dummy"), Calibri::ByteArray("data") };
    Calibri::ByteArray out {};
    ok = Calibri::join(out, in, Calibri::ByteArray(" "), [](const Calibri::ByteArray &data) noexcept { return data != Calibri::ByteArray("dummy"); });
    decltype(out) check { "Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { "Some", "data" };
    ok = Calibri::join(out, in, Calibri::ByteArray(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, Calibri::ByteArray(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinDequeToString()
{
    bool ok {};

    std::deque<std::string> in { std::string("Some"), std::string("dummy"), std::string("data") };
    std::string out {};
    ok = Calibri::join(out, in, std::string(" "), [](const std::string &data) noexcept { return data != std::string("dummy"); });
    decltype(out) check { "Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { std::string("Some"), std::string("data") };
    ok = Calibri::join(out, in, std::string(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, std::string(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinDequeToWString()
{
    bool ok {};

    std::deque<std::wstring> in { std::wstring(L"Some"), std::wstring(L"dummy"), std::wstring(L"data") };
    std::wstring out {};
    ok = Calibri::join(out, in, std::wstring(L" "), [](const std::wstring &data) noexcept { return data != std::wstring(L"dummy"); });
    decltype(out) check { L"Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { std::wstring(L"Some"), std::wstring(L"data") };
    ok = Calibri::join(out, in, std::wstring(L" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, std::wstring(L" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinDequeToByteArray()
{
    bool ok {};

    std::deque<Calibri::ByteArray> in { Calibri::ByteArray("Some"), Calibri::ByteArray("dummy"), Calibri::ByteArray("data") };
    Calibri::ByteArray out {};
    ok = Calibri::join(out, in, Calibri::ByteArray(" "), [](const Calibri::ByteArray &data) noexcept { return data != Calibri::ByteArray("dummy"); });
    decltype(out) check { "Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { "Some", "data" };
    ok = Calibri::join(out, in, Calibri::ByteArray(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, Calibri::ByteArray(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinForwardListToString()
{
    bool ok {};

    std::forward_list<std::string> in { std::string("Some"), std::string("dummy"), std::string("data") };
    std::string out {};
    ok = Calibri::join(out, in, std::string(" "), [](const std::string &data) noexcept { return data != std::string("dummy"); });
    decltype(out) check { "Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { std::string("Some"), std::string("data") };
    ok = Calibri::join(out, in, std::string(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, std::string(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinForwardListToWString()
{
    bool ok {};

    std::forward_list<std::wstring> in { std::wstring(L"Some"), std::wstring(L"dummy"), std::wstring(L"data") };
    std::wstring out {};
    ok = Calibri::join(out, in, std::wstring(L" "), [](const std::wstring &data) noexcept { return data != std::wstring(L"dummy"); });
    decltype(out) check { L"Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { std::wstring(L"Some"), std::wstring(L"data") };
    ok = Calibri::join(out, in, std::wstring(L" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, std::wstring(L" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinForwardListToByteArray()
{
    bool ok {};

    std::forward_list<Calibri::ByteArray> in { Calibri::ByteArray("Some"), Calibri::ByteArray("dummy"), Calibri::ByteArray("data") };
    Calibri::ByteArray out {};
    ok = Calibri::join(out, in, Calibri::ByteArray(" "), [](const Calibri::ByteArray &data) noexcept { return data != Calibri::ByteArray("dummy"); });
    decltype(out) check { "Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { "Some", "data" };
    ok = Calibri::join(out, in, Calibri::ByteArray(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, Calibri::ByteArray(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinListToString()
{
    bool ok {};

    std::list<std::string> in { std::string("Some"), std::string("dummy"), std::string("data") };
    std::string out {};
    ok = Calibri::join(out, in, std::string(" "), [](const std::string &data) noexcept { return data != std::string("dummy"); });
    decltype(out) check { "Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { std::string("Some"), std::string("data") };
    ok = Calibri::join(out, in, std::string(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, std::string(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinListToWString()
{
    bool ok {};

    std::list<std::wstring> in { std::wstring(L"Some"), std::wstring(L"dummy"), std::wstring(L"data") };
    std::wstring out {};
    ok = Calibri::join(out, in, std::wstring(L" "), [](const std::wstring &data) noexcept { return data != std::wstring(L"dummy"); });
    decltype(out) check { L"Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { std::wstring(L"Some"), std::wstring(L"data") };
    ok = Calibri::join(out, in, std::wstring(L" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, std::wstring(L" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

void tst_Join::testJoinListToByteArray()
{
    bool ok {};

    std::list<Calibri::ByteArray> in { Calibri::ByteArray("Some"), Calibri::ByteArray("dummy"), Calibri::ByteArray("data") };
    Calibri::ByteArray out {};
    ok = Calibri::join(out, in, Calibri::ByteArray(" "), [](const Calibri::ByteArray &data) noexcept { return data != Calibri::ByteArray("dummy"); });
    decltype(out) check { "Some data" };
    QVERIFY(ok);
    QCOMPARE(out, check);

    in = { "Some", "data" };
    ok = Calibri::join(out, in, Calibri::ByteArray(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);

    in.clear();
    check.clear();
    ok = Calibri::join(out, in, Calibri::ByteArray(" "));
    QVERIFY(ok);
    QCOMPARE(out, check);
}

QTEST_MAIN(tst_Join)

#include "tst_join.moc"
