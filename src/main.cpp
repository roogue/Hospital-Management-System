#include <iostream>
#include "handlers/errorHandler.h"
#include "handlers/inputHandler.h"
#include "cores/client.h"
#include "managers/patientManager.h"
#include "managers/transactionManager.h"
#include "managers/reportManager.h"
#include "utils/printer.h"
#include "cores/patient.h"

void generatePatients(Manager::PatientManager *pm)
{
    HMS::Patient p1(pm->generatePatientId());
    p1.setName("Aisha");
    p1.setStatus(HMS::PatientStatus::Admitted);
    Handler::Date d1 = {5, 1, 2024};
    p1.addAdmissionDate(d1);
    HMS::Treatment t1;
    t1.setTreatmentType(HMS::TreatmentType::Diarrhoea);
    t1.setOtherTreatmentType("");
    d1 = {6, 1, 2024};
    t1.setAppointment(d1);
    t1.setDayOfStay(2);
    t1.setPriority(2);
    p1.addTreatment(t1);
    d1 = {8, 1, 2024};
    p1.addDischargeDate(d1);
    d1 = {21, 1, 2024};
    p1.addAdmissionDate(d1);
    t1.setTreatmentType(HMS::TreatmentType::Symptomatic);
    t1.setOtherTreatmentType("");
    d1 = {22, 1, 2024};
    t1.setAppointment(d1);
    t1.setDayOfStay(1);
    t1.setPriority(1);
    p1.addTreatment(t1);
    pm->addPatient(p1);

    HMS::Patient p2(pm->generatePatientId());
    p2.setName("Ibrahim");
    p2.setStatus(HMS::PatientStatus::Admitted);
    Handler::Date d2 = {12, 1, 2024};
    p2.addAdmissionDate(d2);
    HMS::Treatment t2;
    t2.setTreatmentType(HMS::TreatmentType::Symptomatic);
    t2.setOtherTreatmentType("");
    d2 = {13, 1, 2024};
    t2.setAppointment(d2);
    t2.setDayOfStay(1);
    t2.setPriority(1);
    p2.addTreatment(t2);
    pm->addPatient(p2);

    HMS::Patient p3(pm->generatePatientId());
    p3.setName("Fatimah");
    p3.setStatus(HMS::PatientStatus::Discharged);
    Handler::Date d3 = {20, 1, 2024};
    p3.addAdmissionDate(d3);
    HMS::Treatment t3;
    t3.setTreatmentType(HMS::TreatmentType::Hemostasis);
    t3.setOtherTreatmentType("");
    d3 = {21, 1, 2024};
    t3.setAppointment(d3);
    t3.setDayOfStay(3);
    t3.setPriority(3);
    p3.addTreatment(t3);
    d3 = {24, 1, 2024};
    p3.addDischargeDate(d3);
    pm->addPatient(p3);

    HMS::Patient p4(pm->generatePatientId());
    p4.setName("Ali");
    p4.setStatus(HMS::PatientStatus::Admitted);
    Handler::Date d4 = {2, 2, 2024};
    p4.addAdmissionDate(d4);
    HMS::Treatment t4;
    t4.setTreatmentType(HMS::TreatmentType::Constipation);
    t4.setOtherTreatmentType("");
    d4 = {3, 2, 2024};
    t4.setAppointment(d4);
    t4.setDayOfStay(1);
    t4.setPriority(2);
    p4.addTreatment(t4);
    d4 = {4, 2, 2024};
    p4.addDischargeDate(d4);
    pm->addPatient(p4);

    HMS::Patient p5(pm->generatePatientId());
    p5.setName("Sara");
    p5.setStatus(HMS::PatientStatus::Discharged);
    Handler::Date d5 = {10, 2, 2024};
    p5.addAdmissionDate(d5);
    HMS::Treatment t5;
    t5.setTreatmentType(HMS::TreatmentType::Other);
    t5.setOtherTreatmentType("Checkup");
    d5 = {11, 2, 2024};
    t5.setAppointment(d5);
    t5.setDayOfStay(1);
    t5.setPriority(1);
    p5.addTreatment(t5);
    d5 = {12, 2, 2024};
    p5.addDischargeDate(d5);
    pm->addPatient(p5);

    HMS::Patient p6(pm->generatePatientId());
    p6.setName("Zainab");
    p6.setStatus(HMS::PatientStatus::Admitted);
    Handler::Date d6 = {18, 2, 2024};
    p6.addAdmissionDate(d6);
    HMS::Treatment t6;
    t6.setTreatmentType(HMS::TreatmentType::Diarrhoea);
    t6.setOtherTreatmentType("");
    d6 = {19, 2, 2024};
    t6.setAppointment(d6);
    t6.setDayOfStay(2);
    t6.setPriority(3);
    p6.addTreatment(t6);
    pm->addPatient(p6);

    HMS::Patient p7(pm->generatePatientId());
    p7.setName("Hassan");
    p7.setStatus(HMS::PatientStatus::Admitted);
    Handler::Date d7 = {1, 3, 2024};
    p7.addAdmissionDate(d7);
    HMS::Treatment t7;
    t7.setTreatmentType(HMS::TreatmentType::Symptomatic);
    t7.setOtherTreatmentType("");
    d7 = {2, 3, 2024};
    t7.setAppointment(d7);
    t7.setDayOfStay(1);
    t7.setPriority(1);
    p7.addTreatment(t7);
    pm->addPatient(p7);

    HMS::Patient p8(pm->generatePatientId());
    p8.setName("Fatima");
    p8.setStatus(HMS::PatientStatus::Discharged);
    Handler::Date d8 = {15, 3, 2024};
    p8.addAdmissionDate(d8);
    HMS::Treatment t8;
    t8.setTreatmentType(HMS::TreatmentType::Constipation);
    t8.setOtherTreatmentType("");
    d8 = {16, 3, 2024};
    t8.setAppointment(d8);
    t8.setDayOfStay(1);
    t8.setPriority(2);
    p8.addTreatment(t8);
    d8 = {17, 3, 2024};
    p8.addDischargeDate(d8);
    pm->addPatient(p8);

    HMS::Patient p9(pm->generatePatientId());
    p9.setName("Yusuf");
    p9.setStatus(HMS::PatientStatus::Admitted);
    Handler::Date d9 = {22, 3, 2024};
    p9.addAdmissionDate(d9);
    HMS::Treatment t9;
    t9.setTreatmentType(HMS::TreatmentType::Hemostasis);
    t9.setOtherTreatmentType("");
    d9 = {23, 3, 2024};
    t9.setAppointment(d9);
    t9.setDayOfStay(2);
    t9.setPriority(3);
    p9.addTreatment(t9);
    pm->addPatient(p9);

    HMS::Patient p10(pm->generatePatientId());
    p10.setName("Maryam");
    p10.setStatus(HMS::PatientStatus::Admitted);
    Handler::Date d10 = {30, 3, 2024};
    p10.addAdmissionDate(d10);
    HMS::Treatment t10;
    t10.setTreatmentType(HMS::TreatmentType::Other);
    t10.setOtherTreatmentType("Routine checkup");
    d10 = {31, 3, 2024};
    t10.setAppointment(d10);
    t10.setDayOfStay(1);
    t10.setPriority(1);
    p10.addTreatment(t10);
    pm->addPatient(p10);
};

int main()
{
    HMS::Client client;
    generatePatients(client.patientManager);

    using Handler::InputError;
    using std::cout, std::endl;

    while (true)
    {
        client.printer->printHeader();

        cout << "1) Manage Patients" << endl
             << "2) Manage Transaction" << endl
             << "3) Generate Reports" << endl
             << "4) Exit" << endl;
        cout << "Selection: ";
        int selection;
        ErrorCode err = client.inputHandler.getInt(selection, 1, 4);
        if (err)
        {
            client.errorHandler.addError(err);
            continue;
        }

        switch (selection)
        {
        case HMS::OptionsMainMenu::ManagePatients:
        {
            client.patientManager->managePatients();
            break;
        }
        case HMS::OptionsMainMenu::ManageTransactions:
        {
            client.transactionManager->manageTransaction();
            break;
        }
        case HMS::OptionsMainMenu::GenerateReport:
        {
            client.reportManager->manageReport();
            break;
        }
        case HMS::OptionsMainMenu::ExitProgram:
        {
            exit(0);
            break;
        }
        }
    }

    return 0;
}