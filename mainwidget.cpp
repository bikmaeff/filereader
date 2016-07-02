#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QDir>
#include "dialog.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    //инициализируем настройки проекта
    settings = new QSettings(this);
    loadSettings ();

    //инициализируем модель в конструкторе
    model = new QFileSystemModel(this);
    model->setFilter (QDir::AllEntries);
    model->setRootPath ("");

    //устанавливаем модель для ListView
    ui->listDirFile->setModel (model);
    connect (ui->listDirFile,SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_listWidget_doubleClicked(QModelIndex)));
}

MainWidget::~MainWidget()
{
    delete ui;
    saveSettings ();
}

void MainWidget::saveSettings()
{
    settings->setValue ("title", windowTitle ());
    settings->setValue ("geometry", geometry ());
}

void MainWidget::loadSettings()
{
    setWindowTitle (settings->value ("title", "File Reader Text").toString ());
    setGeometry (settings->value ("geometry", QRect(600, 600, 600, 600)).toRect ());
}

void MainWidget::on_listWidget_doubleClicked(const QModelIndex &index)
{
    QListView* listView = (QListView*) sender ();
    QFileInfo fileInfo = model->fileInfo (index);

    QDir dir = fileInfo.dir ();

    if (fileInfo.fileName () == ".." )
    {
        //QDir dir = fileInfo.dir ();
        dir.cdUp ();
        listView->setRootIndex (model->index(dir.absolutePath ()));
    }
    else if (fileInfo.fileName () == ".")
    {
        listView->setRootIndex (model->index (""));
    }
    else if (fileInfo.isDir ())
    {
        listView->setRootIndex (index);
    }
    else if (fileInfo.isFile ())
    {
        QString filePath = fileInfo.absoluteFilePath ();
        //qDebug() << filePath << endl;
        //qDebug() << fileInfo.fileName() << endl;

        readToFile (filePath);
    }
}

void MainWidget::on_pushButton_clicked()
{
    Dialog *openWindowDialog = new Dialog(this);
    openWindowDialog->show ();

    connect (openWindowDialog, SIGNAL(openFileToPath(QString)), this, SLOT(readToFile(QString)));
    //connect (mWindow, SIGNAL(FilePath(QString)), this, SLOT(ReadToFile(QString)));
}

void MainWidget::readToFile(const QString &filePath)
{
    QFile mFile(filePath); //without filePath

    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information (this, "Error", "Path not correct!");
        return;
    }

    QTextStream mStream(&mFile);

    QString mBuffer = mStream.readAll ();

    ui->textEdit->setText (mBuffer);

    mFile.flush ();
    mFile.close ();
}
