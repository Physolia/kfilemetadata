/*
    SPDX-FileCopyrightText: 2014 Vishesh Handa <me@vhanda.in>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "popplerextractortest.h"
#include "simpleextractionresult.h"
#include "indexerextractortestsconfig.h"
#include "extractors/popplerextractor.h"
#include "mimeutils.h"

#include <QTest>
#include <QMimeDatabase>

using namespace KFileMetaData;

QString PopplerExtractorTest::testFilePath(const QString& fileName) const
{
    return QLatin1String(INDEXER_TESTS_SAMPLE_FILES_PATH) + QLatin1Char('/') + fileName;
}

void PopplerExtractorTest::testNoExtraction()
{
    PopplerExtractor plugin{this};

    QString fileName = testFilePath(QStringLiteral("test.pdf"));
    QMimeDatabase mimeDb;
    QString mimeType = MimeUtils::strictMimeType(fileName, mimeDb).name();
    QVERIFY(plugin.mimetypes().contains(mimeType));

    SimpleExtractionResult result(fileName, mimeType, ExtractionResult::ExtractNothing);
    plugin.extract(&result);

    QCOMPARE(result.types().size(), 1);
    QCOMPARE(result.types().constFirst(), Type::Document);
    QCOMPARE(result.properties().size(), 0);
}

void PopplerExtractorTest::test()
{
    PopplerExtractor plugin{this};

    QString fileName = testFilePath(QStringLiteral("test.pdf"));
    QMimeDatabase mimeDb;
    QString mimeType = MimeUtils::strictMimeType(fileName, mimeDb).name();
    QVERIFY(plugin.mimetypes().contains(mimeType));

    SimpleExtractionResult result(fileName, mimeType);
    plugin.extract(&result);

    QCOMPARE(result.types().size(), 1);
    QCOMPARE(result.types().constFirst(), Type::Document);

    QCOMPARE(result.text(), QStringLiteral("This is a sample PDF file for KFileMetaData. "));
    QCOMPARE(result.properties().value(Property::Author), QVariant(QStringLiteral("Happy Man")));
    QCOMPARE(result.properties().value(Property::Title), QVariant(QStringLiteral("The Big Brown Bear")));
    QCOMPARE(result.properties().value(Property::Subject), QVariant(QStringLiteral("PDF Metadata")));
    QCOMPARE(result.properties().value(Property::Generator), QVariant(QStringLiteral("LibreOffice 4.2")));
    QCOMPARE(result.properties().value(Property::PageCount), 1);
    QDateTime dt(QDate(2014, 07, 01), QTime(13, 38, 50));
    dt.setTimeSpec(Qt::UTC);
    QCOMPARE(result.properties().value(Property::CreationDate), QVariant(dt));

    QCOMPARE(result.properties().size(), 6);
}

void PopplerExtractorTest::testMetaDataOnly()
{
    PopplerExtractor plugin{this};

    SimpleExtractionResult result(testFilePath("test.pdf"), "application/pdf", ExtractionResult::ExtractMetaData);
    plugin.extract(&result);

    QCOMPARE(result.types().size(), 1);
    QVERIFY(result.text().isEmpty());
    QCOMPARE(result.properties().size(), 6);

}

QTEST_GUILESS_MAIN(PopplerExtractorTest)

#include "moc_popplerextractortest.cpp"
