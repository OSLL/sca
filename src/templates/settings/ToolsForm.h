#ifndef TOOLSFORM_H
#define TOOLSFORM_H

#include <QWidget>
#include <QStringList>
#include <QStringListModel>

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
    QStringListModel *m_toolsModel;

public slots:
    void addTool();
    void removeTool();
    void changeEditableTool(const QModelIndex &index);
    void toolEdited(const QString &tool);
};

#endif // TOOLSFORM_H
