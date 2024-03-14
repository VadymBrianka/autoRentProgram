#include "carswindow.h"
#include "ui_carswindow.h"

CarsWindow::CarsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CarsWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Cars");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
    ui->comboBoxCarsAvailable->setCurrentIndex(-1);
    ui->comboBoxCarsNotAvailable->setCurrentIndex(-1);
    connect(ui->tabWidgetCars,&QTabWidget::currentChanged,this,&CarsWindow::on_tabWidget_currentChanged);
    connect(ui->searchLE2, &QLineEdit::textChanged, this, &CarsWindow::onSearchTextChanged);
    connect(ui->searchLE, &QLineEdit::textChanged, this, &CarsWindow::onSearchTextChanged);
    connect(ui->comboBoxCarsAvailable, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CarsWindow::onCBChanged);
    connect(ui->comboBoxCarsNotAvailable, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CarsWindow::onCBChangedd);


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
}

CarsWindow::~CarsWindow()
{
    delete ui;
}

void CarsWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

void CarsWindow::onSearchTextChanged(const QString &text)
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

void CarsWindow::on_addCarButton_clicked()
{
    AddCarWindow *addCarWindow = new AddCarWindow(this);
    connect(addCarWindow, &AddCarWindow::closed, this, &CarsWindow::onDialogClosed);
    addCarWindow->setModal(true);
    addCarWindow->show();
    hide();
}

void CarsWindow::onDialogClosed()
{
    this->on_tabWidget_currentChanged(1);
    this->on_tabWidget_currentChanged(0);
    show();
}

void CarsWindow::setupModel1(const QString &tableName, const QStringList &headers, int sortField)
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    db->connectToDataBase();
    model1 = new QSqlTableModel(this, db->getDB());
    model1->setTable(tableName);
    model1->setFilter("status = 'available'");
    model1->setSort(sortField, Qt::AscendingOrder);
    for(int i = 0, j = 0; i < model1->columnCount(); i++, j++){
        model1->setHeaderData(i, Qt::Horizontal, headers[j]);
    }

}
void CarsWindow::setupModel2(const QString &tableName, const QStringList &headers, int sortField)
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    db->connectToDataBase();
    model2 = new QSqlTableModel(this, db->getDB());
    model2->setTable(tableName);
    model2->setFilter("status = 'notAvailable'");
    model2->setSort(sortField, Qt::AscendingOrder);
    for(int i = 0, j = 0; i < model2->columnCount(); i++, j++){
        model2->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}

void CarsWindow::createUI1()
{
    proxyModel1 = new QSortFilterProxyModel(this);
    proxyModel1->setSourceModel(model1);

    ui->tableViewCarsAvailable->setModel(proxyModel1);
    ui->tableViewCarsAvailable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewCarsAvailable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewCarsAvailable->resizeColumnsToContents();
    ui->tableViewCarsAvailable->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableViewCarsAvailable->horizontalHeader()->setStretchLastSection(true);

    model1->select();
}
void CarsWindow::createUI2()
{
    proxyModel2 = new QSortFilterProxyModel(this);
    proxyModel2->setSourceModel(model2);

    ui->tableViewCarsNotAvailable->setModel(proxyModel2);
    ui->tableViewCarsNotAvailable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewCarsNotAvailable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewCarsNotAvailable->resizeColumnsToContents();
    ui->tableViewCarsNotAvailable->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableViewCarsNotAvailable->horizontalHeader()->setStretchLastSection(true);

    model2->select();
}

void CarsWindow::setList1(int sortField){
    this->setupModel1(TABLE_CARS,
                      QStringList() << tr("Car_id")
                                    << tr("Brand")
                                    << tr("Model")
                                    << tr("Year")
                                    << tr("VIN")
                                    << tr("Engine capacity")
                                    << tr("Number of seats")
                                    << tr("Trunk volume")
                                    << tr("Price")
                                    << tr("Price of renting")
                                    << tr("Status"),sortField
                      );

    this->createUI1();
}

void CarsWindow::setList2(int sortField){
    this->setupModel2(TABLE_CARS,
                      QStringList() << tr("Car_id")
                                    << tr("Brand")
                                    << tr("Model")
                                    << tr("Year")
                                    << tr("VIN")
                                    << tr("Engine capacity")
                                    << tr("Number of seats")
                                    << tr("Trunk volume")
                                    << tr("Price")
                                    << tr("Price of renting")
                                    << tr("Status"),sortField
                      );

    this->createUI2();
}

void CarsWindow::on_tabWidget_currentChanged(int index){
    int a = 0;
    if(ui->tabWidgetCars->currentIndex()){
        a=1;
    }else{
        a = 0;
    }
    if(!a){
        this->setList1(0);
        ui->searchLE->clear();
        ui->searchLE2->clear();
        ui->comboBoxCarsAvailable->setCurrentIndex(-1);
        ui->comboBoxCarsNotAvailable->setCurrentIndex(-1);
    }else{
        this->setList2(0);
        ui->searchLE->clear();
        ui->searchLE2->clear();
        ui->comboBoxCarsAvailable->setCurrentIndex(-1);
        ui->comboBoxCarsNotAvailable->setCurrentIndex(-1);
    }
}

void CarsWindow::onCBChanged(int index)
{

    const QString selectedRole = ui->comboBoxCarsAvailable->itemText(index);
    if (selectedRole == tr("car_id")){
        setList1(0);
    }
    if (selectedRole == tr("brand")){
        setList1(1);
    }
    if (selectedRole == tr("model")){
        setList1(2);
    }
    if (selectedRole == tr("year")){
        setList1(3);
    }
    if (selectedRole == tr("vin")){
        setList1(4);
    }
    if (selectedRole == tr("engineCapacity")){
        setList1(5);
    }
    if (selectedRole == tr("numberOfSeats")){
        setList1(6);
    }
    if (selectedRole == tr("trunkVolume")){
        setList1(7);
    }
    if (selectedRole == tr("price")){
        setList1(8);
    }
    if (selectedRole == tr("priceOfRenting")){
        setList1(9);
    }
}

void CarsWindow::onCBChangedd(int index)
{
    const QString selectedRole = ui->comboBoxCarsNotAvailable->itemText(index);
    if (selectedRole == tr("car_id")){
        setList2(0);
    }
    if (selectedRole == tr("brand")){
        setList2(1);
    }
    if (selectedRole == tr("model")){
        setList2(2);
    }
    if (selectedRole == tr("year")){
        setList2(3);
    }
    if (selectedRole == tr("vin")){
        setList2(4);
    }
    if (selectedRole == tr("engineCapacity")){
        setList2(5);
    }
    if (selectedRole == tr("numberOfSeats")){
        setList2(6);
    }
    if (selectedRole == tr("trunkVolume")){
        setList2(7);
    }
    if (selectedRole == tr("price")){
        setList2(8);
    }
    if (selectedRole == tr("priceOfRenting")){
        setList2(9);
    }
}
