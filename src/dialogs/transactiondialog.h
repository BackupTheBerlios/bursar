#ifndef TRANSACTIONDIALOG_H
#define TRANSACTIONDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class TransactionDialog;
}

class TransactionDialog : public QDialog {
    Q_OBJECT
public:
    TransactionDialog(QWidget *parent = 0);
    ~TransactionDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::TransactionDialog *m_ui;
};

#endif // TRANSACTIONDIALOG_H
