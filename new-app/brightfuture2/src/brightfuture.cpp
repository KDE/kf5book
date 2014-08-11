/*
 Copyright (C) 2014 by Cornelius Schumacher <schumacher@kde.org>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License as
 published by the Free Software Foundation; either version 2 of
 the License or (at your option) version 3 or any later version
 accepted by the membership of KDE e.V. (or its successor approved
 by the membership of KDE e.V.), which shall act as a proxy 
 defined in Section 14 of version 3 of the license.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "brightfuture.h"

#include <kplotwidget.h>
#include <kplotobject.h>

BrightFuture::BrightFuture()
    : QMainWindow()
{
//@@snippet_begin(constructor)
    KPlotWidget *plot = new KPlotWidget(this);
    setCentralWidget(plot);

    plot->setLimits(-1, 11, -1, 40);

    KPlotObject *po = new KPlotObject(Qt::white, KPlotObject::Bars, 2);
    po->setBarBrush(QBrush(Qt::green, Qt::Dense4Pattern));

    float y = 1;
    for (float x = 1; x <= 10; x += 1) {
        po->addPoint(x, y);
        y *= 1.5;
    }

    plot->addPlotObject(po);

    plot->update();
//@@snippet_end
}

BrightFuture::~BrightFuture()
{
}

#include "brightfuture.moc"
