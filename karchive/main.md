# KArchive

When you are storing large amounts of data, how do you archive it in
a easy way from within your code? The KArchive framework provides a quick
and easy way to do this from within Qt apps.

While Qt5 provides the QZipWriter and QZipReader classes, these are limited
only to Zips. KArchive on the other hand supports a wide array of formats
such as p7zip, tar and ar archives, giving you the flexibility of
choosing the formats which fit your project.

## Show me the code

Here's a simple 'Hello World' example of KArchive.

//@@snippet(karchive/examples/helloworld/main.cpp, helloworld, cpp)

More files can be added by subsequent calls to writeFile(). You also add folders
to your zip by using the writeDir call as follows :

~~~ {#worldDirExample .cpp}
    archive.writeDir(QStringLiteral("world dir"));
~~~

Full API docs can be found [here](https://api.kde.org/frameworks/karchive/html/index.html)

## Advanced usecases

### Sending compressed data over networks
KArchive also supports reading and writing compressed data to devices such as
buffers or sockets via the KCompressionDevice class allowing developers to save
bandwidth while transmitting data over networks.

A quick example of the KCompressionDevice class can be summed up as:

//@@snippet(karchive/examples/bzip2gzip/main.cpp, kcompressiondevice_example, cpp)
