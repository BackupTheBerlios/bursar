#include "burcombobox.h"

#include <QDebug>

/**
  * Constructor
  */
BurComboBox::BurComboBox(QWidget *parent)
    : QComboBox(parent)
{
    m_currentItemData = QVariant();

    // connect signal
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
}


QVariant BurComboBox::currentItemData() const
{
    return m_currentItemData;
}


void BurComboBox::currentIndexChanged(int index)
{
    setCurrentItemData(itemData(index));
}


void BurComboBox::setCurrentItemData(QVariant data)
{
    if (m_currentItemData != data) {
        m_currentItemData = data;

        emit currentItemDataChanged(m_currentItemData);
    }
}
