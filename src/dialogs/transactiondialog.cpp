#include "transactiondialog.h"
#include "ui_transactiondialog.h"

TransactionDialog::TransactionDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::TransactionDialog)
{
    m_ui->setupUi(this);
}

TransactionDialog::~TransactionDialog()
{
    delete m_ui;
}

void TransactionDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
