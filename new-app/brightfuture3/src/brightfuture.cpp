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

#include <KPlotWidget>
#include <KPlotObject>
#include <KLocalizedString>

#include <QPushButton>
#include <QBoxLayout>

BrightFuture::BrightFuture()
    : QMainWindow()
{
//@@snippet_begin(constructor)
    QWidget *topWidget = new QWidget(this);
    setCentralWidget(topWidget);

    QBoxLayout *topLayout = new QVBoxLayout(topWidget);

    QBoxLayout *buttonLayout = new QHBoxLayout;
    topLayout->addLayout(buttonLayout);

    QPushButton *button;

    button = new QPushButton(i18n("Golden"));
    buttonLayout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(plotGoldenFuture()));

    button = new QPushButton(i18n("Pink"));
    buttonLayout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(plotPinkFuture()));

    button = new QPushButton(i18n("Green"));
    buttonLayout->addWidget(button);
    connect(button, SIGNAL(clicked()), SLOT(plotGreenFuture()));

    m_plot = new KPlotWidget(this);
    topLayout->addWidget(m_plot);

    m_plot->setLimits(-1, 11, -1, 40);

    m_plot_object = new KPlotObject(Qt::white, KPlotObject::Bars, 2);

    float y = 1;
    for (float x = 1; x <= 10; x += 1) {
        m_plot_object->addPoint(x, y);
        y *= 1.5;
    }

    m_plot->addPlotObject(m_plot_object);

    plotGreenFuture();
//@@snippet_end
}

BrightFuture::~BrightFuture()
{
}

void BrightFuture::plotGreenFuture()
{
    m_plot_object->setBarBrush(QBrush(Qt::green, Qt::Dense4Pattern));
    m_plot->update();
}

void BrightFuture::plotGoldenFuture()
{
    m_plot_object->setBarBrush(QBrush(QColor("gold"), Qt::Dense4Pattern));
    m_plot->update();
}

void BrightFuture::plotPinkFuture()
{
    m_plot_object->setBarBrush(QBrush(QColor("pink"), Qt::SolidPattern));
    m_plot->update();
}

#include "brightfuture.moc"
