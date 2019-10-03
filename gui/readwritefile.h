/*
 * readwritefile.h - read/write file definition for saj-gui.
 * This file contains the contents of saj.
 *
 *  Copyright (C) 2019 Shintaro Fujiwara
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301 USA
 */

#ifndef READWRITEFILE_H
#define READWRITEFILE_H

#include <QTextEdit>
#include <QDir>

class ReadWriteFile : public QTextEdit
{
    Q_OBJECT

public:
    ReadWriteFile();

public slots:
    int sosDirCheck(const QString selectedDirStr);
    int  configFileSanityCheck(const QString fileName);
    void copyConfigFile();
    void readConfigFile(const QString fileName, QTextEdit *textEdit);
    void writeConfigFile(const QString fileName, QTextEdit *textEdit);
    QString setDirectory();

private:
    QDir currDir;
};

#endif
