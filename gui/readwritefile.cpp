/*
 * readwritefile.cpp - read/write file for saj-gui.
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

#include <QDir> 
#include <QFile> 
#include <QFileDialog> 
#include <QDebug> 
#include <QMessageBox> 
#include "readwritefile.h"

ReadWriteFile::ReadWriteFile()
{
    /* Do nothing */
}

int ReadWriteFile::sosDirCheck(const QString selectedDirStr)
{
    if (QDir(selectedDirStr).exists())
        return 1;
    else
        return 0;
    return 0;
}

void ReadWriteFile::readConfigFile(const QString fileName, QTextEdit *textEdit)
{
    QFile file(fileName);
    if(!file.exists()) {
        /* qDebug() << "File <i>cannot</i> be found "<<fileName; */
        textEdit->setText(textEdit->toPlainText() + "File cannot be found. Please restore it.\n");
    } else {
        /* qDebug() << fileName << " Opening..."; */
        /* textEdit->clear(); */
        textEdit->setText(textEdit->toPlainText() + "Opening...\n");
    }
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        textEdit->clear();
        QTextStream stream(&file);
        while (!stream.atEnd()) {
            line = stream.readLine();
            textEdit->setText(textEdit->toPlainText() + line + "\n");
        }
    }
    file.close();
}

void ReadWriteFile::copyConfigFile()
{
    char *homedir = getenv("HOME");
    QString homeDir = QString::fromLocal8Bit(homedir);
    QString configDir = homeDir + "/.saj";
    if (!QDir(configDir).exists()) {
        QDir().mkdir(configDir);
    }
    QString configFileName1 = "saj.conf";
    QString configFileName2 = "saj-mcinfo.conf";
    QString configFullName1 = homeDir + "/.saj/" + configFileName1;
    QString configFullName2 = homeDir + "/.saj/" + configFileName2;
    /* qDebug() << configFullName1; */
    /* qDebug() << configFullName2; */
    if (QFile::exists(configFullName1)) {
        QFile::remove(configFullName1);
    }
    if (QFile::exists(configFullName2)) {
        QFile::remove(configFullName2);
    }
    QMessageBox msgBox;
    if ((QFile::copy("/usr/share/saj/saj.conf.example",
                    configFullName1)) &&
       (QFile::copy("/usr/share/saj/saj-mcinfo.conf.example",
                    configFullName2))) {
        msgBox.setText("Succeeeded restoring files.");
    } else {
        msgBox.setText("Failed restoring files!");
    }
    msgBox.exec();
}

int ReadWriteFile::configFileSanityCheck(const QString fileName)
{
    if (fileName.contains(QRegExp("saj(.*)?.conf"))) {
        /* qDebug() << "this should be config file"; */
        return 1;
    } else {
        /* qDebug() << "this should not be config file"; */
        return 0;
    }
    return 0;
}

void ReadWriteFile::writeConfigFile(const QString fileName, QTextEdit *textEdit)
{
    QMessageBox msgBox;
    if (configFileSanityCheck(fileName)) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            msgBox.setText("File cannot be opend...");
        } else {
            QTextStream outStream(&file);
            outStream << textEdit->toPlainText();
        }
        file.close();
        msgBox.setText("File saved.");
    } else {
        msgBox.setText("This should not be a config file.");
    }
    msgBox.exec();
}

QString ReadWriteFile::setDirectory()
{
    QString currDirStr = currDir.dirName();
    QString selectedDirStr = QFileDialog::getExistingDirectory
                             (NULL, tr("Open Directory"),
                                    currDirStr,
                                    QFileDialog::ShowDirsOnly
                                    | QFileDialog::DontResolveSymlinks);
    /* qDebug() << selectedDirStr; */
    return selectedDirStr;
}
