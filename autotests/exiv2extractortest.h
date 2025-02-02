/*
    SPDX-FileCopyrightText: 2014 Vishesh Handa <me@vhanda.in>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef EXIV2EXTRACTORTEST_H
#define EXIV2EXTRACTORTEST_H

#include <QObject>

class Exiv2ExtractorTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testNoExtraction();
    void test();
    void testGPS();
    void testJpegJxlProperties();
    void testJpegJxlProperties_data();
    void testHeifProperties();
};

#endif // EXIV2EXTRACTORTEST_H
