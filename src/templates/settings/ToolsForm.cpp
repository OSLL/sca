#include "ToolsForm.h"
#include "ui_ToolsForm.h"

#include <QDebug>

ToolsForm::ToolsForm(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ToolsForm),
    m_toolUi(new Ui::AddToolDialog),
    m_toolDialog(new QDialog(this)),
    m_toolsList(NULL)
{
    m_ui->setupUi(this);
    m_toolUi->setupUi(m_toolDialog);
    m_toolDialog->layout()->setSizeConstraint( QLayout::SetFixedSize );


    connect(m_toolUi->buttonBox, SIGNAL(accepted()),
            m_toolUi->buttonBox, SLOT(close()));
    connect(m_toolUi->buttonBox, SIGNAL(accepted()),
            this, SLOT(editTool()));
    connect(m_toolUi->buttonBox, SIGNAL(rejected()),
            m_toolUi->buttonBox, SLOT(close()));

    connect(m_ui->addButton, SIGNAL(clicked()),
            this, SLOT(openAddDialog()));
    connect(m_ui->editButton, SIGNAL(clicked()),
            this, SLOT(openEditDialog()));
    connect(m_ui->removeButton, SIGNAL(clicked()),
            this, SLOT(removeTool()));

    m_ui->toolsListView->setModel(&m_toolsModel);
}

ToolsForm::~ToolsForm()
{
    delete m_ui;
    delete m_toolUi;
}

void ToolsForm::setTools(QStringList *value)
{
    m_toolsList = value;
    m_toolsModel.setStringList(*m_toolsList);
}

void ToolsForm::openAddDialog()
{
    m_toolUi->buttonBox->show();

     m_toolUi->commandEdit->clear();
     m_toolsList->append(QString());
     m_toolsModel.setStringList(*m_toolsList);
     int lastIndex = m_toolsList->size() - 1;
     QModelIndex index =  m_toolsModel.index(lastIndex);
     m_ui->toolsListView->setCurrentIndex(index);
     m_toolUi->commandEdit->clear();
     m_toolDialog->exec();
}

void ToolsForm::removeTool()
{
    QModelIndex index = m_ui->toolsListView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    m_toolsList->removeAt(index.row());
    m_toolsModel.setStringList(*m_toolsList);
}

void ToolsForm::openEditDialog()
{
    QModelIndex index = m_ui->toolsListView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    QString text = m_toolsList->at(index.row());
    m_toolUi->commandEdit->setText(text);
    m_toolDialog->exec();
}

void ToolsForm::editTool()
{
    m_toolUi->buttonBox->show();

    QModelIndex index = m_ui->toolsListView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    m_toolsList->replace(index.row(), m_toolUi->commandEdit->text());
    m_toolsModel.setStringList(*m_toolsList);
}

