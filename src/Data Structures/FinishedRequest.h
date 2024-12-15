#ifndef FINISHED_REQUEST_H
#define FINISHED_REQUEST_H

struct FinishedRequest
{
    int PID;
    int Severity;
    int nearestHospitalID;
    int nearestHospitalDistance;
    int type = 0;

    double QT;
    double AT;
    double PT;
    double WT;
    double FT;
    double carBusyTime;
};

#endif // FINISHED_REQUEST_H