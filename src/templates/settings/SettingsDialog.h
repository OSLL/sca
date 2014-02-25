#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QSettings>
#include <QSignalMapper>
#include <QListWidgetItem>
#include "templates/settings/ToolsForm.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QSettings *settings, QWidget *parent = 0);
    ~SettingsDialog();
    
    void setSettings(QSettings *settings);

private:
    Ui::SettingsDialog *m_ui;
    QStringList *m_toolsList;
    QSettings *m_settings;
    ToolsForm *m_toolsForm;


private slots:
    void saveSettings();
    void changePage(QListWidgetItem *index);
    void readSettings();
};

#endif // SETTINGSDIALOG_H
