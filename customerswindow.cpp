#include "customerswindow.h"
#include "ui_customerswindow.h"
CustomersWindow::CustomersWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomersWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Customers");
    this->setWindowIcon(QIcon(":/new/icons/Resources/car.png"));
    ui->comboBoxCustomersActive->setCurrentIndex(-1);
    ui->comboBoxCustomersClosed->setCurrentIndex(-1);
    connect(ui->tabWidgetCustomers,&QTabWidget::currentChanged,this,&CustomersWindow::on_tabWidget_currentChanged);
    connect(ui->searchLE2, &QLineEdit::textChanged, this, &CustomersWindow::onSearchTextChanged);
    connect(ui->searchLE, &QLineEdit::textChanged, this, &CustomersWindow::onSearchTextChanged);
    connect(ui->comboBoxCustomersActive, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CustomersWindow::onCBChanged);
    connect(ui->comboBoxCustomersClosed, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CustomersWindow::onCBChangedd);
}

CustomersWindow::~CustomersWindow()
{
    delete ui;
}

void CustomersWindow::closeEvent(QCloseEvent *event)
{
    QDialog::closeEvent(event);
    emit closed();
}

void CustomersWindow::onSearchTextChanged(const QString &text)
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

void CustomersWindow::setupModel1(const QString &tableName, const QStringList &headers, int sortField)
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    db->connectToDataBase();
    model1 = new QSqlTableModel(this, db->getDB());
    model1->setTable(tableName);
    model1->setFilter("status = 'Closed'");
    model1->setSort(sortField, Qt::AscendingOrder);
    for(int i = 0, j = 0; i < model1->columnCount(); i++, j++){
        model1->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}
void CustomersWindow::setupModel2(const QString &tableName, const QStringList &headers, int sortField)
{
    SqliteDBManager* db= SqliteDBManager::getInstance();
    db->connectToDataBase();
    model2 = new QSqlTableModel(this, db->getDB());
    model2->setTable(tableName);
    model2->setFilter("status = 'Active'");
    model2->setSort(sortField, Qt::AscendingOrder);
    for(int i = 0, j = 0; i < model2->columnCount(); i++, j++){
        model2->setHeaderData(i, Qt::Horizontal, headers[j]);
    }
}

void CustomersWindow::createUI1()
{
    proxyModel1 = new QSortFilterProxyModel(this);
    proxyModel1->setSourceModel(model1);

    ui->tableViewCustomersClosed->setModel(proxyModel1);
    ui->tableViewCustomersClosed->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewCustomersClosed->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewCustomersClosed->resizeColumnsToContents();
    ui->tableViewCustomersClosed->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableViewCustomersClosed->horizontalHeader()->setStretchLastSection(true);

    model1->select();
}
void CustomersWindow::createUI2()
{
    proxyModel2 = new QSortFilterProxyModel(this);
    proxyModel2->setSourceModel(model2);

    ui->tableViewCustomersActive->setModel(proxyModel2);
    ui->tableViewCustomersActive->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewCustomersActive->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableViewCustomersActive->resizeColumnsToContents();
    ui->tableViewCustomersActive->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableViewCustomersActive->horizontalHeader()->setStretchLastSection(true);

    model2->select();
}

void CustomersWindow::setList1(int sortField){
    this->setupModel1(TABLE_CUSTOMERS,
                     QStringList() << tr("Customer_id")
                                   << tr("Surname")
                                   << tr("First Name")
                                   << tr("Middle Name")
                                   << tr("Age")
                                   << tr("Phone Number")
                                   << tr("Email")
                                    << tr("Years of experience")
                                   << tr("Individual Taxpayer Identification Number")
                                   << tr("Address")
                                   << tr("Status"),sortField
                     );

    this->createUI1();
}

void CustomersWindow::setList2(int sortField){
    this->setupModel2(TABLE_CUSTOMERS,
                     QStringList() << tr("Customer_id")
                                   << tr("Surname")
                                   << tr("First Name")
                                   << tr("Middle Name")
                                   << tr("Age")
                                   << tr("Phone Number")
                                   << tr("Email")
                                    << tr("Years of experience")
                                   << tr("Individual Taxpayer Identification Number")
                                   << tr("Address")
                                   << tr("Status"),sortField
                     );

    this->createUI2();
}

void CustomersWindow::on_addCustomerButton_clicked()
{
    AddCustomerWindow *addCustomerWindow = new AddCustomerWindow(this);
    connect(addCustomerWindow, &AddCustomerWindow::closed, this, &CustomersWindow::onDialogClosed);
    addCustomerWindow->setModal(true);
    addCustomerWindow->show();
    hide();
}

void CustomersWindow::onDialogClosed()
{
    this->on_tabWidget_currentChanged(1);
    this->on_tabWidget_currentChanged(0);
    show();
}

void CustomersWindow::on_tabWidget_currentChanged(int index){
    int a = 0;
    if(ui->tabWidgetCustomers->currentIndex()){
        a=1;
    }else{
        a = 0;
    }
    if(a){
        this->setList1(0);
    }else{
        this->setList2(0);
    }
}

void CustomersWindow::onCBChanged(int index)
{

    const QString selectedRole = ui->comboBoxCustomersActive->itemText(index);
    if (selectedRole == tr("customer_id")){
        setList2(0);
    }
    if (selectedRole == tr("surname")){
        setList2(1);
    }
    if (selectedRole == tr("firstName")){
        setList2(2);
    }
    if (selectedRole == tr("middleName")){
        setList2(3);
    }
    if (selectedRole == tr("age")){
        setList2(4);
    }
    if (selectedRole == tr("phoneNumber")){
        setList2(5);
    }
    if (selectedRole == tr("email")){
        setList2(6);
    }
    if (selectedRole == tr("yearsOfExperience")){
        setList2(7);
    }
    if (selectedRole == tr("itin")){
        setList2(8);
    }
    if (selectedRole == tr("address")){
        setList2(9);
    }
}

void CustomersWindow::onCBChangedd(int index)
{
    const QString selectedRole = ui->comboBoxCustomersClosed->itemText(index);
    if (selectedRole == tr("customer_id")){
        setList1(0);
    }
    if (selectedRole == tr("surname")){
        setList1(1);
    }
    if (selectedRole == tr("firstName")){
        setList1(2);
    }
    if (selectedRole == tr("middleName")){
        setList1(3);
    }
    if (selectedRole == tr("age")){
        setList1(4);
    }
    if (selectedRole == tr("phoneNumber")){
        setList1(5);
    }
    if (selectedRole == tr("email")){
        setList1(6);
    }
    if (selectedRole == tr("yearsOfExperience")){
        setList1(7);
    }
    if (selectedRole == tr("itin")){
        setList1(8);
    }
    if (selectedRole == tr("address")){
        setList1(9);
    }
}
