#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SettingsDialog),
    m_toolsList(new QStringList)
{
    m_ui->setupUi(this);
    m_ui->settingsForm->setTools(m_toolsList);

    connect(m_ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(close()));
}

SettingsDialog::~SettingsDialog()
{
    delete m_ui;
}
