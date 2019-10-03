/****************************************************************************
 * **
 * ** Copyright (C) 2015 The Qt Company Ltd.
 * ** Contact: http://www.qt.io/licensing/
 * **
 * ** This file is part of the examples of the Qt Toolkit.
 * **
 * ** $QT_BEGIN_LICENSE:BSD$
 * ** You may use this file under the terms of the BSD license as follows:
 * **
 * ** "Redistribution and use in source and binary forms, with or without
 * ** modification, are permitted provided that the following conditions are
 * ** met:
 * **   * Redistributions of source code must retain the above copyright
 * **     notice, this list of conditions and the following disclaimer.
 * **   * Redistributions in binary form must reproduce the above copyright
 * **     notice, this list of conditions and the following disclaimer in
 * **     the documentation and/or other materials provided with the
 * **     distribution.
 * **   * Neither the name of The Qt Company Ltd nor the names of its
 * **     contributors may be used to endorse or promote products derived
 * **     from this software without specific prior written permission.
 * **
 * **
 * ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 * **
 * ** $QT_END_LICENSE$
 * **
 * ****************************************************************************/
/*
 * pages.cpp - pages file for saj-gui.
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

#include <QtGui>

#include "pages.h"
#include "readwritefile.h"

ConfigurationPage::ConfigurationPage(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("configuration"));
    QLabel *itemLabel = new QLabel(tr("analyze items:"));
    fileEdit = new QTextEdit(tr("Please load config file to edit"));
    restoreButton = new QPushButton(tr("Restore configs"));
    saveButton = new QPushButton(tr("Save file"));
    QComboBox *itemCombo = new QComboBox;
    itemCombo->addItem(tr("Load config file to edit"));
    itemCombo->addItem(tr("- sosreport"));
    itemCombo->addItem(tr("- mcinfo"));

    QHBoxLayout *itemLayout = new QHBoxLayout;
    itemLayout->addWidget(itemLabel);
    itemLayout->addWidget(itemCombo);

    QHBoxLayout *fileContentsLayout = new QHBoxLayout;
    fileContentsLayout->addWidget(fileEdit);
    fileContentsLayout->addWidget(restoreButton);
    fileContentsLayout->addWidget(saveButton);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addLayout(itemLayout);
    configLayout->addLayout(fileContentsLayout);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);

    connect(itemCombo,
            SIGNAL(currentIndexChanged(int)),
            this, SLOT(onComboboxCurrentIndexChanged(int)));
    connect(restoreButton,
            SIGNAL(clicked()),
            this, SLOT(restoreConfigFile()));
    connect(saveButton,
            SIGNAL(clicked()),
            this, SLOT(writeConfigFile()));

    setLayout(mainLayout);
}

void ConfigurationPage::restoreConfigFile()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this,
                                "Restore config",
                                "Restore configs from /usr/share/saj ?",
                                QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
      /* qDebug() << "Yes was clicked"; */
      ReadWriteFile *readWriteFile = new ReadWriteFile;
      readWriteFile->copyConfigFile();
  } else {
      /* qDebug() << "Yes was *not* clicked"; */
  }
}

void ConfigurationPage::writeConfigFile()
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this,
                                "Write config",
                                "Write to config ?",
                                QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
      /* qDebug() << "Yes was clicked"; */
      ReadWriteFile *readWriteFile = new ReadWriteFile;
      readWriteFile->writeConfigFile(configFullName, fileEdit);
  } else {
      /* qDebug() << "Yes was *not* clicked"; */
  }
}

void ConfigurationPage::onComboboxCurrentIndexChanged(int index)
{
    if (index == 0) {
        fileEdit->clear();
        fileEdit->setText(fileEdit->toPlainText() + "Please load config file to edit\n");
        configFileName = "";
        configFullName = "";
    } else {
        char *homedir = getenv("HOME");
        QString homeDir = QString::fromLocal8Bit(homedir);
        if (index == 1) {
            fileEdit->clear();
            configFileName = "saj.conf";
        } else if (index == 2) {
            fileEdit->clear();
            configFileName = "saj-mcinfo.conf";
        } 
        configFullName = homeDir + "/.saj/" + configFileName;
        ReadWriteFile *readWriteFile = new ReadWriteFile;
        readWriteFile->readConfigFile(configFullName, fileEdit);
    }
    /* qDebug() << "configFullName:" << configFullName; */
}

AnalyzePage::AnalyzePage(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *setDirectoryButton = new QPushButton(tr("Set Directory and analyze"));
    showDirectoryLabel = new QLabel(tr("none"));
    QGroupBox *groupBox = new QGroupBox(tr("select report type"));
    sosRadio = new QRadioButton(tr("sosreport"));
    mcinfoRadio = new QRadioButton(tr("mcinfo"));
    sosRadio->setChecked(true);
    echoText = new QTextEdit(this);
    echoText->setText("Result will be shown here.");

    QVBoxLayout *selectReportTypeLayout = new QVBoxLayout;
    selectReportTypeLayout->addWidget(sosRadio);
    selectReportTypeLayout->addWidget(mcinfoRadio);
    selectReportTypeLayout->addStretch(1);
    groupBox->setLayout(selectReportTypeLayout);

    connect(setDirectoryButton,
            SIGNAL(clicked()),
            this, SLOT(setDirectory()));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(groupBox);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(setDirectoryButton);
    mainLayout->addStretch(1);
    mainLayout->addWidget(showDirectoryLabel);
    mainLayout->addStretch(1);
    mainLayout->addWidget(echoText);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void AnalyzePage::setDirectory()
{
    QString currPath = QDir::currentPath();
    showDirectoryLabel->setWordWrap(true);
    ReadWriteFile *readWriteFile = new ReadWriteFile;
    selectedDirStr = readWriteFile->setDirectory();
    showDirectoryLabel->setText(selectedDirStr);
    QString sosDirCheckStr;
    if (mcinfoRadio->isChecked() && (!selectedDirStr.isEmpty())) {
        sosDirCheckStr = selectedDirStr + "/cmdlog";
    } else {
        sosDirCheckStr = selectedDirStr + "/sos_commands";
    }
    if (selectedDirStr != "") {
        if (!readWriteFile->sosDirCheck(sosDirCheckStr)) {
            QMessageBox msgBox;
            msgBox.setText("Not a proper directory.");
            msgBox.exec();
        } else {
            checkExecSosreportAnalyzer(mcinfoRadio, selectedDirStr);
        }
    }
}

void AnalyzePage::execSosreportAnalyzer(QRadioButton *mcinfoRadio, QString selectedDirStr)
{
    myProcess = new QProcess(this);
    QString program = "saj";
    if (mcinfoRadio->isChecked())
        arguments << "-M" << "-D" << selectedDirStr;
    else
        arguments << "-D" << selectedDirStr;
    connect(myProcess, SIGNAL(started()), this, SLOT(procStarted()));
    connect(myProcess, SIGNAL(finished(int, QProcess::ExitStatus)),this,SLOT(procFinished(int, QProcess::ExitStatus)));
    connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(updateOutput()));
    connect(myProcess, SIGNAL(readyReadStandardError()), this, SLOT(updateError()));
    try {
        myProcess->start(program, arguments);
    } catch (int e) {
        qDebug() << "Process error";
    }
}

void AnalyzePage::checkExecSosreportAnalyzer(QRadioButton *mcinfoRadio, QString selectedDirStr)
{
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(this,
                                "Analyze",
                                "Analyze this directory ?",
                                QMessageBox::Yes|QMessageBox::No);
  if (reply == QMessageBox::Yes) {
      /* qDebug() << "Yes was clicked"; */
      execSosreportAnalyzer(mcinfoRadio, selectedDirStr);
  } else {
      /* qDebug() << "Yes was *not* clicked"; */
  }
}

void AnalyzePage::showCompleted()
{
    QMessageBox msgBox;
    msgBox.setText("Completed without error.");
    msgBox.exec();
}

void AnalyzePage::resultProcess(void)
{
    qDebug() << "resultProcess was called!";
}

void AnalyzePage::procStarted(void)
{
    qDebug() << "Proc Started";
}

void AnalyzePage::procFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Finished:" << exitCode << ":" << exitStatus;
    if (exitStatus == 0) {
        showCompleted();
    }
}

void AnalyzePage::updateOutput(void)
{
    QByteArray output = myProcess->readAllStandardOutput();
    QString str = QString::fromLocal8Bit(output);
    echoText->setText(str);
    /* qDebug() << str; */
}

void AnalyzePage::updateError(void)
{
    QByteArray output = myProcess->readAllStandardError();
    QString str = QString::fromLocal8Bit(output);
    echoText->setText(str);
    /* qDebug() << str; */
}

/*
 * Refer
 * http://qtexamples.com/combobox-signals-and-slots/
 */
