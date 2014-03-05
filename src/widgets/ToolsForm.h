#ifndef TOOLSFORM_H
#define TOOLSFORM_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include "ui_EditCommandDialog.h"
#include <QDialog>


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

    Ui::EditCommand *m_editCommandUi;
    QDialog *m_editCommandDialog;
    Ui::ToolsForm *m_ui;
    QStringListModel *m_toolsModel;

public slots:
    void addTool();
    void removeTool();
    void editTool();
    void acceptEditedTool();
    void rejectEditedTool();
};

#endif // TOOLSFORM_H
