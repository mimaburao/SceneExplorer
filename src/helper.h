#ifndef HELPER_H
#define HELPER_H



QString rstrip(const QString& str, QChar c);
QString pathCombine(const QString& path1, const QString& path2);
QString canonicalDir(const QString& dir);
void canonicalDirAndName(const QString& full, QString&dir, QString& name);
void Info(QWidget* parent, QString message);
void Alert(QWidget* parent, QString message);
bool YesNo(QWidget* parent, QString message);
QString createSalient(const QString& file, const qint64& size);
QString getUUIDFromThumbfile(const QString& file);

// OSD
bool showInGraphicalShell(QWidget *parent, const QString &pathIn);
void MoveToTrashImpl( QString file );

#endif // HELPER_H
