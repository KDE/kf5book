# Reaching a wider audience

A excellent way of reaching a wider audience with your software is by localizing it.
The KDE community provides the ki18n framework to do this by leveraging gettext underneath.
While Qt provides tr, ki18n is much much more powerful than tr, and offers writing 3 broad
categories of writing messages: General Messages, Specialized Messages, Placeholder Substitution,
while also providing functionality to include user interface markers to provide
better context to translators.

## Writing Messages

Most messages can be internationalized with simple `i18n*` calls,
which are described in the "General Messages" section.
A few messages may require treatment with `ki18n*` calls,
and when this is needed is described in the "Special Messages" section.
Argument substitution in messages is performed using the familiar
Qt syntax `%<number>`, but there may be some differences.

### General Messages

General messages are wrapped with `i18n*` calls.
These calls are *immediate*, which means that they return
the final localized text (including substituted arguments)
as a `QString` object, that can be passed to UI widgets.

The most frequent message type, a simple text without any arguments,
is handled like this:

~~~
QString msg = i18n("Just plain info.");
~~~

The message text may contain arbitrary Unicode characters,
and the source file *must* be UTF-8 encoded.
Ki18n supports no other character encoding.

If there are some arguments to be substituted into the message,
`%<number>` placeholders are put into the text at desired positions,
and arguments are listed after the string:

~~~
QString msg = i18n("%1 has scored %2", playerName, score);
~~~

Arguments can be of any type for which there exists an overloaded
`KLocalizedString::subs` method.
Up to 9 arguments can be inserted in this fashion, due to the fact that
`i18n` calls are realized as overloaded templates.
If more than 9 arguments are needed, which is extremely rare,
a `ki18n*` call must be used.

Sometimes a short message in English is ambiguous to translators,
possibly leading to a wrong translations.
Ambiguity can be resolved by providing a context string along the text,
using the `i18nc` call. In it, the first argument is the context,
which only the translator will see, and the second argument is the text
which the user will see:

~~~
QString msg = i18nc("player name - score", "%1 - %2", playerName, score);
~~~

In messages stating how many of some kind of objects there are,
where the number of objects is inserted at run time, it is necessary
to differentiate between *plural forms* of the text.
In English there are only two forms, one for number 1 (singular) and
another form for any other number (plural).
In other languages this might be more complicated (more than two forms),
or it might be simpler (same form for all numbers).
This is handled properly by using the `i18np` plural call:

~~~
QString msg = i18np("%1 image in album %2", "%1 images in album %2",
                    numImages, albumName);
~~~

The plural form is decided by the first integer-valued argument,
which is `numImages` in this example. In rare cases when there are
two or more integer arguments, they should be ordered carefully.
It is also allowed to omit the plural-deciding placeholder, for example:

~~~
QString msg = i18np("One image in album %2", "%1 images in album %2",
                    numImages, albumName);
~~~

or even:

~~~
QString msg = i18np("One image in album %2", "More images in album %2",
                    numImages, albumName);
~~~

If the code context is such that the number is always greater than 1,
the plural call must be used nevertheless.
This is because in some languages there are different plural forms
for different classes of numbers; in particular, the singular form
may be used for numbers other than 1 (e.g. those ending in 1).

If a message needs both context and plural forms, this is provided by
`i18ncp` call:

~~~
QString msg = i18ncp("file on a person", "1 file", "%1 files", numFiles);
~~~


In the basic `i18n` call (no context, no plural) it is not allowed
to put a literal string as the first argument for substitution.
In debug mode this will even trigger a static assertion,
resulting in compilation error. This serves to prevent misnamed calls:
context or plural frequently needs to be added at a later point to
a basic call, and at that moment the programmer may forget to update
the call name from `i18n` to `i18nc/p`.

Furthermore, an empty string should never be wrapped with
a basic `i18n` call (no `i18n("")`),
because in translation catalog the message with empty text
has a special meaning, and is not intended for client use.
The behavior of `i18n("")` is undefined,
and there will be some warnings in debug mode.

### Specialized Messages

There are some situations where `i18n*` calls are not sufficient,
or are not convenient enough.
One obvious case is if more than 9 arguments need to be substituted.
Another case is if it would be easier to substitute arguments later on,
after the line with the i18n call.
For cases such as these, `ki18n*` calls can be used.
These calls are *deferred*, which means that they do not return
the final translated text as `QString`, but instead return
a `KLocalizedString` instance which needs further treatment.
Arguments are then substituted one by one using
`KLocalizedString::subs` methods, and after all arguments
have been substituted, the translation is finalized by one of
`KLocalizedString::toString` methods (which return `QString`).
For example:

~~~
KLocalizedString ks;
case (reportSource) {
    SRC_ENG: ks = ki18n("Engineering reports: %1"); break;
    SRC_HEL: ks = ki18n("Helm reports: %1"); break;
    SRC_SON: ks = ki18n("Sonar reports: %1"); break;
    default: ks = ki18n("General report: %1");
}
QString msg = ks.subs(reportText).toString();
~~~


`subs` methods do not update the `KLhttps://api.kde.org/frameworks/ki18n/html/prg_guide.htmocalizedString` instance on which
they are invoked, but return a copy of it with one argument slot filled.
This allows to use `KLocalizedString` instances as a templates
for constructing final texts, by supplying different arguments.

Another use for deferred calls is when special formatting of arguments
is needed, like requesting the field width or number of decimals.
`subs` methods can take these formatting parameters.
In particular, arguments should not be formatted in a custom way,
because `subs` methods will also take care of proper localization
(e.g. use either dot or comma as decimal separator in numbers, etc):

~~~
// BAD (number not localized):
QString msg = i18n("Rounds: %1", myNumberFormat(n, 8));
// Good:
QString msg = ki18n("Rounds: %1").subs(n, 8).toString();
~~~


Like with `i18n`, there are context, plural, and context-plural
variants of `ki18n:`

~~~
ki18nc("No function", "None").toString();
ki18np("File found", "%1 files found").subs(n).toString();
ki18ncp("Personal file", "One file", "%1 files").subs(n).toString();
~~~


`toString` methods can be used to override the global locale.
To override only the language of the locale, `toString` can take
a list of languages for which to look up translations
(ordered by decreasing priority):

~~~
QStringList myLanguages;
...
QString msg = ki18n("Welcome").toString(myLanguages);
~~~

[This](https://api.kde.org/frameworks/ki18n/html/prg_guide.html#link_cat)
section describes how to specify
the translation *domain*, a canonical name for the catalog file
from which `*i18n*` calls will draw translations.
But `toString` can always be used to override the domain for a given call,
by supplying a specific domain:

~~~
QString trName = ki18n("Georgia").toString("country-names");
~~~

Relevant here is the set of `ki18nd*` calls
(`ki18nd`, `ki18ndc`, `ki18ndp`, `ki18ndcp`),
which can be used for the same purpose,
but which are not intended to be used directly.
Please refer to [this](http://api.kde.org/frameworks-api/frameworks5-apidocs/ki18n/html/prg_guide.html#link_cat)
page to check when these calls should be made.

#### Dynamic Contexts

Translators are provided with the capability to script translations,
such that the text changes based on arguments supplied at run time.
For the most part, this feature is transparent to the programmer.
However, sometimes the programmer may help in this by providing
a *dynamic* context to the message, through
`KLocalizedString::inContext` methods.
Unlike the static context, the dynamic context changes at run time;
translators have the means to fetch it and use it to script
the translation properly. An example:

~~~
KLocalizedString ks = ki18nc("%1 is user name; may have "
                             "dynamic context gender=[male,female]",
                             "%1 went offline");
if (knownUsers.contains(user) && !knownUsers[user].gender.isEmpty()) {
    ks = ks.inContext("gender", knownUsers[user].gender);
}
QString msg = ks.subs(user).toString();
~~~

Any number of dynamic contexts, with different keys, can be added like this.
Normally every message with a dynamic context should also have
a static context, like in the previous example, informing the translator
of the available dynamic context keys and possible values.
Like `subs` methods, `inContext` does not modify the parent instance,
but returns a copy of it.

<a name="subs_notes">

### Placeholder Substitution

Hopefully, most of the time `%<number>` placeholders are substituted
in the way one would intuitively expect them to be.
Nevertheless, some details about substitution are as follows.

Placeholders are substituted in one pass, so there is no need
to worry about what will happen if one of the substituted arguments
contains a placeholder, and another argument is substituted after it.

All same-numbered placeholders are substituted with the same argument.

Placeholders directly index arguments: they should be numbered from 1
upwards, without gaps in the sequence, until each argument is indexed.
Otherwise, error marks will be inserted into message at run time
(when the code is compiled in debug mode), and any invalid placeholder
will be left unsubstituted.
The exception is the plural-deciding argument in plural calls,
where it is allowed to drop its placeholder,
in either the singular or the plural text.

If none of the arguments supplied to a plural call is integer-valued,
 an error mark will be inserted into the message at run time
 (when compiled in debug mode).

Integer arguments will be by default formatted as if they denote
an amount, according to locale rules (thousands separation, etc.)
But sometimes an integer is a numerical identifier (e.g. port number),
and then it should be manually converted into `QString` beforehand
to avoid treatment as amount:

~~~
i18n("Listening on port %1.", QString::number(port));
~~~

#### User Interface Markers

In the same way there exists a HIG (Human Interface Guidelines) document
for the programmers to follow, translators should establish HIG-like
convention for their language concerning the forms of UI text.
Therefore, for a proper translation, the translator will need too know
not only what does the message mean, but also where it figures in the UI.
E.g. is the message a button label, a menu title, a tooltip, etc.

To this end a convention has been developed among KDE translators,
which programmers can use to succinctly describe UI usage of messages.
In this convention, the context string starts with an *UI marker*
of the form `@<major>:<minor>`, and may be followed by any other
usual context information, separated with a single space:

~~~
i18nc("@action:inmenu create new file", "New");
~~~


The major and minor component of the UI marker are not arbitrary,
but are drawn from a table which can be found [here](https://api.kde.org/frameworks/ki18n/html/prg_guide.html#good_ctxt).

For much more detail, see https://api.kde.org/frameworks/ki18n/html/prg_guide.html
