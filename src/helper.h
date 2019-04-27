//SceneExplorer
//Exploring video files by viewer thumbnails
//
//Copyright (C) 2018  Ambiesoft
//
//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef HELPER_H
#define HELPER_H

#include <QString>
#include <QWidget>
#include <QComboBox>
#include <QMessageBox>
#include <QSqlQuery>

#include "globals.h"




QString normalizeFile(const QString& file);
void nomalizeDirAndName(const QString& full, QString&dir, QString& name);

QString createSalient(const QString& file, const qint64& size);
QString getUUIDFromThumbfile(const QString& file);
Qt::WindowFlags GetDefaultDialogFlags();
void setReadOnly(QLineEdit& le);





QString GetSortColumnName(SORTCOLUMNMY sc);
QString GetAppDir();
QString GetSystemDefaultLang();
void InsertUniqueTextToComboBox(QComboBox& combo, const QString& text);



bool processCommandLine(QString* helpText=nullptr);

QString ExpandEnv(const QString& str);


QSqlQuery myPrepare(const QString& sql);

QString getClipboardText();
void setClipboardText(const QString& text);

bool IsClipboardTagDataAvalable();

bool isLegalFileExt(QString ext);
bool isThumbFileName(const QString& file);
bool isUUID(const QString& s);

// std::wstring qToStdWString(const QString &str);
// QString stdWToQString(const std::wstring &str);

bool IsSubDir(const QString& parent, const QString& child);
QStringList RemoveDuplicateSubDirectory(const QStringList& sources, QStringList& removed);


#endif // HELPER_H
