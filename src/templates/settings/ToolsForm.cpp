#include "ToolsForm.h"
#include "ui_ToolsForm.h"
#include "../../src/StringConstants.h"

#include <QDebug>

ToolsForm::ToolsForm(QStringListModel *model, QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ToolsForm),
    m_toolsModel(model)
{
    m_ui->setupUi(this);
    m_ui->toolsListView->setModel(m_toolsModel);

    connect(m_ui->addButton, SIGNAL(clicked()),
            this, SLOT(addTool()));
    connect(m_ui->removeButton, SIGNAL(clicked()),
            this, SLOT(removeTool()));
    connect(m_ui->toolsListView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(changeEditableTool(QModelIndex)));
    connect(m_ui->commandEdit, SIGNAL(textEdited(QString)),
            this, SLOT(toolEdited(QString)));
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

void ToolsForm::changeEditableTool(const QModelIndex &index)
{
    if(!index.isValid())
    {
        m_ui->commandEdit->clear();
        return;
    }

    QString tool = m_toolsModel->data(index, Qt::DisplayRole).toString();
    m_ui->commandEdit->setText(tool);
}

void ToolsForm::toolEdited(const QString &tool)
{
    QModelIndex index = m_ui->toolsListView->currentIndex();
    if(!index.isValid())
    {
        return;
    }
    m_toolsModel->setData(index, QVariant(tool));
}
