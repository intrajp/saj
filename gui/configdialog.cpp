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
 * Originally copied from
 * https://doc.qt.io/archives/qt-4.8/qt-dialogs-configdialog-example.html
 *
 */
/*
 * configdialog.cpp - dialog for saj-gui.
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
#include <QProcess>
#include <QByteArray>

#include "configdialog.h"
#include "pages.h"

ConfigDialog::ConfigDialog()
{
    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(140);
    contentsWidget->setSpacing(12);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new ConfigurationPage);
    pagesWidget->addWidget(new AnalyzePage);
    pagesWidget->setMinimumWidth(400);
    pagesWidget->setMaximumWidth(800);

    createIcons();
    contentsWidget->setCurrentRow(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    setLayout(mainLayout);

    setWindowTitle(tr("saj"));
}

/* This is an override slot of QDialog::reject() when close() is clicked */
void ConfigDialog::reject()
{
    QProcess *pidProcess = new QProcess(this);
    QString program = "pidof saj";
    QString pidStr;
    try {
        pidProcess->start(program);
        pidProcess->waitForFinished();
        QByteArray output = pidProcess->readAllStandardOutput();
        pidStr = QString::fromLocal8Bit(output);
        qDebug() << "pid:" << pidStr;
    } catch (int e) {
        qDebug() << "Process error";
    }
    if (!pidStr.isEmpty()) {
        QMessageBox msgError;
            msgError.setText("CRITICAL ERROR!\nsaj is running: " + pidStr);
            msgError.setIcon(QMessageBox::Critical);
            msgError.setWindowTitle("Not allowed");
            msgError.exec();
    } else {
        /* call original one */
        QDialog::reject();
    }
}

void ConfigDialog::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(contentsWidget);
    configButton->setIcon(QIcon(":/images/config.png"));
    configButton->setText(tr("Configuration"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *analyzeButton = new QListWidgetItem(contentsWidget);
    analyzeButton->setIcon(QIcon(":/images/analyze.png"));
    analyzeButton->setText(tr("Analyze"));
    analyzeButton->setTextAlignment(Qt::AlignHCenter);
    analyzeButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void ConfigDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
