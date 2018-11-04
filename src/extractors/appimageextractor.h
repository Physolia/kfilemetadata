/*
    Copyright (C) 2019  Friedrich W. H. Kossebau <kossebau@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef APPIMAGEEXTRACTOR_H
#define APPIMAGEEXTRACTOR_H

#include "extractorplugin.h"

namespace KFileMetaData
{

class AppImageExtractor : public ExtractorPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.kf5.kfilemetadata.ExtractorPlugin"
                      FILE "appimageextractor.json")
    Q_INTERFACES(KFileMetaData::ExtractorPlugin)

public:
    explicit AppImageExtractor(QObject* parent = nullptr);

public:
    void extract(ExtractionResult* result) override;
    QStringList mimetypes() const override;
};

}

#endif
