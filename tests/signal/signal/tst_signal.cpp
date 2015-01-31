//! Qt includes
#include <QtTest/QtTest>

//! Calibri-Library includes
#include <signal/signal.hpp>

int func(int value) noexcept { return value * value; }

class tst_Signal : public QObject
{
    Q_OBJECT

private slots:
    void testConnect();
};

void tst_Signal::testConnect()
{
    Calibri::Signal<int (int)> signal;

    QVERIFY(signal.connect(::func));
    QVERIFY(signal.disconnect(::func));
    QVERIFY(!signal.disconnect(::func));

    QVERIFY(signal.connect(::func));
    QVERIFY(signal.connect(::func));
    QVERIFY(signal.disconnect(::func));
    QVERIFY(signal.disconnect(::func));
    QVERIFY(!signal.disconnect(::func));

    QVERIFY(signal.connect(::func));
    QVERIFY(!signal.connect<Calibri::SignalConnectionMode::UniqueConnection>(::func));
    QVERIFY(signal.disconnect(::func));
    QVERIFY(!signal.disconnect(::func));

    auto connection = signal.connect(::func);
    QVERIFY(connection);
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));

    connection = signal.connect(::func);
    QVERIFY(connection);
    QVERIFY(signal.connect(::func));
    QVERIFY(signal.disconnect(connection));
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(signal.disconnect(::func));
    QVERIFY(!signal.disconnect(::func));

    connection = signal.connect(::func);
    QVERIFY(connection);
    QVERIFY(signal.connect(::func));
    signal.disconnectAll();
    QVERIFY(!signal.disconnect(connection));
    QVERIFY(!signal.disconnect(::func));
}

QTEST_MAIN(tst_Signal)

#include "tst_signal.moc"
