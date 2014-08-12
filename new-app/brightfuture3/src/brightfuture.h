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
#ifndef BRIGHTFUTURE_H
#define BRIGHTFUTURE_H

#include <QMainWindow>

class KPlotWidget;
class KPlotObject;

//@@snippet_begin(BrightFuture)
/**
  This class serves as the main window for BrightFuture.

  @short Main window class
  @author Cornelius Schumacher <schumacher@kde.org>
  @version 0.1
*/
class BrightFuture : public QMainWindow
{
    Q_OBJECT
public:
    BrightFuture();
    virtual ~BrightFuture();

public slots:
    void plotGreenFuture();
    void plotGoldenFuture();
    void plotPinkFuture();

protected:
    void plotFuture();

private:
    KPlotWidget *m_plot;
    KPlotObject *m_plot_object;
};
//@@snippet_end

#endif
