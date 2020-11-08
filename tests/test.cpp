// Copyright (C) 2020 Dmitriy Purgin <dpurgin@gmail.com>
//
// Licensed under the MIT license. See LICENSE for details.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <QTest>

#include <QDateTime>
#include <QTimeZone>

#include <nlohmann/json-qt.hpp>
#include <nlohmann/json.hpp>

class NlohmannJsonQtTest : public QObject
{
    Q_OBJECT

    template<typename T>
    void run()
    {
        QFETCH(QByteArray, input);
        QFETCH(T, expected);

        auto json = nlohmann::json::parse(input.constBegin(), input.constEnd());
        QCOMPARE(json.get<T>(), expected);
    }

private slots:
    void testBasicJsonToQString_data();
    void testBasicJsonToQString();

    void testBasicJsonToQDateTime_data();
    void testBasicJsonToQDateTime();

    void testBasicJsonToQUrl_data();
    void testBasicJsonToQUrl();

    void testBasicJsonToQVectorInt();

    void testBasicJsonToQStringList();
};

void NlohmannJsonQtTest::testBasicJsonToQString_data()
{
    QTest::addColumn<QByteArray>("input");
    QTest::addColumn<QString>("expected");

    QTest::addRow("Empty") << QByteArray{R"("")"} << QString{};
    QTest::addRow("Latin1") << QByteArray{R"("foo")"} << QString{"foo"};
    QTest::addRow("Unicode") << QByteArray{R"("\u00e4\u00fc\u0436\u0448")"} << QString{"äüжш"};
}

void NlohmannJsonQtTest::testBasicJsonToQString()
{
    run<QString>();
}

void NlohmannJsonQtTest::testBasicJsonToQDateTime_data()
{
    QTest::addColumn<QByteArray>("input");
    QTest::addColumn<QDateTime>("expected");

    QTest::addRow("ISO 8601 with timezone")
        << QByteArray{R"("2020-11-08T14:31:05+01:00")"}
        << QDateTime{{2020, 11, 8}, {14, 31, 5}, QTimeZone{3600}};
}

void NlohmannJsonQtTest::testBasicJsonToQDateTime()
{
    run<QDateTime>();
}

void NlohmannJsonQtTest::testBasicJsonToQUrl_data()
{
    QTest::addColumn<QByteArray>("input");
    QTest::addColumn<QUrl>("expected");

    QTest::addRow("Example") << QByteArray{R"("https://example.com/example")"}
                             << QUrl{"https://example.com/example"};
}

void NlohmannJsonQtTest::testBasicJsonToQUrl()
{
    run<QUrl>();
}

void NlohmannJsonQtTest::testBasicJsonToQVectorInt()
{
    auto json = R"([-1, 0, 1, 12312, -140])"_json;
    QCOMPARE(json.get<QVector<int>>(), QVector<int>({-1, 0, 1, 12312, -140}));
}

void NlohmannJsonQtTest::testBasicJsonToQStringList()
{
    auto json = R"(["foo", "bar", "", "342"])"_json;
    QCOMPARE(json.get<QStringList>(),
             QStringList{} << "foo"
                           << "bar"
                           << ""
                           << "342");
}

QTEST_APPLESS_MAIN(NlohmannJsonQtTest)

#include "test.moc"
