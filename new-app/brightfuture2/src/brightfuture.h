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

#include "ui_brightfuture.h"

//@@snippet_begin(BrightFuture)
/**
 * This class serves as the main window for BrightFuture.  It handles the
 * menus, toolbars and status bars.
 *
 * @short Main window class
 * @author Your Name <mail@example.com>
 * @version 0.1
 */
class BrightFuture : public QMainWindow
{
    Q_OBJECT
public:
    /**
     * Default Constructor
     */
    BrightFuture();

    /**
     * Default Destructor
     */
    virtual ~BrightFuture();
};
//@@snippet_end

#endif // _BRIGHTFUTURE_H_
