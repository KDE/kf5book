# KArchive

A fairly common issue with storing large amounts of data is archiving it in
a easy way from within your code. The KArchive framework provides a quick
and easy way to do this from within Qt apps.

While Qt5 provides the QZipWriter and QZipReader classes, these are limited
only to Zips. KArchive on the other hand supports a wider array of formats
such as p7zip, tar and ar archives, thus giving you the flexibility of
choosing a format to your liking.

## Show me the code

Here's a simple example of creating a zip with one file 'Frameworks' with
the contents 'KZip Test' using KZip :

```
KArchive zip("magic.zip");
zip.open(QIODevice::WriteOnly)
zip.writeFile("Frameworks", QByteArray("KZip Test"));
zip.close();
```

More files can be added by subsequent calls to writeFile(). You also add folders
to your zip by using the writeDir call as follows :

```
zip.writeDir("magicDir");
```

Full API docs can be found [here](http://api.kde.org/frameworks-api/frameworks5-apidocs/karchive/html/index.html)

## Advanced usecases


### Sending compressed data over networks
KArchive also supports reading and writing compressed data to devices such as
buffers or sockets via the KCompressionDevice class allowing developers to save
bandwidth while transmitting data over networks.

A quick example of this functionality can be summed up as :

```
Magic goes here
```