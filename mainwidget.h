#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDir>
#include <QFileSystemModel>
#include <QSettings>
#include <QDebug>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public:
    void saveSettings();
    void loadSettings();

private slots:
    void on_listWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();
    void readToFile(const QString &filePath);

private:
    Ui::MainWidget *ui;
    //объявляем поле модели
    QFileSystemModel *model;
    //Настройки проекта
    QSettings* settings;
};

#endif // MAINWIDGET_H
