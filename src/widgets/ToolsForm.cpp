#include "ToolsForm.h"
#include "ui_ToolsForm.h"
#include "../../src/StringConstants.h"

#include <QDebug>

ToolsForm::ToolsForm(QStringListModel *model, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ToolsForm),
    m_editCommandUi(new Ui::EditCommand),
    m_editCommandDialog(new QDialog(this)),
    m_toolsModel(model)
{
    m_ui->setupUi(this);
    m_editCommandUi->setupUi(m_editCommandDialog);
    m_ui->toolsListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_ui->toolsListView->setModel(m_toolsModel);

    connect(m_ui->addButton, SIGNAL(clicked()),
            this, SLOT(addTool()));
    connect(m_ui->removeButton, SIGNAL(clicked()),
            this, SLOT(removeTool()));
    connect(m_ui->editButton, SIGNAL(clicked()),
            this, SLOT(editTool()));

    connect(m_editCommandUi->buttonBox, SIGNAL(accepted()),
            m_editCommandDialog, SLOT(accept()));
    connect(m_editCommandUi->buttonBox, SIGNAL(rejected()),
            m_editCommandDialog, SLOT(reject()));
    connect(m_editCommandDialog, SIGNAL(accepted()),
            this, SLOT(acceptEditedTool()));
    connect(m_editCommandDialog, SIGNAL(rejected()),
            this, SLOT(rejectEditedTool()));

}

ToolsForm::~ToolsForm()
{
    delete m_ui;
}

void ToolsForm::setToolsModel(QStringListModel *model)
{
    m_toolsModel = model;
    m_ui->toolsListView->setModel(m_toolsModel);
}

void ToolsForm::addTool()
{
     m_toolsModel->insertRow(m_toolsModel->rowCount());
     QModelIndex index =  m_toolsModel->index(m_toolsModel->rowCount() - 1);
     m_ui->toolsListView->setCurrentIndex(index);
     m_editCommandUi->commandEdit->clear();
     m_editCommandDialog->exec();
}

void ToolsForm::acceptEditedTool()
{
    QModelIndex index = m_ui->toolsListView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    QString tool = m_editCommandUi->commandEdit->text();
    m_toolsModel->setData(index, QVariant(tool));
}

void ToolsForm::rejectEditedTool()
{
    QModelIndex index = m_ui->toolsListView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    QString tool = m_toolsModel->data(index, Qt::DisplayRole).toString();
    if(tool == QString())
    {
        m_toolsModel->removeRow(index.row());
    }
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

void ToolsForm::editTool()
{
    QModelIndex index = m_ui->toolsListView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    QString tool = m_toolsModel->data(index, Qt::DisplayRole).toString();
    m_editCommandUi->commandEdit->setText(tool);
    m_editCommandDialog->exec();
}
