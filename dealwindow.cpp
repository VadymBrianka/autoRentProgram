#include "dealwindow.h"
#include "ui_dealwindow.h"

DealWindow::DealWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DealWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Order");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
    ui->comboBoxDeals1->setCurrentIndex(-1);
    ui->comboBoxDeals2->setCurrentIndex(-1);
    connect(ui->tabWidgetDeals,&QTabWidget::currentChanged,this,&DealWindow::on_tabWidget_currentChanged);
    connect(ui->searchLE2, &QLineEdit::textChanged, this, &DealWindow::onSearchTextChanged);
    connect(ui->searchLE, &QLineEdit::textChanged, this, &DealWindow::onSearchTextChanged);
    connect(ui->comboBoxDeals1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DealWindow::onCBChanged);
    connect(ui->comboBoxDeals2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DealWindow::onCBChangedd);
}

DealWindow::~DealWindow()
{
    delete ui;
}

void DealWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

void DealWindow::on_addDealButton_clicked()
{
    AddDealWindow *addDealWindow = new AddDealWindow(this);
    connect(addDealWindow, &AddDealWindow::closed, this, &DealWindow::onDialogClosed);
    addDealWindow->setModal(true);
    addDealWindow->show();
    hide();
}

void DealWindow::onSearchTextChanged(const QString &text)
{
    if (proxyModel1) {
        proxyModel1->setFilterFixedString(text);
        proxyModel1->setFilterCaseSensitivity(Qt::CaseInsensitive);
    }
    if (proxyModel2) {
        proxyModel2->setFilterFixedString(text);
        proxyModel2->setFilterCaseSensitivity(Qt::CaseInsensitive);
    }
}

void DealWindow::onDialogClosed()
{
    this->on_tabWidget_currentChanged(1);
    this->on_tabWidget_currentChanged(0);
    show();
}


void DealWindow::setupModel1(const QString &tableName, const QStringList &headers, int sortField)
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    db->connectToDataBase();
    QDateTime currentDate = QDateTime::currentDateTime();
    QString queryStr = QString("SELECT deal_id, rentEndDate, vin, checkColumn, status FROM Deals ;");
    QSqlQuery query;
    query.prepare(queryStr);

    if (query.exec()) {
        while (query.next()) {
            int dealId = query.value(0).toInt();
            QDateTime endRentDate = query.value(1).toDateTime();
            QString vin = query.value(2).toString();
            QString check = query.value(3).toString();
            QString status = query.value(4).toString();

            if ((check == "unChecked" && endRentDate.date() <= currentDate.date()) || (check == "unChecked" && status == "closed")) {
                QString updateStr = "UPDATE Deals SET status = 'closed' WHERE deal_id = :dealId;";
                QSqlQuery updateQuery;
                updateQuery.prepare(updateStr);
                updateQuery.bindValue(":dealId", dealId);

                QString updateStr2 = "UPDATE Cars SET status = 'available' WHERE vin = :vin;";
                QSqlQuery updateQuery2;
                updateQuery2.prepare(updateStr2);
                updateQuery2.bindValue(":vin", vin);

                QString updateStr3 = "UPDATE Deals SET checkColumn = 'checked' WHERE deal_id = :dealId;";
                QSqlQuery updateQuery3;
                updateQuery3.prepare(updateStr3);
                updateQuery3.bindValue(":dealId", dealId);

                QString updateStr4 = "UPDATE Cars SET status = 'available' WHERE vin = :vin;";
                QSqlQuery updateQuery4;
                updateQuery4.prepare(updateStr4);
                updateQuery4.bindValue(":vin", vin);

                if (updateQuery.exec() && updateQuery2.exec() && updateQuery3.exec() && updateQuery4.exec()) {
                    qDebug() << "Deal with ID" << dealId << "closed successfully.";
                } else {
                    qDebug() << "Failed to update deal with ID" << dealId;
                }
            }
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }


    model1 = new QSqlTableModel(this, db->getDB());
    model1->setTable(tableName);
    model1->setFilter("status = 'closed'");
    model1->setSort(sortField, Qt::AscendingOrder);
    for(int i = 0, j = 0; i < model1->columnCount(); i++, j++){
        model1->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}
void DealWindow::setupModel2(const QString &tableName, const QStringList &headers,int sortField)
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    db->connectToDataBase();
    QDateTime currentDate = QDateTime::currentDateTime();
    QString queryStr = QString("SELECT deal_id, rentEndDate, vin, checkColumn, status FROM Deals ;");
    QSqlQuery query;
    query.prepare(queryStr);

    if (query.exec()) {
        while (query.next()) {
            int dealId = query.value(0).toInt();
            QDateTime endRentDate = query.value(1).toDateTime();
            QString vin = query.value(2).toString();
            QString check = query.value(3).toString();
            QString status = query.value(4).toString();

            if ((check == "unChecked" && endRentDate.date() <= currentDate.date()) || (check == "unChecked" && status == "closed")) {
                QString updateStr = "UPDATE Deals SET status = 'closed' WHERE deal_id = :dealId;";
                QSqlQuery updateQuery;
                updateQuery.prepare(updateStr);
                updateQuery.bindValue(":dealId", dealId);

                QString updateStr2 = "UPDATE Cars SET status = 'available' WHERE vin = :vin;";
                QSqlQuery updateQuery2;
                updateQuery2.prepare(updateStr2);
                updateQuery2.bindValue(":vin", vin);

                QString updateStr3 = "UPDATE Deals SET checkColumn = 'checked' WHERE deal_id = :dealId;";
                QSqlQuery updateQuery3;
                updateQuery3.prepare(updateStr3);
                updateQuery3.bindValue(":dealId", dealId);

                QString updateStr4 = "UPDATE Cars SET status = 'available' WHERE vin = :vin;";
                QSqlQuery updateQuery4;
                updateQuery4.prepare(updateStr4);
                updateQuery4.bindValue(":vin", vin);

                if (updateQuery.exec() && updateQuery2.exec() && updateQuery3.exec() && updateQuery4.exec()) {
                    qDebug() << "Deal with ID" << dealId << "closed successfully.";
                } else {
                    qDebug() << "Failed to update deal with ID" << dealId;
                }
            }
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    model2 = new QSqlTableModel(this, db->getDB());
    model2->setTable(tableName);
    model2->setFilter("status = 'active'");
    model2->setSort(sortField, Qt::AscendingOrder);
    for(int i = 0, j = 0; i < model2->columnCount(); i++, j++){
        model2->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}

void DealWindow::createUI1()
{
    proxyModel1 = new QSortFilterProxyModel(this);
    proxyModel1->setSourceModel(model1);

    ui->tableViewDealsClosed->setModel(proxyModel1);
    ui->tableViewDealsClosed->setColumnHidden(6, true);
    ui->tableViewDealsClosed->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewDealsClosed->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewDealsClosed->resizeColumnsToContents();
    ui->tableViewDealsClosed->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableViewDealsClosed->horizontalHeader()->setStretchLastSection(true);

    model1->select();
}
void DealWindow::createUI2()
{
    proxyModel2 = new QSortFilterProxyModel(this);
    proxyModel2->setSourceModel(model2);

    ui->tableViewDealsActive->setModel(proxyModel2);
    ui->tableViewDealsActive->setColumnHidden(6, true);
    ui->tableViewDealsActive->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewDealsActive->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewDealsActive->resizeColumnsToContents();
    ui->tableViewDealsActive->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableViewDealsActive->horizontalHeader()->setStretchLastSection(true);

    model2->select();
}

void DealWindow::setList1(int sortField){
    this->setupModel1(TABLE_DEALS,
                      QStringList() << tr("deal_id")
                                    << tr("ITIN")
                                    << tr("VIN")
                                    << tr("Start rent date")
                                    << tr("End rent date")
                                    << tr("status")
                                    << tr("check")
                                    << tr("payment"),sortField
                      );

    this->createUI1();
}

void DealWindow::setList2(int sortField){
    this->setupModel2(TABLE_DEALS,
                      QStringList() << tr("deal_id")
                                    << tr("ITIN")
                                    << tr("VIN")
                                    << tr("Start rent date")
                                    << tr("End rent date")
                                    << tr("status")
                                    << tr("check")
                                    << tr("payment"),sortField
                      );

    this->createUI2();
}


void DealWindow::on_tabWidget_currentChanged(int index)
{
    int a = 0;
    if(ui->tabWidgetDeals->currentIndex()){
        a=1;
    }else{
        a = 0;
    }
    if(a){
        this->setList1(0);
        ui->searchLE->clear();
        ui->searchLE2->clear();
        ui->comboBoxDeals1->setCurrentIndex(-1);
        ui->comboBoxDeals2->setCurrentIndex(-1);
    }else{
        this->setList2(0);
        ui->searchLE->clear();
        ui->searchLE2->clear();
        ui->comboBoxDeals1->setCurrentIndex(-1);
        ui->comboBoxDeals2->setCurrentIndex(-1);
    }
}

void DealWindow::onCBChanged(int index)
{

    const QString selectedRole = ui->comboBoxDeals1->itemText(index);
    if (selectedRole == tr("deal_id")){
        setList2(0);
    }
    if (selectedRole == tr("itin")){
        setList2(1);
    }
    if (selectedRole == tr("vin")){
        setList2(2);
    }
    if (selectedRole == tr("rentStartDate")){
        setList2(3);
    }
    if (selectedRole == tr("rentEndDate")){
        setList2(4);
    }
}

void DealWindow::onCBChangedd(int index)
{
    const QString selectedRole = ui->comboBoxDeals2->itemText(index);
    if (selectedRole == tr("deal_id")){
        setList1(0);
    }
    if (selectedRole == tr("itin")){
        setList1(1);
    }
    if (selectedRole == tr("vin")){
        setList1(2);
    }
    if (selectedRole == tr("rentStartDate")){
        setList1(3);
    }
    if (selectedRole == tr("rentEndDate")){
        setList1(4);
    }
}

void DealWindow::on_paymentButton_clicked()
{
    PaymentWindow *paymentWindow = new PaymentWindow(this);
    connect(paymentWindow, &PaymentWindow::closed, this, &DealWindow::onDialogClosed);
    paymentWindow->setModal(true);
    paymentWindow->show();
    hide();
}

