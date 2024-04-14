#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool check(const AvailabilityMatrix& avail, DailySchedule& sched, vector<int>& shifts, size_t curr, size_t dailyNeed, size_t maxShifts);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    if(avail[0].empty()){
        return false;
    }

    vector<int> shifts(avail[0].size(), 0);
    sched.resize(avail.size(), vector<Worker_T>());
    return check(avail, sched, shifts, 0, dailyNeed, maxShifts);
}

bool check(const AvailabilityMatrix& avail, DailySchedule& sched, vector<int>& shifts, size_t curr, size_t dailyNeed, size_t maxShifts){
    if(curr == avail.size()) return true;

    if(sched[curr].size() == dailyNeed){
        return check(avail, sched, shifts, curr + 1, dailyNeed, maxShifts);
    }

    for(int i=0; i<avail[curr].size(); i++){
        if(avail[curr][i] and shifts[i] < maxShifts and find(sched[curr].begin(), sched[curr].end(), i) == sched[curr].end()){
            sched[curr].push_back(i);
            shifts[i] ++;
            if(check(avail, sched, shifts, curr, dailyNeed, maxShifts)){
                return true;
            }
            shifts[i] --;
            sched[curr].pop_back();
        }
    }
    return false;
}


