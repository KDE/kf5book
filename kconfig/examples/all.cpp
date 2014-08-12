//@@snippet_begin(creation)
// a plain old read/write config object
KConfig config("myapprc");

// a specific file in the filesystem
// currently must be an INI style file
KConfig fullPath("/etc/kderc");

// not merged with global values
KConfig globalFree( "localsrc", KConfig::NoGlobals );

// not merged with globals or the $KDEDIRS hierarchy
KConfig simpleConfig( "simplerc", KConfig::SimpleConfig );
//@@snippet_end


//@@snippet_begin(getconfig)
#include <KSharedConfig>

MyClass::MyClass()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
}
//@@snippet_end


//@@snippet_begin(getconfig2)
#include <KConfig>

MyClass::MyClass()
{
    KConfig config;
}
//@@snippet_end


//@@snippet_begin(getgroups)
KSharedConfig::Ptr config = KSharedConfig::openConfig();

foreach ( const QString& group, config->groupList() ) {
    qDebug() << "next group:" << group;
}
//@@snippet_end


//@@snippet_begin(sharedconfig)
KSharedConfig::Ptr config = KSharedConfig::openConfig("ksomefilerc");
//@@snippet_end


//@@snippet_begin(configgroup)
KConfig config;
KConfigGroup generalGroup( &config, "General" );
KConfigGroup colorsGroup = config.group( "Colors" ); // ... or a bit differently ...
//@@snippet_end


//@@snippet_begin(nestedgroups)
KConfigGroup subGroup1( &generalGroup, "LessGeneral" );
KConfigGroup subGroup2 = colorsGroup.group( "Dialogs" );
//@@snippet_end


//@@snippet_begin(reading)
QString accountName = generalGroup.readEntry( "Account",
                                              QString() );
QColor color = colorsGroup.readEntry( "background",
                                      Qt::white );
QStringList list = generalGroup.readEntry( "List",
                                           QStringList() );
QString path = generalGroup.readPathEntry( "SaveTo",
                                           defaultPath );
//@@snippet_end


//@@snippet_begin(writing)
generalGroup.writeEntry( "Account", accountName );
generalGroup.writePathEntry( "SaveTo", savePath );
colorGroup.writeEntry( "background", color );
generalGroup.config()->sync();
//@@snippet_end
