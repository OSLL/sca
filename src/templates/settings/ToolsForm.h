#ifndef TOOLSFORM_H
#define TOOLSFORM_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include "ui_AddToolDialog.h"


namespace Ui {
    class ToolsForm;
}

class ToolsForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit ToolsForm(QWidget *parent = 0);
    ~ToolsForm();

    void setTools(QStringList *value);

private:

    Ui::ToolsForm *m_ui;
    Ui::AddToolDialog *m_toolUi;
    QDialog *m_addToolDialog;
    QStringList *m_toolsList;
    QStringListModel m_toolsModel;

public slots:
    void addTool();
};

#endif // TOOLSFORM_H
