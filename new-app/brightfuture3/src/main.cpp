/***************************************************************************
 *   Copyright (C) 2014 by Cornelius Schumacher <schumacher@kde.org>                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 ***************************************************************************/

// application header
#include "brightfuture.h"
// KDE headers
#include <QApplication>
#include <QCommandLineParser>
#include <KAboutData>
#include <KLocalizedString>

int main(int argc, char **argv)
{
//@@snippet_begin(application)
    QApplication application(argc, argv);
//@@snippet_end

//@@snippet_begin(i18n)
    KLocalizedString::setApplicationDomain("brightfuture");
//@@snippet_end
//@@snippet_begin(about)
    KAboutData aboutData( QStringLiteral("brightfuture"),
            i18n("Simple App"),
            QStringLiteral("0.1"),
            i18n("A Simple Application written with KDE "
            "Frameworks"),
            KAboutLicense::GPL,
            i18n("(c) 2013-2014, "
            "Cornelius Schumacher <schumacher@kde.org>"));

    aboutData.addAuthor(i18n("Cornelius Schumacher"),
                    i18n("Author"),
                    QStringLiteral("schumacher@kde.org"));
    aboutData.setProgramIconName("brightfuture");
//@@snippet_end
//@@snippet_begin(commandline)
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    aboutData.setupCommandLine(&parser);
    parser.process(application);
    aboutData.processCommandLine(&parser);
//@@snippet_end

//@@snippet_begin(mainwindow)
    BrightFuture *appwindow = new BrightFuture;
    appwindow->show();
    return application.exec();
//@@snippet_end
}
