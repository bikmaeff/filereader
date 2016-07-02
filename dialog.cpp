#include "dialog.h"
#include "ui_dialog.h"
#include <QPushButton>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect (ui->buttonBox->button (QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(okClicked()));
    connect (ui->buttonBox->button (QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(close()));
}

void Dialog::okClicked ()
{
    emit openFileToPath (ui->lineEdit->text ());
    close ();
}

Dialog::~Dialog()
{
    delete ui;
}
