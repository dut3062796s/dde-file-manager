#ifndef PROPERTYDIALOG_H
#define PROPERTYDIALOG_H

#include "basedialog.h"
#include "../models/abstractfileinfo.h"
#include <QLabel>
#include <QCloseEvent>
#include <QTextEdit>
#include <QStackedWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QFrame;
class QCheckBox;
class QTimer;
class QListWidget;
class QButtonGroup;
QT_END_NAMESPACE

DWIDGET_BEGIN_NAMESPACE
class DExpandGroup;
DWIDGET_END_NAMESPACE

class AbstractFileInfo;
class UDiskDeviceInfo;
class DUrl;

DWIDGET_USE_NAMESPACE


class NameTextEdit: public QTextEdit
{
    Q_OBJECT

public:
    explicit NameTextEdit(const QString &text="", QWidget *parent=0);

signals:
    void editFinished();

public slots:
    void setPlainText(const QString & text);

protected:
    void focusOutEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent* event);
};


class GroupTitleLabel: public QLabel
{
    Q_OBJECT

public:
    explicit GroupTitleLabel(const QString &text="", QWidget *parent=0, Qt::WindowFlags f=0);
};

class SectionKeyLabel: public QLabel
{
    Q_OBJECT

public:
    explicit SectionKeyLabel(const QString &text="", QWidget *parent=0, Qt::WindowFlags f=0);
};

class SectionValueLabel: public QLabel
{
    Q_OBJECT

public:
    explicit SectionValueLabel(const QString &text="", QWidget *parent=0, Qt::WindowFlags f=0);
};


class PropertyDialog : public BaseDialog
{
    Q_OBJECT

public:
    explicit PropertyDialog(const DUrl &url, QWidget *parent = 0);

public:
    void initUI();
    void startComputerFolderSize(const DUrl &url);
    void toggleFileExecutable(bool isChecked);
    DUrl getUrl();
    int getFileCount();
    qint64 getFileSize();

public slots:
    void raise();
    void updateFolderSize(qint64 size);
    void renameFile();
    void showTextShowFrame();


signals:
    void requestStartComputerFolderSize();
    void closed(const DUrl& url);
    void aboutToClosed(const DUrl& url);
    void raised();

protected:
    void closeEvent(QCloseEvent* event);
    void timerEvent(QTimerEvent* event);
    void resizeEvent(QResizeEvent* event);

private:
    DUrl m_url;
    QString m_absolutePath;
    qint64 m_size = 0;
    bool m_editDisbaled = false;
    int m_fileCount = 0;
    QLabel *m_icon = NULL;
    NameTextEdit *m_edit = NULL;
    QStackedWidget *m_editStackWidget = NULL;
    QFrame* m_textShowFrame = NULL;
    QLabel* m_textShowLastLabel = NULL;
    QPushButton* m_editButton = NULL;
    QCheckBox * m_executableCheckBox = NULL;
    SectionValueLabel* m_folderSizeLabel = NULL;
    QFrame *m_basicInfoFrame = NULL;
    QFrame *m_localDeviceInfoFrame = NULL;
    QFrame *m_deviceInfoFrame = NULL;
    QFrame *m_OpenWithFrame = NULL;
    QListWidget* m_OpenWithListWidget = NULL;
    QButtonGroup* m_OpenWithButtonGroup;

    DExpandGroup *addExpandWidget(const QStringList &titleList);

    void initTextShowFrame(const QString& text);
    QFrame *createBasicInfoWidget(const AbstractFileInfoPointer &info);
    QFrame *createLocalDeviceInfoWidget(const DUrl& url);
    QFrame *createDeviceInfoWidget(UDiskDeviceInfo* info);

    QListWidget *createOpenWithListWidget(const AbstractFileInfoPointer &info);
    QFrame *createAuthorityManagermentWidget(const AbstractFileInfoPointer &info);

};

#endif // PROPERTYDIALOG_H
