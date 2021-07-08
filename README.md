# nlohmann_json_qt
A collection of helper functions for Qt to use with nlohmann/json

Adds support for deserialization of the following Qt types from `basic_json`: 

* `QString`
* `QUrl`
* `QDateTime` with `Qt::ISODateWithMs`
* `QVector<T>`
* `QList<T>`
* `QVariantList`
* `QVariantMap`
* A limited subset of values stored in `QVariant`:
  * `QVariantList`
  * `QVariantMap`
  * `QString`
  * `double`
  * `bool`
  * `int`
  * `unsigned int`
  * All other values are converted to a `null` JSON value.

This is a header-only library. Add the header to your include paths or use CMake and link against `nlohmann_json_qt`.
