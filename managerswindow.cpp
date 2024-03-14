#include "managerswindow.h"
#include "ui_managerswindow.h"

ManagersWindow::ManagersWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagersWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Managers");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
    connect(ui->tabWidgetManagers,&QTabWidget::currentChanged,this,&ManagersWindow::on_tabWidget_currentChanged);
}

ManagersWindow::~ManagersWindow()
{
    delete ui;
}

void ManagersWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

void ManagersWindow::on_tabWidget_currentChanged(int index){
    int a = 0;
    if(ui->tabWidgetManagers->currentIndex()){
        a=1;
    }else{
        a = 0;
    }
    if(a){
        this->setList1();
    }else{
        this->setList2();
    }
}

void ManagersWindow::setupModel1(const QString &tableName, const QStringList &headers)
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    db->connectToDataBase();
    model1 = new QSqlTableModel(this, db->getDB());
    model1->setTable(tableName);
    model1->setFilter("status = 'Not_Verificated'");
    for(int i = 0, j = 0; i < model1->columnCount(); i++, j++){
        model1->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
    model1->setSort(0,Qt::AscendingOrder);
}
void ManagersWindow::setupModel2(const QString &tableName, const QStringList &headers)
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    db->connectToDataBase();
    model2 = new QSqlTableModel(this, db->getDB());
    model2->setTable(tableName);
    model2->setFilter("status = 'VERIFICATED'");
    for(int i = 0, j = 0; i < model2->columnCount(); i++, j++){
        model2->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
    model2->setSort(0,Qt::AscendingOrder);
}

void ManagersWindow::createUI1()
{
    ui->tableViewManagersNotVerificated->setModel(model1);
    ui->tableViewManagersNotVerificated->setColumnHidden(2, true);
    ui->tableViewManagersNotVerificated->setColumnHidden(3, true);
    ui->tableViewManagersNotVerificated->setColumnHidden(4, true);
    ui->tableViewManagersNotVerificated->setColumnHidden(5, true);
    ui->tableViewManagersNotVerificated->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewManagersNotVerificated->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewManagersNotVerificated->resizeColumnsToContents();
    ui->tableViewManagersNotVerificated->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableViewManagersNotVerificated->horizontalHeader()->setStretchLastSection(true);

    model1->select();
}
void ManagersWindow::createUI2()
{
    ui->tableViewManagersVerificated->setModel(model2);
    ui->tableViewManagersVerificated->setColumnHidden(2, true);
    ui->tableViewManagersVerificated->setColumnHidden(3, true);
    ui->tableViewManagersVerificated->setColumnHidden(4, true);
    ui->tableViewManagersVerificated->setColumnHidden(5, true);
    ui->tableViewManagersVerificated->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewManagersVerificated->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewManagersVerificated->resizeColumnsToContents();
    ui->tableViewManagersVerificated->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableViewManagersVerificated->horizontalHeader()->setStretchLastSection(true);

    model2->select();
}

void ManagersWindow::setList1(){
    this->setupModel1(TABLE_MANAGERS,
                      QStringList() << tr("Manager_id")
                                    << tr("Login")
                                    << tr("Question")
                                    << tr("Answer")
                                    << tr("Password")
                                    << tr("Surname")
                                    << tr("First Name")
                                    << tr("Middle Name")
                                    << tr("Phone Number")
                                    << tr("Email")
                                    << tr("Role")
                                    << tr("Status")
                      );

    this->createUI1();
}

void ManagersWindow::setList2(){
    this->setupModel2(TABLE_MANAGERS,
                      QStringList() << tr("Manager_id")
                                    << tr("Login")
                                    << tr("Question")
                                    << tr("Answer")
                                    << tr("Password")
                                    << tr("Surname")
                                    << tr("First Name")
                                    << tr("Middle Name")
                                    << tr("Phone Number")
                                    << tr("Email")
                                    << tr("Role")
                                    << tr("Status")
                      );

    this->createUI2();
}
