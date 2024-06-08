#include <iostream>
#include <queue>
#include <thread>
#include <chrono>

using namespace std;

class PrintJob {
public:
    PrintJob(int id, string data) : job_id(id), data(data) {}
    int job_id;
    string data;
};

class PrinterDaemon {
public:
    PrinterDaemon() : printer_busy(false) {}

    void addPrintJob(PrintJob job) {
        print_queue.push(job);
    }

    void printJob() {
        while (true) {
            if (!print_queue.empty() && !printer_busy) {
                PrintJob job = print_queue.front();
                print_queue.pop();
                printer_busy = true;
                cout << "Printing job " << job.job_id << ": " << job.data << endl;
                // Simulate printing
                this_thread::sleep_for(chrono::seconds(2));
                printer_busy = false;
            }
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

private:
    queue<PrintJob> print_queue;
    bool printer_busy;
};

int main() {
    PrinterDaemon printer_daemon;
    thread printer_thread(&PrinterDaemon::printJob, &printer_daemon);

    // Add some print jobs
    for (int i = 1; i <= 5; ++i) {
        PrintJob job(i, "Print data for job " + to_string(i));
        printer_daemon.addPrintJob(job);
    }

    // Wait for the print jobs to finish
    this_thread::sleep_for(chrono::seconds(10));

    return 0;
}
