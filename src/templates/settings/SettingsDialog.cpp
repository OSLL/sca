#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

#include <QDebug>

SettingsDialog::SettingsDialog(QSettings *settings, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::SettingsDialog),
    m_toolsModel(new QStringListModel(this)),
    m_settings(settings),
    m_toolsForm(new ToolsForm(m_toolsModel, this))
{
    m_ui->setupUi(this);
    m_ui->stackedWidget->addWidget(m_toolsForm);

    readSettings();

    connect(m_ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(close()));
    connect(m_ui->buttonBox, SIGNAL(rejected()),
            this, SLOT(readSettings()));
    connect(m_ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(saveSettings()));
    connect(m_ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(close()));

    connect(m_ui->settingsList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*)));

    
    
}

SettingsDialog::~SettingsDialog()
{
    delete m_ui;
}

void SettingsDialog::saveSettings()
{
    qDebug() <<"[Save dialog] save:" << m_toolsModel->stringList();
    m_settings->beginGroup("Tools");
    m_settings->setValue("toolsList", QVariant(m_toolsModel->stringList()));
    m_settings->endGroup();

    m_settings->sync();
}

void SettingsDialog::changePage(QListWidgetItem *index)
{
    QString settingsName = index->text();

    if(settingsName == "Tools")
    {
        m_ui->stackedWidget->setCurrentWidget(m_toolsForm);
    }
}

void SettingsDialog::setSettings(QSettings *settings)
{
    m_settings = settings;
}

void SettingsDialog::readSettings()
{
    m_settings->beginGroup("Tools");
    QStringList m_toolsList = m_settings->value("toolsList", QStringList()).toStringList();
    m_settings->endGroup();

    m_toolsModel->setStringList(m_toolsList);
}

QStringListModel *SettingsDialog::getToolsModel() const
{
    return m_toolsModel;
}
