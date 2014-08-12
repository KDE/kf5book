# Introduction to KConfig

*This is based on the [KConfig tutorial on Techbase](https://techbase.kde.org/Development/Tutorials/KConfig)*

## Abstract

This tutorial looks at the KDE configuration data system, starting with an overview of the design fundamentals from an application developer's point of view. It then looks at the classes relevant to application development one by one.


## Design Essentials

KConfig is designed to abstract away the concept of actual storage and retrieval of configuration settings behind an API that allows easy fetching and setting of information. Where and in what format the data is stored is not relevant to an application using KConfig. This keeps all KDE applications consistent in their handling of configurations while alleviating each and every application author to build such a system on their own from scratch, which can be a highly error prone exercise.

A KConfig object represents a single configuration object. Each configuration object is referenced by its unique name and may be actually read from multiple local or remote files or services. Each application has a default configuration object associated with it and there is also a global configuration object.

These configuration objects are broken down into a two level hierarchy: groups and keys. A configuration object can have any number of groups and each group can have one or more keys with associated values.

Values stored may be of any number of data types. They are stored and retrieved as the objects themselves. For example, a `QColor` object is passed to a config object directly when storing a color value and when retrieved a `QColor` object is returned. Applications themselves therefore generally do not have to perform serialization and deserialization of objects themselves.


## The KConfig Class

The `KConfig` object is used to access a given configuration object. There are a number of ways to create a config object:

@@snippet(examples/all.cpp, creation, cpp)

The KConfig object create on line 3 is a regular config object. We can read values from it, write new entries and ask for various properties of the object.  This object will be loaded from the config resource as determined by `QStandardPaths`, meaning that every instance of the `myapprc` object in each of the directories in the config resource hierarchy will be merged to create the values seen in this object. This is how system wide and per-user/group profiles are generated and supported and it all happens transparently to the application itself.

The hierarchy of directories which is searched for configuration is defined by `$XDG_CONFIG_DIRS`, which is defined in the [XDG Base Directory Specification](http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html). Qt supports this specification in `QStandardPaths`.

On line 7 we open a specific local file, this case `/etc/kderc`. This performs no merging of values and expects an INI style file.

Line 10 sees the creation of a configuration object that is not merged with the user global configuration object, while the configuration file on line 13 is additionally not merged with any files in the `$XDG_CONFIG_DIRS` hierarchy. This can noticeably improve performance in the case where one is simply reading values out of a simple configuration for which global values are not meaningful.

### Special Configuration Objects

Each application has its own configuration object that uses the name provided to `KAboutData` appended with "rc" as its name. So an app named `myapp` would have the default configuration object of `myapprc` (located in `$XDG_CONFIG_HOME`, which is `~/.config` by default). This configuration file can be retrieved in this way:

@@snippet(examples/all.cpp, getconfig, cpp)

This actually uses `KSharedConfig`, which is a ref-counted shared `KConfig` object. More about that in a later section.

The default configuration object for the application is accessed when no name is specified when creating a `KConfig` object. So we could also do this instead - but it would be slower because it would have to parse the whole file again:

@@snippet(examples/all.cpp, getconfig2, cpp)

### Commonly Useful Methods

To save the current state of the configuration object we call the `sync()` method. This method is also called when the object is destroyed. If no changes have been made or the resource reports itself as non-writable (such as in the case of the user not having write permissions to the file) then no disk activity occurs. `sync()` merges changes performed concurrently by other processes - local changes have priority, though.

If we want to make sure that we have the latest values from disk we can call `reparseConfiguration()` which calls `sync()` and then reloads the data from disk.

If we need to prevent the config object from saving already made modifications to disk we need to call `markAsClean()`. A particular use case for this is rolling back the configuration to the on-disk state by calling `markAsClean()` followed by `reparseConfiguration()`.

Listing all groups in a configuration object is as simple as calling `groupList()` as in this code snippet:

@@snippet(examples/all.cpp, getgroups, cpp)


## KSharedConfig

The `KSharedConfig` class is a reference counted pointer to a `KConfig`. It thus provides a way to reference the same configuration object from multiple places in your application without the extra overhead of separate objects or concerns about synchronizing writes to disk even if the configuration object is updated from multiple code paths.

Accessing a `KSharedConfig` object is as easy as this:

@@snippet(examples/all.cpp, sharedconfig, cpp)

`openConfig()` take the same parameters as `KConfig`'s constructors do, allowing one to define which configuration file to open, flags to control merging and non-`config` resources.

`KSharedConfig` is generally recommended over using `KConfig` itself.


## KConfigGroup

Now that we have a configuration object, the next step is to actually use it. The first thing we must do is to define which group of key/value pairs we wish to access in the object. We do this by creating a KConfigGroup object:

@@snippet(examples/all.cpp, configgroup, cpp)

You can pass `KConfig` or `KSharedConfig` objects to `KConfigGroup`.

Config groups can be nested as well:

@@snippet(examples/all.cpp, nestedgroups, cpp)


## Reading Entries

With a `KConfigGroup` object in hand reading entries is now quite straight forward:

@@snippet(examples/all.cpp, reading, cpp)

As can be seen from the above, you can mix reads from different `KConfigGroup` objects created on the same `KConfig` object. The read methods take the key, which is case sensitive, as the first argument and the default value as the second argument. This argument controls what kind of data, e.g. a color in line 74 above, is to be expected as well as the type of object returned. The returned object is wrapped in a `QVariant` to make this magic happen.

If no such key currently exists in the configuration object, the default value is returned instead. If there is a localized (e.g. translated into another language) entry for the key that matches the current locale, that is returned.


## Writing Entries

Setting new values is similarly straightforward:

@@snippet(examples/all.cpp, writing, cpp)

Note the use of `writePathEntry` and how the type of object we use, such as `QColor` on line 86, dictates how the data is serialized. Additionally, once we are done writing entries, `sync()` must be called on the config object for it to be saved to disk. We can also simply wait for the object to be destroyed, which triggers an automatic `sync()` if necessary.


## KDesktopFile: A Special Case

When is a configuration file not a configuration file? When it is a [desktop file](http://freedesktop.org/wiki/Specifications/desktop-entry-spec). These files, which are essentially configuration files at their heart, are used to describe entries for application menus, mimetypes, plugins and various services.

When accessing a .desktop file, one should instead use the `KDesktopFile` class which, while a `KConfig` class offering all the capabilities described above, offers a set of methods designed to make accessing standard attributes of these files consistent and reliable.


## KConfig XT

There is a way to make certain use cases of KConfig easier, faster and more reliable: KConfig XT. In particular, for main application or plugin configuration objects and when syncing configuration dialogs and other interfaces with these values, KConfig XT can help immensely. It also  simultaneously documents the configuration options available, which makes every sys admin and system integrator that uses KDE that much more happy.

Read more about [Using KConfig XT](https://techbase.kde.org/Development/Tutorials/Using_KConfig_XT).
