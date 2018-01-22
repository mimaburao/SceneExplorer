

#include "extension.h"

QReadWriteLock Extension::sLock_;
bool Extension::bOrderAllow_;

QSet<QString> Extension::sExtsAllowCache_;
QStringList Extension::sExtsAllow_;
bool Extension::bAllAllow_;
bool Extension::bNoExtAllow_;

QSet<QString> Extension::sExtsDenyCache_;
QStringList Extension::sExtsDeny_;
bool Extension::bAllDeny_;
bool Extension::bNoExtDeny_;


QStringList Extension::GetDefaultAllow()
{
    static QStringList sqExts = {
        ".3g2",
        ".3gp",
        ".amv",
        ".asf",
        ".avi",
        ".avs",
        ".divx",
        ".drc",
        ".f4a",
        ".f4b",
        ".f4p",
        ".f4v",
        ".flv",
        ".m2v",
        ".m4p",
        ".m4v",
        ".mkv",
        ".mng",
        ".mov",
        ".mp2",
        ".mp4",
        ".mpe",
        ".mpeg",
        ".mpg",
        ".mpv",
        ".mxf",
        ".nsv",
        ".ogg",
        ".ogm",
        ".ogv",
        ".qt",
        ".rm",
        ".rmvb",
        ".roq",
        ".svi",
        ".swf",
        ".vob",
        ".webm",
        ".wmv",
        ".yuv",
    };

    return sqExts;
}
QStringList Extension::GetDefaultDeny()
{
    return QStringList();
}

QString StringListToString(const QStringList& ar)
{
    QString ret;
    for(const QString& t : ar)
    {
        ret.append(t);
        ret.append("\n");
    }
    return ret.trimmed();
}


QString Extension::GetDefaultAllowAsString()
{
    return StringListToString(GetDefaultAllow());
}
QString Extension::GetDefaultDenyAsString()
{
    return StringListToString(GetDefaultDeny());
}


QStringList Extension::GetMovieExtensionAllow()
{
    QReadLocker locker(&sLock_);
    return sExtsAllow_;
}
QStringList Extension::GetMovieExtensionDeny()
{
    QReadLocker locker(&sLock_);
    return sExtsDeny_;
}


QString Extension::GetMovieExtensionAllowAsString()
{
    return StringListToString(GetMovieExtensionAllow());
}
QString Extension::GetMovieExtensionDenyAsString()
{
    return StringListToString(GetMovieExtensionDeny());
}
void Extension::SetMovieExtensionAllow(const QStringList& exts)
{
    QWriteLocker locker(&sLock_);

    sExtsAllow_ = exts;
    sExtsAllowCache_.clear();
    bAllAllow_ = bNoExtAllow_ = false;
    foreach(const QString& ext, exts)
    {
        if(ext=="*")
        {
            bAllAllow_ = true;
            continue;
        }
        if(ext=="noext")
        {
            bNoExtAllow_= true;
            continue;
        }
        sExtsAllowCache_.insert(ext);
    }
}
void Extension::SetMovieExtensionDeny(const QStringList& exts)
{
    QWriteLocker locker(&sLock_);

    sExtsDeny_ = exts;
    sExtsDenyCache_.clear();
    bAllDeny_ = bNoExtDeny_ = false;
    foreach(const QString& ext, exts)
    {
        if(ext=="*")
        {
            bAllDeny_ = true;
            continue;
        }
        if(ext=="noext")
        {
            bNoExtDeny_ = true;
            continue;
        }
        sExtsDenyCache_.insert(ext);
    }
}

QString GetExtension(const QString& file)
{
    int li = file.lastIndexOf('.');
    if (li < 0)
        return QString();

    QString ext = file.right(file.length() - li);
    if(ext.contains('/') || ext.contains('\\'))
        return QString();

    ext = ext.toLower();
    return ext;
}
bool Extension::IsMovieExtension(const QString& file)
{
    QReadLocker locker(&sLock_);


    if(IsOrderAllow())
    {
        if(bAllAllow_)
            return true;
        QString ext=GetExtension(file);
        if(ext.isEmpty())
        {
            if(bNoExtAllow_)
                return true;
            return false;
        }
        return sExtsAllowCache_.contains(ext);
    }
    else
    {
        if(bAllDeny_)
            return false;
        QString ext=GetExtension(file);
        if(ext.isEmpty())
        {
            if(bNoExtDeny_)
                return false;
            return true;
        }
        return !sExtsAllowCache_.contains(ext);
    }
    Q_ASSERT(false);
    return false;
}

bool Extension::IsOrderAllow()
{
    return bOrderAllow_;
}
void Extension::SetOrderAllow(bool b)
{
    bOrderAllow_=b;
}

void Extension::Load(Settings& settings)
{
    bOrderAllow_ = settings.valueBool(Consts::KEY_EXTENSION_ORDERALLOW, true);

    QVariant vVal;
    vVal = settings.value(Consts::KEY_ALLOW_EXTENSIONS);
    if(vVal.isValid())
    {
        Extension::SetMovieExtensionAllow(vVal.toStringList());
    }
    else
    {
        Extension::SetMovieExtensionAllow(Extension::GetDefaultAllow());
    }

    vVal = settings.value(Consts::KEY_DENY_EXTENSIONS);
    if(vVal.isValid())
    {
        Extension::SetMovieExtensionDeny(vVal.toStringList());
    }
    else
    {
        Extension::SetMovieExtensionDeny(Extension::GetDefaultDeny());
    }
}
void Extension::Save(Settings& settings)
{
    settings.setValue(Consts::KEY_EXTENSION_ORDERALLOW, bOrderAllow_);
    settings.setValue(Consts::KEY_ALLOW_EXTENSIONS, GetMovieExtensionAllow());
    settings.setValue(Consts::KEY_DENY_EXTENSIONS, GetMovieExtensionDeny());
}
