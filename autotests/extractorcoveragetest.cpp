/*
 * This file is part of the KDE KFileMetaData project
 * Copyright (C) 2014  Vishesh Handa <me@vhanda.in>
 *               2017  Igor Poboiko <igor.poboiko@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <QObject>
#include <QTest>
#include <QDirIterator>
#include <QMimeDatabase>

#include "mimeutils.h"

#include "indexerextractortestsconfig.h"

namespace KFileMetaData {

class ExtractorCoverageTest : public QObject
{
    Q_OBJECT

private:
    static QString filePath() {
        return QLatin1String(INDEXER_TESTS_SAMPLE_FILES_PATH);
    }

    QStringList m_testFiles;
    QMap<QString, QString> m_knownFiles;

private Q_SLOTS:

    void initTestCase() {
        // Expected mimetypes
        m_knownFiles = {
            { "test.aif",                      "audio/x-aifc"},
            { "test.ape",                      "audio/x-ape"},
            { "test.AppImage",                 "application/vnd.appimage"},
            { "test_apple_systemprofiler.spx", "application/xml"},
            { "test.dot",                      "text/vnd.graphviz"},
            { "test.eps",                      "image/x-eps"},
            { "test.epub",                     "application/epub+zip"},
            { "test.flac",                     "audio/flac"},
            { "test.jpg",                      "image/jpeg"},
            { "test_libreoffice.docx",         "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
            { "test.m4a",                      "audio/mp4"},
            { "test_missing_content.odt",      "application/vnd.oasis.opendocument.text"},
            { "test_missing_meta.odt",         "application/vnd.oasis.opendocument.text"},
            { "test.mkv",                      "video/x-matroska"},
            { "test.mp3",                      "audio/mpeg"},
            { "test.mpc",                      "audio/x-musepack"},
            { "test_no_gps.jpg",               "image/jpeg"},
            { "test.odp",                      "application/vnd.oasis.opendocument.presentation"},
            { "test.odt",                      "application/vnd.oasis.opendocument.text"},
            { "test.ogg",                      "audio/x-vorbis+ogg"},
            { "test.mml",                      "application/mathml+xml"},
            { "test_multivalue.ogg",           "audio/x-vorbis+ogg"},
            { "test.ogv",                      "video/x-theora+ogg"},
            { "test.opus",                     "audio/x-opus+ogg"},
            { "test.pdf",                      "application/pdf"},
            { "test.pl",                       "application/x-perl"},
            { "test.ps",                       "application/postscript"},
            { "test_public_key.gpg",           "application/pgp-encrypted"},
            { "test.spx",                      "audio/x-speex+ogg"},
            { "test.ts",                       "video/mp2t"},
            { "test.wav",                      "audio/x-wav"},
            { "test.webm",                     "video/webm"},
            { "test_with_container.svg",       "image/svg+xml"},
            { "test_with_metadata.svg",        "image/svg+xml"},
            { "test.wma",                      "audio/x-ms-wma"},
            { "test.wv",                       "audio/x-wavpack"},
            { "test_zero_gps.jpg",             "image/jpeg"},
            { "test.mobi",                     "application/x-mobipocket-ebook"},
        };

        // Collect all test files from the samplefiles directory
        QDirIterator it(filePath(), {QStringLiteral("test*")}, QDir::Files);
        while (it.hasNext()) {
            it.next();
            m_testFiles.append(it.fileName());
        }
    }

    void testMimetype_data()
    {
        /*
         * Check if we get the correct mimetype for
         * each available test sample
         */
        QTest::addColumn<QString>("fileName");
        QTest::addColumn<QString>("mimeType");

        auto it = m_knownFiles.cbegin();
        while (it != m_knownFiles.cend()) {
            QTest::addRow("%s", it.key().toUtf8().constData())
                << it.key() << it.value();
            ++it;
        }
    }

    void testMimetype()
    {
        QFETCH(QString, fileName);
        QFETCH(QString, mimeType);
        QString url = filePath() + QChar('/') + fileName;

        QMimeDatabase db;
        auto fileMime = MimeUtils::strictMimeType(url, db);

        QVERIFY(fileMime.isValid());
        QCOMPARE(fileMime.name(), mimeType);
    }

    void testFileCoverage_data()
    {
        /*
         * Check if we get the correct mimetype for
         * each available test sample
         */
        QTest::addColumn<QString>("fileName");

        auto it = m_testFiles.cbegin();
        while (it != m_testFiles.cend()) {
            QTest::addRow("%s", it->toUtf8().constData()) << (*it);
            ++it;
        }
    }

    void testFileCoverage()
    {
        QFETCH(QString, fileName);

        QVERIFY2(m_knownFiles.contains(fileName), "test file omitted from test suite");
    }

};

}

QTEST_GUILESS_MAIN(KFileMetaData::ExtractorCoverageTest)

#include "extractorcoveragetest.moc"
