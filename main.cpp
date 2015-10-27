/* This file is part of nCircos.
   Copyright 2015, Arun Narayanankutty <n.arun.lifescience@gmail.com>

   nCircos is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   nCircos is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with nCircos.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <stdio.h>
#include <stdlib.h>

#include "commandline/commandline.h"
#include "ui/mainwindow.h"

#include <iostream>

// Custom message handler for total control
// can be activated by -debug flag
void debugOutput(QtMsgType type, const QMessageLogContext &context,
                     const QString &msg) {
  QByteArray localMsg = msg.toLocal8Bit();
  switch (type) {
  case QtDebugMsg:
    fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(),
            context.file, context.line, context.function);
    break;
  case QtInfoMsg:
    fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(),
            context.file, context.line, context.function);
    break;
  case QtWarningMsg:
    fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(),
            context.file, context.line, context.function);
    break;
  case QtCriticalMsg:
    fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(),
            context.file, context.line, context.function);
    break;
  case QtFatalMsg:
    fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(),
            context.file, context.line, context.function);
    abort();
  }
}

// Function to check weather a commandline flag is present or not
bool checkFlagStatus(const int &argc, char *argv[], QString flag) {
  for (int i = 0; i < argc; ++i) {
    if (!qstrcmp(argv[i], flag.toLatin1().data())) {
      return true;
    }
  }
  return false;
}

// Dynamically create an appropriate type of application instance
QCoreApplication* createApplication(int &argc, char *argv[]) {
    if(checkFlagStatus(argc, argv, "-nogui")) {
      return new QCoreApplication(argc, argv);
    }
  return new QApplication(argc, argv);
}

int main(int argc, char *argv[]) {
  QScopedPointer<QCoreApplication> app(createApplication(argc, argv));

  app->setApplicationName("nCircos");
  app->setApplicationVersion("version");
  app->setOrganizationName("My Company");
  app->setOrganizationDomain("website");

  if(checkFlagStatus(argc, argv, "-debug"))
      qInstallMessageHandler(debugOutput);

  if (qobject_cast<QApplication *>(app.data())) {
    // start GUI version...
    MainWindow nCircos;
    nCircos.show();
    nCircos.setWindowState(Qt::WindowMaximized);
    return app->exec();
  } else {
    // start non-GUI version...
    commandline cli;
  }
}
