// Helper definitions for Qt types to use with nlohmann/json deserializer
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

#ifndef NLOHMANN_JSON_QT_HPP
#define NLOHMANN_JSON_QT_HPP

#include <nlohmann/json.hpp>

#include <QtCore/qdatetime.h>
#include <QtCore/qglobal.h>
#include <QtCore/qlist.h>
#include <QtCore/qstring.h>
#include <QtCore/qurl.h>
#include <QtCore/qvector.h>

#include <string>

QT_BEGIN_NAMESPACE

inline void from_json(const nlohmann::json &j, QString &string)
{
    string = QString::fromStdString(j.get<std::string>());
}

inline void from_json(const nlohmann::json &j, QDateTime &dateTime)
{
    dateTime = QDateTime::fromString(j.get<QString>(), Qt::ISODateWithMs);
}

inline void from_json(const nlohmann::json &j, QUrl &url)
{
    url.setUrl(j.get<QString>());
}

template<typename T>
inline void from_json(const nlohmann::json &j, QVector<T> &vector)
{
    for (const auto &item : j) {
        vector.push_back(item.get<T>());
    }
}

template<typename T>
inline void from_json(const nlohmann::json &j, QList<T> &list)
{
    for (const auto &item : j) {
        list.push_back(item.get<T>());
    }
}

QT_END_NAMESPACE

#endif
