#include "ToolsForm.h"
#include "ui_ToolsForm.h"

#include <QDebug>

ToolsForm::ToolsForm(QStringListModel *model, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ToolsForm),
    m_toolUi(new Ui::AddToolDialog),
    m_toolDialog(new QDialog(this)),
    m_toolsModel(model)
{
    m_ui->setupUi(this);
    m_toolUi->setupUi(m_toolDialog);
    m_toolDialog->layout()->setSizeConstraint( QLayout::SetFixedSize );
    m_ui->toolsListView->setModel(m_toolsModel);


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
}

ToolsForm::~ToolsForm()
{
    delete m_ui;
    delete m_toolUi;
}

void ToolsForm::setToolsModel(QStringListModel *model)
{
    m_toolsModel = model;
    m_ui->toolsListView->setModel(m_toolsModel);
}

void ToolsForm::openAddDialog()
{
    m_toolUi->buttonBox->show();

     m_toolUi->commandEdit->clear();
     m_toolsModel->insertRow(m_toolsModel->rowCount());
     QModelIndex index =  m_toolsModel->index(m_toolsModel->rowCount() - 1);
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
    m_toolsModel->removeRow(index.row());
}

void ToolsForm::openEditDialog()
{
    QModelIndex index = m_ui->toolsListView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    QString text = m_toolsModel->data(index, Qt::DisplayRole).toString();
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
    m_toolsModel->setData(index, m_toolUi->commandEdit->text());
}
