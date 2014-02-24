#include "ToolsForm.h"
#include "ui_ToolsForm.h"

#include <QDebug>

ToolsForm::ToolsForm(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::ToolsForm),
    m_toolUi(new Ui::AddToolDialog),
    m_toolsList(NULL)
{
    m_ui->setupUi(this);
    m_addToolDialog = new QDialog(this);
    m_toolUi->setupUi(m_addToolDialog);

    connect(m_toolUi->buttonBox, SIGNAL(accepted()),
            this, SLOT(addTool()));
    connect(m_toolUi->buttonBox, SIGNAL(accepted()),
            m_toolUi->buttonBox, SLOT(close()));
    connect(m_toolUi->buttonBox, SIGNAL(rejected()),
            m_toolUi->buttonBox, SLOT(close()));
    connect(m_ui->addButton, SIGNAL(clicked()),
            m_addToolDialog, SLOT(exec()));


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

void ToolsForm::addTool()
{
    qDebug() << m_toolUi->commandEdit->text();
    m_toolsList->append(m_toolUi->commandEdit->text());
    m_toolsModel.setStringList(*m_toolsList);
    m_toolUi->commandEdit->clear();

}

