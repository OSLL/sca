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
    explicit ToolsForm(QStringListModel *model, QWidget *parent = 0);
    ~ToolsForm();

    void setToolsModel(QStringListModel *model);

private:

    Ui::ToolsForm *m_ui;
    Ui::AddToolDialog *m_toolUi;
    QDialog *m_toolDialog;
    QStringListModel *m_toolsModel;

public slots:
    void openAddDialog();
    void removeTool();
    void openEditDialog();
    void editTool();
};

#endif // TOOLSFORM_H
